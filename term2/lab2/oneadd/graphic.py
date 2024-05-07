from matplotlib import pyplot as plt
import numpy as np


def mnk2(x, y):
    def _mean(x):
        return sum(x) / len(x)
    meanx2 = _mean([i**2 for i in x])
    meanx = _mean(x)
    meany2 = _mean([i**2 for i in y])
    meany = _mean(y)
    meanxy = _mean([i*j for i, j in zip(x, y)])
    k = (meanxy - meanx*meany) / (meanx2 - meanx**2)
    b = meany - k * meanx
    sigma_k = (((meany2 - meany**2) / (meanx2 - meanx**2) - k**2) / len(x))**.5
    sigma_b = sigma_k*(meanx2 - meanx**2)**.5
    return k, b

def mnk1(x, y):
    def _mean(x):
        return sum(x) / len(x)
    meanx2 = _mean([i**2 for i in x])
    meanx = _mean(x)
    meany2 = _mean([i**2 for i in y])
    meany = _mean(y)
    meanxy = _mean([i*j for i, j in zip(x, y)])
    k = meanxy / meanx2
    sigma_k = ((meanx2*meany2 - meanxy**2) / (len(x) * meanx2**2))**.5
    return k, sigma_k

def line_data(x, k, b):
    return [k*i + b for i in x]


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
lin_plt.scatter(iters, time)
fig.suptitle('Удлинение на 1 (измерение времени заполнения пустой очереди до N элементов)')
lin_plt.set_xlabel('N, array lenght')
lin_plt.set_ylabel('t, ms')

log_plt.plot(np.log(iters), np.log(time))
log_plt.scatter(np.log(iters), np.log(time))

k, b = mnk2(np.log(iters), np.log(time))
log_plt.plot(np.log(iters), line_data(np.log(iters), k, b))

log_plt.set_xlabel('log(N)')
log_plt.set_ylabel('log(t)')

lin_plt.grid()
log_plt.grid()

print(k)

plt.show()

fig.savefig('oneadd.eps')
