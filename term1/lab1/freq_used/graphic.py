from matplotlib import pyplot as plt
import numpy as np

def draw_graphic(lin_ax, log_ax, filename, label):
	data = []

	with open(filename) as file:
	    for line in file.readlines():
	    	time, iters = line.split()
	    	data.append([float(time), int(iters)])

	# plt.title("Sum of two")

	# fig, ((lin_sorted, log_sorted), (lin_unsorted, log_unsorted)) = plt.subplots(2, 2, figsize = (10, 10))

	# fig.suptitle('Sum of two')

	time, iters = list(zip(*data))

	time = np.array(time)
	iters = np.array(iters)

	lin_ax.plot(iters, time)
	lin_ax.set_xlabel('N, array lenght')
	lin_ax.set_ylabel('t, ms')
	lin_ax.set_title(label)
	lin_ax.grid()

	# lin_ax.set_title("Sorted");

	log_ax.plot(np.log(iters), np.log(time))
	log_ax.set_xlabel('log(N), array lenght')
	log_ax.set_ylabel('log(t), ms')
	lin_ax.set_title(label)
	log_ax.grid()


fig, ((lin_A, lin_B, lin_C), (log_A, log_B, log_C)) = plt.subplots(2, 3, figsize = (15, 10))

fig.suptitle('Smart search')

draw_graphic(lin_A, log_A, 'A.txt', 'A')
draw_graphic(lin_B, log_B, 'B.txt', 'B')
draw_graphic(lin_C, log_C, 'C.txt', 'C')

plt.show()


