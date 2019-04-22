import numpy as np
import matplotlib.pyplot as plt


def makegraph(x,y,n):
    for i in range(0,1):
        print(i)

    return 

for i in range(1,10):
    print(i)

t = np.arange(0., 5., 0.2)
print(t)


def function_f(a):

    arr=[ 100, 7, 8, 67, 100,
        7, 4, 87, 22, 23,
        45, 55, 1, 9, 0 ]
    i = int(a)

    if i < 0 or i >= len(arr):
        return -9999
    else:
        return arr[i]

def make_parabol(n, p):
    arr=[[],[]]

    arr[0] = np.arange(-2*n, 2*n, 0.5)
    for x in arr[0]:
        y = x*x - 2*x*p + p*p + function_f(p)
        arr[1].append(y)

    return arr

n=10
for i in range(n):
    aa = make_parabol(n, i)
    # print(aa[0])
    # print(aa[1])

    plt.plot(aa[0], aa[1])
    plt.plot([i], [function_f(i)], 'ro')

plt.axis([-2*n, 2*n, 0, 500])
plt.show()

