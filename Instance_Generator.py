import numpy as np
import sys


def get_conflicting_variables(p_criteria, nb_replication):
    s = ""

    for i in range(0,nb_replication):
    
        z = np.random.lognormal(size=p_criteria)
        
        z = (1000 - 10) * z  + 10
    
        A = np.random.rand(p_criteria,p_criteria)
        
        A = A.dot(A.T)
    
        L = np.tril(A)
    
        x = L.dot(z)
        
        for i in x : 
            s += str(i) + " "
        
        s += "\n"
    
    return s


if( len(sys.argv) > 2 ):
    p_criteria = int(sys.argv[1])
    replication = int(sys.argv[2])
    print( get_conflicting_variables( p_criteria , replication ) )
else:
    print("error")