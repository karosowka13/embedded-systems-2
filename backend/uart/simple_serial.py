import logging

from serial_asyncio import open_serial_connection


logger = logging.getLogger(__name__)


class Serial:

    def __init__(self, port, speed=9600, debug=False):
        self.port = port
        self.speed = speed
        self.debug = debug
        self._reader = None
        self._writer = None

    async def open(self):
        if not self.debug:
            self._reader, self._writer = await open_serial_connection(port=self.port, baudrate=self.speed)
            logger.info(f"Established connection on port {self.port}")

    async def close(self):
        if not self.debug:
            logger.debug(f"Closing connection on port {self.port}")
            self._writer.close()
            await self._writer.wait_closed()
        self._reader = None
        self._writer = None
        logger.info(f"Closed connection on port {self.port}")

    def write(self, msg):
        if self._writer is not None:
            logger.debug(f"Writing message {msg!r}")
            msg = msg.ljust(12)
            self._writer.write(msg.encode("ascii"))

    async def write_read(self, msg):
        if self._reader is not None:
            self.write(msg)
            ret = await self.read()
            return ret
        return "0"

    async def read(self):
        if self._reader is not None:
            ret = await self._reader.readline()
            ret.decode("ascii")
            logger.debug(f"Received message {ret!r}")
            return ret
        return "\n"
