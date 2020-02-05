import logging

from .simple_serial import Serial


logger = logging.getLogger(__name__)


class UART(Serial):

    async def manage_task(self, args):
        idx = args["index"]
        priority = args.get("priority")
        duration = args.get("duration")
        logger.debug(f"Managing Task {idx}: priority {priority} and duration {duration}")
        if priority is not None:
            await self.write_read(f"cpt{idx} {priority}")
        if duration is not None:
            await self.write_read(f"cdt{idx} {duration}")

    async def manage_timer(self, args):
        control = args.get("running")
        period = args.get("period")
        semaphore = args.get("semaphore")
        logger.debug(f"Managing timer: is running {control}, period {period} and semaphore {semaphore}")
        if control is not None:
            if control is True:
                await self.write_read("sta_t")
            else:
                await self.write_read("sto_t")
        if period is not None:
            await self.write_read(f"tp {period}")
        logger.debug(f"Semaphore: value: {semaphore!r}, type: {type(semaphore)}")
        if semaphore is not None:
            await self.write_read(f"ts {semaphore}")

    async def queue_put(self, args):
        value = args.get("value")
        logger.debug(f"Putting value {value} to queue")
        if value is not None:
            await self.write_read(f"pq {value}")

    async def give_semaphore(self, args):
        idx = args.get("index")
        logger.debug(f"Giving semaphore of index {idx}")
        if idx is not None:
            await self.write_read(f"gs {idx}")
