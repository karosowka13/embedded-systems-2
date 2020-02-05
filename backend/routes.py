import logging

from aiohttp import web, WSMsgType
from jsonschema import validate, ValidationError

from . import schemas


logger = logging.getLogger(__name__)
routes = web.RouteTableDef()


@routes.post(r"/task/{task_id:\d}")
async def task1(request):
    task_id = int(request.match_info["task_id"])
    if task_id not in request.app["uart"].TASKS:
        return web.Response(text=f"Bas Task ID. Received: {task_id}. Allowed: {request.app['uart'].TASKS}", status=400)
    args = await request.json()
    try:
        validate(args, schemas.task_schema)
    except ValidationError as e:
        return web.Response(text=f"Invalid JSON sent: {e}", status=400)
    rc = request.app["uart"].manage_task(task_id, args)
    if rc == 0:
        return web.Response(text="OK")
    else:
        return web.Response(text=f"Problem with UARt command. Return code: {rc}", status=500)


@routes.post("/timer")
async def timer(request):
    args = await request.json()
    try:
        validate(args, schemas.timer_schema)
    except ValidationError as e:
        return web.Response(text=f"Invalid JSON sent: {e}", status=400)
    rc = request.app["uart"].manage_timer(args)
    if rc == 0:
        return web.Response(text="OK")
    else:
        return web.Response(text=f"Problem with UARt command. Return code: {rc}", status=500)


@routes.post("/queue")
async def queue(request):
    args = await request.json()
    try:
        validate(args, schemas.queue_schema)
    except ValidationError as e:
        return web.Response(text=f"Invalid JSON sent: {e}", status=400)
    rc = request.app["uart"].queue_put(args)
    if rc == 0:
        return web.Response(text="OK")
    else:
        return web.Response(text=f"Problem with UARt command. Return code: {rc}", status=500)


@routes.post("/semaphore")
async def semaphore(request):
    args = await request.json()
    try:
        validate(args, schemas.semaphore_schema)
    except ValidationError as e:
        return web.Response(text=f"Invalid JSON sent: {e}", status=400)
    rc = request.app["uart"].give_semaphore(args)
    if rc == 0:
        return web.Response(text="OK")
    else:
        return web.Response(text=f"Problem with UARt command. Return code: {rc}", status=500)


@routes.get("/ws")
async def websocket(request):
    ws = web.WebSocketResponse()
    await ws.prepare(request)
    request.app["websockets"].append(ws)

    async for msg in ws:
        try:
            if msg.type == WSMsgType.TEXT:
                logger.debug(f"Message received: {msg!r}")
                if msg.data == "close":
                    logger.info("Closing web socket on user request")
                    await ws.close()
                    request.app["websockets"].remove(ws)
                    logger.debug("Web socket closed")
            elif msg.type == WSMsgType.ERROR:
                logger.error(f"Web socket connection closed with exception: {ws.exception()}")
        except Exception as e:
            logger.error(f"Exception in websocket handler: {e}")
    return ws
