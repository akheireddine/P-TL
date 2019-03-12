
#include "MainKnapsack.h"
#include <time.h>
using namespace std;





void main_Knapsack(string filename_instance, string pref_filename, string init_population_filename,string weighted_DM_preferences){

	MainKnapsack * knaps = new MainKnapsack(filename_instance, pref_filename, init_population_filename);

	clock_t t1 = clock();
	knaps->MOLS();
	float t2 = (clock() - t1) * 1.0/CLOCKS_PER_SEC;
	cout<<"Execution time : "<<t2<<" sec"<<endl;


	knaps->evaluate_solutions(weighted_DM_preferences,t2);


}




int main(int argc, char** argv){

//	if(argc!=3){
//		cerr<<"Error arguments"<<endl;
//		return 1;
//	}
//	string filename_instance = argv[1];
//	string pref_filename = argv[2];
//	string init_population_filename = argv[3];

	//without extension
//	string filename_instance ="./Instances_Knapsack/Type_A/100_items/mini_inst_10";
//	string filename_instance = "./Instances_Knapsack/Type_A/600_items/2KP600-TA-8";


	for(int i = 0; i < 10; i++){
		string filename_instance = "./Instances_Knapsack/Type_A/100_items/2KP100-TA-"+to_string(i);
		string pref_filename = "./WS_Matrix.csv";
		string init_population_filename = "./initial_population_knapsack.ks";
		string WS_DM = "./weighted_DM_preferences.ks";
		main_Knapsack(filename_instance, pref_filename, init_population_filename,WS_DM);
	}

	return 1;

}
