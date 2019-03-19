
#include "MainKnapsack.h"
#include <time.h>
#include "Tools.h"
using namespace std;



MainKnapsack* main_Knapsack_PLS(string filename_instance,string type_instance, string num_instance, int size_population, string weighted_DM_preferences){

	MainKnapsack * knaps = new MainKnapsack(filename_instance, type_instance+"_PLS", num_instance, size_population);

	clock_t t1 = clock();
	knaps->MOLS(t1/CLOCKS_PER_SEC); 								 //3min
	float t2 = (clock() - t1) * 1.0/CLOCKS_PER_SEC;
	cout<<"Execution time : "<<t2<<" sec"<<endl<<endl;

	knaps->evaluate_solutions(weighted_DM_preferences,t2);

	knaps->pareto_front_evaluation();

	return knaps;


}


MainKnapsack* main_Knapsack_WSLS(string filename_instance,string type_instance, string num_instance, int size_population, string weighted_DM_preferences){

	string pref_filename = "./WS_Matrix.csv";

	MainKnapsack * knaps = new MainKnapsack(filename_instance, type_instance+"_WS", num_instance, size_population, pref_filename);

	clock_t t1 = clock();
	knaps->MOLS(t1/CLOCKS_PER_SEC); 								 //3min
	float t2 = (clock() - t1) * 1.0/CLOCKS_PER_SEC;

	cout<<"Execution time : "<<t2<<" sec"<<endl<<endl;

	knaps->evaluate_solutions(weighted_DM_preferences,t2);

	knaps->pareto_front_evaluation();

	return knaps;
}





int main(int argc, char** argv){

	string WS_DM = "./weighted_DM_preferences.ks";

	string type_inst = "A";
	string taille = "100";

	MainKnapsack * knaps;





//PLS
		for(int i = 0; i < 2; i++){
			//without extension
			string filename_instance = "./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);
			knaps = main_Knapsack_PLS(filename_instance, type_inst,to_string(i),1,WS_DM);
		}




//WSLS
//		Tools::generate_random_WS("WS_Matrix.csv",2);
//		for(int i = 0; i < 2; i++){
//			//without extension
//			string filename_instance = "./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);
//			knaps = main_Knapsack_WSLS(filename_instance, type_inst,to_string(i),1,WS_DM);
//		}


	return 1;

}
