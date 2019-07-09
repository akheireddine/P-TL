"NORMALIZATION"





import csv

type_inst = "A"
taille = "100"
p = "2"


filename = "./Data/Evaluation"+p+"/"+type_inst+"/"+taille+"/K_30.eval"

with open(filename, newline='') as csvfile:
    reader = csv.DictReader(csvfile)
    min_d1 = -1
    max_d1 = -1
    for i in range(0,N):
        for row in reader:
