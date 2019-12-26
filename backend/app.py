from flask import Flask, request
from jsonschema import validate, ValidationError

from .uart import UART
from . import schemas


app = Flask(__name__)
uart = UART()


@app.route("/task1", methods=["POST"])
def task1():
    args = request.get_json()
    try:
        validate(args, schemas.task_schema)
    except ValidationError as e:
        return f"Invalid JSON sent: {e}", 400
    rc = uart.manage_task(1, args)
    if rc == 0:
        return "OK"
    else:
        return f"Problem with UARt command. Return code: {rc}", 500


@app.route("/timer")
def timer():
    return "Timer"
