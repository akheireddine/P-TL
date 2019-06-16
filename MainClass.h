

#include "MainKnapsack.h"
#include <time.h>
#include "Tools.h"
#include "Evaluator.h"
#include "Gnuplotter.h"
#include "Instance_Generator.h"






int INFO = 0;

list<set<int>> init_population;

int GRAIN;

shared_ptr< Evaluator >  eval_ks;

int k_replication = 0;
