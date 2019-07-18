
import csv
import matplotlib.pyplot as plt



p = "2"
type_inst = "A"
taille="100"

div = 0
Information = [90]
Informations_in = [90, 40.6012,28.1257, 11.5757]

N = 2
Budget = [20,60,100,140,220,420,540,820,1220,1820,2020,3200,4020]
filename = "./Data/Evaluation"+p+"/"+type_inst+"/"+taille+"/K_30.eval"

filename_dyn = "./Data/Evaluation"+p+"/"+type_inst+"/"+taille+"/K_20.eval12_STRAT"

Bigreader = list(csv.DictReader(open(filename, newline=''), delimiter = ','))
Smallreader = list(csv.DictReader(open(filename_dyn, newline=''), delimiter = ','))

fig = plt.figure(figsize=(13,10))

for i in range(0,N):
    for info in Information : 
        X = list()
        Ymin = list()
        Ymax = list()
        Ydyn = list()
        for b in Budget :
            minus = -1
            maxus = -1

            for row in Bigreader:
#                if int(row['Diversification']) == div  and float(row['Info']) == info and int(row['Budget']) == b and int(row['Instance']) == i :
                if float(row['Info']) == info and int(row['Budget']) == b and int(row['Instance']) == i :
#                if int(row['Diversification']) == div and (float(row['Info']) in Informations_in) and int(row['Budget']) == b and int(row['Instance']) == i :
                    avg_min = float(row['AVG_dist'])
                    if (avg_min < minus) or (minus == -1) :
                        minus = avg_min
                    if (avg_min > maxus) or (maxus == -1) :
                        maxus = avg_min
                

            Ymin.append(minus)
            Ymax.append(maxus)
            X.append(b)
            
            
            for row in Smallreader : 
#                if int(row['Diversification']) == div  and float(row['Info']) == info and int(row['Budget']) == b and int(row['Instance']) == i :
                if float(row['Info']) == info and int(row['Budget']) == b and int(row['Instance']) == i :
#                if int(row['Diversification']) == div and int(row['Budget']) == b and int(row['Instance']) == i :
                    Ydyn.append(float(row['AVG_dist']))
        
        if i == 0 :
            plt.plot(X,Ymin,c="blue",label="Lower bound")
            plt.plot(X,Ymax,c="red",label="Upper bound")
            plt.plot(X,Ydyn,c="green",label="Dynamic method")
        else:
            plt.plot(X,Ymin,c="blue")
            plt.plot(X,Ymax,c="red")
            plt.plot(X,Ydyn,c="green")
        
plt.grid()
plt.legend(prop={'size': 15})
plt.xlabel("Budget",size=15)
plt.ylabel("Average minimum distance Indicator",size=15)
plt.title("Compare a dynamic approach (increase the Population size) and a static one (best/worst approx) \n "+type_inst+taille+", Diversification : "+str(div) ,fontsize=15)
fig.savefig("Bounding_"+type_inst+taille+"_I"+str(info)+"_D01_STRAT12.png", dpi=fig.dpi)
plt.close()
            
                
            
        
##### TWHO METHOD DYNAMIC COMPARISON POPSIZE 
def compare_dynamic_method():       
    Bigreader = list(csv.DictReader(open(filename, newline=''), delimiter = ','))
    Smallreader = list(csv.DictReader(open(filename_dyn, newline=''), delimiter = ','))
    for i in range(0,N):
        for info in Information : 
            X = list()
            Ydyn = list()
            Ydyn2 = list()
            for b in Budget :
                
                for row in Bigreader : 
                    if int(row['Diversification']) == div  and float(row['Info']) == info and int(row['Budget']) == b and int(row['Instance']) == i :
                        Ydyn2.append(float(row['AVG_dist']))
                        X.append(b)
    
                for row in Smallreader : 
                    if int(row['Diversification']) == div  and float(row['Info']) == info and int(row['Budget']) == b and int(row['Instance']) == i :
                        Ydyn.append(float(row['AVG_dist']))
                        
            
            fig = plt.figure(figsize=(10,8))
            plt.plot(X,Ydyn,c="red",label="Dynamic methodDEC")
            plt.plot(X,Ydyn2,c="green",label="Dynamic methodINC")
            
            plt.grid()
            plt.legend()
            plt.title("Dynamically varying the Population size - "+type_inst+taille+" (T"+str(i)+") Diversification :"+str(div) )
            fig.savefig("BoundingDECINC_"+type_inst+taille+"_T"+str(i)+"_I"+str(info)+"_D"+str(div)+".png", dpi=fig.dpi)
            plt.close()