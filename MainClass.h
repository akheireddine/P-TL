

#include "MainKnapsack.h"
#include <time.h>
#include "Tools.h"
#include "Evaluator.h"
#include "Gnuplotter.h"
#include "Instance_Generator.h"






float Ta = 500;

float Temperature = 1500;

vector< float > Tools::dist_time_avg(2,0);

vector< float > Tools::indicator_avg(3,0);

vector< float > Tools:: ratios_dist_to_OPT;

int Tools::cpt_count = 0;

int INFO = 0;

list<set<int>> init_population;

int GRAIN;



map<string, list<string> > common_neighbors;
