
import csv
import matplotlib.pyplot as plt
import numpy as np

###############INFO/D1

path = "./Data/Evaluation2"
file_plot = [path+"/A/100/AVG_K_30.evalRAPPORT", path+"/A/200/AVG_K_30.evalRAPPORT", path+"/C/100/AVG_K_20.evalRAPPORT"]
labels= "A-100","A-200","C-100"

fig = plt.figure(figsize=(13,10))

plt.minorticks_on()
plt.grid(which='both')
plt.grid(which='minor', alpha=0.4, linestyle='-.')

plt.xlabel("Degré d'incertitude (°)",size=15, fontweight="bold")
plt.xlim(90, 0)
plt.ylabel("D1",size=15, fontweight="bold")

for f,l in zip(file_plot,labels) : 
    M = np.loadtxt(f)
    plt.plot(M[:,5], M[:,7], label=l, marker='o',linewidth=4.0)
    
    
plt.legend(prop={'size': 15})
plt.title("Évolution de l'indicateur D1 selon le degré d'incertitude", fontweight="bold",size=20,)
fig.savefig("Info_D1_REPPORT.png")

plt.show()




###############INFO/D2



fig = plt.figure(figsize=(13,10))

plt.minorticks_on()
plt.grid(which='both')
plt.grid(which='minor', alpha=0.4, linestyle='-.')

plt.xlabel("Degré d'incertitude (°)",size=15, fontweight="bold")
plt.xlim(90, 0)
plt.ylabel("D2",size=15, fontweight="bold")

for f,l in zip(file_plot,labels) : 
    M = np.loadtxt(f)
    plt.plot(M[:,5], M[:,8], label=l, marker='o',linewidth=4.0)
    
    
plt.legend(prop={'size': 15})
plt.title("Évolution de l'indicateur D2 selon le degré d'incertitude", fontweight="bold",size=20,)
fig.savefig("Info_D2_REPPORT.png")

plt.show()



###############INFO/D3




fig = plt.figure(figsize=(13,10))

plt.minorticks_on()
plt.grid(which='both')
plt.grid(which='minor', alpha=0.4, linestyle='-.')

plt.xlabel("Degré d'incertitude (°)",size=15, fontweight="bold")
plt.xlim(90, 0)
plt.ylabel("D3",size=15, fontweight="bold")

for f,l in zip(file_plot,labels) : 
    M = np.loadtxt(f)
    plt.plot(M[:,5], M[:,9], label=l, marker='o',linewidth=4.0)
    
    
plt.legend(prop={'size': 15})
plt.title("Évolution de l'indicateur D3 selon le degré d'incertitude", fontweight="bold",size=20,)
fig.savefig("Info_D3_REPPORT.png")

plt.show()






###############INFO/BUDGET (nb sol eval)




fig = plt.figure(figsize=(13,10))

plt.minorticks_on()
plt.grid(which='both')
plt.grid(which='minor', alpha=0.4, linestyle='-.')

plt.xlabel("Degré d'incertitude (°)",size=15, fontweight="bold")
plt.xlim(90, 0)
plt.ylabel("Nombre de solutions évalué",size=15, fontweight="bold")

for f,l in zip(file_plot,labels) : 
    M = np.loadtxt(f)
    plt.plot(M[:,5], M[:,6], label=l, marker='o',linewidth=4.0)
    
    
plt.legend(prop={'size': 15})
plt.title("Evolution du nombre de solutions évalué (Budget) selon  le degré d'incertitude", fontweight="bold",size=20,)
fig.savefig("Info_Budget_REPPORT.png")

plt.show()






###############INFO/BUDGET (TIME)

fig = plt.figure(figsize=(13,10))

plt.minorticks_on()
plt.grid(which='both')
plt.grid(which='minor', alpha=0.4, linestyle='-.')

plt.xlabel("Degré d'incertitude (°)",size=15, fontweight="bold")
plt.xlim(90, 0)
plt.ylabel("Temps d'exécution",size=15, fontweight="bold")

for f,l in zip(file_plot,labels) : 
    M = np.loadtxt(f)
    plt.plot(M[:,5], M[:,6], label=l, marker='o',linewidth=4.0)
    
    
plt.legend(prop={'size': 15})
plt.title("Evolution temps d'exécution (Budget) selon  le degré d'incertitude", fontweight="bold",size=20,)
fig.savefig("Info_TEMPS_REPPORT.png")

plt.show()





###############D1/BUDGET( nb eval)






fig = plt.figure(figsize=(13,10))

plt.minorticks_on()
plt.grid(which='both')
plt.grid(which='minor', alpha=0.4, linestyle='-.')

plt.xlabel("Budget (# sol évalué)",size=15, fontweight="bold")
plt.xlim(90, 0)
plt.ylabel("D1",size=15, fontweight="bold")

for f,l in zip(file_plot,labels) : 
    M = np.loadtxt(f)
    plt.plot(M[:,3], M[:,6], label=l, marker='o',linewidth=4.0)
    
    
plt.legend(prop={'size': 15})
plt.title("Evolution de l'indicateur D1 selon le budget fixé avec 90° d'incertitude", fontweight="bold",size=20,)
fig.savefig("Budget_D1_90.png")

plt.show()







