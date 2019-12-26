from serial import Serial, SerialTimeoutException


class UART:
    TASKS = (1, 2, 3)

    def __init__(self, port, speed=9600, timeout=1.0, debug=False):
        if not debug:
            self.ser = Serial(port, baudrate=speed, timeout=timeout)
        self.debug = debug

    def __del__(self):
        if not self.debug:
            if self.ser.is_open:
                self.ser.close()
            del self.ser

    def write(self, msg):
        if not self.debug:
            self.ser.write(msg.encode())

    def read(self, msg):
        if self.debug:
            return "0"
        self.write(msg)
        try:
            return self.ser.read(1).decode()
        except SerialTimeoutException:
            return "-2"

    def manage_task(self, idx, args):
        priority = args.get("priority")
        duration = args.get("duration")
        rc = 0
        if priority is not None:
            rc += int(self.read(f"cpt{idx} {priority}"))
        if duration is not None:
            rc += int(self.read(f"cdt{idx} {duration}"))
        return rc

    def manage_timer(self, args):
        control = args.get("running")
        period = args.get("period")
        semaphore = args.get("semaphore")
        rc = 0
        if control is not None:
            if control is True:
                self.write("sta_t")
            else:
                self.write("sto_t")
        if period is not None:
            rc += int(self.read(f"tp {period}"))
        if semaphore is not None:
            rc += int(self.read(f"tc {semaphore}"))
        return rc

    def queue_put(self, args):
        value = args.get("value")
        if value is not None:
            rc = int(self.read(f"pq {value}"))

    def get_semaphore(self, idx):
        pass
