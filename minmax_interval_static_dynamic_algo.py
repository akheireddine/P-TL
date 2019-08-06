
import csv
import matplotlib.pyplot as plt



p = "2"
type_inst = "A"
taille="100"

Information = [40.6012]
Informations_in = [90, 40.6012,28.1257, 11.5757]

N = 10 
Budget = [20,60,100,140,220,420,540,820,1220,1820,2020,3200,4020]
#Budget = [50,500,1000,2000,3000,4000,5000,8000]

filename = "./Data/Evaluation"+p+"/"+type_inst+"/"+taille+"/K_30.eval"

filename_dyn = "./Data/Evaluation"+p+"/"+type_inst+"/"+taille+"/K_15.eval_DYN_PSize_INC1"

Bigreader = list(csv.DictReader(open(filename, newline=''), delimiter = ','))
Smallreader = list(csv.DictReader(open(filename_dyn, newline=''), delimiter = ','))

div = 0

def compare_INF_SUP_BOUND() : 
    fig = plt.figure(figsize=(13,10))

    for i in  range(0,N): #N : #
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
    
        for info in Information : 
            Ymin = list()
            Ymax = list()
            Ydyn = list()
            
            for b in Xbudget_f1 :
                minus = -1
                maxus = -1
    
                for row in Bigreader:
                    if int(row['Diversification']) == div  and float(row['Info']) == info and int(row['Budget']) == b and int(row['Instance']) == i :
#                    if float(row['Info']) == info and int(row['Budget']) == b and int(row['Instance']) == i :
#                    if int(row['Budget']) == b and int(row['Instance']) == i :
#                    if int(row['Diversification']) == div and (float(row['Info']) in Informations_in) and int(row['Budget']) == b and int(row['Instance']) == i :
                        avg_min = float(row['AVG_dist'])
                        if (avg_min < minus) or (minus == -1) :
                            minus = avg_min
                        if (avg_min > maxus) or (maxus == -1) :
                            maxus = avg_min
                    
                Ymin.append(minus)
                Ymax.append(maxus)
                
            for b in Xbudget_f2 :
    
                for row in Smallreader : 
                    if int(row['Diversification']) == div  and float(row['Info']) == info and int(row['Budget']) == b and int(row['Instance']) == i :
#                    if float(row['Info']) == info and int(row['Budget']) == b and int(row['Instance']) == i :
#                    if int(row['Budget']) == b and int(row['Instance']) == i :
    #                if int(row['Diversification']) == div and int(row['Budget']) == b and int(row['Instance']) == i :
                        Ydyn.append(float(row['AVG_dist']))
            
            
            print(Xbudget_f2)
            print("\n__________________________________\n")
            print(Ydyn)
            print("\n=============================================================\n")
            print("=============================================================\n")

            
            if i == 0 :
                plt.plot(Xbudget_f1 + Xbudget_f2[-2:],Ymin+Ymin[-1:]+Ymin[-1:],c="blue",label="Lower bound")
                plt.plot(Xbudget_f1 + Xbudget_f2[-2:],Ymax+Ymax[-1:]+Ymax[-1:],c="red",label="Upper bound")
                plt.plot(Xbudget_f2,Ydyn,c="green",label="Dynamic method")
            else:
                plt.plot(Xbudget_f1 + Xbudget_f2[-2:],Ymin+Ymin[-1:]+Ymin[-1:],c="blue")
                plt.plot(Xbudget_f1 + Xbudget_f2[-2:],Ymax+Ymax[-1:]+Ymax[-1:],c="red")
                plt.plot(Xbudget_f2,Ydyn,c="green")
            
    plt.grid()
    plt.legend(prop={'size': 15})
    plt.xlabel("Budget",size=15)
    plt.ylabel("Average minimum distance Indicator",size=15)
    plt.title("Compare a dynamic approach (INCREASE PopSize Parameter) and a static one (best/worst approx)   \n Information : "+str(info)+"% - "+type_inst+taille ,fontsize=15)
    fig.savefig("Bounding_"+type_inst+taille+"_I"+str(info)+"_POPSize_INC_DIV0.png", dpi=fig.dpi)
    plt.close()
            
            
            
compare_INF_SUP_BOUND()            
            
            
            
            
                
    
    

filename = "./Data/Evaluation"+p+"/"+type_inst+"/"+taille+"/K_20.evalINC"

filename_dyn = "./Data/Evaluation"+p+"/"+type_inst+"/"+taille+"/K_10.eval_ML"         

filename_dyn2 = "./Data/Evaluation"+p+"/"+type_inst+"/"+taille+"/K_20.eval12_STRAT01"


        
##### TWHO METHOD DYNAMIC COMPARISON POPSIZE 
def compare_dynamic_method():       
    Bigreader = list(csv.DictReader(open(filename, newline=''), delimiter = ','))
    Smallreader = list(csv.DictReader(open(filename_dyn, newline=''), delimiter = ','))
    Mediumreader = list(csv.DictReader(open(filename_dyn2, newline=''), delimiter = ','))
    
    fig = plt.figure(figsize=(13,10))

    Xbudget_f1 = set()
    Xbudget_f2 = set()
    Xbudget_f3 = set()

    for r in Bigreader :
        Xbudget_f1.add(int(r['Budget']))
        
    Xbudget_f1 = list(Xbudget_f1)
    Xbudget_f1.sort()
    
    for r in Smallreader :
        Xbudget_f2.add(int(r['Budget']))
    
    Xbudget_f2 = list(Xbudget_f2)
    Xbudget_f2.sort()
    
    for r in Mediumreader :
        Xbudget_f3.add(int(r['Budget']))
    
    Xbudget_f3 = list(Xbudget_f3)
    Xbudget_f3.sort()
            

    for i in N : #range(0,N):
        for info in Information : 
            Ydyn1 = list()
            Ydyn2 = list()
            Ydyn3 = list()
            for b in Xbudget_f1 :
                
                for row in Bigreader : 
                    if float(row['Info']) == info and int(row['Budget']) == b and int(row['Instance']) == i :
                        Ydyn1.append(float(row['AVG_dist']))
    
            for b in Xbudget_f2 :

                for row in Smallreader : 
                    if float(row['Info']) == info and int(row['Budget']) == b and int(row['Instance']) == i :
                        Ydyn2.append(float(row['AVG_dist']))
                        
                        
            for b in Xbudget_f3 :

                for row in Mediumreader : 
                    if float(row['Info']) == info and int(row['Budget']) == b and int(row['Instance']) == i :
                        Ydyn3.append(float(row['AVG_dist']))
                   
            print(Xbudget_f2)
            print("\n__________________________________\n")
            print(Ydyn2)
            print("\n=============================================================\n")
            print("=============================================================\n")

            if i == 0:
                plt.plot(Xbudget_f1  + Xbudget_f2[-1:],Ydyn1 + Ydyn1[-1:],c="green",label="method 1")
                plt.plot(Xbudget_f2,Ydyn2,c="red",label="method 2")
                plt.plot(Xbudget_f3  + Xbudget_f2[-1:],Ydyn3 + Ydyn3[-1:],c="blue",label="method 3")
                
            else : 
                plt.plot(Xbudget_f1  + Xbudget_f2[-1:],Ydyn1 + Ydyn1[-1:],c="green")
                plt.plot(Xbudget_f2,Ydyn2,c="red")
                plt.plot(Xbudget_f3  + Xbudget_f2[-1:],Ydyn3 + Ydyn3[-1:],c="blue")

            
    plt.grid()
    plt.legend()
    plt.xlabel("Budget",size=15)
    plt.ylabel("Average minimum distance Indicator",size=15)
    plt.title("Dynamically varying the Parameters  - "+type_inst+taille+" using different approaches"  ,fontsize=15)
    fig.savefig("Compare_INC_ML_STRAT1201_"+type_inst+taille+"_I"+str(info)+".png", dpi=fig.dpi)
    plt.close()
    
    
    



#compare_dynamic_method()