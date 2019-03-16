
#include "MainKnapsack.h"
#include <time.h>
#include "Tools.h"
using namespace std;





MainKnapsack* main_Knapsack_PLS(string filename_instance, string init_population_filename,string weighted_DM_preferences, string type_inst){

	string pref_filename = "./Pareto_Matrix.csv";

	MainKnapsack * knaps = new MainKnapsack(filename_instance, pref_filename, init_population_filename);

	clock_t t1 = clock();
	knaps->MOLS(t1/CLOCKS_PER_SEC);  // nb iteration  pour 100 et 200 items   et 5min pour le reste
	float t2 = (clock() - t1) * 1.0/CLOCKS_PER_SEC;
	cout<<"Execution time : "<<t2<<" sec"<<endl<<endl;

	knaps->evaluate_solutions(weighted_DM_preferences,t2,type_inst);

	knaps->pareto_front_evaluation(type_inst);

	return knaps;
}


MainKnapsack* main_Knapsack_WSLS(string filename_instance, string init_population_filename,string weighted_DM_preferences, string type_inst){

	string pref_filename = "./WS_Matrix.csv";
	MainKnapsack * knaps = new MainKnapsack(filename_instance, pref_filename, init_population_filename);

	clock_t t1 = clock();
	knaps->MOLS(t1/CLOCKS_PER_SEC);  // nb iteration  pour 100 et 200 items   et 5min pour le reste
	float t2 = (clock() - t1) * 1.0/CLOCKS_PER_SEC;
	cout<<"Execution time : "<<t2<<" sec"<<endl<<endl;

	knaps->evaluate_solutions(weighted_DM_preferences,t2,type_inst);

	knaps->pareto_front_evaluation(type_inst);

	return knaps;
}





int main(int argc, char** argv){

	string init_population_filename = "./initial_population_knapsack.ks";
	string WS_DM = "./weighted_DM_preferences.ks";

	string type_inst = "A";
	string taille = "100";

	MainKnapsack * knaps;



	////	PLS
		for(int i = 0; i < 10; i++){
			//without extension
			string filename_instance = "./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);
			//PLS
			knaps = main_Knapsack_PLS(filename_instance, init_population_filename,WS_DM,type_inst+"_PLS");
		}
		knaps->write_coeff_functions(type_inst+"_PLS");


	////	WSLS
	for(int k = 0; k < 50; k++){
		Tools::generate_random_WS("WS_Matrix.csv",2);
		for(int i = 0; i < 10; i++){
			//without extension
			string filename_instance = "./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);
			//WSLS
			knaps = main_Knapsack_WSLS(filename_instance, init_population_filename,WS_DM,type_inst+"_WS");
		}
		knaps->write_coeff_functions(type_inst+"_WS");

	}

	return 1;

}
