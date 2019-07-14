
import csv
import matplotlib.pyplot as plt




p = "2"
type_inst = "A"
taille="100"

filename = "./Data/Evaluation"+p+"/"+type_inst+"/"+taille+"/K_30_normalize.eval"

filename_pred = "./Data/Evaluation"+p+"/"+type_inst+"/"+taille+"/predicted_value.eval"

Bigreader = list(csv.DictReader(open(filename, newline=''), delimiter = ','))
Smallreader = list(csv.DictReader(open(filename_pred, newline=''), delimiter = ','))


Budget = [0.005, 0.01, 0.0125, 0.015, 0.02, 0.025, 0.03, 0.035, 0.04, 0.045, 0.05, 0.06, 0.07, 0.085, 0.095, 0.11, 0.12, 0.135, 0.145, 0.16, 0.17, 0.185,
			0.195, 0.205, 0.21, 0.22, 0.235, 0.245, 0.255, 0.305, 0.355, 0.455, 0.505, 0.605, 0.705, 0.8, 0.855, 0.955, 1.0]

Information = [1.00]#, 0.89, 0.78, 0.67, 0.56, 0.44, 0.33, 0.22, 0.17, 0.11, 0.09, 0.04, 0.01, 0]

N = [0, 0.11, 0.22, 0.33, 0.44, 0.55, 0.66, 0.77, 0.88, 0.99 ]

PopSize = [ 0.20]#, 0.08, 0.10, 0.15, 0.20, 0.31, 0.41, 0.51, 0.61, 0.82, 1.02]

div = 0

epsi = 0
def compare_predicted_expected_value():       
    Bigreader = list(csv.DictReader(open(filename, newline=''), delimiter = ','))
    Smallreader = list(csv.DictReader(open(filename_pred, newline=''), delimiter = ','))
    
    fig = plt.figure(figsize=(10,8))

    for i in N :
        for s in PopSize : 
            for info in Information : 
                X = list()
                Y = list()
                Xpred = list()
                Ypred = list()
                for b in Budget :
                    
                    for row in Bigreader : 
                        if int(row['Diversification']) == div  and (float(row['Info']) == info ) and ( float(row['Budget']) == b) and float(row['Instance']) == i and float(row['PopSize']) == s :
                            Y.append(float(row['AVG_dist']))
                            X.append(b)
                    
        
                    for row in Smallreader : 
                        if int(row['Diversification']) == div  and (float(row['Info']) == info ) and ( float(row['Budget']) == b) and float(row['Instance']) == i and float(row['PopSize']) == s :
                            Ypred.append(float(row['AVG_dist']))
                            Xpred.append(b)
    
    
                plt.plot(X,Y,c="green",label="Expected AVG_min")
                plt.plot(Xpred,Ypred,c="red",label="Predicted AVG_min")
                
    plt.grid()
    plt.legend()
    plt.title("Predicted AVG_min "+type_inst+taille+" (T"+str(i*9)+") Diversification :"+str(div) )
#        fig.savefig("PredictedD1"+type_inst+taille+"_T"+str(i*9)+"_I"+str(info*90)+"_D"+str(div)+".png", dpi=fig.dpi)
    fig.savefig("PredictedD1"+type_inst+taille+"_I"+str(info*90)+"_D"+str(div)+".png", dpi=fig.dpi)
    plt.close()
            
            
            
            
compare_predicted_expected_value()
            
            
            
            
            
            
            
            