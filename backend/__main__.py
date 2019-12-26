from .app import app

app.run(port=app.config["APP_PORT"], host=app.config["APP_HOST"], debug=app.config["APP_DEBUG"])
