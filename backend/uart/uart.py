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
            self.write(f"cpt{idx} {priority}")
        if duration is not None:
            self.write(f"cdt{idx} {duration}")

    async def manage_timer(self, args):
        control = args.get("running")
        period = args.get("period")
        semaphore = args.get("semaphore")
        logger.debug(f"Managing timer: is running {control}, period {period} and semaphore {semaphore}")
        if control is not None:
            if control is True:
                self.write("sta_t")
            else:
                self.write("sto_t")
        if period is not None:
            self.write(f"tp {period}")
        if semaphore is not None:
            self.write(f"ts {semaphore}")

    async def queue_put(self, args):
        value = args.get("value")
        logger.debug(f"Putting value {value} to queue")
        if value is not None:
            self.write(f"pq {value}")

    async def give_semaphore(self, args):
        idx = args.get("index")
        logger.debug(f"Giving semaphore of index {idx}")
        if idx is not None:
            self.write(f"gs {idx}")
