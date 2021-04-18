import numpy as np
import matplotlib.pylab as plt
from random import seed
from random import randint
from copy import copy, deepcopy
from matplotlib.pyplot import plot, draw, show, ion
from mpl_toolkits.mplot3d import Axes3D
import math

Generations = 100
Mutation_number = 10
cols = 40
rows = 100

arr = np.random.randint(1,5, size=(rows,cols))
arr_next = np.random.randint(5,10, size=(rows,cols))
error_aray = np.empty(1000,dtype=float)
array_iterator = 0
error_history_array = [0]*Generations
mutation_array = [0]*Mutation_number
mtation_switch = 1
graph_array = [[0] * 1000 ] * 100
generation_iterator = 0
elitism_matrix = np.random.randint(5,10, size=(rows*2,cols))
elitism_switch = 1

Data_set_size = 10

x = np.empty(Data_set_size,dtype=float)
y = np.empty(Data_set_size,dtype=float)
z = [[0.0] * Data_set_size ] * Data_set_size

#Original X input array
x1 = np.empty(Data_set_size,dtype=float)

#Original Y input array
y1 = np.empty(Data_set_size,dtype=float)

z1 = [[0.0] * Data_set_size ] * Data_set_size

mf1 = np.empty(Data_set_size,dtype=float)
mf2 = np.empty(Data_set_size,dtype=float)
mf3 = np.empty(Data_set_size,dtype=float)
mf4 = np.empty(Data_set_size,dtype=float)
mf5 = np.empty(Data_set_size,dtype=float)
mf6 = np.empty(Data_set_size,dtype=float)

inf1 = np.empty(Data_set_size,dtype=float)
inf2 = np.empty(Data_set_size,dtype=float)
inf3 = np.empty(Data_set_size,dtype=float)
inf4 = np.empty(Data_set_size,dtype=float)
inf5 = np.empty(Data_set_size,dtype=float)
inf6 = np.empty(Data_set_size,dtype=float)
inf7 = np.empty(Data_set_size,dtype=float)
inf8 = np.empty(Data_set_size,dtype=float)
inf9 = np.empty(Data_set_size,dtype=float)

reg1 = np.empty(Data_set_size,dtype=float)
reg2 = np.empty(Data_set_size,dtype=float)
reg3 = np.empty(Data_set_size,dtype=float)
reg4 = np.empty(Data_set_size,dtype=float)
reg5 = np.empty(Data_set_size,dtype=float)
reg6 = np.empty(Data_set_size,dtype=float)
reg7 = np.empty(Data_set_size,dtype=float)
reg8 = np.empty(Data_set_size,dtype=float)
reg9 = np.empty(Data_set_size,dtype=float)

def originalGraph():
	print("Original Graph Function")

def plottingGraphs():
	print("Plotting Graphs Function")

def get_error():
	#Iterate through a given number of generations.
	for k in range (rows):

		#For X
		for i in range(Data_set_size):

			#For Y
			for j in range(Data_set_size):
				x1[i] = i;
				y1[j] = i;
				
				#Initial set of parameters mn, dn range from 0 to 11 (12 in total)

				#Fuzzy logic set X - 1
				mf1[i] = math.exp((-(x1[i]-arr[k][0])**2)/(2*arr[k][6]**2))

				#Fuzzy logic set X - 2
				mf2[i] = math.exp((-(x1[i]-arr[k][1])**2)/(2*arr[k][7]**2))

				#Fuzzy logic set X - 3
				mf3[i] = math.exp((-(x1[i]-arr[k][2])**2)/(2*arr[k][8]**2))

				#Fuzzy logic set Y - 1
				mf4[i] = math.exp((-(y1[i]-arr[k][3])**2)/(2*arr[k][9]**2))

				#Fuzzy logic set Y - 2
				mf5[i] = math.exp((-(y1[i]-arr[k][4])**2)/(2*arr[k][10]**2))

				#Fuzzy logic set Y - 3
				mf6[i] = math.exp((-(y1[i]-arr[k][5])**2)/(2*arr[k][11]**2))

				#Permutations of input parameters with one another
				inf1 = mf1[i]*mf4[j]
				inf2 = mf1[i]*mf5[j]
				inf3 = mf1[i]*mf6[j]
				inf4 = mf2[i]*mf4[j]
				inf5 = mf2[i]*mf5[j]
				inf6 = mf2[i]*mf6[j]
				inf7 = mf3[i]*mf4[j]
				inf8 = mf3[i]*mf5[j]
				inf9 = mf3[i]*mf6[j]

				#Multiplying permutations of input parameters with the function: pn*X + qn*Y + rn.
				#The rest of the parameters are here (27), 39 in total.
				reg1 = inf1*(arr[k][12]*x1[i]+arr[k][21]*y1[j]+arr[k][30])
				reg2 = inf2*(arr[k][13]*x1[i]+arr[k][22]*y1[j]+arr[k][31])
				reg3 = inf3*(arr[k][14]*x1[i]+arr[k][23]*y1[j]+arr[k][32])
				reg4 = inf4*(arr[k][15]*x1[i]+arr[k][24]*y1[j]+arr[k][33])
				reg5 = inf5*(arr[k][16]*x1[i]+arr[k][25]*y1[j]+arr[k][34])
				reg6 = inf6*(arr[k][17]*x1[i]+arr[k][26]*y1[j]+arr[k][35])
				reg7 = inf7*(arr[k][18]*x1[i]+arr[k][27]*y1[j]+arr[k][36])
				reg8 = inf8*(arr[k][19]*x1[i]+arr[k][28]*y1[j]+arr[k][37])
				reg9 = inf9*(arr[k][20]*x1[i]+arr[k][29]*y1[j]+arr[k][38])

				#Now for the a/b operation.

				#The total sum of the chain of operations from the other path of the network is the dividend. 
				a = reg1 + reg2 + reg3 + reg4 + reg5 + reg6 + reg7 + reg8 + reg9

				#The divisor of the net will be the sum original input parameters:
				b = inf1 + inf2 + inf3 + inf4 + inf5 + inf6 + inf7 + inf8 + inf9

				#For this member of Z prime, the final Z will be used to calculate the total error. 
				z1[i][j] = a/b
				#print(z1)


get_error()
print(z1)

z1 = np.array(z1)

fig = plt.figure()
ax = Axes3D(fig)

# create 2d x,y grid (both X and Y will be 2d)
X, Y = np.meshgrid(x1, y1)

# repeat Z to make it a 2d grid
#Z = np.tile(z1, (len(z1), 1))
Z = z1


ax.scatter(X, Y, Z, cmap='ocean')

plt.show()