import logging

import asyncio
from aiohttp import web
import aiohttp_cors

from .uart import UART
from . import config
from . import routes


logger = logging.getLogger(__name__)

if config.APP_DEBUG:
    logger.debug("Running in debug mode")


async def uart_conn(app):
    app["uart"] = UART(
        config.SERIAL_PORT,
        speed=config.SERIAL_SPEED,
        debug=config.APP_DEBUG,
        queue=app["queue"]
    )
    await app["uart"].open()
    yield
    await app["uart"].close()


# it may be better to create polling task only when there's one client and cancel it when there's no client at all
# however current implementation is simpler
async def poll_uart(app):
    async def read_uart(app):
        while True:
            try:
                ret = await app["uart"].read()
                ret = int(ret)
                if ret < 20:
                    await app["uart"].q.put(ret)
                if app["websocket"] is not None:
                    await app["websocket"].send_str(str(ret))
            except Exception as e:
                logger.error(f"Exception when reading uart: {e}")
    task = asyncio.create_task(read_uart(app))
    yield
    task.cancel()
    await task

app = web.Application(debug=config.APP_DEBUG)
app["port"] = config.APP_PORT
app["host"] = config.APP_HOST
app["websocket"] = None
app["queue"] = asyncio.Queue()

app.cleanup_ctx.append(uart_conn)
app.cleanup_ctx.append(poll_uart)

cors = aiohttp_cors.setup(app, defaults={
    "*": aiohttp_cors.ResourceOptions(
        allow_headers="*",
        allow_methods="*",
        allow_credentials=False,
        max_age=3600,
    )
})

ws_resource = cors.add(app.router.add_resource("/ws"))
cors.add(ws_resource.add_route("GET", routes.websocket))

task_resource = cors.add(app.router.add_resource("/task"))
cors.add(task_resource.add_route("POST", routes.task))

timer_resource = cors.add(app.router.add_resource("/timer"))
cors.add(timer_resource.add_route("POST", routes.timer))

queue_resource = cors.add(app.router.add_resource("/queue"))
cors.add(queue_resource.add_route("POST", routes.queue))

semaphore_resource = cors.add(app.router.add_resource("/semaphore"))
cors.add(semaphore_resource.add_route("POST", routes.semaphore))
