import os



types = ["A"]
taille = ["100"]

UB = ["2","8","20","60","100"]
info = ["0","1","2","3","4","5","6","7"]

path = "./Data/Population/"
methodes = ["MOLS_PSize"]#,"MOLS_PSzie_DIV/OS","MOLS_PSize_DIV/RS"]

for t in types:
    for ta in taille:
        for i in range(0,10):
            for m in methodes:
                for u in UB:
                    for step in info:
                        filename = path+t+"/"+ta+"/T"+str(i)+"/"+m+"/"+u+"/"+step+"/"
                        for fic in os.listdir(filename):
#                            print filename+fic
                            f = open(filename+fic, "r")
                            lines =  f.readlines( )
                            first = True
                            for id_line,l in zip(range(0,len(lines)),lines):
                                split_line = l.split()
                                if len(split_line) > 1 and split_line[3] == '0'  and first :
                                    first = False
                                
                                elif len(split_line) > 1 and split_line[3] == '0' and first == False:
                                    with open(filename+fic, "w") as f_write :
                                        f_write.writelines(lines[0:id_line -1 ])
                                    break
                                
                            
                                