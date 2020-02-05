# MONKEY PATCH START
import asyncio

import serial
import serial_asyncio
from serial_asyncio import SerialTransport


@asyncio.coroutine
def fixed_create_serial_connection(loop, protocol_factory, *args, **kwargs):
    url = kwargs.pop("port")
    ser = serial.serial_for_url(url, *args, **kwargs)
    protocol = protocol_factory()
    transport = SerialTransport(loop, protocol, ser)
    return (transport, protocol)


serial_asyncio.create_serial_connection = fixed_create_serial_connection

# MONKEYPATCH END

from .uart import UART
