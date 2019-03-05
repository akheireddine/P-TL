
#include "MainKnapsack.h"

using namespace std;





void main_Knapsack(string filename_instance, string pref_filename, string init_population_filename){

	MainKnapsack * knaps = MainKnapsack(filename_instance, pref_filename, init_population_filename);

	knaps->MOLS();

}




int main(int argc, char** argv){

	if(argc!=3){
		cerr<<"Error arguments"<<endl;
		return 1;
	}

	string filename_instance = argv[1];
	string pref_filename = argv[2];
	string init_population_filename = argv[3];

	main_Knapsack(filename_instance, pref_filename, init_population_filename);

	return 1;

}
