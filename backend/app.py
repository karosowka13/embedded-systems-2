import asyncio
from aiohttp import web

from .uart import UART
from . import config
from .routes import routes


async def uart_conn(app):
    app["uart"] = UART(
        config.SERIAL_PORT,
        speed=config.SERIAL_SPEED,
        debug=config.APP_DEBUG,
    )
    await app["uart"].open()
    yield
    await app["uart"].close()


# it may be better to create polling task only when there's one client and cancel it when there's no client at all
# however current implementation is simpler
async def poll_uart(app):
    async def read_uart(uart, websockets):
        while True:
            await asyncio.sleep(1)
            ret = await uart.read_line()
            for ws in websockets:
                ws.send_str(ret)
    app["uart_poller"] = asyncio.create_task(read_uart(app["uart"], app["websockets"]))
    yield
    app["uart_poller"].cancel()
    await app["uart_poller"]

app = web.Application(debug=config.APP_DEBUG)
app["port"] = config.APP_PORT
app["host"] = config.APP_HOST

app.cleanup_ctx.append(uart_conn)
app.cleanup_ctx.append(poll_uart)

app.add_routes(routes)
