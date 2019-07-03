import numpy as np
import sys


def get_conflicting_variables(n_variables):
    z = np.random.lognormal(size=n_variables)
    
    z = (1000 - 10) * z  + 10

    A = np.random.rand(n_variables,n_variables)
    
    A = A.dot(A.T)

    L = np.tril(A)

    x = L.dot(z)
    
    s = ""
    for i in x : 
        s += str(i) + " "

        
    
    return s



for arg in sys.argv:
    print (arg)
