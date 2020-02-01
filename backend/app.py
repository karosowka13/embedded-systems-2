from aiohttp import web

from .uart import UART
from . import config
from .routes import routes


app = web.Application(debug=config.APP_DEBUG)
app["port"] = config.APP_PORT
app["host"] = config.APP_HOST
app["uart"] = UART(
    config.SERIAL_PORT,
    speed=config.SERIAL_SPEED,
    debug=config.APP_DEBUG,
)

app.add_routes(routes)
