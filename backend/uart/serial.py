from serial_asyncio import create_serial_connection


class Serial:

    def __init__(self, port, speed=9600, debug=False):
        self.port = port
        self.speed = speed
        self.debug = debug
        self._reader = None
        self._writer = None

    # async def __del__(self):
    #     await self.close()

    async def open(self):
        self._reader, self._writer = await create_serial_connection(port=self.port, baudrate=self.speed)

    async def close(self):
        self._writer.close()
        await self._writer.wait_closed()
        self._reader = None
        self._writer = None

    def write(self, msg):
        if self._writer is not None:
            self._writer.write(msg.encode("ascii"))

    def read(self, msg):
        if self._reader is not None:
            self.write(msg)
            return self._reader.readline().decode("ascii")
        return ""
