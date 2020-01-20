from aiohttp import web
from .async_app import app


web.run_app(app, port=app["port"], host=app["host"])
