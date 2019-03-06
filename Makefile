


# ---------------------------------------------------------------------
# Compiler selection 
# ---------------------------------------------------------------------

CCC = g++ -O0 


# ---------------------------------------------------------------------
# Compiler options 
# ---------------------------------------------------------------------

CCOPT = -m64 -O -fPIC -fno-strict-aliasing -fexceptions -DNDEBUG -DIL_STD

# ---------------------------------------------------------------------
# Link options and libraries
# ---------------------------------------------------------------------


CCLNFLAGS = -lm -lpthread -ldl

CCFLAGS = $(CCOPT)




# ---------------------------------------------------------------------
# Your part
# ---------------------------------------------------------------------



all: WS_KNAPSACK



WS_KNAPSACK: MainKnapsack.o AlternativeKnapsack.o MainClass.o
	$(CCC) $(CCFLAGS) $(CCLNFLAGS) -o WS_KNAPSACK MainKnapsack.o AlternativeKnapsack.o MainClass.o


AlternativeKnapsack.o: AlternativeKnapsack.cpp
	$(CCC) $(CCFLAGS) -o AlternativeKnapsack.o -c AlternativeKnapsack.cpp 
	
MainKnapsack.o: MainKnapsack.cpp
	$(CCC) $(CCFLAGS) -o MainKnapsack.o -c MainKnapsack.cpp 

MainClass.o: MainClass.cpp MainKnapsack.h
	$(CCC) $(CCFLAGS) -o MainClass.o -c MainClass.cpp 



clean:
	rm -f *.o WS_KNAPSACK
