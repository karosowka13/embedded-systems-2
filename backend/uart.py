import serial


class UART:
    TASKS = (1, 2, 3)

    def manage_task(self, idx, args):
        return 0

    def manage_timer(self, args):
        return 0

    def queue_put(self, value):
        return 0

    def get_semaphore(self, idx):
        pass
