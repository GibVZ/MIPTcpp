from matplotlib import pyplot as plt
import numpy as np

data = []

with open('out_sorted.txt') as file:
    for line in file.readlines():
    	time, iters = line.split()
    	data.append([float(time), int(iters)])

#plt.title("Sum of two")

fig, ((lin_sorted, log_sorted), (lin_unsorted, log_unsorted)) = plt.subplots(2, 2, figsize = (10, 10))

fig.suptitle('Sum of two')

time, iters = list(zip(*data))

time = np.array(time)
iters = np.array(iters)

lin_sorted.plot(iters, time)
lin_sorted.set_xlabel('N, array lenght')
lin_sorted.set_ylabel('t, ms')
lin_sorted.grid()

lin_sorted.set_title("Sorted");

log_sorted.plot(np.log(iters), time)
log_sorted.set_xlabel('log(N), array lenght')
log_sorted.set_ylabel('t, ms')
log_sorted.grid()


data = []

with open('out_unsorted.txt') as file:
    for line in file.readlines():
    	time, iters = line.split()
    	data.append([float(time), int(iters)])

time, iters = list(zip(*data))

time = np.array(time)
iters = np.array(iters)


lin_unsorted.plot(iters, time)
# lin_unsorted.title('Sum of two')
lin_unsorted.set_xlabel('N, array lenght')
lin_unsorted.set_ylabel('t, ns')
lin_unsorted.grid()

lin_unsorted.set_title("Unsorted");

log_unsorted.plot(np.log(iters), np.log(time))
log_unsorted.set_xlabel('log(N), array lenght')
log_unsorted.set_ylabel('log(t)')
log_unsorted.grid()


plt.show()


