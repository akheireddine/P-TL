
#include "MainKnapsack.h"
#include <time.h>
#include "Tools.h"
#include "Evaluator.h"
#include "Gnuplotter.h"


#define WS_ITERATION 13   //A_100 max 13
//#define __PRINT__


using namespace std;



vector< float > Tools::dist_time_avg(2,0);
vector< float > Tools::indicator_avg(3,0);
int Tools::cpt = 0;
int ITERATION_WS_PLS = 0;

list<set<int>> init_population;

Evaluator* main_Knapsack(string filename_instance, string type_instance, string num_instance, int size_population, string WS_DM_preferences){

	string pref_filename = "./WS_Matrix.csv";

	MainKnapsack * knaps = new MainKnapsack(filename_instance, size_population, pref_filename);

	clock_t t1 = clock();
	knaps->MOLS1(t1/CLOCKS_PER_SEC); 								 //3min
	float t2 = (clock() - t1) * 1.0/CLOCKS_PER_SEC;

	cout<<"Execution time : "<<t2<<" sec"<<endl<<endl;

	string size_instance = to_string(knaps->get_n_items());

	Evaluator * eval = new Evaluator(filename_instance, knaps, WS_DM_preferences,
			"./Data/DistTime/"+type_instance+"/I"+num_instance+"_"+size_instance+".eval"
			, t2,
			"./Data/ParetoFront/"+type_instance+"/I"+num_instance+"_"+size_instance+".front");


	return eval;
}


Evaluator* main_Knapsack2(string filename_instance, string type_instance, string num_instance, int size_population, string WS_DM_preferences){

	string pref_filename = "./WS_Matrix.csv";

	MainKnapsack * knaps = new MainKnapsack(filename_instance, size_population, pref_filename);

	knaps->setInitialPopulation();

	clock_t t1 = clock();
	knaps->MOLS2(t1/CLOCKS_PER_SEC); 								 //3min
	float t2 = (clock() - t1) * 1.0/CLOCKS_PER_SEC;

	cout<<"Execution time : "<<t2<<" sec"<<endl<<endl;

	string size_instance = to_string(knaps->get_n_items());

	Evaluator * eval = new Evaluator(filename_instance, knaps, WS_DM_preferences,
			"./Data/DistTime/"+type_instance+"/I"+num_instance+"_"+size_instance+".eval"
			, t2,
			"./Data/ParetoFront/"+type_instance+"/I"+num_instance+"_"+size_instance+".front");


	return eval;
}


void script_knapsack(string type_inst, string taille, string WS_DM){

	Evaluator * eval_ks;
	init_population.clear();


	for(int i = 4; i < 10 ; i++){
		string filename_instance = "./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);


		//!!!!!!!!!!!!!!!!!!!!! CHANGE DMS WSUMM FOR TEST1 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		for(int step = 0; step < 8; step++){
			cout<<"_________________________________ STEP"<<step<<"___________________________"<<endl;
			Tools::copy_into("./Data/WS_Learning/Test2/Iteration_"+to_string(step),"WS_Matrix.csv");

			Tools::cpt = 0;
			Tools::clean_up();

			for(int k = 0; k < 10; k++){
				eval_ks = main_Knapsack(filename_instance, type_inst , to_string(i) , 1 , WS_DM);
				delete eval_ks;
			}

			Tools::save_average_dist_time("./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_MOLS1.eval");
			Tools::save_average_indicator("./Data/ParetoFront/"+type_inst+"/I_"+taille+"_AVG_MOLS1.front");


		}
		Tools::separate_results("./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_MOLS1.eval",type_inst+to_string(i)+"____");
		Tools::separate_results("./Data/ParetoFront/"+type_inst+"/I_"+taille+"_AVG_MOLS1.front",type_inst+to_string(i)+"____");
	}




	for(int i = 4; i < 10 ; i++){
		string filename_instance = "./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);


		//!!!!!!!!!!!!!!!!!!!!! CHANGE DMS WSUMM FOR TEST1 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		for(int step = 0; step < 8; step++){
			cout<<"_________________________________ STEP"<<step<<"___________________________"<<endl;
			Tools::copy_into("./Data/WS_Learning/Test2/Iteration_"+to_string(step),"WS_Matrix.csv");

			Tools::cpt = 0;
			Tools::clean_up();

			for(int k = 0; k < 10; k++){
				eval_ks = main_Knapsack2(filename_instance, type_inst , to_string(i) , 1 , WS_DM);
				delete eval_ks;
			}

			Tools::save_average_dist_time("./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_MOLS2.eval");
			Tools::save_average_indicator("./Data/ParetoFront/"+type_inst+"/I_"+taille+"_AVG_MOLS2.front");


		}
		Tools::separate_results("./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_MOLS2.eval",type_inst+to_string(i)+"____");
		Tools::separate_results("./Data/ParetoFront/"+type_inst+"/I_"+taille+"_AVG_MOLS2.front",type_inst+to_string(i)+"____");
	}




}



//***********************************************************************************************************************************//


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

void script_WSPLS(string type_inst, string taille, string WS_DM){

	Evaluator * eval_ks;


	for(int i = 0; i < 10; i++){

		string filename_instance = "./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);


		for(int iter = 2; iter <= 14 ; iter += 2){
			cout<<"============================================   "<<iter<<" STEPS   ============================================"<<endl;
			ITERATION_WS_PLS = iter;
			Tools::cpt = 0;
			Tools::clean_up();

			for(int k = 0; k < 10; k++){
				Tools::generate_random_WS("WS_Matrix.csv",2);
				eval_ks = main_Knapsack_WSPLS(filename_instance, type_inst, to_string(i),1, WS_DM, iter);
			}

			Tools::save_average_dist_time("./Data/DistTime/"+type_inst+"/I_WSPLS"+taille+"_AVG.eval");
			Tools::save_average_indicator("./Data/ParetoFront/"+type_inst+"/I_WSPLS"+taille+"_AVG.front");

			eval_ks->write_objective_OPT_information();
//			free(eval_ks);
		}
		Tools::separate_results("./Data/DistTime/"+type_inst+"/I_WSPLS"+taille+"_AVG.eval",type_inst+to_string(i)+"___");
		Tools::separate_results("./Data/ParetoFront/"+type_inst+"/I_WSPLS"+taille+"_AVG.front",type_inst+to_string(i)+"___");

	}


}


//***********************************************************************************************************************************//


Evaluator* main_Knapsack_PLSWS(string filename_instance, string type_instance, string num_instance,
		int size_population, string WS_DM_preferences, int max_step){

//	string pref_filename = "./WS_Matrix.csv";

	MainKnapsack * knaps = new MainKnapsack(filename_instance, size_population);

	clock_t t1 = clock();
	knaps->HYBRID_PLS_WS(t1/CLOCKS_PER_SEC,max_step);
	float t2 = (clock() - t1) * 1.0/CLOCKS_PER_SEC;

	cout<<"Execution time : "<<t2<<" sec"<<endl<<endl;

	string size_instance = to_string(knaps->get_n_items());

	Evaluator * eval = new Evaluator(filename_instance, knaps, WS_DM_preferences,
			"./Data/DistTime/"+type_instance+"/I"+num_instance+"_"+size_instance+"_PLSWS.eval"
			, t2,
			"./Data/ParetoFront/"+type_instance+"/I"+num_instance+"_"+size_instance+"_PLSWS.front");

	return eval;
}

void script_PLSWS(string type_inst, string taille, string WS_DM){

	Evaluator * eval_ks;


	for(int i = 0; i < 3; i++){

		string filename_instance = "./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);


		for(int iter = 10; iter <= 11 ; iter+= 50 ){
			cout<<"============================================   "<<iter<<" STEPS   ============================================"<<endl;
			Tools::cpt = 0;
			Tools::clean_up();
			ITERATION_WS_PLS = iter;


			for(int k = 0; k < 1; k++){
				eval_ks = main_Knapsack_PLSWS(filename_instance, type_inst, to_string(i),1, WS_DM, iter);
			}
			Tools::save_average_dist_time("./Data/DistTime/"+type_inst+"/I_PLSWS"+taille+"_AVG.eval");

			Tools::save_average_indicator("./Data/ParetoFront/"+type_inst+"/I_PLSWS"+taille+"_AVG.front");

			eval_ks->write_objective_OPT_information();

			free( eval_ks );
		}
		Tools::separate_results("./Data/DistTime/"+type_inst+"/I_PLSWS"+taille+"_AVG.eval",type_inst+to_string(i)+"___");
		Tools::separate_results("./Data/ParetoFront/"+type_inst+"/I_PLSWS"+taille+"_AVG.front",type_inst+to_string(i)+"___");

	}


}


//***********************************************************************************************************************************//



Evaluator* main_Knapsack_Cst_PSize(string filename_instance, string type_instance, string num_instance,
		int size_population, string WS_DM_preferences, int max_size_population){

	string pref_filename = "./WS_Matrix2.csv";

	MainKnapsack * knaps = new MainKnapsack(filename_instance, size_population,pref_filename);

	clock_t t1 = clock();
	knaps->MOLS2_Cst_PSize(t1/CLOCKS_PER_SEC,max_size_population);
	float t2 = (clock() - t1) * 1.0/CLOCKS_PER_SEC;

	cout<<"Execution time : "<<t2<<" sec"<<endl<<endl;

	string size_instance = to_string(knaps->get_n_items());

	Evaluator * eval = new Evaluator(filename_instance, knaps, WS_DM_preferences,
			"./Data/DistTime/"+type_instance+"/I"+num_instance+"_"+size_instance+"_PSize_"+to_string(max_size_population)+".eval"
			, t2,
			"./Data/ParetoFront/"+type_instance+"/I"+num_instance+"_"+size_instance+"_PSize_"+to_string(max_size_population)+".front");

	return eval;
}


void script_Cst_PSize(string type_inst, string taille, string WS_DM){

	Evaluator * eval_ks;

	for(int i = 0; i < 1; i++){

		string filename_instance = "./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);


		for(int iter = 10; iter <= 210 ; iter += 20){
			cout<<"============================================   "<<iter<<" POP SIZE   ============================================"<<endl;

			for(int step = 0; step < 8; step++){
				cout<<"_________________________________ STEP"<<step<<"___________________________"<<endl;
				Tools::copy_into("./Data/WS_Learning/Test2/Iteration_"+to_string(step),"WS_Matrix2.csv");
				Tools::cpt = 0;
				Tools::clean_up();

				for(int k = 0; k < 10; k++){
					eval_ks = main_Knapsack_Cst_PSize(filename_instance, type_inst, to_string(i),1, WS_DM, iter);
//					eval_ks->write_objective_OPT_information();
					delete eval_ks;
				}

				Tools::save_average_dist_time("./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_PS2.eval");
				Tools::save_average_indicator("./Data/ParetoFront/"+type_inst+"/I_"+taille+"_AVG_PS2.front");

			}

			Tools::separate_results("./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_PS2.eval",type_inst+to_string(i)+"___"+to_string(iter)+"__");
			Tools::separate_results("./Data/ParetoFront/"+type_inst+"/I_"+taille+"_AVG_PS2.front",type_inst+to_string(i)+"___"+to_string(iter)+"__");
		}
	}
}





//***********************************************************************************************************************************//




int main(int argc, char** argv){

	string WS_DM = "./weighted_DM_preferences.ks";

	string type_inst = "A";
	string taille = "100";

//	script_knapsack(type_inst, taille, WS_DM);

//	Gnuplotter::Comparison_Plot_DIST_TIME("./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_MOLS1.eval","./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_MOLS2.eval"
//			,type_inst,taille,"MOLS1 - global filtering"," MOLS2 - continous filtering");




	script_Cst_PSize(type_inst,taille,WS_DM);


//	Gnuplotter::Comparison_Plot_DIST_TIME("./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_PS1.eval","./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_PS2.eval"
//			,type_inst,taille,"MOLS1 - global filtering"," MOLS2 - continous filtering");



	return 1;

}
