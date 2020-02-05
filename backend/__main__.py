import logging
from aiohttp import web
from .app import app


logging.basicConfig(level=logging.DEBUG)
web.run_app(app, port=app["port"], host=app["host"])
