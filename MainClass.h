

#include "MainKnapsack.h"
#include <time.h>
#include "Tools.h"
#include "Evaluator.h"
#include "Gnuplotter.h"
#include "Instance_Generator.h"






int INFO = 0;

int UB_Size;

list<set<int>> init_population;

int GRAIN;

shared_ptr< Evaluator >  eval_ks;

int K_replication = 0;
