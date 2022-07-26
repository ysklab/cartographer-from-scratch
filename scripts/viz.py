import json
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.collections import PolyCollection


class Map:
    def __init__(self, size, data, origin, r):
        self.size = size
        self.data = data
        self.origin = origin
        self.r = r


def LoadVec2d(j):
    return np.array([j['x'], j['y']], dtype=float)


def LoadVec2i(j):
    return np.array([j['x'], j['y']], dtype=int)


def LoadMap(j):
    r = j["resolution"]
    origin = LoadVec2d(j['origin'])
    size = LoadVec2i(j['size'])
    numx, numy = size[0], size[1]
    data = np.zeros((numx, numy), dtype=int)
    for x in range(0, numx):
        for y in range(0, numy):
            data[x, y] = j["data"][x * numy + y]
    return Map(size, data, origin, r)


def LoadScan(j):
    n = len(j)
    scan = np.zeros((2, n), dtype=float)
    for i in range(0, n):
        scan[:, i] = LoadVec2d(j[i])
    return scan


def PlotMap(ax, m):
    verts = []
    colors = []
    for i in range(0, m.size[0]):
        for j in range(0, m.size[1]):
            x, y = i * m.r, j * m.r
            xs = [x, x + m.r, x + m.r, x]
            ys = [y, y, y + m.r, y + m.r]
            verts.append(list(zip(xs, ys)))
            colors.append(1.0 - m.data[i, j] / 255)
    ax.add_collection(PolyCollection(verts, facecolors=[
                      str(c) for c in colors], edgecolors='k', closed=True))


def PlotScan(ax, s):
    return None


with open('/tmp/cart.json') as f:
    j1 = json.loads(f.readline())
    scan1 = LoadScan(j1)
    print(scan1)
    j2 = json.loads(f.readline())
    map = LoadMap(j2)
    print(map.data)
    j3 = json.loads(f.readline())
    scan2 = LoadScan(j3)

fig = plt.figure()
ax = fig.add_subplot(111)
plt.plot(scan1[0, :], scan1[1, :], 'go')
PlotMap(ax, map)
plt.axis('equal')
plt.plot(scan2[0, :], scan2[1, :], 'ro')
plt.show()
input()
