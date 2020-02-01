from aiohttp import web
from jsonschema import validate, ValidationError

from . import schemas


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
