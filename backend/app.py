from flask import Flask, request
from jsonschema import validate, ValidationError

from .uart import UART
from . import schemas


app = Flask(__name__)
uart = UART()


@app.route("/task/<int:task_id>", methods=["POST"])
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


@app.route("/timer", methods=["POST"])
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
