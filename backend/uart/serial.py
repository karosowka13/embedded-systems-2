import logging

from serial_asyncio import create_serial_connection


logger = logging.getLogger(__name__)


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
        logger.info(f"Established connection on port {self.port}")

    async def close(self):
        logger.debug(f"Closing connection on port {self.port}")
        self._writer.close()
        await self._writer.wait_closed()
        self._reader = None
        self._writer = None
        logger.info(f"Closed connection on port {self.port}")

    def write(self, msg):
        if self._writer is not None:
            logger.debug(f"Writing message {msg!r}")
            self._writer.write(msg.encode("ascii"))

    def read(self, msg):
        if self._reader is not None:
            self.write(msg)
            ret = self._reader.readline().decode("ascii")
            logger.info(f"Received message {ret!r}")
            return ret
        return ""
