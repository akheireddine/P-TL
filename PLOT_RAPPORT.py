
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
#plt.xlabel("Degré d'incertitude (°)",size=20, fontweight="bold")
#plt.xlim(90, 0)
#plt.ylabel("D1",size=20, fontweight="bold")
#
#for i in range(1,2) :
#    M = np.loadtxt(file_plot[i])
#    plt.plot(M[:,5], M[:,7], label=labels[i], color=colors[i], marker='o',linewidth=4.0)
#    
#    M = np.loadtxt(file_v1[i])
#    plt.plot(M[:,5], M[:,7], label=labels_v1[i],linestyle=':', color=colors[i], marker='o',linewidth=4.0)
#    
#plt.legend(prop={'size': 25})
#plt.title("Comparison de l'indicateur D1 \nsous differents degrés d'incertitudes", fontweight="bold",size=25)
#fig.savefig("Budget_D1_V1_A200.png")
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


#file_plot = [path+"/A/100/AVG_K_30.evalRAPPORT4", path+"/C/100/AVG_K_20.evalRAPPORT4"]
#colors = ['tab:blue',"tab:green"]
#labels_D1 = ["avec Diversification A-100","avec Diversification C-100"]
#labels= "A-100","C-100"
#
#
#
#
#for f,l,i in zip(file_plot,labels,range(0,len(labels))) : 
#    fig = plt.figure(figsize=(13,10))
#    plt.minorticks_on()
#    plt.grid(which='both')
#    plt.grid(which='minor', alpha=0.4, linestyle='-.')
#    
#    plt.xlabel("Degré d'incertitude (°)",size=15, fontweight="bold")
#    plt.xlim(90,0)
#    plt.ylabel("D1",size=15, fontweight="bold")
#
#    M = np.loadtxt(f)
#    X0 = list()
#    Y0 = list()
#    X1 = list()
#    Y1 = list()
#    for m in M : 
#        if m[10] == 0:
#            X0.append(m[5])
#            Y0.append(m[7])
#        else:
#            X1.append(m[5])
#            Y1.append(m[7])
#
#    plt.plot(X1, Y1, label=labels_D1[i],linestyle=':', color=colors[i], marker='o',linewidth=4.0)
#    plt.plot(X0, Y0, label="sans Diversification "+l, marker='o', color=colors[i], linewidth=4.0)
#
#    plt.legend(prop={'size': 15})
#    plt.title("Evolution de l'indicateur  D1 \n sous différents degré d'incertitude avec et sans Diversification", fontweight="bold",size=20,)
#    fig.savefig("Diversification_D1_Info"+l+".png")
    
#    plt.show()
#    plt.close()







###############TIMEouBudget/INFO pour Diversification

#
#file_plot = [path+"/A/100/AVG_K_30.evalRAPPORT4", path+"/C/100/AVG_K_20.evalRAPPORT4"]
#colors = ['tab:blue',"tab:green"]
#labels_D1 = ["avec Diversification A-100","avec Diversification C-100"]
#labels= "A-100","C-100"
#
#
#
#
#for f,l,i in zip(file_plot,labels,range(0,len(labels))) : 
#    fig = plt.figure(figsize=(13,10))
#    plt.minorticks_on()
#    plt.grid(which='both')
#    plt.grid(which='minor', alpha=0.4, linestyle='-.')
#    
#    plt.xlabel("Degré d'incertitude (°)",size=15, fontweight="bold")
#    plt.xlim(90,0)
#    plt.ylabel("Budget #sol évalué (log)",size=15, fontweight="bold")
#
#    M = np.loadtxt(f)
#    X0 = list()
#    Y0 = list()
#    X1 = list()
#    Y1 = list()
#    for m in M : 
#        if m[10] == 0:
#            X0.append(m[5])
#            Y0.append(np.log(m[6]))
#        else:
#            X1.append(m[5])
#            Y1.append(np.log(m[6]))
#
#    plt.plot(X1, Y1, label=labels_D1[i],linestyle=':', color=colors[i], marker='o',linewidth=4.0)
#    plt.plot(X0, Y0, label="sans Diversification "+l, marker='o', color=colors[i], linewidth=4.0)
#
#    plt.legend(prop={'size': 15})
#    plt.title("Nombre de solutions évalué (log) \n sous différents degré d'incertitude avec et sans Diversification", fontweight="bold",size=20,)
#    fig.savefig("Diversification_Budget_Info"+l+".png")
#    
#    plt.show()





###############  ML apprentissage bInf bSup MOYENNE

#file_plot_static = [path+"/A/100/K_30.eval", path+"/C/100/K_20.eval"]
#file_plot_dyn = [path+"/A/100/AVG_K_10.evalRAPPORT_ML", path+"/C/100/AVG_K_10.evalRAPPORT_ML"]
#
#labels= "A-100","C-100"
#
#info = 90
#nb_instance = 10
#for i,l in zip(range(len(file_plot_static)), labels):
#    
#    fig = plt.figure(figsize=(6,5))
#    plt.minorticks_on()
#    plt.grid(which='both')
#    plt.grid(which='minor', alpha=0.4, linestyle='-.')
#    
#    plt.xlabel("Budget #sol évalué",size=14, fontweight="bold")
#    plt.xlim(0,4000)
#    plt.ylabel("log D1",size=15, fontweight="bold")
#
#    file_static,file_dyn = file_plot_static[i],file_plot_dyn[i]
#    
#    Bigreader = list(csv.DictReader(open(file_static, newline=''), delimiter = ','))
#    Smallreader = list(csv.DictReader(open(file_dyn, newline=''), delimiter = ','))
#    
#    Xbudget_f1 = set()
#    Xbudget_f2 = set()
#    PopSize = set()
#    for r in Bigreader :
#        Xbudget_f1.add(int(r['Budget']))
#        
#    for r in Bigreader : 
#        PopSize.add(int(r['PopSize']))
#
#    Xbudget_f1 = list(Xbudget_f1)
#    Xbudget_f1.sort()
#    
#    for r in Smallreader :
#        Xbudget_f2.add(int(r['Budget']))
#    
#    Xbudget_f2 = list(Xbudget_f2)
#    Xbudget_f2.sort()
#
#    Ymin = list()
#    Ymax = list()
#    Ydyn = list()
#    
#    for b in Xbudget_f1:# [60,540,2020,4020] : #Xbudget_f1  :
#        avg_minus = 0
#        avg_maxus = 0
#        for inst in range(0,nb_instance) :
#            minus = -1
#            maxus = -1
#            for row in Bigreader:
#                if float(row['Info']) == info and int(row['Budget']) == b and int(row['Instance']) == inst :
#                    avg_tmp = float(row['AVG_dist'])
#                    if (avg_tmp < minus) or (minus == -1) :
#                        minus = avg_tmp
#                    if (avg_tmp > maxus) or (maxus == -1) :
#                        maxus = avg_tmp
#            avg_minus += minus
#            avg_maxus += maxus
#                
##        print(avg_minus_opt, avg_minus_opt/ (len(PopSize)))
#
#        Ymin.append(np.log(avg_minus/ nb_instance))
#        Ymax.append(np.log(avg_maxus/ nb_instance))
#    
#    
#    for b in Xbudget_f2 : #[60,540,1220,6020] : #[50,500,800,6020] : #Xbudget_f2  :
#        for row in Smallreader : 
#            if float(row['Info']) == info and int(row['Budget']) == b  :
#                Ydyn.append(np.log( float(row['AVG_dist'])))
#        
#        
#    plt.plot(Xbudget_f1,Ymin,c="blue",label="Best static",marker='.',linewidth=2.0)
#    plt.plot(Xbudget_f1,Ymax,c="red",label="Worst static",marker='.',linewidth=2.0)
#    plt.plot(Xbudget_f2,Ydyn,c="green",label="$PLS_{ML}$",marker='.',linewidth=2.0)
#        
#    plt.grid()
#    plt.legend(prop={'size': 13})
#    plt.title(l,fontsize=15,fontweight="bold")
##  Log Moyenne de D1 retourné par $PLS_{ML}$ contre la meilleure et pire approximation avec l'approche statique \n Instances  "+l ,fontsize=10,fontweight="bold")
#    fig.savefig("Compare_"+l+"_ML_MOY.png", dpi=fig.dpi)
#    plt.show()




###############  ML apprentissage bInf bSup MEDIANE

#file_plot_static = [path+"/A/100/K_30.eval", path+"/C/100/K_20.eval"]
#file_plot_dyn = [path+"/A/100/K_10.evalRAPPORT_ML", path+"/C/100/K_10.evalRAPPORT_ML"]
#labels= "A-100","C-100"
#
#info = 90
#for i,l in zip(range(len(file_plot_static)), labels):
#    
#    fig = plt.figure(figsize=(13,10))
#    plt.minorticks_on()
#    plt.grid(which='both')
#    plt.grid(which='minor', alpha=0.4, linestyle='-.')
#    
#    plt.xlabel("Budget #sol évalué",size=15, fontweight="bold")
#    plt.xlim(0,4000)
#    plt.ylabel("Médiane D1",size=15, fontweight="bold")
#
#    file_static,file_dyn = file_plot_static[i],file_plot_dyn[i]
#    
#    Bigreader = list(csv.DictReader(open(file_static, newline=''), delimiter = ','))
#    Smallreader = list(csv.DictReader(open(file_dyn, newline=''), delimiter = ','))
#    
#    Xbudget_f1 = set()
#    Xbudget_f2 = set()
#    for r in Bigreader :
#        Xbudget_f1.add(int(r['Budget']))
#        
#    Xbudget_f1 = list(Xbudget_f1)
#    Xbudget_f1.sort()
#    
#    for r in Smallreader :
#        Xbudget_f2.add(int(r['Budget']))
#    
#    Xbudget_f2 = list(Xbudget_f2)
#    Xbudget_f2.sort()
#
#    Ymin = list()
#    Ydyn = list()
#
#    for b in Xbudget_f1 : #[60,540,1220,6020] : #Xbudget_f1  :
#        Ytmp = list()
#
#        for row in Bigreader:
#            if float(row['Info']) == info and int(row['Budget']) == b :
#                Ytmp.append(float(row['AVG_dist']))
#            
#        Ytmp.sort()
#        Ymin.append(np.median(Ytmp))
#        
#    for b in Xbudget_f2 : #[60,540,1220,6020] : #[50,500,800,6020] : #Xbudget_f2  :
#        Ytmp = list()
#
#        for row in Smallreader : 
#            if float(row['Info']) == info and int(row['Budget']) == b :
#                Ytmp.append((float(row['AVG_dist'])))
#        
#        Ytmp.sort()
#        Ydyn.append(np.median(Ytmp))
#    
#        
#    if i == 0 :
#        plt.plot(Xbudget_f1,Ymin,c="blue",label="static method",marker='.',linewidth=2.0)
#        plt.plot(Xbudget_f2,Ydyn,c="green",label="$PLS_{ML}$",marker='.',linewidth=2.0)
#    else :
#        plt.plot(Xbudget_f1,Ymin,c="blue",marker='.',linewidth=2.0)
#        plt.plot(Xbudget_f2,Ydyn,c="green",marker='.',linewidth=2.0)
#        
#    plt.grid()
#    plt.legend(prop={'size': 15})
#    plt.title("Valeur médiane de D1 par $PLS_{ML}$ et de l'approche statique \n Instances  "+l ,fontsize=15,fontweight="bold")
#    fig.savefig("Compare_"+l+"_ML_MED.png", dpi=fig.dpi)
#    plt.show()


#file_plot_static = [path+"/A/100/K_30.eval", path+"/C/100/K_20.eval"]
#file_plot_dyn = [path+"/A/100/K_10.evalRAPPORT_ML", path+"/C/100/K_10.evalRAPPORT_ML"]
#labels= "A-100","C-100"
#colors = ['tab:blue',"tab:orange"]
#
#info = 90
#fig = plt.figure(figsize=(7,6))
#plt.minorticks_on()
#plt.grid(which='both')
#plt.grid(which='minor', alpha=0.4, linestyle='-.')
#
#plt.xlabel("Budget #sol évalué",size=15, fontweight="bold")
#plt.xlim(0,4000)
#plt.ylabel("Médiane D1",size=15, fontweight="bold")
#
#for i,l in zip(range(len(file_plot_static)), labels):
#    
#  
#    file_static,file_dyn = file_plot_static[i],file_plot_dyn[i]
#    
#    Bigreader = list(csv.DictReader(open(file_static, newline=''), delimiter = ','))
#    Smallreader = list(csv.DictReader(open(file_dyn, newline=''), delimiter = ','))
#    
#    Xbudget_f1 = set()
#    Xbudget_f2 = set()
#    for r in Bigreader :
#        Xbudget_f1.add(int(r['Budget']))
#        
#    Xbudget_f1 = list(Xbudget_f1)
#    Xbudget_f1.sort()
#    
#    for r in Smallreader :
#        Xbudget_f2.add(int(r['Budget']))
#    
#    Xbudget_f2 = list(Xbudget_f2)
#    Xbudget_f2.sort()
#
#    Ymin = list()
#    Ydyn = list()
#
#    for b in Xbudget_f1 : #[60,540,1220,6020] : #Xbudget_f1  :
#        Ytmp = list()
#
#        for row in Bigreader:
#            if float(row['Info']) == info and int(row['Budget']) == b :
#                Ytmp.append(float(row['AVG_dist']))
#            
#        Ytmp.sort()
#        Ymin.append(np.median(Ytmp))
#        
#    for b in Xbudget_f2 : #[60,540,1220,6020] : #[50,500,800,6020] : #Xbudget_f2  :
#        Ytmp = list()
#
#        for row in Smallreader : 
#            if float(row['Info']) == info and int(row['Budget']) == b :
#                Ytmp.append((float(row['AVG_dist'])))
#        
#        Ytmp.sort()
#        Ydyn.append(np.median(Ytmp))
#    
#    print(Xbudget_f2)
#    print(Ydyn)
#    print("__________________")
#        
#    plt.plot(Xbudget_f1,Ymin,c=colors[i],label="static ("+labels[i]+")",marker='.',linewidth=3.0,linestyle=":")
#    plt.plot(Xbudget_f2,Ydyn,c=colors[i],label="$PLS_{ML}$",marker='.',linewidth=3.0)
#        
#plt.grid()
#plt.legend(prop={'size': 16})
#plt.title("Instances  "+labels[0]+" et "+labels[1] ,fontsize=15,fontweight="bold")
##plt.title("Valeur médiane de D1 par $PLS_{ML}$ et de l'approche statique \n Instances  "+labels[0]+" et "+labels[1] ,fontsize=15,fontweight="bold")
#fig.savefig("Compare_AC100_ML_MED.png", dpi=fig.dpi)
#plt.show()




###############  DYN apprentissage bInf bSup MOYENNE

#file_plot_static = [path+"/A/100/K_30.evalPARETO", path+"/C/100/K_20.evalPareto"]
#file_plot_dyn = [path+"/A/100/AVG_K_10.evalRAPPORT_DYN_INFO_60", path+"/C/100/AVG_K_10.evalRAPPORT_DYN_INFO_100"]
#labels= "A-100","C-100"
#
#div = 0
#PopSize = 60,100
#nb_instance = 10
#
#for i,l in zip(range(len(file_plot_static)), labels):
#    
#    fig = plt.figure(figsize=(6,5))
#    plt.minorticks_on()
#    plt.grid(which='both')
#    plt.grid(which='minor', alpha=0.4, linestyle='-.')
#    
#    plt.xlabel("Budget #sol évalué",size=15, fontweight="bold")
#    plt.xlim(0,4000)
#    plt.ylabel("log D1",size=15, fontweight="bold")
#
#    file_static,file_dyn = file_plot_static[i],file_plot_dyn[i]
#    
#    Bigreader = list(csv.DictReader(open(file_static, newline=''), delimiter = ','))
#    Smallreader = list(csv.DictReader(open(file_dyn, newline=''), delimiter = ','))
#    
#    Xbudget_f1 = set()
#    Xbudget_f2 = set()
#    for r in Bigreader :
#        Xbudget_f1.add(int(r['Budget']))
#        
#    Xbudget_f1 = list(Xbudget_f1)
#    Xbudget_f1.sort()
#    
#    print(file_dyn)
#    for r in Smallreader :
#        Xbudget_f2.add(int(r['Budget']))
#    
#    Xbudget_f2 = list(Xbudget_f2)
#    Xbudget_f2.sort()
#
#    Ymin = list()
#    Ymax = list()
#    Ydyn = list()
#    
#    for b in Xbudget_f1:# [60,540,2020,4020] : #Xbudget_f1  :
#        avg_minus = 0
#        avg_maxus = 0
#        for inst in range(0,nb_instance) :
#            minus = -1
#            maxus = -1
#            for row in Bigreader:
#                if int(row['Budget']) == b and int(float(row['Diversification'])) == div and int(float(row['PopSize'])) == PopSize[i] :
#                    avg_tmp = float(row['AVG_dist'])
#                    if (avg_tmp < minus) or (minus == -1) :
#                        minus = avg_tmp
#                    if (avg_tmp > maxus) or (maxus == -1) :
#                        maxus = avg_tmp
#            avg_minus += minus
#            avg_maxus += maxus
#                
#
#        Ymin.append(np.log(avg_minus/ nb_instance))
#        Ymax.append(np.log(avg_maxus/ nb_instance))
#        
#    for b in Xbudget_f2 : #[60,540,1220,6020] : #[50,500,800,6020] : #Xbudget_f2  :
#
#        for row in Smallreader : 
#            if int(row['Budget']) == b and int(float(row['Diversification'])) == div and int(float(row['PopSize'])) == PopSize[i] :
#                Ydyn.append(np.log(float(row['AVG_dist'])))
#        
#        
#    
#        
#    plt.plot(Xbudget_f1,Ymin,c="blue",label="Best static",marker='.',linewidth=2.0)
#    plt.plot(Xbudget_f1,Ymax,c="red",label="Worst static",marker='.',linewidth=2.0)
#    plt.plot(Xbudget_f2,Ydyn,c="green",label="$PLS_{dyn}$",marker='.',linewidth=2.0)
#        
#    plt.grid()
#    plt.legend(prop={'size': 14})
#    plt.title(l,fontsize=15,fontweight="bold")
##    plt.title("Moyenne de D1 retourné par $PLS_{dyn}$ contre la meilleure et pire approximation avec l'approche statique \n Instances  "+l ,fontsize=15,fontweight="bold")
#    fig.savefig("Compare_"+l+"_DYN_MOY.png", dpi=fig.dpi)
#    plt.show()

#
#
#
################ DYN apprentissage bInf bSup MEDIANE

file_plot_static = [path+"/A/100/K_30.evalPARETO", path+"/C/100/K_20.evalPareto"]
file_plot_dyn = [path+"/A/100/K_10.evalRAPPORT_DYN_INFO_60", path+"/C/100/K_10.evalRAPPORT_DYN_INFO_100"]
div = 0
PopSize = 60,100
labels= "A-100","C-100"
colors = ['tab:blue',"tab:orange"]

fig = plt.figure(figsize=(7,6))
plt.minorticks_on()
plt.grid(which='both')
plt.grid(which='minor', alpha=0.4, linestyle='-.')

plt.xlabel("Budget #sol évalué",size=15, fontweight="bold")
plt.xlim(0,3500)
plt.ylabel("Médiane D1",size=15, fontweight="bold")

for i,l in zip(range(len(file_plot_static)), labels):
    


    file_static,file_dyn = file_plot_static[i],file_plot_dyn[i]
    
    Bigreader = list(csv.DictReader(open(file_static, newline=''), delimiter = ','))
    Smallreader = list(csv.DictReader(open(file_dyn, newline=''), delimiter = ','))
    
    Xbudget_f1 = set()
    Xbudget_f2 = set()
    for r in Bigreader :
        Xbudget_f1.add(int(r['Budget']))
        
    Xbudget_f1 = list(Xbudget_f1)
    Xbudget_f1.sort()
    
    for r in Smallreader :
        Xbudget_f2.add(int(r['Budget']))
    
    Xbudget_f2 = list(Xbudget_f2)
    Xbudget_f2.sort()

    Ymin = list()
    Ydyn = list()

    for b in Xbudget_f1 : #[60,540,1220,6020] : #Xbudget_f1  :
        Ytmp = list()

        for row in Bigreader:
            if int(float(row['Diversification'])) == div and int(row['Budget']) == b and int(float(row['PopSize'])) == PopSize[i] :
                Ytmp.append(float(row['AVG_dist']))

        Ytmp.sort()
        Ymin.append(np.median(Ytmp))
        
    for b in Xbudget_f2 : #[60,540,1220,6020] : #[50,500,800,6020] : #Xbudget_f2  :
        Ytmp = list()

        for row in Smallreader : 
            if int(float(row['Diversification'])) == div and int(row['Budget']) == b and int(float(row['PopSize'])) == PopSize[i] :
                Ytmp.append((float(row['AVG_dist'])))
        
        Ytmp.sort()
        Ydyn.append(np.median(Ytmp))
    
        
    plt.plot(Xbudget_f1,Ymin,label="static method - "+labels[i],marker='.',linewidth=3.0, color=colors[i], linestyle=':')
    plt.plot(Xbudget_f2,Ydyn,label="$PLS_{dyn}$",marker='.',linewidth=3.0, color=colors[i])
        
plt.grid()
plt.legend(prop={'size': 14})
#plt.title("Valeur médiane de D1 par $PLS_{dyn}$ et de l'approche statique \n Instances  "+l ,fontsize=15,fontweight="bold")
plt.title(labels[0]+" et "+labels[1] ,fontsize=15,fontweight="bold")
fig.savefig("Compare_DYN_MED.png", dpi=fig.dpi)
plt.show()

#
################ DYN Fréquence d'interaction / Budget
#    
#file_plot = [path+"/A/100/AVG_K_10.evalRAPPORT_DYN_INFO_60", path+"/C/100/AVG_K_10.evalRAPPORT_DYN_INFO_100"]
#
#labels= "A-100","C-100"
#
#fig = plt.figure(figsize=(13,10))
#
#plt.minorticks_on()
#plt.grid(which='both')
#plt.grid(which='minor', alpha=0.4, linestyle='-.')
#
#plt.xlabel("Budget (# sol évalué)",size=15, fontweight="bold")
#plt.xlim(0,4000)
#plt.ylabel("Fréquence d'intéraction",size=15, fontweight="bold")
#
#for f,l in zip(file_plot,labels) : 
#    M = np.loadtxt(f)
#    X = list()
#    Y = list()
#    budgets = list(set(M[:,3]))
#    budgets.sort()
#    for b in budgets :
#        freq = None
#        for m in M : 
#            if m[3] == b :
#                min_ind = m[7]
#                freq = m[11]
#                
#        X.append(b)
#        Y.append(freq)
#        
#    plt.plot(X, Y, label=l, marker='o',linewidth=4.0)
#    
#    
#plt.legend(prop={'size': 15})
#plt.title("Fréquence d'échange avec le DM pour différents budget alloué", fontweight="bold",size=20,)
#fig.savefig("Freq_Interaction_Budget.png")
#
#plt.show()
#
#
#






###############  2Learning apprentissage bInf bSup MOYENNE

#file_plot_static = [path+"/A/100/AVG_K_30.evalPARETO"]#, path+"/C/100/AVG_K_30.evalPARETO"]
#file_plot_dyn = [path+"/A/100/AVG_K_10.evalRAPPORT_DYN_INFO_60"]#, path+"/C/100/AVG_K_10.evalRAPPORT_DYN_INFO_60"]
#
#for i,l in zip(range(len(file_plot_static)), labels):
#    
#    fig = plt.figure(figsize=(13,10))
#    plt.minorticks_on()
#    plt.grid(which='both')
#    plt.grid(which='minor', alpha=0.4, linestyle='-.')
#    
#    plt.xlabel("Budget #sol évalué",size=15, fontweight="bold")
#    plt.xlim(0,4000)
#    plt.ylabel("log D1",size=15, fontweight="bold")
#
#    file_static,file_dyn = file_plot_static[i],file_plot_dyn[i]
#    
#    Bigreader = list(csv.DictReader(open(file_static, newline=''), delimiter = ','))
#    Smallreader = list(csv.DictReader(open(file_dyn, newline=''), delimiter = ','))
#    
#    Xbudget_f1 = set()
#    Xbudget_f2 = set()
#    for r in Bigreader :
#        Xbudget_f1.add(int(r['Budget']))
#        
#    Xbudget_f1 = list(Xbudget_f1)
#    Xbudget_f1.sort()
#    
#    for r in Smallreader :
#        Xbudget_f2.add(int(r['Budget']))
#    
#    Xbudget_f2 = list(Xbudget_f2)
#    Xbudget_f2.sort()
#
#    Ymin = list()
#    Ymax = list()
#    Ydyn = list()
#    
#    for b in Xbudget_f1 : #[60,540,1220,6020] : #Xbudget_f1  :
#        minus = -1
#        maxus = -1
#
#        for row in Bigreader:
#            if int(row['Budget']) == b  :
#                avg_min = float(row['AVG_dist'])
#                if (avg_min < minus) or (minus == -1) :
#                    minus = avg_min
#                if (avg_min > maxus) or (maxus == -1) :
#                    maxus = avg_min
#            
#        Ymin.append(np.log(minus))
#        Ymax.append(np.log(maxus))
#        
#    for b in Xbudget_f2 : #[60,540,1220,6020] : #[50,500,800,6020] : #Xbudget_f2  :
#
#        for row in Smallreader : 
#            if int(row['Budget']) == b  :
#                Ydyn.append(np.log(float(row['AVG_dist'])))
#        
#    
#        
#    if i == 0 :
#        plt.plot(Xbudget_f1,Ymin,c="blue",label="Best approximation",marker='.',linewidth=2.0)
#        plt.plot(Xbudget_f1,Ymax,c="red",label="Worst approximation",marker='.',linewidth=2.0)
#        plt.plot(Xbudget_f2,Ydyn,c="green",label="$PLS_{2L}$",marker='.',linewidth=2.0)
#    else :
#        plt.plot(Xbudget_f1,Ymin,c="blue",marker='.',linewidth=2.0)
#        plt.plot(Xbudget_f1,Ymax,c="red",marker='.',linewidth=2.0)
#        plt.plot(Xbudget_f2,Ydyn,c="green",marker='.',linewidth=2.0)
#        
#    plt.grid()
#    plt.legend(prop={'size': 15})
#    plt.title("Log Moyenne de D1 retourné par $PLS_{2L}$ contre la meilleure et pire approximation avec l'approche statique \n Instances  "+l ,fontsize=15,fontweight="bold")
#    fig.savefig("Compare_"+l+"_2L_MOY.png", dpi=fig.dpi)
#    plt.show()




############### 2L apprentissage bInf bSup MEDIANE

#file_plot_static = [path+"/A/100/K_30.evalPARETO"]#, path+"/C/100/K_30.evalPARETO"]
#file_plot_dyn = [path+"/A/100/K_10.evalRAPPORT_MULTIPLE_PARAM"]#, path+"/C/100/K_10.evalRAPPORT_DYN_MULTIPLE_PARAM"]
#for i,l in zip(range(len(file_plot_static)), labels):
#    
#    fig = plt.figure(figsize=(13,10))
#    plt.minorticks_on()
#    plt.grid(which='both')
#    plt.grid(which='minor', alpha=0.4, linestyle='-.')
#    
#    plt.xlabel("Budget #sol évalué",size=15, fontweight="bold")
#    plt.xlim(0,3500)
#    plt.ylabel("Médiane D1",size=15, fontweight="bold")
#
#    file_static,file_dyn = file_plot_static[i],file_plot_dyn[i]
#    
#    Bigreader = list(csv.DictReader(open(file_static, newline=''), delimiter = ','))
#    Smallreader = list(csv.DictReader(open(file_dyn, newline=''), delimiter = ','))
#    
#    Xbudget_f1 = set()
#    Xbudget_f2 = set()
#    for r in Bigreader :
#        Xbudget_f1.add(int(r['Budget']))
#        
#    Xbudget_f1 = list(Xbudget_f1)
#    Xbudget_f1.sort()
#    
#    for r in Smallreader :
#        Xbudget_f2.add(int(r['Budget']))
#    
#    Xbudget_f2 = list(Xbudget_f2)
#    Xbudget_f2.sort()
#
#    Ymin = list()
#    Ydyn = list()
#
#    for b in Xbudget_f1 : #[60,540,1220,6020] : #Xbudget_f1  :
#        Ytmp = list()
#
#        for row in Bigreader:
#            if int(row['Budget']) == b  :
#                Ytmp.append(float(row['AVG_dist']))
#
#        Ytmp.sort()
#        Ymin.append(np.median(Ytmp))
#        
#    for b in Xbudget_f2 : #[60,540,1220,6020] : #[50,500,800,6020] : #Xbudget_f2  :
#        Ytmp = list()
#
#        for row in Smallreader : 
#            if int(row['Budget']) == b  :
#                Ytmp.append((float(row['AVG_dist'])))
#        
#        Ytmp.sort()
#        Ydyn.append(np.median(Ytmp))
#    
#        
#    if i == 0 :
#        plt.plot(Xbudget_f1,Ymin,c="blue",label="static method",marker='.',linewidth=2.0)
#        plt.plot(Xbudget_f2,Ydyn,c="green",label="$PLS_{2L}$",marker='.',linewidth=2.0)
#    else :
#        plt.plot(Xbudget_f1,Ymin,c="blue",marker='.',linewidth=2.0)
#        plt.plot(Xbudget_f2,Ydyn,c="green",marker='.',linewidth=2.0)
#        
#    plt.grid()
#    plt.legend(prop={'size': 15})
#    plt.title("Valeur médiane de D1 par $PLS_{2L}$ et de l'approche statique \n Instances  "+l ,fontsize=15,fontweight="bold")
#    fig.savefig("Compare_"+l+"_2L_MED.png", dpi=fig.dpi)
#    plt.show()




