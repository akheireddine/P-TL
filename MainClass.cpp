
#include "MainKnapsack.h"
#include <time.h>
#include "Tools.h"
#include "Evaluator.h"

#define WS_ITERATION 13   //A_100 max 13
#define __PRINT__


using namespace std;



vector< float > Tools::dist_time_avg(2,0);
vector< float > Tools::indicator_avg(3,0);
int Tools::cpt = 0;



Evaluator* main_Knapsack(string filename_instance, string type_instance, string num_instance, int size_population, string WS_DM_preferences){

	string pref_filename = "./WS_Matrix.csv";

	MainKnapsack * knaps = new MainKnapsack(filename_instance, size_population, pref_filename);

	clock_t t1 = clock();
	knaps->MOLS(t1/CLOCKS_PER_SEC); 								 //3min
	float t2 = (clock() - t1) * 1.0/CLOCKS_PER_SEC;

	cout<<"Execution time : "<<t2<<" sec"<<endl<<endl;

	string size_instance = to_string(knaps->get_n_items());

	Evaluator * eval = new Evaluator(filename_instance, knaps, WS_DM_preferences,
			"./Data/DistTime/"+type_instance+"/I"+num_instance+"_"+size_instance+".eval"
			, t2,
			"./Data/ParetoFront/"+type_instance+"/I"+num_instance+"_"+size_instance+".front");


	free(knaps);
	return eval;
}




Evaluator* main_Knapsack_WSPLS(string filename_instance, string type_instance, string num_instance,
		int size_population, string WS_DM_preferences, int max_step){

	string pref_filename = "./WS_Matrix.csv";

	MainKnapsack * knaps = new MainKnapsack(filename_instance, size_population, pref_filename);

	clock_t t1 = clock();
	knaps->HYBRID_WS_PLS(t1/CLOCKS_PER_SEC,max_step);
	float t2 = (clock() - t1) * 1.0/CLOCKS_PER_SEC;

	cout<<"Execution time : "<<t2<<" sec"<<endl<<endl;

	string size_instance = to_string(knaps->get_n_items());

	Evaluator * eval = new Evaluator(filename_instance, knaps, WS_DM_preferences,
			"./Data/DistTime/"+type_instance+"/I"+num_instance+"_"+size_instance+"_WSPLS.eval"
			, t2,
			"./Data/ParetoFront/"+type_instance+"/I"+num_instance+"_"+size_instance+"_WSPLS.front");

	return eval;
}








int main(int argc, char** argv){

	string WS_DM = "./weighted_DM_preferences.ks";

	string type_inst = "A";
	string taille = "200";

	Evaluator * eval_ks;



//	for(int i = 0; i < 1 ; i++){
//		//without extension
//		string filename_instance = "./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);
//
//		//string filename_instance = "./Instances_Knapsack/instance_test";
//
//		//SET COEFF_OBJECTIVE      !!!!!!!!!!!!!!!!!!!!! CHANGE DMS WSUMM FOR TEST1 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//		for(int step = 9; step < 10; step++){
//
//			Tools::copy_into("./Data/WS_Learning/Test1/Iteration_"+to_string(step),"WS_Matrix.csv");
//
//			Tools::cpt = 0;
//			Tools::clean_up();
//
//			for(int k = 0; k < 30; k++){
//				Tools::generate_random_WS("WS_Matrix.csv",2);
//				eval_ks = main_Knapsack(filename_instance, type_inst , to_string(i) , 1 , WS_DM);
//			}
////			eval_ks->compute_information_rate();
////			Tools::save_average_dist_time("./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG.eval");
////			Tools::save_average_indicator("./Data/ParetoFront/"+type_inst+"/I_"+taille+"_AVG.front");
////			eval_ks->write_objective_OPT_information();
////			free(eval_ks);
//
//		}
////		int size_front = eval_ks->get_PFront().size();
////		Tools::separate_results("./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG.eval",type_inst+to_string(i)+"____"+to_string(size_front));
////		Tools::separate_results("./Data/ParetoFront/"+type_inst+"/I_"+taille+"_AVG.front",type_inst+to_string(i)+"____"+to_string(size_front));
//
//	}







	for(int i = 0; i < 10; i++){

		string filename_instance = "./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);


		for(int iter = 3; iter <= 35 ; iter++){
			cout<<"============================================   "<<iter<<" STEPS   ============================================"<<endl;
			iter+=4;

			Tools::cpt = 0;
			Tools::clean_up();

			for(int k = 0; k < 20; k++){
				Tools::generate_random_WS("WS_Matrix.csv",2);
				eval_ks = main_Knapsack_WSPLS(filename_instance, type_inst, to_string(i),1, WS_DM, iter);
			}

			Tools::save_average_dist_time("./Data/DistTime/"+type_inst+"/I_WSPLS"+taille+"_AVG.eval");
			Tools::save_average_indicator("./Data/ParetoFront/"+type_inst+"/I_WSPLS"+taille+"_AVG.front");

			eval_ks->write_objective_OPT_information();
			free(eval_ks);

		}
		Tools::separate_results("./Data/DistTime/"+type_inst+"/I_WSPLS"+taille+"_AVG.eval",type_inst+to_string(i)+"___");
		Tools::separate_results("./Data/ParetoFront/"+type_inst+"/I_WSPLS"+taille+"_AVG.front",type_inst+to_string(i)+"___");

	}





	return 1;

}
