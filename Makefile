

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

#Graph_AK.o: ../Graph_AK.cpp ../Graph_AK.h
#	$(CCC) -c $(CCFLAGS) $(CCLNDIRS) -c ../Graph_AK.cpp -o ../Graph_AK.o
#
#
#meta-heuristic-VRP.o : meta-heuristic-VRP.cpp 
#	$(CCC) -c $(CCFLAGS) $(CCLNDIRS)  -c meta-heuristic-VRP.cpp
#	
#META_HEURISTIC_RESOLUTION : meta-heuristic-VRP.o Graph_AK.o 
#	$(CCC) $(CCFLAGS) $(CCLNDIRS) ../Graph_AK.o meta-heuristic-VRP.o  -o META_HEURISTIC_RESOLUTION $(CCLNFLAGS)


clean:
	rm -f *.o WS_Knapsack
