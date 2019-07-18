
import csv
import matplotlib.pyplot as plt




p = "2"
type_inst = "A"
taille="100"

filename = "./Data/Evaluation"+p+"/"+type_inst+"/"+taille+"/K_30_normalize.eval"

filename_pred = "./Data/Evaluation"+p+"/"+type_inst+"/"+taille+"/predicted_value.eval"

Bigreader = list(csv.DictReader(open(filename, newline=''), delimiter = ','))
Smallreader = list(csv.DictReader(open(filename_pred, newline=''), delimiter = ','))


Budget = [20, 40, 50, 60, 80, 100, 120, 140, 160, 180, 200,220, 240, 280, 340, 380, 420,440, 480, 540, 580, 640, 680, 740, 780, 820, 840, 880
          , 980, 1020, 1220, 1420, 1820, 2020, 2420, 2820, 3200, 3420, 3820, 4020]

Information = [90, 80, 70, 60, 50, 41, 40.6012,40, 30, 28.1257, 20, 15, 12, 11.5757, 10, 8.01411, 5, 4.2937,3.73078, 1, 0]

N = list(range(0,10))

PopSize = [ 2, 8, 10, 15, 20, 30, 40, 50, 60, 80, 100 ]

div = 1



def normalize_parameters() :
    
    
    Budgets = [ round((b*1.0 - min(Budget))/(max(Budget) - min(Budget)),3) for b in Budget]
    
    Informations = [ round((inf*1.0 - min(Information))/(max(Information) - min(Information)),3) for inf in Information]
    
    
    N_inst = [ round((n*1.0 - min(N))/(max(N) - min(N)),3) for n in N]
    
    
    PopulationSize = [ round((p*1.0 - min(PopSize)) /( max(PopSize) - min(PopSize)),3) for p in PopSize]

    return Budgets, Informations, N_inst, PopulationSize



Budget_norm, Information_norm, N_norm, PopSize_norm = normalize_parameters()


filename_in = "./Data/Evaluation"+p+"/"+type_inst+"/"+taille+"/K_30._4.eval"
filename_out = "./Data/Evaluation"+p+"/"+type_inst+"/"+taille+"/INDIVIDUAL/K_30_normalize_4.eval"

def normalize_eval_file(filename_eval_in, filename_eval_out):
    
    csvdic =  list(csv.DictReader(open(filename_eval_in, newline=''), delimiter = ','))
    
    coef_D1 = {float(i): list() for i in N }
    coef_D2 = {float(i): list() for i in N }
    coef_D3 = {float(i): list() for i in N }

    for r in csvdic:
        int_inst = float(r["Instance"])
        coef_D1[int_inst].append(float(r["AVG_dist"])) 
        coef_D2[int_inst].append(float(r["MaxMin"])) 
        coef_D3[int_inst].append(float(r["PR"])) 

    fwrite = open(filename_eval_out,"w")
    fwrite.write("Type,Size,Instance,Budget,PopSize,Info,nb_evaluation,AVG_dist,MaxMin,PR,Diversification\n")

    for row in csvdic : 
        inst_int = float(row["Instance"])

        coef1 = (max(coef_D1[inst_int]) - min(coef_D1[inst_int]) )
        coef2 = (max(coef_D2[inst_int]) - min(coef_D2[inst_int]) )
        coef3 = (max(coef_D3[inst_int]) - min(coef_D3[inst_int]) )
        
        
        inst = str(N_norm[N.index(int(inst_int))])
        budget = str(Budget_norm[Budget.index(int(float(row["Budget"])))])
        pop = str(PopSize_norm[PopSize.index(int(float(row["PopSize"])))])
        info = str(Information_norm[Information.index(float(row["Info"]))])
        
        
        avg = round( (float(row["AVG_dist"]) - min(coef_D1[inst_int]))/coef1*1.0,3)
        maxmin = round( (float(row["MaxMin"]) - min(coef_D2[inst_int]))/coef2*1.0,3)
        pr = round( (float(row["PR"]) - min(coef_D3[inst_int]))/coef3*1.0,3)
        
        fwrite.write(row["Type"]+","+row["Size"]+","+inst+","+budget+","+pop+","+info+",0,"+str(avg) +","+str(maxmin)
        +","+str(pr)+","+row["Diversification"]+"\n")
        

    fwrite.close()

####################################################################################

normalize_eval_file(filename_in,filename_out)

####################################################################################


def F_prediction_A100(siz, budg, inf, div, inst) :

    avg = 0.062 + (-0.0162)* inst +  (-0.2201)* budg + 0.1379 * siz + 0.0283 * inf + 0.1225 * div

    maxmin = 0.0835 + (-0.0319) * inst + (-0.2109) * budg + 0.1092 * siz + 0.2197 * inf + 0.1125 * div

    pr = 0.0145 + (-0.089) * inst + 0.2857 * budg + 0.0533 * siz + (-0.0205) * inf + 0.1441 * div


    return round(avg,3),round(maxmin,3),round(pr,3)


def ML_LinearRegression(type_inst, taille, p_criteria, filename_o):
    
    id_type_inst = "0"
    
    if type_inst == "C" :
        type_inst = "1"


    fic_write = open(filename_o,"w");
    fic_write.write("Type,Size,Instance,Budget,PopSize,Info,nb_evaluation,AVG_dist,MaxMin,PR,Diversification\n")

    for  i in N_norm :
        for s in PopSize_norm:
            for b in Budget_norm :
                for info in Information_norm :
                    for d in [0,1] :
                        predicted_avg_min,MaxMmin,PR = F_prediction_A100(s, b, info, d, i)
                        
                        fic_write.write(id_type_inst+","+taille+","+str(i)+","+str(b)+","+str(s)+","
                                        +str(info)+",0,"+str(predicted_avg_min)+","+str(MaxMmin)+","
                                        +str(PR)+","+str(d)+"\n")

    fic_write.close()
filename_outter = "./Data/Evaluation"+p+"/"+type_inst+"/"+taille+"/predicted_value.eval"

####################################################################################

#ML_LinearRegression("A","100","2",filename_outter)

####################################################################################


""
"               COMPARISON"
""


PopSizeIndex = [0, 1, 4,8, 10]

InformationIndex = [0,6,9,13,15,17,18,20]

div = 0

def compare_predicted_expected_value():       
    Bigreader = list(csv.DictReader(open(filename, newline=''), delimiter = ','))
    Smallreader = list(csv.DictReader(open(filename_pred, newline=''), delimiter = ','))
    
    for si in PopSizeIndex : 
        s = PopSize_norm[si]
        fig = plt.figure(figsize=(15,12))
        fig.suptitle("Prediction of Average min distance from optimal front "+type_inst+taille+" (Varying uncertainty, Populatin size = "
                                                                +str(PopSize[si])+" ,Diversification :"+str(div)+")" , fontsize=16)
        
        fig.text(0.5, 0.04, 'Budget (normalized)', ha='center', fontsize=10)
        fig.text(0.04, 0.5, 'Average minimal indicator (normalized)', va='center', rotation='vertical', fontsize=10)
        fig.tight_layout()
        
        for ii,inf_index in zip(InformationIndex,range(0,len(InformationIndex))) : 
            info = Information_norm[ii]
            for i in N_norm :
                X = list()
                Y = list()
                Xpred = list()
                Ypred = list()
                for b in Budget_norm :
                    
                    for row in Bigreader : 
                        if int(float(row['Diversification'])) == div  and (float(row['Info']) == info ) and ( float(row['Budget']) == b) and float(row['Instance']) == i and float(row['PopSize']) == s :
                            Y.append(float(row['AVG_dist']))
                            X.append(b)
        
                    for row in Smallreader : 
                        if int(float(row['Diversification'])) == div  and (float(row['Info']) == info ) and ( float(row['Budget']) == b) and float(row['Instance']) == i and float(row['PopSize']) == s :
                            Ypred.append(float(row['AVG_dist']))
                            Xpred.append(b)
    
    
                ax = fig.add_subplot("33"+str(inf_index+1))
                ax.legend()

                if i == 0 :
                    ax.plot(X,Y,c="green",label="Expected AVG_min  ("+str(Information[ii])+"°)")
                    ax.plot(Xpred,Ypred,c="red",label="Predicted AVG_min  ("+str(Information[ii])+"°)")
                else:
                    ax.plot(X,Y,c="green")
                    ax.plot(Xpred,Ypred,c="red")

        fig.savefig("PredictedD1"+type_inst+taille+"_PopS"+str(PopSize[si])+"_D"+str(div)+".png", dpi=fig.dpi*5)
            
        
####################################################################################

#compare_predicted_expected_value()

####################################################################################




BudgetIndex = [0,3,5,7, 11,16,19,25,30,32,33,35,38]
PopSizeIndex = [0, 1, 4,8, 10]

InformationIndex = [0,6,9,13,15,17,18,20]

div = 1

def Difference_predicted_expected_valueD1():       
    Bigreader = list(csv.DictReader(open(filename, newline=''), delimiter = ','))
    Smallreader = list(csv.DictReader(open(filename_pred, newline=''), delimiter = ','))
    
    colors = ["red","blue","green","orange","pink","magenta","brown","black","yellow"]
    

    for si in PopSizeIndex : 
        s = PopSize_norm[si]
        fig = plt.figure(figsize=(13,10))
        fig.suptitle("Deviation of Average min distance "+type_inst+taille+" (Varying uncertainty, Populatin size = "
                                                                +str(PopSize[si])+" ,Diversification :"+str(div)+")" , fontsize=16)

        fig.text(0.5, 0.04, 'Budget (normalized)', ha='center', fontsize=10)
        fig.text(0.04, 0.5, 'Average minimal indicator (normalized)', va='center', rotation='vertical', fontsize=10)
        fig.tight_layout()

        for ii,c in zip(InformationIndex,range(0,len(InformationIndex))) : 
            info = Information_norm[ii]
            for i in N_norm :

                X = list()
                Y = list()
                Xpred = list()
                Ypred = list()
                for bi in BudgetIndex :
                    b = Budget_norm[bi]
                    for row in Bigreader : 
                        if int(row['Diversification']) == div  and (float(row['Info']) == info ) and ( float(row['Budget']) == b) and float(row['Instance']) == i and float(row['PopSize']) == s :
                            Y.append(float(row['AVG_dist']))
                            X.append(b)
                    
        
                    for row in Smallreader : 
                        if int(row['Diversification']) == div  and (float(row['Info']) == info ) and ( float(row['Budget']) == b) and float(row['Instance']) == i and float(row['PopSize']) == s :
                            Ypred.append(float(row['AVG_dist']))
                            Xpred.append(b)
                

                ax = fig.add_subplot("33"+str(c+1))
                
                Yplot = [ abs(Y[i] - Ypred[i]) for i in range(0,len(Y))]
                if i == 0 :
                    ax.plot(X, Yplot,c=colors[c%len(colors)], label=Information[ii])
                else:
                    ax.plot(X, Yplot,c=colors[c%len(colors)])
                    
                ax.legend()


        fig.savefig("DeviationD1"+type_inst+taille+"_PopS"+str(PopSize[si])+"_D"+str(div)+".png", dpi=fig.dpi*5)
    
    
####################################################################################
        
#Difference_predicted_expected_valueD1()

####################################################################################

            
def Difference_predicted_expected_valueD2():       
    Bigreader = list(csv.DictReader(open(filename, newline=''), delimiter = ','))
    Smallreader = list(csv.DictReader(open(filename_pred, newline=''), delimiter = ','))
    

    colors = ["red","blue","green","orange","pink","magenta","brown","black","yellow"]
    

    for si in PopSizeIndex : 
        s = PopSize_norm[si]
        fig = plt.figure(figsize=(13,10))
        fig.suptitle("Deviation of MaxMin distance "+type_inst+taille+" (Varying uncertainty, Populatin size = "
                                                                +str(PopSize[si])+" ,Diversification :"+str(div)+")" , fontsize=16)

        fig.text(0.5, 0.04, 'Budget (normalized)', ha='center', fontsize=10)
        fig.text(0.04, 0.5, 'MaxMin indicator (normalized)', va='center', rotation='vertical', fontsize=10)
        fig.tight_layout()

        for ii,c in zip(InformationIndex,range(0,len(InformationIndex))) : 
            info = Information_norm[ii]
            for i in N_norm :

                X = list()
                Y = list()
                Xpred = list()
                Ypred = list()
                for bi in BudgetIndex :
                    b = Budget_norm[bi]
                    for row in Bigreader : 
                        if int(row['Diversification']) == div  and (float(row['Info']) == info ) and ( float(row['Budget']) == b) and float(row['Instance']) == i and float(row['PopSize']) == s :
                            Y.append(float(row['MaxMin']))
                            X.append(b)
                    
        
                    for row in Smallreader : 
                        if int(row['Diversification']) == div  and (float(row['Info']) == info ) and ( float(row['Budget']) == b) and float(row['Instance']) == i and float(row['PopSize']) == s :
                            Ypred.append(float(row['MaxMin']))
                            Xpred.append(b)
                

                ax = fig.add_subplot("33"+str(c+1))
                
                Yplot = [ abs(Y[i] - Ypred[i]) for i in range(0,len(Y))]
                if i == 0 :
                    ax.plot(X, Yplot,c=colors[c%len(colors)], label=Information[ii])
                else:
                    ax.plot(X, Yplot,c=colors[c%len(colors)])
                    
                ax.legend()


        fig.savefig("DeviationD2"+type_inst+taille+"_PopS"+str(PopSize[si])+"_D"+str(div)+".png", dpi=fig.dpi*5)
    
     
            
####################################################################################
        
#Difference_predicted_expected_valueD2()

####################################################################################

                    
def Difference_predicted_expected_valueD3():       
    Bigreader = list(csv.DictReader(open(filename, newline=''), delimiter = ','))
    Smallreader = list(csv.DictReader(open(filename_pred, newline=''), delimiter = ','))
    

    colors = ["red","blue","green","orange","pink","magenta","brown","black","yellow"]
    

    for si in PopSizeIndex : 
        s = PopSize_norm[si]
        fig = plt.figure(figsize=(13,10))
        fig.suptitle("Deviation of PR  "+type_inst+taille+" (Varying uncertainty, Populatin size = "
                                                                +str(PopSize[si])+" ,Diversification :"+str(div)+")" , fontsize=16)

        fig.text(0.5, 0.04, 'Budget (normalized)', ha='center', fontsize=10)
        fig.text(0.04, 0.5, 'Proportion of optimal solutions indicator (normalized)', va='center', rotation='vertical', fontsize=10)
        fig.tight_layout()

        for ii,c in zip(InformationIndex,range(0,len(InformationIndex))) : 
            info = Information_norm[ii]
            for i in N_norm :

                X = list()
                Y = list()
                Xpred = list()
                Ypred = list()
                for bi in BudgetIndex :
                    b = Budget_norm[bi]
                    for row in Bigreader : 
                        if int(row['Diversification']) == div  and (float(row['Info']) == info ) and ( float(row['Budget']) == b) and float(row['Instance']) == i and float(row['PopSize']) == s :
                            Y.append(float(row['PR']))
                            X.append(b)
                    
        
                    for row in Smallreader : 
                        if int(row['Diversification']) == div  and (float(row['Info']) == info ) and ( float(row['Budget']) == b) and float(row['Instance']) == i and float(row['PopSize']) == s :
                            Ypred.append(float(row['PR']))
                            Xpred.append(b)
                

                ax = fig.add_subplot("33"+str(c+1))
                
                Yplot = [ abs(Y[i] - Ypred[i]) for i in range(0,len(Y))]
                if i == 0 :
                    ax.plot(X, Yplot,c=colors[c%len(colors)], label=Information[ii])
                else:
                    ax.plot(X, Yplot,c=colors[c%len(colors)])
                    
                ax.legend()


        fig.savefig("DeviationD3"+type_inst+taille+"_PopS"+str(PopSize[si])+"_D"+str(div)+".png", dpi=fig.dpi*5)
    
     
            
####################################################################################
        
#Difference_predicted_expected_valueD3()

####################################################################################

              
                  
            
            