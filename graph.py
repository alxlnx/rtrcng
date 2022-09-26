#!/opt/rh/rh-python38/root/usr/bin/python3

from matplotlib import pyplot as plt

x = [i for i in range(10)]
y = [i ** 2 for i in x]

plt.scatter(x, y)
