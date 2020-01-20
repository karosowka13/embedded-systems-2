from uart import UART

u = UART('/dev/ttyACM0', speed=115200)
# u.write('cdt1 200'.ljust(12))
# u.write('cpt1 10'.ljust(12))
# u.write('tp 2000'.ljust(12))
# u.write('gs 4'.ljust(12))
# u.write('pq 10'.ljust(12))
print(u.read('sta_t 0'.ljust(12)))
# print(u.read('pq 10'.ljust(12)))
