import asyncio
import sys

from .serial import Serial


async def main(port):
    s = Serial(port)
    print(f"Connecting to {port}...")
    await s.open()
    print("Connected")
    print("Press Ctrl+C to exit")
    try:
        while True:
            msg = input(">>>")
            ret = s.write(msg)
            print(repr(ret))
    except KeyboardInterrupt:
        await s.close()


if __name__ == '__main__':
    port = sys.argv[1]
    asyncio.get_event_loop().run_until_complete(main(port))
