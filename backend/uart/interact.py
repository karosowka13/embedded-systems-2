import asyncio
import sys

from .simple_serial import Serial


async def main(port, speed):
    s = Serial(port, speed=speed)
    print(f"Connecting to {port}...")
    await s.open()
    print("Connected")
    print("Press Ctrl+C to exit")
    try:
        while True:
            msg = input(">>>")
            ret = s.write(msg.ljust(12))
            if ret is not None:
                print(f"Return message: {ret!r}")
    except KeyboardInterrupt:
        await s.close()


if __name__ == '__main__':
    port = sys.argv[1]
    speed = int(sys.argv[2])
    asyncio.get_event_loop().run_until_complete(main(port, speed))
