from aiohttp import web


routes = web.RouteTableDef()

from jsonschema import validate, ValidationError

from .uart import UART
from . import schemas


# app = Flask(__name__)
# app.config.from_object("backend.config")
uart = UART(
    app.config["SERIAL_PORT"],
    speed=app.config["SERIAL_SPEED"],
    timeout=app.config["SERIAL_TIMEOUT"],
    debug=app.config["APP_DEBUG"],
)


@routes.post(r'/{name:\d}')
def task1(task_id):
    if task_id not in uart.TASKS:
        return f"Bas Task ID. Received: {task_id}. Allowed: {uart.TASKS}", 400
    args = request.get_json()
    try:
        validate(args, schemas.task_schema)
    except ValidationError as e:
        return f"Invalid JSON sent: {e}", 400
    rc = uart.manage_task(task_id, args)
    if rc == 0:
        return "OK"
    else:
        return f"Problem with UARt command. Return code: {rc}", 500


@routes.post("/timer")
def timer():
    args = request.get_json()
    try:
        validate(args, schemas.timer_schema)
    except ValidationError as e:
        return f"Invalid JSON sent: {e}", 400
    rc = uart.manage_timer(args)
    if rc == 0:
        return "OK"
    else:
        return f"Problem with UARt command. Return code: {rc}", 500


@routes.post("/queue")
def queue():
    args = request.get_json()
    try:
        validate(args, schemas.queue_schema)
    except ValidationError as e:
        return f"Invalid JSON sent: {e}", 400
    rc = uart.queue_put(args)
    if rc == 0:
        return "OK"
    else:
        return f"Problem with UARt command. Return code: {rc}", 500


@routes.post("/semaphore")
def semaphore():
    args = request.get_json()
    try:
        validate(args, schemas.semaphore_schema)
    except ValidationError as e:
        return f"Invalid JSON sent: {e}", 400
    rc = uart.get_semaphore(args)
    if rc == 0:
        return "OK"
    else:
        return f"Problem with UARt command. Return code: {rc}", 500






app = web.Application()
app.add_routes(routes)
web.run_app(app)
