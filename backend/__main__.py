from aiohttp import web
from .app import app


web.run_app(app, port=app["port"], host=app["host"])
