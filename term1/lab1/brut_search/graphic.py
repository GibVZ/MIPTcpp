from matplotlib import pyplot as plt


data = []

with open('out.txt') as file:
    for line in file.readlines():
    	time, iters = line.split()
    	data.append([float(time), int(iters)])


plt.plot(*list(zip(*data))[::-1])
plt.title('Brut foce search')
plt.xlabel('N, array lenght')
plt.ylabel('t, ns')
plt.grid()
plt.show()
