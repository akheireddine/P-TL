
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

void script_knapsack(string type_inst, string taille, string WS_DM, string p_criteria ){

	int K = 10;
	int N = 1;
	int I = 1;

	vector<int> graines;

	string prefix = "_AVG_MOLS2";

	srand(time(NULL));



	for(int i = 0; i < N ; i++){
		string filename_instance = "./Instances_Knapsack"+p_criteria+"/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);

		eval_ks = make_shared< Evaluator >(filename_instance, WS_DM,
				"./Data/Evaluation"+p_criteria+"/"+type_inst+"/"+taille+"/T"+to_string(i)+"/"+prefix+"/K_"+to_string(K)+".eval");

		MainKnapsack::Generate_random_Population(eval_ks, K);


		graines.clear();

		for(int k = 0; k < K; k++){
			graines.push_back( rand());
		}


//!!!!!!!!!!!!!!!!!!!!! CHANGE DMS WSUMM FOR TEST1 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		for(int step = 0; step < I; step++){

			string filename_population = "./Data/Population"+p_criteria+"/"+type_inst+"/"+taille+"/T"+to_string(i);
			INFO = to_string(step);
			cout<<"_________________________________ STEP"<<step<<"___________________________"<<endl;
			eval_ks->set_WS_matrix(Tools::readMatrix("./Data/WS_Learning/Test2/Iteration_"+to_string(step)));

//			eval_ks->readWS_matrix(WS_matrix_file);
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

void script_knapsack_WSPLS(string type_inst, string taille, string WS_DM, string p_criteria ){

	int K = 1;
	int N = 1;
	string I = "1";

//	int iter;
	vector<int> graines;

	string prefix = "_AVG_Ta_500";

	srand(time(NULL));

	INFO = I;
	for(int i = 0; i < N ; i++){
		string filename_instance = "./Instances_Knapsack"+p_criteria+"/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);

		eval_ks = make_shared< Evaluator >(filename_instance, WS_DM,
				"./Data/Evaluation"+p_criteria+"/"+type_inst+"/"+taille+"/T"+to_string(i)+"/"+prefix+"/K_"+to_string(K)+".eval");


		MainKnapsack::Generate_random_Population(eval_ks, K);

		string filename_population = "./Data/Population"+p_criteria+"/"+type_inst+"/"+taille+"/T"+to_string(i);
	//!!!!!!!!!!!!!!!!!!!!! CHANGE DMS WSUMM FOR TEST1 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		for(int step = 500; step < 501; step++){
			cout<<"_________________________________ NB-ITER "<<step<<"___________________________"<<endl;
			eval_ks->set_WS_matrix(Tools::readMatrix("./Data/WS_Learning/Test2/Iteration_"+I));

//			eval_ks->readWS_matrix(WS_matrix_file);      //A VOIR PB
			eval_ks->update_covered_PFront();


			for(int k = 0; k < K; k++){
				k_replication = k;
//				Tools::generate_random_WS(WS_matrix_file, 2);   // NOT SYNCHRO AVEC EVAL
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

void main_Knapsack_PLSWS(string filename_instance, int size_population, vector< int > UB, vector< string > steps){

	MainKnapsack * knaps = new MainKnapsack(eval_ks, size_population, filename_instance, false);

	clock_t t = clock();

	knaps->MOLS_SWITCH_OBJECTIVE(t/CLOCKS_PER_SEC, UB , steps);

	float time_cpu = (clock() - t) * 1.0/CLOCKS_PER_SEC;

	cout<<"Execution time : "<<time_cpu<<" sec"<<endl<<endl;

//	eval_ks->evaluate_PF( knaps->get_OPT_Solution(), time_cpu);


//	delete knaps;
}



void script_knapsack_PLSWS(string type_inst, string taille, string WS_DM, string p_criteria ){

	int K = 30;
	int N = 3;
	string path_information = "./Data/WS_Learning/Test2/Iteration_";
	vector< string > I = {path_information+"0", path_information+"1", path_information+"2", path_information+"3", path_information+"4", path_information+"5"
	,path_information+"6", path_information+"7"};


	vector<int> graines;

	string prefix = "MOLS_SWITCH_OBJECTIVE/OS";                //OS and RS  use MOLS_PSize/OS

	srand(time(NULL));

	vector<int> sizer = {2,8,20,30,40,50,60}; //       //A

//	vector<int> sizer = {2,8,20,60,100,200};       //C

//	vector<int> sizer = {2,8,20,60,100,200};        //D

	int info = 0;
	INFO = to_string(info);

	for(int i = 0; i < N; i++){
		string filename_instance = "./Instances_Knapsack"+p_criteria+"/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);
		string filename_indicator = "./Data/Evaluation"+p_criteria+"/"+type_inst+"/"+taille+"/T"+to_string(i)+"/"+prefix+"/K_"+to_string(K)+".eval";
		string filename_population = "./Data/Population"+p_criteria+"/"+type_inst+"/"+taille+"/T"+to_string(i)+"/"+prefix;

		eval_ks = make_shared< Evaluator >(filename_instance, WS_DM,filename_indicator);

		eval_ks->set_WS_matrix(Tools::readMatrix(I[info]));

		eval_ks->update_covered_PFront();

		MainKnapsack::Generate_random_Population(eval_ks, K);

		graines.clear();
		for(int k = 0; k < K; k++){
			graines.push_back( rand());
		}

//		for(auto iter : sizer){
//			cout<<"============================================   "<<iter<<" POP SIZE   ============================================"<<endl;

			for(int k = 0; k < K; k++){
				k_replication = k  ;
				GRAIN = graines[k];
				srand( GRAIN );
				main_Knapsack_PLSWS(filename_population, 1, sizer, I);
			}
//		}
		eval_ks.reset();
	}
}



//***********************************************************************************************************************************//






void script_Cst_PSizeV1V2(string type_inst, string taille, string WS_DM, string p_criteria ){

	int K = 29;
	int N = 1;
	string testname = "./Data/WS_Learning/Test2/Iteration_";
	vector< string > I = {testname+"1",testname+"2",testname+"3",testname+"4",testname+"5",testname+"6",testname+"7"};

	vector< string> step(1,testname+"0");

	vector< string > prefixes = {"MOLS_PSize", "MOLS_PSize_DIV/OS"};                //OS and RS  use MOLS_PSize/OS

	vector<int> sizer = {2,8,20,60,100};     //   //A

//	vector<int> sizer = {2,8,20,60,100,200};  //C

//	vector<int> sizer = {2,8,20,60,100,200};        //D


	string filename_indicator = "./Data/Evaluation"+p_criteria+"/"+type_inst+"/"+taille;
	ofstream fic1(filename_indicator+"/K_"+to_string(K)+".v1");
	ofstream fic2(filename_indicator+"/K_"+to_string(K)+".v2");

	for(size_t j = 0; j < prefixes.size(); j++){
		for(int i = 0; i < N; i++){
			string filename_instance = "./Instances_Knapsack"+p_criteria+"/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);
			string filename_population = "./Data/Population"+p_criteria+"/"+type_inst+"/"+taille+"/T"+to_string(i)+"/"+prefixes[j];

			eval_ks = make_shared< Evaluator >(filename_instance, WS_DM);

			eval_ks->set_K_replication(K);

			//V2 NO FILTERING
			eval_ks->save_information(filename_population+"/V2",filename_indicator, "v2", step, sizer, vector<int>(1,-1), to_string(i), type_inst, taille, j);

			//V1 FILTERING
			eval_ks->save_information(filename_population+"/V1", filename_indicator, "v1", I, sizer, vector<int>(1,-1), to_string(i), type_inst, taille, j);

			eval_ks.reset();
		}
	}
}





//ORIGINAL
void main_Knapsack_Cst_PSize(string filename_instance, int size_population, int max_size_population ) {

	MainKnapsack * knaps = new MainKnapsack(eval_ks, size_population, filename_instance, false);

	clock_t t = clock();

//	knaps->MOLS_Cst_PSize(t/CLOCKS_PER_SEC,max_size_population);

//	knaps->MOLS_Cst_PSize_RS(t/CLOCKS_PER_SEC,max_size_population);

	knaps->MOLS_Cst_PSize_OS(t/CLOCKS_PER_SEC,max_size_population);

	float time_cpu = (clock() - t) * 1.0/CLOCKS_PER_SEC;

	cout<<"Execution time : "<<time_cpu<<" sec"<<endl<<endl;

	delete knaps;
}





//// ORIGINAL VERSION
void script_Cst_PSize(string type_inst, string taille, string WS_DM, string p_criteria){

	int K = 30;
	int N = 1;
	vector< string > I = {"0","1","2","3","4","5","6","7"};
	string testname = "Test2";

	vector<int> graines;

	string prefix = "MOLS_PSize_DIV/OS";                //OS and RS  use MOLS_PSize/OS

	srand(time(NULL));

	vector<int> sizer = {2, 8, 20, 60, 100, 400};  //       //A

//	vector<int> sizer = {2,8,20,60,100,200};       //C

//	vector<int> sizer = {2,8,20,60,100,200};        //D


	for(int i = 0; i < N; i++){
		string filename_instance = "./Instances_Knapsack"+p_criteria+"/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);
		string filename_indicator = "./Data/Evaluation"+p_criteria+"/"+type_inst+"/"+taille+"/T"+to_string(i)+"/"+prefix+"/K_"+to_string(K)+".eval";
		string filename_population = "./Data/Population"+p_criteria+"/"+type_inst+"/"+taille+"/T"+to_string(i);

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

				eval_ks->set_WS_matrix(Tools::readMatrix("./Data/WS_Learning/"+testname+"/Iteration_"+step));

				eval_ks->update_covered_PFront();

				for(int k = 0; k < K; k++){
					k_replication = k + 3 ;
					GRAIN = graines[k];
					srand( GRAIN );
					main_Knapsack_Cst_PSize(filename_population, 1, iter);
				}
			}
		}

		eval_ks.reset();
	}

}



//***********************************************************************************************************************************//







void script_save_information(string type_inst, string taille, string WS_DM, string p_criteria ){

	int K = 30;
	int N = 10;
	string testname = "./Data/WS_Learning/Test2/Iteration_";
	vector< string > I = {testname+"0",testname+"1",testname+"2",testname+"3",testname+"4",testname+"5",testname+"6",testname+"7"};

	vector< string > prefixes = {"MOLS_PSize", "MOLS_PSize_DIV/OS"};                //OS and RS  use MOLS_PSize/OS

	vector<int> sizer = {2,8,20,60,100};  //       //A

//	vector<int> sizer = {2,8,20,60,100,200};  //C

//	vector<int> sizer = {2,8,20,60,100,200};        //D

	string filename_indicator = "./Data/Evaluation"+p_criteria+"/"+type_inst+"/"+taille;

	ofstream fic(filename_indicator+"/K_"+to_string(K)+".eval");
	fic<<"Type, Size, Instance, Budget, PopSize, Info, nb_evaluation, AVG_dist, MaxMin, PR, Diversification"<<endl;
	fic.close();

	for(size_t j = 0; j < prefixes.size(); j++){
		for(int i = 0; i < N; i++){
			string filename_instance = "./Instances_Knapsack"+p_criteria+"/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);
			string filename_population = "./Data/Population"+p_criteria+"/"+type_inst+"/"+taille+"/T"+to_string(i)+"/"+prefixes[j];

			eval_ks = make_shared< Evaluator >(filename_instance, WS_DM);

			eval_ks->set_K_replication(K);

			eval_ks->save_information(filename_population, filename_indicator, "eval", I, sizer,vector< int >(1,-1),to_string(i), type_inst, taille, j );

			eval_ks.reset();
		}
	}
}




void save_avg_instances(string type_inst, string taille, string WS_DM, string p_criteria ){

	int K = 10;
	int N = 3;
	vector<int> I = {1,2,3,4,5,6,7};

	string prefix = "MOLS_PSize";

	vector<int> sizer = {2,8,20,60,100};  //       //A

//	vector<int> sizer = {2,8,20,60,100,200};  //C

//	vector<int> sizer = {2,8,20,60,100,200};        //D

	string save_file = "./Data/Evaluation"+p_criteria+"/"+type_inst+"/"+taille;
	eval_ks->compute_avg_type_instances(save_file, prefix, "v2", K, N, sizer , I);

	eval_ks.reset();

}



//***********************************************************************************************************************************//


void script_learning_data(string type_inst, string taille, string WS_DM, string p_criteria ){

	int K = 30;
	int N = 10;
	vector< int > Budget = {20,60,100,140,220,420,540,820,1220,1820,2020,3200,4020};   //A

	string testname = "./Data/WS_Learning/Test2/Iteration_";
	vector< string > I = {testname+"0",testname+"1",testname+"2",testname+"3",testname+"4",testname+"5",testname+"6",testname+"7"};

	vector< string > prefixes = {"MOLS_PSize", "MOLS_PSize_DIV/OS"};                //OS and RS  use MOLS_PSize/OS

	vector<int> sizer = {2,8,20,60,100};  //       //A

//	vector<int> sizer = {2,8,20,60,100,200};       //C

//	vector<int> sizer = {2,8,20,60,100,200};        //D


	string filename_indicator = "./Data/Evaluation"+p_criteria+"/"+type_inst+"/"+taille;

//	ofstream fic1(filename_indicator+"/K_"+to_string(K)+".eval");
//	fic1<<"Type, Size, Instance, Budget, PopSize, Info, nb_evaluation, AVG_dist, MaxMin, PR, Diversification"<<endl;
//	fic1.close();
	ofstream fic2(filename_indicator+"/K_"+to_string(K)+".opt");
	fic2<<"Type, Size, Instance, Budget, PopSize, Info, nb_evaluation, AVG_dist, MaxMin, PR, Diversification"<<endl;
	fic2.close();

	for(size_t j = 0; j < prefixes.size(); j++){
		for(int i = 0; i < N; i++){
			string filename_instance = "./Instances_Knapsack"+p_criteria+"/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);
			string filename_population = "./Data/Population"+p_criteria+"/"+type_inst+"/"+taille+"/T"+to_string(i)+"/"+prefixes[j];

			eval_ks = make_shared< Evaluator >(filename_instance, WS_DM);

			eval_ks->set_K_replication(K);

//			eval_ks->save_information(filename_population, filename_indicator, "eval", I, sizer, Budget, to_string(i), type_inst, taille, j);

			eval_ks->save_best_parameters(filename_indicator, "eval", I, sizer, Budget,to_string(i));

			eval_ks.reset();
		}
	}
}


void script_learning_data_SWITCH(string type_inst, string taille, string WS_DM, string p_criteria ){

	int K = 25;
	int N = 3;
	vector< int > Budget = {20,60,100,140,220,420,540,820,1220,1820,2020,3200,4020};   //A

	string testname = "./Data/WS_Learning/Test2/Iteration_";
	vector< string > I = {testname+"0"};//,testname+"1",testname+"2",testname+"3",testname+"4",testname+"5",testname+"6",testname+"7"};

	vector< string > prefixes = {"MOLS_SWITCH_OBJECTIVE", "MOLS_SWITCH_OBJECTIVE/OS"};                //OS and RS  use MOLS_PSize/OS

	vector<int> sizer = {-1};


	string filename_indicator = "./Data/Evaluation"+p_criteria+"/"+type_inst+"/"+taille;

	ofstream fic1(filename_indicator+"/K_"+to_string(K)+".evalS");
	fic1<<"Type, Size, Instance, Budget, PopSize, Info, nb_evaluation, AVG_dist, MaxMin, PR, Diversification"<<endl;
	fic1.close();
//	ofstream fic2(filename_indicator+"/K_"+to_string(K)+".optS");
//	fic2<<"Type, Size, Instance, Budget, PopSize, Info, nb_evaluation, AVG_dist, MaxMin, PR, Diversification"<<endl;
//	fic2.close();

	for(size_t j = 0; j < prefixes.size(); j++){
		for(int i = 0; i < N; i++){
			string filename_instance = "./Instances_Knapsack"+p_criteria+"/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);
			string filename_population = "./Data/Population"+p_criteria+"/"+type_inst+"/"+taille+"/T"+to_string(i)+"/"+prefixes[j];

			eval_ks = make_shared< Evaluator >(filename_instance, WS_DM);

			eval_ks->set_K_replication(K);

			eval_ks->save_information(filename_population, filename_indicator, "evalS", I, sizer, Budget, to_string(i), type_inst, taille, j);

//			eval_ks->save_best_parameters(filename_indicator, "evalS", I, sizer, Budget,to_string(i));

			eval_ks.reset();
		}
	}
}



void script_learning_opt_algo(string type_inst, string taille, string WS_DM, string p_criteria ){

	int K = 30;
	int N = 7;
	vector< int > Budget = {20,60,100,140,220,420,540,820,1220,1820,2020,3200,4020};   //A

	string testname = "./Data/WS_Learning/Test2/Iteration_";
	vector< string > I = {testname+"0",testname+"1",testname+"2",testname+"3",testname+"4",testname+"5",testname+"6",testname+"7"};

	string algo1 = "MOLS_PSize";                //OS and RS  use MOLS_PSize/OS
	string algo2 = "MOLS_PSize_DIV/OS";

	vector<int> sizer = {2,8,20,60,100};  //       //A

//	vector<int> sizer = {2,8,20,60,100,200};       //C

//	vector<int> sizer = {2,8,20,60,100,200};        //D

	string save_data = "./Data/Evaluation"+p_criteria+"/"+type_inst+"/"+taille;

//	ofstream fic_write(save_data+"/K_"+to_string(K_replication)+".algo",ios::app);
//	fic_write<<"Type, Size, Budget, Instance, Diversification, PopSize, Info, AVG_dist, MaxMin, PR"<<endl;

	for(auto b : Budget){
		for(int i = 0; i < N; i++){
			string filename_instance = "./Instances_Knapsack"+p_criteria+"/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);
			string filename_indicator = "./Data/Evaluation"+p_criteria+"/"+type_inst+"/"+taille;
			eval_ks = make_shared< Evaluator >(filename_instance, WS_DM);

			eval_ks->set_K_replication(K);

//			eval_ks->best_algo_parametrized(save_data, filename_indicator, to_string(i),b);

			eval_ks.reset();
		}
	}


}

//***********************************************************************************************************************************//




int main(int argc, char** argv){

	string WS_DM = "./weighted_DM_preferences.ks";

	string type_inst = "A";
	string taille = "200";
	string p_criteria = "2";

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

	script_learning_data(type_inst, taille, WS_DM, p_criteria);
//	script_learning_opt_algo(type_inst, taille, WS_DM, p_criteria);
/*
  *************************************************************************************************************************
*/
//	string output1="";
//	string output2="";
//	system( ("python3.7 Instance_Generator.py 2 10 > toto"));


//	Instance_Generator * inst = new Instance_Generator(stoi(taille), stoi(p_criteria), 10);
//	inst->random_instances("Instances_Knapsack"+p_criteria+"/Type_A/"+taille+"_items");
//
//	inst->conflicting_instances("Instances_Knapsack"+p_criteria+"/Type_B/"+taille+"_items");


/*
  *************************************************************************************************************************
*/
//	script_Cst_PSize(type_inst,taille,WS_DM, p_criteria);
////
//	script_Cst_PSizeV1V2(type_inst, taille, WS_DM, p_criteria);
//////
//	script_save_information(type_inst, taille, WS_DM, p_criteria);

//	save_avg_instances(type_inst, taille, WS_DM, p_criteria);
//

/*
  *************************************************************************************************************************
*/


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


//	script_knapsack_PLSWS(type_inst,taille,WS_DM, p_criteria);
//	script_learning_data_SWITCH(type_inst,taille,WS_DM, p_criteria);
//	Gnuplotter::Plot_SEARCH_EVOLUTION("./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst, type_inst, taille
//			,"MOLS2", -1, 10, 111 , "./DM_preference_point");


//	Gnuplotter::Plot_SEARCH_EVOLUTION("./Instances_Knapsack/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst, type_inst, taille
//			,"MOLS2", -1, 20, 201 , "./DM_preference_point");
	return 1;

}

































