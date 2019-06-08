

#include "MainKnapsack.h"
#include <time.h>
#include "Tools.h"
#include "Evaluator.h"
#include "Gnuplotter.h"
#include "Instance_Generator.h"






float Ta = 500;

float Temperature = 1500;

int INFO = 0;

int UB_Size;

list<set<int>> init_population;

int GRAIN;



map<string, set<string> > common_neighbors;


shared_ptr< Evaluator >  eval_ks;
