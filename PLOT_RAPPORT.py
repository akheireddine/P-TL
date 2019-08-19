
import csv
import matplotlib.pyplot as plt
import numpy as np


path = "./Data/Evaluation2"
file_plot = [path+"/A/100/AVG_K_30.evalRAPPORT", path+"/A/200/AVG_K_30.evalRAPPORT", path+"/C/100/AVG_K_20.evalRAPPORT"]
labels= "A-100","A-200","C-100"




###############INFO/D1

#fig = plt.figure(figsize=(13,10))
#
#plt.minorticks_on()
#plt.grid(which='both')
#plt.grid(which='minor', alpha=0.4, linestyle='-.')
#
#plt.xlabel("Degré d'incertitude (°)",size=15, fontweight="bold")
#plt.xlim(90, 0)
#plt.ylabel("D1",size=15, fontweight="bold")
#
#for f,l in zip(file_plot,labels) : 
#    M = np.loadtxt(f)
#    plt.plot(M[:,5], M[:,7], label=l, marker='o',linewidth=4.0)
#    
#    
#plt.legend(prop={'size': 15})
#plt.title("Évolution de l'indicateur D1 selon le degré d'incertitude", fontweight="bold",size=20,)
#fig.savefig("Info_D1_REPPORT.png")
#
#plt.show()




###############INFO/D2



#fig = plt.figure(figsize=(13,10))
#
#plt.minorticks_on()
#plt.grid(which='both')
#plt.grid(which='minor', alpha=0.4, linestyle='-.')
#
#plt.xlabel("Degré d'incertitude (°)",size=15, fontweight="bold")
#plt.xlim(90, 0)
#plt.ylabel("D2",size=15, fontweight="bold")
#
#for f,l in zip(file_plot,labels) : 
#    M = np.loadtxt(f)
#    plt.plot(M[:,5], M[:,8], label=l, marker='o',linewidth=4.0)
#    
#    
#plt.legend(prop={'size': 15})
#plt.title("Évolution de l'indicateur D2 selon le degré d'incertitude", fontweight="bold",size=20,)
#fig.savefig("Info_D2_REPPORT.png")
#
#plt.show()



###############INFO/D3




#fig = plt.figure(figsize=(13,10))
#
#plt.minorticks_on()
#plt.grid(which='both')
#plt.grid(which='minor', alpha=0.4, linestyle='-.')
#
#plt.xlabel("Degré d'incertitude (°)",size=15, fontweight="bold")
#plt.xlim(90, 0)
#plt.ylabel("D3",size=15, fontweight="bold")
#
#for f,l in zip(file_plot,labels) : 
#    M = np.loadtxt(f)
#    plt.plot(M[:,5], M[:,9], label=l, marker='o',linewidth=4.0)
#    
#    
#plt.legend(prop={'size': 15})
#plt.title("Évolution de l'indicateur D3 selon le degré d'incertitude", fontweight="bold",size=20,)
#fig.savefig("Info_D3_REPPORT.png")
#
#plt.show()






###############INFO/BUDGET (nb sol eval)




#fig = plt.figure(figsize=(13,10))
#
#plt.minorticks_on()
#plt.grid(which='both')
#plt.grid(which='minor', alpha=0.4, linestyle='-.')
#
#plt.xlabel("Degré d'incertitude (°)",size=15, fontweight="bold")
#plt.xlim(90, 0)
#plt.ylabel("Nombre de solutions évalué",size=15, fontweight="bold")
#
#for f,l in zip(file_plot,labels) : 
#    M = np.loadtxt(f)
#    plt.plot(M[:,5], M[:,6], label=l, marker='o',linewidth=4.0)
#    
#    
#plt.legend(prop={'size': 15})
#plt.title("Evolution du nombre de solutions évalué (Budget) \n selon  le degré d'incertitude", fontweight="bold",size=20,)
#fig.savefig("Info_Budget_REPPORT.png")
#
#plt.show()






###############INFO/BUDGET (TIME)

#fig = plt.figure(figsize=(13,10))
#
#plt.minorticks_on()
#plt.grid(which='both')
#plt.grid(which='minor', alpha=0.4, linestyle='-.')
#
#plt.xlabel("Degré d'incertitude (°)",size=15, fontweight="bold")
#plt.xlim(90, 0)
#plt.ylabel("Logarithme du temps d'exécution (second)",size=15, fontweight="bold")
#
#for f,l in zip(file_plot,labels) : 
#    M = np.loadtxt(f)
#    plt.plot(M[:,5], np.log(M[:,11]), label=l, marker='o',linewidth=4.0)
#    
#    
#plt.legend(prop={'size': 15})
#plt.title("Evolution logarithmique du temps d'exécution (Budget)\n selon  le degré d'incertitude", fontweight="bold",size=20,)
#fig.savefig("Info_TEMPS_REPPORT.png")
#
#plt.show()




###############D1/BUDGET( nb eval)


#file_plot = [path+"/A/100/AVG_K_30.evalRAPPORT2", path+"/A/200/AVG_K_30.evalRAPPORT2", path+"/C/100/AVG_K_20.evalRAPPORT2"]
#
#
#fig = plt.figure(figsize=(13,10))
#
#plt.minorticks_on()
#plt.grid(which='both')
#plt.grid(which='minor', alpha=0.4, linestyle='-.')
#
#plt.xlabel("Budget (# sol évalué)",size=15, fontweight="bold")
#plt.xlim(0,5020)
#plt.ylabel("log D1",size=15, fontweight="bold")
#
#for f,l in zip(file_plot,labels) : 
#    M = np.loadtxt(f)
#    X = list()
#    Y = list()
#    for m in M : 
#        if m[5] == 90:
#            X.append(m[3])
#            Y.append(np.log(m[7]))
#    plt.plot(X, Y, label=l, marker='o',linewidth=4.0)
#    
#    
#plt.legend(prop={'size': 15})
#plt.title("Evolution de l'indicateur  D1 (log) selon le budget fixé pour 90° d'incertitude", fontweight="bold",size=20,)
#fig.savefig("Budget_D1_90.png")
#
#plt.show()




###############OPT Info/BUDGET( nb eval)

#file_plot = [path+"/A/100/AVG_K_30.evalRAPPORT2", path+"/A/200/AVG_K_30.evalRAPPORT2", path+"/C/100/AVG_K_20.evalRAPPORT2"]
#
#
#fig = plt.figure(figsize=(13,10))
#
#plt.minorticks_on()
#plt.grid(which='both')
#plt.grid(which='minor', alpha=0.4, linestyle='-.')
#
#plt.xlabel("Budget (# sol évalué)",size=15, fontweight="bold")
#plt.xlim(0,5020)
#plt.ylabel("Degré d'incertitude OPTimal (°)",size=15, fontweight="bold")
#plt.ylim(-0.001, 91)
#
#for f,l in zip(file_plot,labels) : 
#    M = np.loadtxt(f)
#    X = list()
#    Y = list()
#    budgets = list(set(M[:,3]))
#    budgets.sort()
#    for b in budgets :
#        min_ind = None
#        info_opt = None
#        for m in M : 
#            if (min_ind == None) or (m[7] < min_ind)  and (m[3] == b) :
#                min_ind = m[7]
#                info_opt = m[5]
#                
#        X.append(b)
#        Y.append(info_opt)
#        
#    plt.plot(X, Y, label=l, marker='o',linewidth=4.0)
#    
#    
#plt.legend(prop={'size': 15})
#plt.title("Degré d'incertitude optimal de l'indicateur D1  suivnat un budget donné", fontweight="bold",size=20,)
#fig.savefig("Budget_OPTInfo_Budget.png")
#
#plt.show()


###############D1/FILTERING FRONT

#file_v1 = [path+"/A/100/AVG_K_30.v1", path+"/A/200/AVG_K_30.v1", path+"/C/100/AVG_K_20.v1"]
#labels_v1 = ["sans information A-100","sans information A-200","sans information C-100"]
#labels = ["avec information A-100","avec information A-200","avec information C-100"]
#colors = ['tab:blue',"tab:orange","tab:green"]
#fig = plt.figure(figsize=(13,10))
#
#plt.minorticks_on()
#plt.grid(which='both')
#plt.grid(which='minor', alpha=0.4, linestyle='-.')
#
#plt.xlabel("Degré d'incertitude (°)",size=15, fontweight="bold")
#plt.xlim(90, 0)
#plt.ylabel("D1",size=15, fontweight="bold")
#
#for i in range(0,1) :
#    M = np.loadtxt(file_plot[i])
#    plt.plot(M[:,5], M[:,7], label=labels[i], color=colors[i], marker='o',linewidth=4.0)
#    
#    M = np.loadtxt(file_v1[i])
#    plt.plot(M[:,5], M[:,7], label=labels_v1[i],linestyle='-.', color=colors[i], marker='o',linewidth=4.0)
#    
#plt.legend(prop={'size': 15})
#plt.title("Comparison de l'indicateur D1 sous differents degrés d'incertitudes", fontweight="bold",size=20,)
#fig.savefig("Budget_D1_V1_A100.png")
#
#plt.show()




###############D2/FILTERING FRONT

#fig = plt.figure(figsize=(13,10))
#
#plt.minorticks_on()
#plt.grid(which='both')
#plt.grid(which='minor', alpha=0.4, linestyle='-.')
#
#plt.xlabel("Degré d'incertitude (°)",size=15, fontweight="bold")
#plt.xlim(90, 0)
#plt.ylabel("D2",size=15, fontweight="bold")
#
#for i in range(0,1) :
#    M = np.loadtxt(file_plot[i])
#    plt.plot(M[:,5], M[:,8], label=labels[i], color=colors[i], marker='o',linewidth=4.0)
#    
#    M = np.loadtxt(file_v1[i])
#    plt.plot(M[:,5], M[:,8], label=labels_v1[i],linestyle='-.', color=colors[i], marker='o',linewidth=4.0)
#    
#plt.legend(prop={'size': 15})
#plt.title("Comparison de l'indicateur D2 sous differents degrés d'incertitudes", fontweight="bold",size=20,)
#fig.savefig("Budget_D2_V1_A100.png")
#
#plt.show()




###############D1/POPSize changing


#file_plot = [path+"/A/100/AVG_K_30.evalRAPPORT3", path+"/A/200/AVG_K_30.evalRAPPORT3", path+"/C/100/AVG_K_20.evalRAPPORT3"]
#
#
#fig = plt.figure(figsize=(13,10))
#
#plt.minorticks_on()
#plt.grid(which='both')
#plt.grid(which='minor', alpha=0.4, linestyle='-.')
#
#plt.xlabel("Taille de Population",size=15, fontweight="bold")
#plt.xlim(2,200)
#plt.ylabel("D1",size=15, fontweight="bold")
#
#for f,l,i in zip(file_plot,labels,range(0,len(labels))) : 
#    M = np.loadtxt(f)
#    X = list()
#    Y = list()
#    for m in M : 
#        if m[5] == 0:
#            X.append(m[4])
#            Y.append(m[7])
#    if i in {0,1} :
#        X.append(200)
#        Y.append(Y[-1])
#        
#    plt.plot(X, Y, label=l, marker='o',linewidth=4.0)
#    
#plt.legend(prop={'size': 15})
#plt.title("Evolution de l'indicateur  D1 \nsous différentes taille de Population pour 0° d'incertitude", fontweight="bold",size=20,)
#fig.savefig("Budget_D1PopSize_0.png")
#
#plt.show()




###############D1/Diversification


file_plot = [path+"/A/100/AVG_K_30.evalRAPPORT4", path+"/C/100/AVG_K_20.evalRAPPORT4"]
colors = ['tab:blue',"tab:green"]
labels_D1 = ["avec Diversification A-100","avec Diversification C-100"]
labels= "A-100","C-100"




for f,l,i in zip(file_plot,labels,range(0,len(labels))) : 
    fig = plt.figure(figsize=(13,10))
    plt.minorticks_on()
    plt.grid(which='both')
    plt.grid(which='minor', alpha=0.4, linestyle='-.')
    
    plt.xlabel("Degré d'incertitude (°)",size=15, fontweight="bold")
    plt.xlim(90,0)
    plt.ylabel("D1",size=15, fontweight="bold")

    M = np.loadtxt(f)
    X0 = list()
    Y0 = list()
    X1 = list()
    Y1 = list()
    for m in M : 
        if m[10] == 0:
            X0.append(m[5])
            Y0.append(m[7])
        else:
            X1.append(m[5])
            Y1.append(m[7])

    plt.plot(X1, Y1, label=labels_D1[i],linestyle=':', color=colors[i], marker='o',linewidth=4.0)
    plt.plot(X0, Y0, label="sans Diversification "+l, marker='o', color=colors[i], linewidth=4.0)

    plt.legend(prop={'size': 15})
    plt.title("Evolution de l'indicateur  D1 \n sous différents degré d'incertitude avec et sans Diversification", fontweight="bold",size=20,)
    fig.savefig("Diversification_D1_Info"+l+".png")
    
#    plt.show()
#    plt.close()











