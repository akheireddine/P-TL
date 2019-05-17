

CPLEXDIR = $(PATHTUTOMIP)/cplex-12.7.1/cplex
CONCERTDIR = $(PATHTUTOMIP)/cplex-12.7.1/concert


SYSTEM     = x86-64_linux
LIBFORMAT = static_pic

# ---------------------------------------------------------------------
# Compiler selection 
# ---------------------------------------------------------------------

CCC = g++ -O0 -g -Wall


# ---------------------------------------------------------------------
# Compiler options 
# ---------------------------------------------------------------------

CCOPT = -m64 -O -fPIC -fno-strict-aliasing -fexceptions -DNDEBUG -DIL_STD

# ---------------------------------------------------------------------
# Link options and libraries
# ---------------------------------------------------------------------

CPLEXBINDIR = $(CPLEXDIR)/bin/$(BINDIST)
CPLEXLIBDIR   = $(CPLEXDIR)/lib/$(SYSTEM)/$(LIBFORMAT)
CONCERTLIBDIR = $(CONCERTDIR)/lib/$(SYSTEM)/$(LIBFORMAT)

CCLNDIRS = -L$(CPLEXLIBDIR) -L$(CONCERTLIBDIR)

CONCERTINCDIR = $(CONCERTDIR)/include
CPLEXINCDIR   = $(CPLEXDIR)/include

CCLNFLAGS = -lconcert -lilocplex -lcplex -lm -lpthread -ldl -lboost_iostreams -lboost_system -lboost_filesystem

CCFLAGS = $(CCOPT) -I$(CPLEXINCDIR) -I$(CONCERTINCDIR) 

#CCFLAGS = $(CCOPT)




# ---------------------------------------------------------------------
# Your part
# ---------------------------------------------------------------------



all: WS_KNAPSACK


Tools.o: Tools.cpp
	$(CCC) $(CCFLAGS) -c Tools.cpp 

Instance_Generator.o: Instance_Generator.cpp
	$(CCC) $(CCFLAGS) -c Instance_Generator.cpp 
	
Gnuplotter.o: Gnuplotter.cpp
	$(CCC) $(CCFLAGS) -c Gnuplotter.cpp

AlternativeKnapsack.o: AlternativeKnapsack.cpp 
	$(CCC) $(CCFLAGS) -o AlternativeKnapsack.o  -c AlternativeKnapsack.cpp 
	
MainKnapsack.o: MainKnapsack.cpp Tools.h
	$(CCC) $(CCFLAGS) $(CCLNDIRS) -o MainKnapsack.o -c MainKnapsack.cpp 
	
Evaluator.o: Evaluator.cpp
	$(CCC) $(CCFLAGS) -c Evaluator.cpp 

MainClass.o: MainClass.cpp MainKnapsack.h Gnuplotter.h
	$(CCC) $(CCFLAGS) -o MainClass.o -c MainClass.cpp 


WS_KNAPSACK: Tools.o Instance_Generator.o Gnuplotter.o MainKnapsack.o AlternativeKnapsack.o Evaluator.o MainClass.o 
	$(CCC) $(CCFLAGS) $(CCLNDIRS) -o WS_KNAPSACK Tools.o Instance_Generator.o Gnuplotter.o  MainKnapsack.o AlternativeKnapsack.o  Evaluator.o MainClass.o $(CCLNFLAGS)


clean:
	rm -f *.o WS_KNAPSACK
