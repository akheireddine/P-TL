

SYSTEM     = x86-64_linux
LIBFORMAT  = static_pic


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

MainKnapsack.o: MainKnapsack.cpp MainKnapsack.h
	$(CCC) -c $(CCFLAGS) $(CCLNDIRS) -c MainKnapsack.cpp -o MainKnapsack.o


#MainClass.o : MainClass.cpp 
#	$(CCC) -c $(CCFLAGS) $(CCLNDIRS) -c MainClass.cpp
	
#WS_KNAPSACK : MainClass.o MainKnapsack.o 
#	$(CCC) $(CCFLAGS) $(CCLNDIRS) MainKnapsack.o MainClass.o -o WS_KNAPSACK $(CCLNFLAGS)


WS_KNAPSACK : MainKnapsack.o
	$(CCC) $(CCFLAGS) $(CCLNDIRS) MainKnapsack.o -o WS_KNAPSACK $(CCLNFLAGS)

clean:
	rm -f *.o WS_Knapsack
