
#include "MainKnapsack.h"

using namespace std;





void main_Knapsack(string filename_instance, string pref_filename, string init_population_filename){

	MainKnapsack * knaps = new MainKnapsack(filename_instance, pref_filename, init_population_filename);

	knaps->MOLS();
	cout<<"hell yeaah DONE"<<endl;

}




int main(int argc, char** argv){

//	if(argc!=3){
//		cerr<<"Error arguments"<<endl;
//		return 1;
//	}
//	string filename_instance = argv[1];
//	string pref_filename = argv[2];
//	string init_population_filename = argv[3];



	string filename_instance = "./Instances_Knapsack/Type_A/100_items/2KP100-TA-0.dat";
	string pref_filename = "./WS_Matrix.csv";
	string init_population_filename = "./initial_population_knapsack.ks";

	main_Knapsack(filename_instance, pref_filename, init_population_filename);

	return 1;

}
