
#include "MainClass.h"
#include <time.h>

using namespace std;



list< vector< float > > OPT_Solution;


void main_Knapsack(string filename_instance, int size_population){

	MainKnapsack * knaps = new MainKnapsack(eval_ks, size_population, filename_instance, false);
	clock_t t = clock();

	knaps->MOLS(t/CLOCKS_PER_SEC); 								 //3min

	float time_cpu = (clock() - t ) * 1.0/CLOCKS_PER_SEC;

	cout<<"Execution time : "<<time_cpu<<" sec"<<endl<<endl;

	eval_ks->evaluate_PF(knaps->get_OPT_Solution(), time_cpu);

	delete knaps;
}




void script_knapsack(string type_inst, string taille, string WS_DM){

	int K = 10;
	int N = 1;
	int I = 1;

	vector<int> graines;

	string WS_matrix_file = "WS_MatrixA.csv";
	string prefix = "_AVG_MOLS2";
	srand(time(NULL));



	for(int i = 0; i < N ; i++){
		string filename_instance = "./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);

		eval_ks = make_shared< Evaluator >(filename_instance, WS_DM,
				"./Data/Evaluation/"+type_inst+"/"+taille+"/T"+to_string(i)+"/"+prefix+"/K_"+to_string(K)+".eval");

		MainKnapsack::Generate_random_Population(eval_ks, K);


		graines.clear();

		for(int k = 0; k < K; k++){
			graines.push_back( rand());
		}


//!!!!!!!!!!!!!!!!!!!!! CHANGE DMS WSUMM FOR TEST1 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		for(int step = 0; step < I; step++){

			string filename_population = "./Data/Population/"+type_inst+"/"+taille+"/T"+to_string(i);
			INFO = step;
			cout<<"_________________________________ STEP"<<step<<"___________________________"<<endl;
			Tools::copy_into("./Data/WS_Learning/Test2/Iteration_"+to_string(step),WS_matrix_file);

			eval_ks->readWS_matrix(WS_matrix_file);
			eval_ks->update_covered_PFront();


			for(int k = 0; k < K; k++){
				k_replication = k;
				GRAIN = graines[k];
				srand( GRAIN );
				main_Knapsack(filename_population, 1);
			}
			eval_ks->save_PF_evaluation();
		}

		eval_ks.reset();
	}
}



//***********************************************************************************************************************************//


void main_Knapsack_WSPLS(string filename_instance, int size_population, int iter){

	MainKnapsack * knaps = new MainKnapsack(eval_ks, size_population, filename_instance, false);

	clock_t t = clock();

	knaps->HYBRID_WS_PLS(t/CLOCKS_PER_SEC,iter);

	float time_cpu = (clock() - t) * 1.0/CLOCKS_PER_SEC;

	cout<<"Execution time : "<<time_cpu<<" sec"<<endl<<endl;

	eval_ks->evaluate_PF( knaps->get_OPT_Solution(), time_cpu);

	delete knaps;
}


void script_knapsack_WSPLS(string type_inst, string taille, string WS_DM){

	int K = 1;
	int N = 1;
	int I = 1;

//	int iter;
	vector<int> graines;

	string WS_matrix_file = "WS_MatrixA.csv";
	string prefix = "_AVG_Ta_500";
	srand(time(NULL));

	INFO = I;
	for(int i = 0; i < N ; i++){
		string filename_instance = "./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);
		Tools::copy_into("./Data/WS_Learning/Test2/Iteration_"+to_string(I), WS_matrix_file);

		eval_ks = make_shared< Evaluator >(filename_instance, WS_DM,
				"./Data/Evaluation/"+type_inst+"/"+taille+"/T"+to_string(i)+"/"+prefix+"/K_"+to_string(K)+".eval");


		MainKnapsack::Generate_random_Population(eval_ks, K);

		string filename_population = "./Data/Population/"+type_inst+"/"+taille+"/T"+to_string(i);
	//!!!!!!!!!!!!!!!!!!!!! CHANGE DMS WSUMM FOR TEST1 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		for(int step = 500; step < 501; step++){
			cout<<"_________________________________ NB-ITER "<<step<<"___________________________"<<endl;
			eval_ks->readWS_matrix(WS_matrix_file);      //A VOIR PB
			eval_ks->update_covered_PFront();


			for(int k = 0; k < K; k++){
				k_replication = k;
				Tools::generate_random_WS(WS_matrix_file, 2);   // NOT SYNCHRO AVEC EVAL
				GRAIN = graines[k];
				srand( GRAIN );
				main_Knapsack_WSPLS(filename_population, 1, step);
			}

			eval_ks->save_PF_evaluation();
		}

		eval_ks.reset();
	}
}



//***********************************************************************************************************************************//

void main_Knapsack_PLSWS(string filename_instance, int size_population, int iter){

	MainKnapsack * knaps = new MainKnapsack(eval_ks, size_population, filename_instance, false);

	clock_t t = clock();

//	knaps->HYBRID_PLS_WS(t/CLOCKS_PER_SEC,iter);

	knaps->SWITCH_PLS_WS(t/CLOCKS_PER_SEC,iter, 10);

	float time_cpu = (clock() - t) * 1.0/CLOCKS_PER_SEC;

	cout<<"Execution time : "<<time_cpu<<" sec"<<endl<<endl;

	eval_ks->evaluate_PF( knaps->get_OPT_Solution(), time_cpu);

	delete knaps;
}



void script_knapsack_PLSWS(string type_inst, string taille, string WS_DM){

	int K = 1;
	int N = 1;
	int I = 1;

	INFO = I;
	vector<int> graines;

	string WS_matrix_file = "WS_MatrixA.csv";
	string prefix = "_AVG_Ta_500";
	srand(time(NULL));



	for(int i = 0; i < N ; i++){
		string filename_instance = "./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);
		Tools::copy_into("./Data/WS_Learning/Test2/Iteration_"+to_string(I), WS_matrix_file);

		eval_ks = make_shared< Evaluator >(filename_instance, WS_DM,
				"./Data/Evaluation/"+type_inst+"/"+taille+"/T"+to_string(i)+"/"+prefix+"/K_"+to_string(K)+".eval");

		MainKnapsack::Generate_random_Population(eval_ks, K);

		string filename_population = "./Data/Population/"+type_inst+"/"+taille+"/T"+to_string(i);

	//!!!!!!!!!!!!!!!!!!!!! CHANGE DMS WSUMM FOR TEST1 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		for(int step = 50; step < 51; step++){
			cout<<"_________________________________ NB-ITER "<<step<<"___________________________"<<endl;
			eval_ks->readWS_matrix(WS_matrix_file);
			eval_ks->update_covered_PFront();

			for(int k = 0; k < K; k++){
				k_replication = k;
				GRAIN = graines[k];
				srand( GRAIN );
				main_Knapsack_PLSWS(filename_population, 1, step);
			}
			eval_ks->save_PF_evaluation();
		}
		eval_ks.reset();
	}
}



//***********************************************************************************************************************************//






void script_Cst_PSizeV1V2(string type_inst, string taille, string WS_DM){

	int K = 30;
	int N = 10;
	vector<int> I = {0,1,2,3,4,5,6,7};

	string WS_matrix_file = "WS_MatrixA_V12.csv";
	string prefix = "MOLS_PSize";

	vector<int> sizer = {2,8,20,60,100};     //   //A

//	vector<int> sizer = {2,8,20,60,100,200};  //C

//	vector<int> sizer = {2,8,20,60,100,200};        //D


	for(int i = 0; i < N; i++){
		string filename_instance = "./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);
		string filename_indicator = "./Data/Evaluation/"+type_inst+"/"+taille+"/T"+to_string(i)+"/"+prefix;
		eval_ks = make_shared< Evaluator >(filename_instance, WS_DM);

		eval_ks->set_K_replication(K);

		for(auto step : {0}){
			cout<<"_________________________________ STEP"<<step<<"___________________________"<<endl;
			Tools::copy_into("./Data/WS_Learning/Test2/Iteration_"+to_string(step),WS_matrix_file);
			INFO = step;

			eval_ks->readWS_matrix(WS_matrix_file);

			eval_ks->update_covered_PFront();

			for(auto iter : sizer){
				cout<<"============================================   "<<iter<<" POP SIZE   ============================================"<<endl;
				// READ PLS 0 OF UB_BOUND = iter
				string filename_population = "./Data/Population/"+type_inst+"/"+taille+"/T"+to_string(i)+"/"+prefix+"/"+to_string(iter)+"/"+to_string(step);

				//V1 FILTERING
				for(auto steper : {1,2,3,4,5,6,7} ){
					Tools::copy_into("./Data/WS_Learning/Test2/Iteration_"+to_string(steper),WS_matrix_file);

					eval_ks->readWS_matrix(WS_matrix_file);

					eval_ks->update_covered_PFront();

					eval_ks->save_information(filename_population,filename_indicator, "v1");

					Tools::copy_into("./Data/WS_Learning/Test2/Iteration_"+to_string(step),WS_matrix_file);
					eval_ks->readWS_matrix(WS_matrix_file);

					eval_ks->save_information(filename_population,filename_indicator, "v2");
				}
				Tools::separate_results(filename_indicator+"/K_"+to_string(K)+".v1","__________"+to_string(iter));
				Tools::separate_results(filename_indicator+"/K_"+to_string(K)+".v2","__________"+to_string(iter));
			}
		}
		eval_ks.reset();
	}
}





//ORIGINAL
void main_Knapsack_Cst_PSize(string filename_instance, int size_population, int max_size_population ) {

	MainKnapsack * knaps = new MainKnapsack(eval_ks, size_population, filename_instance, false);

	clock_t t = clock();

	knaps->MOLS_Cst_PSize(t/CLOCKS_PER_SEC,max_size_population);

//	knaps->MOLS_Cst_PSize_RS(t/CLOCKS_PER_SEC,max_size_population);

//	knaps->MOLS_Cst_PSize_OS(t/CLOCKS_PER_SEC,max_size_population);


	float time_cpu = (clock() - t) * 1.0/CLOCKS_PER_SEC;

	cout<<"Execution time : "<<time_cpu<<" sec"<<endl<<endl;

//	eval_ks->evaluate_PF( knaps->get_OPT_Solution(), max_size_population, INFO, time_cpu);

//	eval_ks->evaluate_PF( knaps->get_OPT_Solution(), time_cpu);

	delete knaps;
}





//// ORIGINAL VERSION
void script_Cst_PSize(string type_inst, string taille, string WS_DM){

	int K = 30;
	int N = 10;
	vector<int> I = {0,1,2,3,4,5,6,7};

	vector<int> graines;

	string WS_matrix_file = "WS_MatrixAVA.csv";
	string prefix = "MOLS_PSize";                //OS and RS  use MOLS_PSize/OS

	srand(time(NULL));

	vector<int> sizer = {2,8,20,60,100};  //       //A

//	vector<int> sizer = {2,8,20,60,100,200};       //C

//	vector<int> sizer = {2,8,20,60,100,200};        //D


	for(int i = 0; i < N; i++){
		string filename_instance = "./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);
		string filename_indicator = "./Data/Evaluation/"+type_inst+"/"+taille+"/T"+to_string(i)+"/"+prefix+"/K_"+to_string(K)+".eval";
		string filename_population = "./Data/Population/"+type_inst+"/"+taille+"/T"+to_string(i);

		eval_ks = make_shared< Evaluator >(filename_instance, WS_DM,filename_indicator);

		MainKnapsack::Generate_random_Population(eval_ks, K);

		graines.clear();
		for(int k = 0; k < K; k++){
			graines.push_back( rand());
		}

		for(auto iter : sizer){
			cout<<"============================================   "<<iter<<" POP SIZE   ============================================"<<endl;

			for(auto step : I){
				cout<<"_________________________________ STEP"<<step<<"___________________________"<<endl;
				INFO = step;
				Tools::copy_into("./Data/WS_Learning/Test2/Iteration_"+to_string(step),WS_matrix_file);

				eval_ks->readWS_matrix(WS_matrix_file);
				eval_ks->update_covered_PFront();

				for(int k = 0; k < K; k++){
					k_replication = k + 10 ;
					GRAIN = graines[k];
					srand( GRAIN );
					main_Knapsack_Cst_PSize(filename_population, 1, iter);
				}
//				eval_ks->save_PF_evaluation();
			}
//			Tools::separate_results(filename_indicator,"__________"+to_string(iter));
		}

		eval_ks.reset();
	}

}



//***********************************************************************************************************************************//







void script_save_information(string type_inst, string taille, string WS_DM){

	int K = 30;
	int N = 10;
	vector<int> I = {0,1,2,3,4,5,6,7};

	vector<int> graines;

	string WS_matrix_file = "WS_MatrixAz.csv";
	string prefix = "MOLS_PSize";

	vector<int> sizer = {2,8,20,60,100};  //       //A

//	vector<int> sizer = {2,8,20,60,100,200};  //C

//	vector<int> sizer = {2,8,20,60,100,200};        //D


	for(int i = 0; i < N; i++){
		string filename_instance = "./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);
		string filename_indicator = "./Data/Evaluation/"+type_inst+"/"+taille+"/T"+to_string(i)+"/"+prefix;
		eval_ks = make_shared< Evaluator >(filename_instance, WS_DM);

		eval_ks->set_K_replication(K);

		for(auto iter : sizer){

			for(auto step : I){
				cout<<"_________________________________ STEP"<<step<<"___________________________"<<endl;
				INFO = step;
				Tools::copy_into("./Data/WS_Learning/Test2/Iteration_"+to_string(step),WS_matrix_file);
				string filename_population = "./Data/Population/"+type_inst+"/"+taille+"/T"+to_string(i)+"/"+prefix+"/"+to_string(iter)+"/"+to_string(step);

				eval_ks->readWS_matrix(WS_matrix_file);
				eval_ks->update_covered_PFront();

				eval_ks->save_information(filename_population, filename_indicator, "eval");
//				eval_ks->save_other_information(filename_population, filename_indicator+"/"+to_string(iter)+"/"+to_string(step),"iter");
			}
			Tools::separate_results(filename_indicator+"/K_"+to_string(K)+".eval","#__________"+to_string(iter));
//			Tools::separate_results(filename_indicator+".iter","__________"+to_string(iter));
		}

		eval_ks.reset();
	}

}





void save_avg_instances(string type_inst, string taille, string WS_DM){

	int K = 10;
	int N = 3;
	vector<int> I = {1,2,3,4,5,6,7};

	string prefix = "MOLS_PSize";

	vector<int> sizer = {2,8,20,60,100};  //       //A

//	vector<int> sizer = {2,8,20,60,100,200};  //C

//	vector<int> sizer = {2,8,20,60,100,200};        //D

	string save_file = "./Data/Evaluation/"+type_inst+"/"+taille;
	eval_ks->compute_avg_type_instances(save_file, prefix, "v2", K, N, sizer , I);

	eval_ks.reset();

}

//***********************************************************************************************************************************//





int main(int argc, char** argv){

	string WS_DM = "./weighted_DM_preferences.ks";

	string type_inst = "A";
	string taille = "100";

//	script_knapsack(type_inst, taille, WS_DM);
//
//	Gnuplotter::Plot_SEARCH_EVOLUTION_WITH_INFO("./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst, type_inst, taille
//		,"MOLS2", -1 , 10, 410 , "./DM_preference_point");
//
//	Gnuplotter::Comparison_Plot_DIST_TIME("./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_MOLS2_DIVERS_LTA.eval","./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_MOLS2.eval"
//				,type_inst,taille,"DIVERSIFICATION LT_A","NO DIVERSIFICATION");
//	Gnuplotter::Comparison_Plot_INDICATORS("./Data/ParetoFront/"+type_inst+"/I_"+taille+"_AVG_MOLS2_DIVERS_LTA.front",
//			"./Data/ParetoFront/"+type_inst+"/I_"+taille+"_AVG_MOLS2.front",type_inst,taille,"DIVERSIFICATION LT_A","NO DIVERSIFICATION");




//	Gnuplotter::AllPlot_DIST_TIME_PSize("./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_MOLS2.eval", type_inst, taille ,
//			"MOLS2" , 10,  20);



//	Gnuplotter::Comparison_Plot_DIST_TIME("./Data/OTHER_MEASUREMENTS/"+type_inst+"/I_"+taille+"_AVG_MOLS2_onceWS.eval","./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_MOLS2.eval"
//			,type_inst,taille,"Fixe WS - line (1)","Changing WS - line (2)");

//	Gnuplotter::Comparison_Plot_VARIABLE_WS_NEIGHBORHOOD("./Data/OTHER_MEASUREMENTS/"+type_inst+"/I_"+taille+"_AVG_MOLS2_random_w.eval",
//			"./Data/OTHER_MEASUREMENTS/"+type_inst+"/I_"+taille+"_AVG_MOLS2_feasible_w.eval",
//			"./Data/OTHER_MEASUREMENTS/"+type_inst+"/I_"+taille+"_AVG_MOLS2_opt_w.eval",
//			type_inst, taille, "Random weights", "Feasible weights", "Optimal weights");
////
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



//	Instance_Generator::random_instances(stoi(taille),3,"Instances_Knapsack/Type_A/"+taille+"_items", 1);

/*
  *************************************************************************************************************************
*/
//	script_Cst_PSize(type_inst,taille,WS_DM);

	script_Cst_PSizeV1V2(type_inst, taille, WS_DM);
////
	script_save_information(type_inst, taille, WS_DM);

//	save_avg_instances(type_inst, taille, WS_DM);
//
//	vector<int> sizer = {2,8,20,60,80,100};//4,6,8,10,15,20,40,60,80,100,200};//10,50,150,200}; //A
//
////	vector<int> sizer = {2,8,20,60,100,200};  //D
//////
//	for(auto t : sizer){
//		Gnuplotter::Plot_SEARCH_EVOLUTION_WITH_INFO_PSize("./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst, type_inst, taille
//			,"FRONT", t , 10, 410 , "./DM_preference_point");
//		Gnuplotter::Plot_SEARCH_EVOLUTION_WITH_INFO_PSize("./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst, type_inst, taille
//			,"POPULATION", t , 10, 410 , "./DM_preference_point");
////		Gnuplotter::Plot_SEARCH_EVOLUTION_WITH_INFO_PSize("./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst, type_inst, taille
////			,"NON_DOMINATED_LOCALLY", t , 10, 410 , "./DM_preference_point");
////		Gnuplotter::Plot_SEARCH_EVOLUTION_WITH_INFO_PSize("./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst, type_inst, taille
////			,"NEIGHBORS", t , 10, 410 , "./DM_preference_point");
//	}

//	Gnuplotter::Plot_SEARCH_EVOLUTION("./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst, type_inst, taille
//			,"MOLS2", 1, 20, 201 , "./DM_preference_point");
//
//	Gnuplotter::AllPlot_DIST_TIME_PSize("./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_PS2","./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_MOLS2.eval",
//			type_inst, taille , "PS2" , 10,  20);


//
//	Gnuplotter::DIST_TIME_PSize_RESUM_X("./Data/DistTime/"+type_inst+"/I_"+taille+"_AVG_PS_LTA", type_inst, taille,"PS" ,1, 10);
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


//	script_knapsack_PLSWS(type_inst,taille,WS_DM);


//	Gnuplotter::Plot_SEARCH_EVOLUTION("./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst, type_inst, taille
//			,"MOLS2", -1, 10, 111 , "./DM_preference_point");


//	Gnuplotter::Plot_SEARCH_EVOLUTION("./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst, type_inst, taille
//			,"MOLS2", -1, 20, 201 , "./DM_preference_point");
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
//			Tools::cpt_count = 0;
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
//			Tools::cpt_count = 0;
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

