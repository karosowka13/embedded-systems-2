async def loop_forever(coro):
    while True:
        ret = await coro()
