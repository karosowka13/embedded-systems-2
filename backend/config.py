import os
import json


def load_from_env(name):
    raw_var = os.environ[f"BACKEND_{name}"]
    try:
        return json.loads(raw_var)
    except json.JSONDecodeError:  # problem with decoding - return plain string
        return raw_var


APP_PORT = load_from_env("APP_PORT")
APP_HOST = load_from_env("APP_HOST")
APP_DEBUG = load_from_env("APP_DEBUG")
SERIAL_PORT = load_from_env("SERIAL_PORT")
SERIAL_SPEED = load_from_env("SERIAL_SPEED")
