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


app = web.Application(debug=config.APP_DEBUG)
app["port"] = config.APP_PORT
app["host"] = config.APP_HOST

app.cleanup_ctx.append(uart_conn)

app.add_routes(routes)
