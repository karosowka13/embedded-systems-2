import logging

from aiohttp import web, WSMsgType
from jsonschema import validate, ValidationError

from . import schemas


logger = logging.getLogger(__name__)


async def task(request):
    args = await request.json()
    try:
        validate(args, schemas.task_schema)
    except ValidationError as e:
        return web.Response(text=f"Invalid JSON sent: {e}", status=400)
    await request.app["uart"].manage_task(args)
    return web.Response(text="OK")


async def timer(request):
    args = await request.json()
    try:
        validate(args, schemas.timer_schema)
    except ValidationError as e:
        return web.Response(text=f"Invalid JSON sent: {e}", status=400)
    await request.app["uart"].manage_timer(args)
    return web.Response(text="OK")


async def queue(request):
    args = await request.json()
    try:
        validate(args, schemas.queue_schema)
    except ValidationError as e:
        return web.Response(text=f"Invalid JSON sent: {e}", status=400)
    await request.app["uart"].queue_put(args)
    return web.Response(text="OK")


async def semaphore(request):
    args = await request.json()
    try:
        validate(args, schemas.semaphore_schema)
    except ValidationError as e:
        return web.Response(text=f"Invalid JSON sent: {e}", status=400)
    await request.app["uart"].give_semaphore(args)
    return web.Response(text="OK")


async def websocket(request):
    ws = web.WebSocketResponse()
    await ws.prepare(request)
    request.app["websocket"] = ws

    async for msg in ws:
        logger.debug("New message in websocket")
        try:
            if msg.type == WSMsgType.TEXT:
                logger.debug(f"Message received: {msg!r}")
                if msg.data == "close":
                    logger.info("Closing web socket on user request")
                    await ws.close()
                    logger.debug("Web socket closed")
            elif msg.type == WSMsgType.ERROR:
                logger.error(f"Web socket connection closed with exception: {ws.exception()}")
        except Exception as e:
            logger.error(f"Exception in websocket handler: {e}")
    return ws
