from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
import numpy as np
from sys import argv

x,y,z = np.loadtxt('/Users/alex/Desktop/healthcare-dataset-stroke-data.csv', delimiter=",", unpack=True)


fig = plt.figure()
ax = Axes3D(fig)
surf = ax.scatter(x, y, z, cmap='ocean', linewidth=0.5)
ax.set_xlabel('Edad')
ax.set_ylabel('BMI')
ax.set_zlabel('Has had a stroke')
ax.set_zlim(0,1)

#plt.savefig('teste.pdf')
plt.show()
"""

fig = plt.figure()
ax = Axes3D(fig)
surf = ax.plot_trisurf(x, y, z, cmap=cm.jet, linewidth=0.1)
fig.colorbar(surf, shrink=0.5, aspect=5)
plt.savefig('teste.pdf')
plt.show()
"""
