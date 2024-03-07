from matplotlib import pyplot as plt
import numpy as np

data = []

with open('out.txt') as file:
    for line in file.readlines():
    	time, iters = line.split()
    	data.append([float(time), int(iters)])

fig, (lin_plt, log_plt) = plt.subplots(1, 2, figsize = (10, 5))

time, iters = list(zip(*data))

time = np.array(time)
iters = np.array(iters)

lin_plt.plot(iters, time)
plt.title('Binary search')
lin_plt.set_xlabel('N, array lenght')
lin_plt.set_ylabel('t, ms')

log_plt.plot(np.log(iters), time)
log_plt.set_xlabel('log(N), array lenght')
log_plt.set_ylabel('t, ms')

lin_plt.grid()
log_plt.grid()
plt.show()


