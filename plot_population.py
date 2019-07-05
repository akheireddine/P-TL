import numpy as np
import matplotlib.pyplot as plt

from mpl_toolkits.mplot3d import Axes3D


p_criteria = "3"
t = "B"
size = "101"
i = "0"
filename = "Instances_Knapsack"+p_criteria+"/Type_"+t+"/"+size+"_items/2KP"+size+"-T"+t+"-"+i+".eff"

with open(filename) as f:
    data = f.read()

data = data.split('\n')

#
#
x = [row.split(' ')[0] for row in data if len(row.split(' ')) > 1 ]

x = [ float(i) for i in x]

y = [row.split(' ')[1] for row in data if len(row.split(' ')) > 1]

y = [ float(i) for i in y]

z = [row.split(' ')[2] for row in data if len(row.split(' ')) > 1]

z = [ float(i) for i in z]

#
#fig = plt.figure()
#
#ax1 = fig.add_subplot(111, projection='3d')
#
#ax1.plot(x,y,z)
#
#leg = ax1.legend()
#
#plt.show()



fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

ax.scatter(x, y, z)
plt.show()
