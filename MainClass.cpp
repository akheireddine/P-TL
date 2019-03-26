
#include "MainKnapsack.h"
#include <time.h>
#include "Tools.h"
using namespace std;



vector< float > Tools::dist_time_avg(2,0);
vector< float > Tools::indicator_avg(3,0);
int Tools::cpt = 0;



MainKnapsack* main_Knapsack(string filename_instance,string type_instance, string num_instance, int size_population, string weighted_DM_preferences){

	string pref_filename = "./WS_Matrix.csv";

	MainKnapsack * knaps = new MainKnapsack(filename_instance, type_instance, num_instance, size_population, pref_filename);

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
	string taille = "300";

	MainKnapsack * knaps;



	for(int i = 3; i < 4; i++){

	//SET COEFF_OBJECTIVE      !!!!!!!!!!!!!!!!!!!!! CHANGE DMS WSUMM FOR TEST1 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		for(int step = 0; step < 1; step++){

			Tools::copy_into("./Data/WS_Learning/Test2/Iteration_"+to_string(step),"WS_Matrix.csv");

			Tools::cpt = 0;
			Tools::clean_up();

			for(int k = 0; k < 1; k++){
	//		Tools::generate_random_WS("WS_Matrix.csv",2);
				//without extension
				string filename_instance = "./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);

				knaps = main_Knapsack(filename_instance, type_inst,to_string(i),1,WS_DM);
			}

			Tools::save_average_dist_time("./Data/DistTime/"+type_inst+"/I"+to_string(i)+"_"+taille+".eval");
			Tools::save_average_indicator("./Data/ParetoFront/"+type_inst+"/I"+to_string(i)+"_"+taille+".front");
//			Tools::compute_average_column_files("./Data/DistTime/"+type_inst+"/I"+to_string(i)+"_"+taille+".eval",2);
//
//			Tools::compute_average_column_files("./Data/ParetoFront/"+type_inst+"/I"+to_string(i)+"_"+taille+".front",3);

			knaps->write_coeff_functions("./Data/DistTime/"+type_inst+"/I"+to_string(i)+"_"+taille+".eval");
			knaps->write_coeff_functions("./Data/ParetoFront/"+type_inst+"/I"+to_string(i)+"_"+taille+".front");

		}

	}




	return 1;

}
