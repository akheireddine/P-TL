
#include "MainKnapsack.h"
#include <time.h>
#include "Tools.h"
#include "Evaluator.h"
#include "Gnuplotter.h"

#define WS_ITERATION 13   //A_100 max 13
//#define __PRINT__


using namespace std;

float Ta = 500;


vector< float > Tools::dist_time_avg(2,0);
vector< float > Tools::indicator_avg(3,0);
int Tools::cpt = 0;
int ITERATION_WS_PLS = 0;
int INFO = 0;

list<set<int>> init_population;




Evaluator* main_Knapsack(string filename_instance, string type_instance, string num_instance, int size_population, string WS_DM_preferences){

	string pref_filename = "./WS_Matrix3.csv";

	MainKnapsack * knaps = new MainKnapsack(size_population, filename_instance, pref_filename);

	clock_t t1 = clock();
	knaps->MOLS(t1/CLOCKS_PER_SEC); 								 //3min
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

	int K = 1;
	int N = 9;
	Evaluator * eval_ks;
	init_population.clear();


	//INIT ALL POPULATION FOR ALL INSTANCES
	for(int i = 8; i < N; i++){
		string filename_instance = "./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);
		MainKnapsack::Generate_random_Population(filename_instance, K);
	}



	for(int i = 8; i < N ; i++){
		string filename_instance = "./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);

	//!!!!!!!!!!!!!!!!!!!!! CHANGE DMS WSUMM FOR TEST1 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		for(int step = 0; step < 1; step++){
			INFO = step;
			cout<<"_________________________________ STEP"<<step<<"___________________________"<<endl;
			Tools::copy_into("./Data/WS_Learning/Test2/Iteration_"+to_string(step),"WS_Matrix3.csv");

			Tools::cpt = 0;
			Tools::clean_up();

			for(int k = 0; k < K; k++){
				Ta = 500;
				eval_ks = main_Knapsack(filename_instance, type_inst , to_string(i) , 1 , WS_DM);
				delete eval_ks;
			}

//			Tools::save_average_dist_time("./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_MOLS2_MODIF.eval");
//			Tools::save_average_indicator("./Data/ParetoFront/"+type_inst+"/I_"+taille+"_AVG_MOLS2_MODIF.front");
		}
//		Tools::separate_results("./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_MOLS2_MODIF.eval",type_inst+to_string(i)+"___");
//		Tools::separate_results("./Data/ParetoFront/"+type_inst+"/I_"+taille+"_AVG_MOLS2_MODIF.front",type_inst+to_string(i)+"___");

		Tools::skip(init_population,K);
	}

}



//***********************************************************************************************************************************//


Evaluator* main_Knapsack_WSPLS(string filename_instance, string type_instance, string num_instance, int size_population, string WS_DM_preferences,int iter){

	string pref_filename = "./WS_Matrix.csv";

	MainKnapsack * knaps = new MainKnapsack(size_population, filename_instance, pref_filename);

	clock_t t1 = clock();
	knaps->HYBRID_WS_PLS(t1/CLOCKS_PER_SEC,iter);
	float t2 = (clock() - t1) * 1.0/CLOCKS_PER_SEC;

	cout<<"Execution time : "<<t2<<" sec"<<endl<<endl;

	string size_instance = to_string(knaps->get_n_items());

	Evaluator * eval = new Evaluator(filename_instance, knaps, WS_DM_preferences,
			"./Data/DistTime/"+type_instance+"/I"+num_instance+"_"+size_instance+".eval"
			, t2,
			"./Data/ParetoFront/"+type_instance+"/I"+num_instance+"_"+size_instance+".front");

	return eval;
}


void script_knapsack_WSPLS(string type_inst, string taille, string WS_DM){

	int K = 1;
	int N = 9;
	Evaluator * eval_ks;
	init_population.clear();


	//INIT ALL POPULATION FOR ALL INSTANCES
	for(int i = 8; i < N; i++){
		string filename_instance = "./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);
		MainKnapsack::Generate_random_Population(filename_instance, K);
	}



	for(int i = 8; i < N ; i++){
		string filename_instance = "./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);

	//!!!!!!!!!!!!!!!!!!!!! CHANGE DMS WSUMM FOR TEST1 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		for(int step = 500; step < 501; step++){
			cout<<"_________________________________ NB-ITER "<<step<<"___________________________"<<endl;

			Tools::cpt = 0;
			Tools::clean_up();

			for(int k = 0; k < K; k++){
				Tools::generate_random_WS("WS_Matrix.csv", 2);
				Ta = 500;
				eval_ks = main_Knapsack_WSPLS(filename_instance, type_inst , to_string(i) , 1 , WS_DM, step);
				delete eval_ks;
			}

//			Tools::save_average_dist_time("./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_Ta_500.eval");
//			Tools::save_average_indicator("./Data/ParetoFront/"+type_inst+"/I_"+taille+"_AVG_Ta_500.front");
		}
//		Tools::separate_results("./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_Ta_500.eval",type_inst+to_string(i)+"___");
//		Tools::separate_results("./Data/ParetoFront/"+type_inst+"/I_"+taille+"_AVG_Ta_500.front",type_inst+to_string(i)+"___");

		Tools::skip(init_population,K);
	}

}



//***********************************************************************************************************************************//

Evaluator* main_Knapsack_PLSWS(string filename_instance, string type_instance, string num_instance, int size_population, string WS_DM_preferences,int iter){

	string pref_filename = "./WS_Matrix3.csv";

	MainKnapsack * knaps = new MainKnapsack(size_population, filename_instance, pref_filename);

	clock_t t1 = clock();
	knaps->HYBRID_PLS_WS(t1/CLOCKS_PER_SEC,iter);
	float t2 = (clock() - t1) * 1.0/CLOCKS_PER_SEC;

	cout<<"Execution time : "<<t2<<" sec"<<endl<<endl;

	string size_instance = to_string(knaps->get_n_items());

	Evaluator * eval = new Evaluator(filename_instance, knaps, WS_DM_preferences,
			"./Data/DistTime/"+type_instance+"/I"+num_instance+"_"+size_instance+".eval"
			, t2,
			"./Data/ParetoFront/"+type_instance+"/I"+num_instance+"_"+size_instance+".front");

	return eval;
}


void script_knapsack_PLSWS(string type_inst, string taille, string WS_DM){

	int K = 1;
	int N = 9;
	Evaluator * eval_ks;
	init_population.clear();


	//INIT ALL POPULATION FOR ALL INSTANCES
	for(int i = 8; i < N; i++){
		string filename_instance = "./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);
		MainKnapsack::Generate_random_Population(filename_instance, K);
	}



	for(int i = 8; i < N ; i++){
		string filename_instance = "./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);

	//!!!!!!!!!!!!!!!!!!!!! CHANGE DMS WSUMM FOR TEST1 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		for(int step = 250; step < 251; step++){
			cout<<"_________________________________ NB-ITER "<<step<<"___________________________"<<endl;
			int information_rate = 0;
			Tools::copy_into("./Data/WS_Learning/Test2/Iteration_"+to_string(information_rate),"WS_Matrix3.csv");

			Tools::cpt = 0;
			Tools::clean_up();

			for(int k = 0; k < K; k++){
				Tools::generate_random_WS("WS_Matrix.csv", 2);
				Ta = 500;
				eval_ks = main_Knapsack_PLSWS(filename_instance, type_inst , to_string(i) , 1 , WS_DM, step);
				delete eval_ks;
			}

//			Tools::save_average_dist_time("./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_Ta_500.eval");
//			Tools::save_average_indicator("./Data/ParetoFront/"+type_inst+"/I_"+taille+"_AVG_Ta_500.front");
		}
//		Tools::separate_results("./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_Ta_500.eval",type_inst+to_string(i)+"___");
//		Tools::separate_results("./Data/ParetoFront/"+type_inst+"/I_"+taille+"_AVG_Ta_500.front",type_inst+to_string(i)+"___");

		Tools::skip(init_population,K);
	}

}



















//***********************************************************************************************************************************//





Evaluator* main_Knapsack_Cst_PSize(string filename_instance, string type_instance, string num_instance,
	int size_population, string WS_DM_preferences, int max_size_population){

	string pref_filename = "./WS_Matrix3.csv";

	MainKnapsack * knaps = new MainKnapsack(size_population,filename_instance,pref_filename);


	clock_t t1 = clock();
	knaps->MOLS_Cst_PSize(t1/CLOCKS_PER_SEC,max_size_population);
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

	int K = 1;
	int N = 9;
	init_population.clear();

	Evaluator * eval_ks;

	//INIT ALL POPULATION FOR ALL INSTANCES
	for(int i = 8; i < N; i++){
		string filename_instance = "./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);
		MainKnapsack::Generate_random_Population(filename_instance, K);
	}

	for(int i = 8; i < N; i++){

		for(int iter = 231; iter <= 231 ; iter += 10){
			cout<<"============================================   "<<iter<<" POP SIZE   ============================================"<<endl;

			for(int step = 0; step < 1; step++){

				cout<<"_________________________________ STEP"<<step<<"___________________________"<<endl;
				Tools::copy_into("./Data/WS_Learning/Test2/Iteration_"+to_string(step),"WS_Matrix3.csv");

				Tools::cpt = 0;
				Tools::clean_up();

				string filename_instance = "./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);

				for(int k = 0; k < K; k++){
					Ta = 500;
					eval_ks = main_Knapsack_Cst_PSize(filename_instance, type_inst, to_string(i),1, WS_DM, iter);
					delete eval_ks;
				}

//				Tools::save_average_dist_time("./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_PS_T"+to_string(i)+".eval");
//				Tools::save_average_indicator("./Data/ParetoFront/"+type_inst+"/I_"+taille+"_AVG_PS_T"+to_string(i)+".front");

			}
//			Tools::separate_results("./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_PS_T"+to_string(i)+".eval",type_inst+to_string(i)+"___"+to_string(iter));
//			Tools::separate_results("./Data/ParetoFront/"+type_inst+"/I_"+taille+"_AVG_PS_T"+to_string(i)+".front",type_inst+to_string(i)+"___"+to_string(iter));

		}
		Tools::skip(init_population,K);

	}


}





//***********************************************************************************************************************************//



int main(int argc, char** argv){

	string WS_DM = "./weighted_DM_preferences.ks";

	string type_inst = "A";
	string taille = "200";

//	script_knapsack(type_inst, taille, WS_DM);


//
//	Gnuplotter::Comparison_Plot_DIST_TIME("./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_MOLS2_MODIF.eval","./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_MOLS2.eval"
//				,type_inst,taille,"MODIF","BEFORE");
//	Gnuplotter::Comparison_Plot_INDICATORS("./Data/ParetoFront/"+type_inst+"/I_"+taille+"_AVG_MOLS2_MODIF.front",
//			"./Data/ParetoFront/"+type_inst+"/I_"+taille+"_AVG_MOLS2.front",type_inst,taille,"MODIF","BEFORE");




//	Gnuplotter::AllPlot_DIST_TIME_PSize("./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_MOLS2.eval", type_inst, taille ,
//			"MOLS2" , 10,  20);



//	Gnuplotter::Comparison_Plot_DIST_TIME("./Data/OTHER_MEASUREMENTS/"+type_inst+"/I_"+taille+"_AVG_MOLS2_onceWS.eval","./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_MOLS2.eval"
//			,type_inst,taille,"Fixe WS - line (1)","Changing WS - line (2)");

//	Gnuplotter::Comparison_Plot_VARIABLE_WS_NEIGHBORHOOD("./Data/OTHER_MEASUREMENTS/"+type_inst+"/I_"+taille+"_AVG_MOLS2_random_w.eval",
//			"./Data/OTHER_MEASUREMENTS/"+type_inst+"/I_"+taille+"_AVG_MOLS2_feasible_w.eval",
//			"./Data/OTHER_MEASUREMENTS/"+type_inst+"/I_"+taille+"_AVG_MOLS2_opt_w.eval",
//			type_inst, taille, "Random weights", "Feasible weights", "Optimal weights");

//	Gnuplotter::Comparison_Plot_VARIABLE_WS_NEIGHBORHOOD("./Data/OTHER_MEASUREMENTS/"+type_inst+"/I_"+taille+"_AVG_MOLS2_random_w.front",
//			"./Data/OTHER_MEASUREMENTS/"+type_inst+"/I_"+taille+"_AVG_MOLS2_feasible_w.front",
//			"./Data/OTHER_MEASUREMENTS/"+type_inst+"/I_"+taille+"_AVG_MOLS2_opt_w.front",
//			type_inst, taille, "Random weights", "Feasible weights", "Optimal weights");

//	Gnuplotter::Comparison_Plot_DIST_TIME("./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_MOLS1.eval",
//			"./Data/OTHER_MEASUREMENTS/"+type_inst+"/I_"+taille+"_AVG_MOLS1_onceWS.eval"
//			,type_inst,taille,"varying WS (line 2)","keep same WS (line 1)");





/*
  *************************************************************************************************************************
*/
	//TEST2
//	vector<float> opt_points{37652, 41042};  //A-100-T0
//	vector<float> opt_points{78121,76394};   //A-200-T0
//	vector<float> opt_points{115950, 114016};            //A-300-T0
//	vector<float> opt_points{31157,35210}; //C-100-T0
//	vector<float> opt_points{39061,40421};  //A-100-T2

//	Gnuplotter::Plot_SEARCH_EVOLUTION("./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst, type_inst, taille
//			,"MOLS2", -1, 10, 231 , "./DM_preference_point");



//	Gnuplotter::Plot_SEARCH_EVOLUTION_WITH_INFO("./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst, type_inst, taille
//			,"MOLS2", -1, 10, 410 , "./DM_preference_point");

/*
  *************************************************************************************************************************
*/
//	script_Cst_PSize(type_inst,taille,WS_DM);
//
//
//
//	Gnuplotter::AllPlot_DIST_TIME_PSize("./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_PS2","./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_MOLS2.eval",
//			type_inst, taille , "PS2" , 10,  20);


//
//	Gnuplotter::DIST_TIME_PSize_RESUM_X("./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_PS", type_inst, taille,"PS" ,1, 10);
//
//	Gnuplotter::INDICATORS_PSize_RESUM_X("./Data/ParetoFront/"+type_inst+"/I_"+taille+"_AVG_PS", type_inst, taille,"PS" ,1, 10);



/*
  *************************************************************************************************************************
*/


//	script_knapsack_WSPLS(type_inst,taille,WS_DM);


//	Gnuplotter::Plot_SEARCH_EVOLUTION("./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst, type_inst, taille
//			,"MOLS2", -1, 10, 111 , "./DM_preference_point");



/*
  *************************************************************************************************************************
*/

//
	script_knapsack_PLSWS(type_inst,taille,WS_DM);


	Gnuplotter::Plot_SEARCH_EVOLUTION("./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst, type_inst, taille
			,"MOLS2", -1, 10, 111 , "./DM_preference_point");


	return 1;

}







































//Evaluator* main_Knapsack_WSPLS(string filename_instance, string type_instance, string num_instance,
//		int size_population, string WS_DM_preferences, int max_step){
//
//	string pref_filename = "./WS_Matrix.csv";
//
//	MainKnapsack * knaps = new MainKnapsack(filename_instance, size_population, pref_filename);
//
//	clock_t t1 = clock();
//	knaps->HYBRID_WS_PLS(t1/CLOCKS_PER_SEC,max_step);
//	float t2 = (clock() - t1) * 1.0/CLOCKS_PER_SEC;
//
//	cout<<"Execution time : "<<t2<<" sec"<<endl<<endl;
//
//	string size_instance = to_string(knaps->get_n_items());
//
//	Evaluator * eval = new Evaluator(filename_instance, knaps, WS_DM_preferences,
//			"./Data/DistTime/"+type_instance+"/I"+num_instance+"_"+size_instance+"_WSPLS.eval"
//			, t2,
//			"./Data/ParetoFront/"+type_instance+"/I"+num_instance+"_"+size_instance+"_WSPLS.front");
//
//	return eval;
//}
//
//void script_WSPLS(string type_inst, string taille, string WS_DM){
//
//	Evaluator * eval_ks;
//
//
//	for(int i = 0; i < 10; i++){
//
//		string filename_instance = "./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);
//
//
//		for(int iter = 2; iter <= 14 ; iter += 2){
//			cout<<"============================================   "<<iter<<" STEPS   ============================================"<<endl;
//			ITERATION_WS_PLS = iter;
//			Tools::cpt = 0;
//			Tools::clean_up();
//
//			for(int k = 0; k < 10; k++){
//				Tools::generate_random_WS("WS_Matrix.csv",2);
//				eval_ks = main_Knapsack_WSPLS(filename_instance, type_inst, to_string(i),1, WS_DM, iter);
//			}
//
//			Tools::save_average_dist_time("./Data/DistTime/"+type_inst+"/I_WSPLS"+taille+"_AVG.eval");
//			Tools::save_average_indicator("./Data/ParetoFront/"+type_inst+"/I_WSPLS"+taille+"_AVG.front");
//
//			eval_ks->write_objective_OPT_information();
////			free(eval_ks);
//		}
//		Tools::separate_results("./Data/DistTime/"+type_inst+"/I_WSPLS"+taille+"_AVG.eval",type_inst+to_string(i)+"___");
//		Tools::separate_results("./Data/ParetoFront/"+type_inst+"/I_WSPLS"+taille+"_AVG.front",type_inst+to_string(i)+"___");
//
//	}
//
//
//}

////***********************************************************************************************************************************//
//
//
//Evaluator* main_Knapsack_PLSWS(string filename_instance, string type_instance, string num_instance,
//		int size_population, string WS_DM_preferences, int max_step){
//
////	string pref_filename = "./WS_Matrix.csv";
//
//	MainKnapsack * knaps = new MainKnapsack(filename_instance, size_population);
//
//	clock_t t1 = clock();
//	knaps->HYBRID_PLS_WS(t1/CLOCKS_PER_SEC,max_step);
//	float t2 = (clock() - t1) * 1.0/CLOCKS_PER_SEC;
//
//	cout<<"Execution time : "<<t2<<" sec"<<endl<<endl;
//
//	string size_instance = to_string(knaps->get_n_items());
//
//	Evaluator * eval = new Evaluator(filename_instance, knaps, WS_DM_preferences,
//			"./Data/DistTime/"+type_instance+"/I"+num_instance+"_"+size_instance+"_PLSWS.eval"
//			, t2,
//			"./Data/ParetoFront/"+type_instance+"/I"+num_instance+"_"+size_instance+"_PLSWS.front");
//
//	return eval;
//}
//
//void script_PLSWS(string type_inst, string taille, string WS_DM){
//
//	Evaluator * eval_ks;
//
//
//	for(int i = 0; i < 3; i++){
//
//		string filename_instance = "./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);
//
//
//		for(int iter = 10; iter <= 11 ; iter+= 50 ){
//			cout<<"============================================   "<<iter<<" STEPS   ============================================"<<endl;
//			Tools::cpt = 0;
//			Tools::clean_up();
//			ITERATION_WS_PLS = iter;
//
//
//			for(int k = 0; k < 1; k++){
//				eval_ks = main_Knapsack_PLSWS(filename_instance, type_inst, to_string(i),1, WS_DM, iter);
//			}
//			Tools::save_average_dist_time("./Data/DistTime/"+type_inst+"/I_PLSWS"+taille+"_AVG.eval");
//
//			Tools::save_average_indicator("./Data/ParetoFront/"+type_inst+"/I_PLSWS"+taille+"_AVG.front");
//
//			eval_ks->write_objective_OPT_information();
//
//			free( eval_ks );
//		}
//		Tools::separate_results("./Data/DistTime/"+type_inst+"/I_PLSWS"+taille+"_AVG.eval",type_inst+to_string(i)+"___");
//		Tools::separate_results("./Data/ParetoFront/"+type_inst+"/I_PLSWS"+taille+"_AVG.front",type_inst+to_string(i)+"___");
//
//	}
//
//
//}
//

