
#include <map>
#include "Alternative.h"

using namespace std;

enum A {P, WS};




void main_Knapsack(string filename, A relation, vector< Set<int> > start_alternative){

	MainKnapsack knaps = MainKnapsack(filename, relation, start_alternative);


	AlternativeKnapsack * population = AlternativeKnapsack(start_alternative[0], data_Object);

	vector< AlternativeKnapsack * > solution_set = MOLS(population, relation);

	save_knapsack_solution_set(solution_set);
}



void main_PFS(string filename){

}






void main(int argc, char** argv){

	if(argc!=1){
		cerr<<"Error arguments"<<endl;
		return 1;
	}

	string filename = argv[1];


}
