import logging

from .serial import Serial


logger = logging.getLogger(__name__)


class UART(Serial):
    TASKS = (1, 2, 3)

    async def manage_task(self, idx, args):
        priority = args.get("priority")
        duration = args.get("duration")
        rc = 0
        logger.debug(f"Managing Task {idx}: priority {priority} and duration {duration}")
        if priority is not None:
            rc += int(await self.write_read(f"cpt{idx} {priority}"))
        if duration is not None:
            rc += int(await self.write_read(f"cdt{idx} {duration}"))
        return rc

    async def manage_timer(self, args):
        control = args.get("running")
        period = args.get("period")
        semaphore = args.get("semaphore")
        logger.debug(f"Managing timer: is running {control}, period {period} and semaphpre {semaphore}")
        rc = 0
        if control is not None:
            if control is True:
                self.write("sta_t")
            else:
                self.write("sto_t")
        if period is not None:
            rc += int(await self.write_read(f"tp {period}"))
        if semaphore is not None:
            rc += int(await self.write_read(f"tc {semaphore}"))
        return rc

    async def queue_put(self, args):
        value = args.get("value")
        logger.debug(f"Putting value {value} to queue")
        rc = 0
        if value is not None:
            rc += int(await self.write_read(f"pq {value}"))
        return rc

    async def give_semaphore(self, args):
        idx = args.get("index")
        logger.debug(f"Giving semaphore of index {idx}")
        rc = 0
        if idx is not None:
            rc += int(await self.write_read(f"gs {idx}"))
        return rc

    async def read_line(self):
        return await self.read(end="\n")
