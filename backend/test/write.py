from uart import UART

u = UART('/dev/ttyACM0', speed=115200)
u.write('cpt1 3'.ljust(12))