import numpy as np
import matplotlib.pyplot as plt

from mpl_toolkits.mplot3d import Axes3D


p_criteria = "2"
t = "A"
size = "100"
i = "0"
#EFFICIENT SOL
#filename = "Instances_Knapsack"+p_criteria+"/Type_"+t+"/"+size+"_items/2KP"+size+"-T"+t+"-"+i+".eff"


#INSTANCE POPULATION
algo = "MOLS_SWITCH_OBJECTIVE_DEC"
filename = "./Data/Population"+p_criteria+"/"+t+"/"+size+"/T"+i+"/"+algo+"/"+i+"/Pop_0.pop"




with open(filename) as f:
    data = f.read()

data = data.split('\n')

#
#
x = [row.split(' ')[0] for row in data if len(row.split(' ')) > 1 ]

x = [ float(j) for j in x]



y = [row.split(' ')[1] for row in data if len(row.split(' ')) > 1]

y = [ float(j) for j in y]

#z = [row.split(' ')[2] for row in data if len(row.split(' ')) > 1]
#
#z = [ float(j) for j in z]

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



#fig = plt.figure()
#ax = fig.add_subplot(111, projection='3d')
##ax.scatter(x, y, z)

plt.scatter(x, y)
plt.show()
