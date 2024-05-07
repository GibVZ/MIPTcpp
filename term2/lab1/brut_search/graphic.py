from matplotlib import pyplot as plt
import numpy as np

data = []

with open('out.txt') as file:
    for line in file.readlines():
    	time, iters = line.split()
    	data.append([float(time), int(iters)])


fig, (lin_ax, log_ax) = plt.subplots(1, 2, figsize = (10, 5))

fig.suptitle('Brut search')

iters, time = list(zip(*data))[::-1]

lin_ax.plot(iters, time)
lin_ax.set_xlabel('N, array lenght')
lin_ax.set_ylabel('t, ns')
lin_ax.grid()

log_ax.plot(np.log(iters), np.log(time))
log_ax.set_xlabel('log(N)')
log_ax.set_ylabel('log(t)')
log_ax.grid()

fig.savefig('brut_search.png')

plt.show()
