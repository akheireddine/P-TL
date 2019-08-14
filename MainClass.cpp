
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
	int N = 10;
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

			eval_ks->update_covered_PFront();


			for(int k = 0; k < K; k++){
				k_replication = k;
				GRAIN = graines[k];
				srand( GRAIN );
				main_Knapsack(filename_population, 1);
			}
//			eval_ks->save_PF_evaluation();
		}

		eval_ks.reset();
	}
}





//***********************************************************************************************************************************//

void main_Knapsack_PLSWS(string filename_instance, int size_population, vector< int > UB, vector< string > steps){

	MainKnapsack * knaps = new MainKnapsack(eval_ks, size_population, filename_instance, false);

	clock_t t = clock();

//	knaps->MOLS_DYN_PSize(t/CLOCKS_PER_SEC, UB , steps);


//	knaps->MOLS_DYN_PSize_OS(t/CLOCKS_PER_SEC, UB , steps);


//	knaps->MOLS_DYNAMIC(t/CLOCKS_PER_SEC, UB, steps);


	knaps->MOLS_DYN_INFO(t/CLOCKS_PER_SEC, UB , steps);


	float time_cpu = (clock() - t) * 1.0/CLOCKS_PER_SEC;

	cout<<"Execution time : "<<time_cpu<<" sec"<<endl<<endl;


}





void script_knapsack_PLSWS(string type_inst, string taille, string WS_DM, string p_criteria ){

	int K = 10;
	int N = 10;
	string path_information = "./Data/WS_Learning/Test2/Iteration_";
	vector< string > I = {path_information+"0", path_information+"1", path_information+"2", path_information+"3", path_information+"4", path_information+"5"
	,path_information+"6", path_information+"7"};


	vector<int> graines;

	string prefix = "FINAL_MOLS_DYN_Info";                //OS and RS  use MOLS_PSize/OS

	srand(time(NULL));

	vector<int> sizer = {60};//,60,100};
//	vector<int> sizer = {100,60,20,8,2};


	int info = 0;
	INFO = to_string(info);

	for(int i = 5; i < N; i++){
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

		for(int k = 0; k < K; k++){
			k_replication = k  ;
			GRAIN = graines[k];
			srand( GRAIN );
			main_Knapsack_PLSWS(filename_population, 1, sizer, I);
		}
		eval_ks.reset();
	}
}



//***********************************************************************************************************************************//


//ORIGINAL
void main_Knapsack_Cst_PSize(string filename_instance, int size_population, int max_size_population ) {

	MainKnapsack * knaps = new MainKnapsack(eval_ks, size_population, filename_instance, false);

	clock_t t = clock();

	knaps->MOLS_Cst_PSize(t/CLOCKS_PER_SEC,max_size_population);

//	knaps->MOLS_Cst_PSize_RS(t/CLOCKS_PER_SEC,max_size_population);

//	knaps->MOLS_Cst_PSize_OS(t/CLOCKS_PER_SEC,max_size_population);

	float time_cpu = (clock() - t) * 1.0/CLOCKS_PER_SEC;

	cout<<"Execution time : "<<time_cpu<<" sec"<<endl<<endl;

	delete knaps;
}


//// ORIGINAL VERSION
void script_Cst_PSize(string type_inst, string taille, string WS_DM, string p_criteria){

	int K = 15;
	int N = 5;
	vector< string > I = {"0","1","2","3","4","5","6","7"};
	string testname = "Test2";

	vector<int> graines;

	string prefix = "MOLS_PSize";                //OS and RS  use MOLS_PSize/OS

	srand(time(NULL));

//	vector<int> sizer = {2, 8, 20, 60, 100, 200};  //
	vector<int> sizer = {10,50, 100, 200};  //
//	vector<int> sizer = {10,30,60,100,200};  //

//	vector<int> sizer = {2,8,20,60,100,200};        //D


	for(int i = 1; i < N; i++){
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
					k_replication = k ;
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


void main_Knapsack_ML_RegLin(string filename_instance, int size_population, vector< int > UB, int Budget
		, int inst_name, float Info_rate) {

	MainKnapsack * knaps = new MainKnapsack(eval_ks, size_population, filename_instance, false);

	clock_t t = clock();

	knaps->MOLS_ML_RegLin(Budget,UB, inst_name, Info_rate);

	float time_cpu = (clock() - t) * 1.0/CLOCKS_PER_SEC;

	cout<<"Execution time : "<<time_cpu<<" sec"<<endl<<endl;

//	delete knaps;
}


void script_knapsack_ML_RegLin(string type_inst, string taille, string WS_DM, string p_criteria ){

	int K = 10;
	int N = 3;
	string path_information = "./Data/WS_Learning/Test2/Iteration_";
	vector< string > I = {path_information+"0", path_information+"1", path_information+"2", path_information+"3", path_information+"4", path_information+"5"
	,path_information+"6", path_information+"7"};


	vector< int > Budget = {50,500,1000,2000,3000,4000};
	vector<int> graines;

	string prefix = "MOLS_ML_RegLin";                //OS and RS  use MOLS_PSize/OS

	srand(time(NULL));

	vector<int> sizer = {2,10,30,50,70,100};

	for(auto info : {0,1}){

		INFO = to_string(info);
		float Info_rate = Tools::compute_information_rate(Tools::readMatrix(I[info]), stoi(p_criteria));


		for(int i = 0; i < N; i++){
			string filename_instance = "./Instances_Knapsack"+p_criteria+"/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);
			string filename_indicator = "./Data/Evaluation"+p_criteria+"/"+type_inst+"/"+taille+"/T"+to_string(i)+"/"+prefix+"/K_"+to_string(K)+".eval";
			string filename_population = "./Data/Population"+p_criteria+"/"+type_inst+"/"+taille+"/T"+to_string(i);

			eval_ks = make_shared< Evaluator >(filename_instance, WS_DM,filename_indicator);

			eval_ks->set_WS_matrix(Tools::readMatrix(I[info]));

			eval_ks->update_covered_PFront();

			MainKnapsack::Generate_random_Population(eval_ks, K);

			graines.clear();
			for(int k = 0; k < K; k++){
				graines.push_back( rand());
			}

			for(auto b : Budget){
				for(int k = 0; k < K; k++){
					k_replication = k  ;
					GRAIN = graines[k];
					srand( GRAIN );
					main_Knapsack_ML_RegLin(filename_population, 1, sizer, b, i, Info_rate);
				}
			}
			eval_ks.reset();
		}
	}
}


//***********************************************************************************************************************************//

void main_Knapsack_DYN_MULTIPLE_PARAM(string filename_instance, int size_population, vector< int > UB, int Budget
		, int inst_name, vector< string> Informations){

	MainKnapsack * knaps = new MainKnapsack(eval_ks, size_population, filename_instance, false);

	clock_t t = clock();

	knaps->MOLS_DYN_MULTIPLE_PARAM(Budget, UB, inst_name, Informations);

	float time_cpu = (clock() - t) * 1.0/CLOCKS_PER_SEC;

	cout<<"Execution time : "<<time_cpu<<" sec"<<endl<<endl;

}

void script_knapsack_DYN_MULTIPLE_PARAM(string type_inst, string taille, string WS_DM, string p_criteria ){

	int K = 10;
	int N = 10;
	string path_information = "./Data/WS_Learning/Test2/Iteration_";
	vector< string > I = {path_information+"0", path_information+"1", path_information+"2", path_information+"3", path_information+"4", path_information+"5"
	,path_information+"6", path_information+"7"};


//	vector< int > Budget = {50,500,1000,2000,3000,4000,5000,8000};
	vector< int > Budget = {50,250,500,800,2020,4020,6020,8020};

	vector<int> graines;

	string prefix = "FINAL_MOLS_DYN_MULTIPLE_PARAM";                //OS and RS  use MOLS_PSize/OS

	srand(time(NULL));

	vector<int> sizer = {2,10,20,30,40,50,60,70,100};




	for(int i = 0; i < N; i++){
		string filename_instance = "./Instances_Knapsack"+p_criteria+"/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);
		string filename_indicator = "./Data/Evaluation"+p_criteria+"/"+type_inst+"/"+taille+"/T"+to_string(i)+"/"+prefix+"/K_"+to_string(K)+".eval";
		string filename_population = "./Data/Population"+p_criteria+"/"+type_inst+"/"+taille+"/T"+to_string(i)+"/"+prefix;

		eval_ks = make_shared< Evaluator >(filename_instance, WS_DM,filename_indicator);

		eval_ks->set_WS_matrix(Tools::readMatrix(I[0]));

		eval_ks->update_covered_PFront();

		MainKnapsack::Generate_random_Population(eval_ks, K);

		graines.clear();
		for(int k = 0; k < K; k++){
			graines.push_back( rand());
		}

		for(auto b : Budget){
			for(int k = 0; k < K; k++){
				k_replication = k  ;
				GRAIN = graines[k];
				srand( GRAIN );
				main_Knapsack_DYN_MULTIPLE_PARAM(filename_population, 1, sizer, b, i, I);
			}
		}
		eval_ks.reset();
	}
}


//***********************************************************************************************************************************//


void script_save_information(string type_inst, string taille, string WS_DM, string p_criteria ){

	int id_type_inst = 0;
	if(type_inst.compare("C") == 0)
		id_type_inst = 1;
	else if (type_inst.compare("D") == 0)
		id_type_inst = 2;

	int K = 20;
	int N = 10;
	string testname = "./Data/WS_Learning/Test2/Iteration_";
	vector< string > I = {testname+"0",testname+"1",testname+"2",testname+"3",testname+"4",testname+"5",testname+"6",testname+"7"};

	vector< string > prefixes = {"MOLS_PSize"};//, "MOLS_PSize_DIV/OS"};                //OS and RS  use MOLS_PSize/OS

	vector<int> sizer = {200};//2,8,20,60,100,200};


	string filename_indicator = "./Data/Evaluation"+p_criteria+"/"+type_inst+"/"+taille;

	string format_in = "evalRAPPORT";
	ofstream fic(filename_indicator+"/K_"+to_string(K)+"."+format_in);
	fic<<"Type, Size, Instance, Budget, PopSize, Info, nb_evaluation, AVG_dist, MaxMin, PR, Diversification"<<endl;
	fic.close();

	for(size_t j = 0; j < prefixes.size(); j++){
		for(int i = 0; i < N; i++){
			string filename_instance = "./Instances_Knapsack"+p_criteria+"/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);
			string filename_population = "./Data/Population"+p_criteria+"/"+type_inst+"/"+taille+"/T"+to_string(i)+"/"+prefixes[j];

			eval_ks = make_shared< Evaluator >(filename_instance, WS_DM);

			eval_ks->set_K_replication(K);

			eval_ks->save_information(filename_population, filename_indicator, format_in, I, sizer,vector< int >(1,-1), i, id_type_inst, taille, j );

			eval_ks.reset();
		}
	}
}

void save_avg_instances(string type_inst, string taille, string WS_DM, string p_criteria ){

	int K = 30;
	int N = 10;
	vector<int> I = {0,1,2,3,4,5,6,7};

	string prefix = "MOLS_PSize";
	string format_in = "evalRAPPORT";
	vector<int> sizer = {100};//2,8,20,60,100};  //       //A

//	vector<int> sizer = {2,8,20,60,100,200};  //C

//	vector<int> sizer = {2,8,20,60,100,200};        //D

	string save_file = "./Data/Evaluation"+p_criteria+"/"+type_inst+"/"+taille;
	eval_ks->compute_avg_type_instances(save_file, prefix, format_in, K, N, sizer , I);

	eval_ks.reset();

}

void script_Cst_PSizeV1V2(string type_inst, string taille, string WS_DM, string p_criteria ){

	int id_type_inst = 0;
	if(type_inst.compare("C") == 0)
		id_type_inst = 1;


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
			eval_ks->save_information(filename_population+"/V2",filename_indicator, "v2", step, sizer, vector<int>(1,-1), i, id_type_inst, taille, j);

			//V1 FILTERING
			eval_ks->save_information(filename_population+"/V1", filename_indicator, "v1", I, sizer, vector<int>(1,-1), i, id_type_inst, taille, j);

			eval_ks.reset();
		}
	}
}


//***********************************************************************************************************************************//



void script_learning_data(string type_inst, string taille, string WS_DM, string p_criteria ){

	int id_type_inst = 0;
	if(type_inst.compare("C") == 0)
		id_type_inst = 1;

	int K = 20;
	int N = 10;
	vector< int > Budget = {20,60,100,140,220,420,540,820,1220,1820,2020,3200,4020,6020,8020};   //A
//	vector< int > Budget = {50,500,1000,2000,3000,4000,5000,8000};

	string testname = "./Data/WS_Learning/Test2/Iteration_";

	vector< string > I = {testname+"0",testname+"1",testname+"2",testname+"3",testname+"4",testname+"5",testname+"6",testname+"7"};
	vector<float> info_rate;
	for(size_t i = 0; i < I.size(); i++){
		info_rate.push_back( Tools::compute_information_rate(Tools::readMatrix(I[i]), stoi(p_criteria)) );
	}

	vector< string > prefixes = {"MOLS_PSize"};//,"MOLS_PSize_DIV/OS"};                //OS and RS  use MOLS_PSize/OS

	vector<int> sizer = {100};//2,8,20,60,100};  //       //A

//	vector<int> sizer = {2,8,20,60,100,200};       //C

//	vector<int> sizer = {2,8,20,60,100,200};        //D


	string filename_indicator = "./Data/Evaluation"+p_criteria+"/"+type_inst+"/"+taille;

	string format_in = "evalRAPPORT2";
	string format_out = "opt";

	ofstream fic1(filename_indicator+"/K_"+to_string(K)+"."+format_in);
	fic1<<"Type, Size, Instance, Budget, PopSize, Info, nb_evaluation, AVG_dist, MaxMin, PR, Diversification"<<endl;
	fic1.close();
//	ofstream fic2(filename_indicator+"/K_"+to_string(K)+"."+format_out);
//	fic2<<"Type,  Size,  Instance,  Budget,  PopSize, Info,  nb_evaluation,  AVG_dist,  MaxMin,  PR,  Diversification"<<endl;
//	fic2.close();


	for(int i = 0; i < N; i++){
		string filename_instance = "./Instances_Knapsack"+p_criteria+"/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);
		eval_ks = make_shared< Evaluator >(filename_instance, WS_DM);
		eval_ks->set_K_replication(K);

		for(size_t j = 0; j < prefixes.size(); j++){
			string filename_population = "./Data/Population"+p_criteria+"/"+type_inst+"/"+taille+"/T"+to_string(i)+"/"+prefixes[j];
			eval_ks->save_information(filename_population, filename_indicator, format_in, I, sizer, Budget, i, id_type_inst, taille, j);
		}
//		eval_ks->save_best_parameters(filename_indicator, format_in, format_out, info_rate, sizer, Budget, i);
		eval_ks.reset();
	}
}


void script_learning_data_SWITCH(string type_inst, string taille, string WS_DM, string p_criteria ){

	int id_type_inst = 0;
	if(type_inst.compare("C") == 0)
		id_type_inst = 1;

	int K = 10;
	int N = 10;
	vector< int > Budget = {20,60,100,140,220,420,540,820,1220,1820,2020,3200,4020,6020,8020};   //A
//	vector< int > Budget = {50,250,500,800,2020,4020,6020,8020};

	string testname = "./Data/WS_Learning/Test2/Iteration_";

	vector< string > I = {testname+"1"};//,testname+"1",testname+"2",testname+"3",testname+"4",testname+"5",testname+"6",testname+"7"};
	vector<float> info_rate;
	for(size_t i = 0; i < I.size(); i++){
		info_rate.push_back( Tools::compute_information_rate(Tools::readMatrix(I[i]), stoi(p_criteria)) );
	}
	vector< string > prefixes = {"FINAL_MOLS_DYN_PSize_DEC/1"};                //OS and RS  use MOLS_PSize/OS

	vector<int> sizer = {-1};


	string filename_indicator = "./Data/Evaluation"+p_criteria+"/"+type_inst+"/"+taille;

	string format_in = "eval_DYN_PSize_DEC1";
	string format_out = "opt_DYN_PSize_DEC1";

	ofstream fic1(filename_indicator+"/K_"+to_string(K)+"."+format_in);
	fic1<<"Type, Size, Instance, Budget, PopSize, Info, nb_evaluation, AVG_dist, MaxMin, PR, Diversification"<<endl;
	fic1.close();
//	ofstream fic2(filename_indicator+"/K_"+to_string(K)+"."+format_out);
//	fic2<<"Type, Size, Instance, Budget, PopSize, Info, nb_evaluation, AVG_dist, MaxMin, PR, Diversification"<<endl;
//	fic2.close();

	for(int i = 0; i < N; i++){
		string filename_instance = "./Instances_Knapsack"+p_criteria+"/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);
		eval_ks = make_shared< Evaluator >(filename_instance, WS_DM);
		eval_ks->set_K_replication(K);

		for(size_t j = 0; j < prefixes.size(); j++){
			string filename_population = "./Data/Population"+p_criteria+"/"+type_inst+"/"+taille+"/T"+to_string(i)+"/"+prefixes[j];
			eval_ks->save_information(filename_population, filename_indicator, format_in, I, sizer, Budget, i, id_type_inst, taille, j);
		}
//		eval_ks->save_best_parameters(filename_indicator, format_in, format_out, info_rate, sizer, Budget, i);
		eval_ks.reset();
	}
}


void script_learning_opt_algo(string type_inst, string taille, string WS_DM, string p_criteria ){

	int K = 30;
	int N = 10;
	vector< int > Budget = {20,60,100,140,220,420,540};//,820,1220,1820,2020,3200,4020};   //A

	string testname = "./Data/WS_Learning/Test2/Iteration_";
	vector< string > I = {testname+"0",testname+"1",testname+"2",testname+"3",testname+"4",testname+"5",testname+"6",testname+"7"};

	string algo1 = "MOLS_PSize";                //OS and RS  use MOLS_PSize/OS
	string algo2 = "MOLS_PSize_DIV/OS";

	vector<int> sizer = {2,8,20,60,100};  //       //A

//	vector<int> sizer = {2,8,20,60,100,200};       //C

//	vector<int> sizer = {2,8,20,60,100,200};        //D

	string save_data = "./Data/Evaluation"+p_criteria+"/"+type_inst+"/"+taille;
	string format_in = "opt";
	string format_out = "algo";
	ofstream fic_write(save_data+"/K_"+to_string(K)+"."+format_out);
	fic_write<<"Type,  Size,  Instance,  Budget,  PopSize,  Info,  nb_evaluation,  AVG_dist,  MaxMin,  PR,  Diversification"<<endl;

	for(auto b : Budget){
		for(int i = 0; i < N; i++){
			string filename_instance = "./Instances_Knapsack"+p_criteria+"/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);
			string filename_indicator = "./Data/Evaluation"+p_criteria+"/"+type_inst+"/"+taille;
			eval_ks = make_shared< Evaluator >(filename_instance, WS_DM);

			eval_ks->set_K_replication(K);

			eval_ks->best_algo_parametrized(save_data, filename_indicator,format_in, format_out, i,b);

			eval_ks.reset();
		}
	}


}



//***********************************************************************************************************************************//










int main(int argc, char** argv){

	string WS_DM = "./weighted_DM_preferences.ks";

	string type_inst = "C";
	string taille = "100";
	string p_criteria = "2";

//	script_knapsack(type_inst, taille, WS_DM, p_criteria);
//
//	Gnuplotter::Plot_SEARCH_EVOLUTION_WITH_INFO("./Data"+p_criteria+"/"+type_inst+"/"+taille, type_inst, taille
//		,"MOLS_PSize", 100 , -1, 410 , "./DM_preference_point");

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
	script_learning_data_SWITCH(type_inst,taille,WS_DM, p_criteria);




/*
  *************************************************************************************************************************
*/

//	script_OPT_ParamsCheating(type_inst,taille,WS_DM, p_criteria);
//	script_learning_data_SWITCH(type_inst,taille,WS_DM, p_criteria);





/*
  *************************************************************************************************************************
*/

//	script_knapsack_ML_RegLin(type_inst,taille,WS_DM, p_criteria);

/*
  *************************************************************************************************************************
*/


//	script_knapsack_DYN_MULTIPLE_PARAM(type_inst,taille,WS_DM, p_criteria);





	return 1;

}

























//void main_Knapsack_ParamsCheating(string filename_instance, int size_population, vector< map< string, float > > Parameters,
//		map<float,int> info_rate, string info_file ){
//
//	MainKnapsack * knaps = new MainKnapsack(eval_ks, size_population, filename_instance, false);
//
//	clock_t t = clock();
//
//	knaps->MOLS_OPT_PARAMETERS(t/CLOCKS_PER_SEC, Parameters, info_rate, info_file);
//
//	float time_cpu = (clock() - t) * 1.0/CLOCKS_PER_SEC;
//
//	cout<<"Execution time : "<<time_cpu<<" sec"<<endl<<endl;
//
//	delete knaps;
//}
//
//void script_OPT_ParamsCheating(string type_inst, string taille, string WS_DM, string p_criteria){
//
//	int K_read = 30;
//	int K = 10;
//	int N = 10;
//	string testname = "./Data/WS_Learning/Test2/Iteration_";
//	vector< string > I = {testname+"0",testname+"1",testname+"2",testname+"3",testname+"4",testname+"5",testname+"6",testname+"7"};
//
//	vector<int> graines;
//
//	string prefix = "MOLS_OPT_PARAMETERS_SHUFFLE";
//
//	srand(time(NULL));
//
//
//
//	map<float, int> info_rate;
//	for(size_t i = 0; i < I.size(); i++){
//		float key = Tools::compute_information_rate(Tools::readMatrix(I[i]), stoi(p_criteria));
//		info_rate[key] = i;
//	}
//
//	string datafile = "./Data/Evaluation"+p_criteria+"/"+type_inst+"/"+taille+"/K_"+to_string(K_read)+".algo";
//
//	for(int i = 0; i < N; i++){
//
//		vector< map< string, float > > opt_parameters = Tools::readOPTalgoFile(datafile, i);
//
//		string filename_instance = "./Instances_Knapsack"+p_criteria+"/Type_"+type_inst+"/"+taille+"_items/2KP"+taille+"-T"+type_inst+"-"+to_string(i);
//		string filename_indicator = "./Data/Evaluation"+p_criteria+"/"+type_inst+"/"+taille+"/T"+to_string(i)+"/"+prefix+"/K_"+to_string(K)+".eval";
//		string filename_population = "./Data/Population"+p_criteria+"/"+type_inst+"/"+taille+"/T"+to_string(i);
//
//		eval_ks = make_shared< Evaluator >(filename_instance, WS_DM,filename_indicator);
//		eval_ks->set_WS_matrix(Tools::readMatrix(I[0]));
//		eval_ks->update_covered_PFront();
//
//
//		MainKnapsack::Generate_random_Population(eval_ks, K);
//
//		graines.clear();
//		for(int k = 0; k < K; k++){
//			graines.push_back( rand());
//		}
//
//		for(int k = 0; k < K; k++){
//			k_replication = k ;
//			GRAIN = graines[k];
//			srand( GRAIN );
//			main_Knapsack_ParamsCheating(filename_population, 1, opt_parameters, info_rate, testname);
//		}
//		eval_ks.reset();
//	}
//
//}







//void F_prediction_A100(float siz, float budg, float inf, int div, float inst, float & avg, float & pr, float & maxmin){
//
//	avg = 0.0603 + (-0.0135)* inst +  (-0.2201)* budg + 0.138 * siz + 0.0283 * inf + 0.1225 * div;
//
//	maxmin = 0.0816 + (-0.023) * inst + (-0.2109) * budg + 0.1092 * siz + 0.2197 * inf + 0.1125 * div;
//
//	pr = 0.012 + (-0.089) * inst + 0.2857 * budg + 0.0534 * siz + (-0.0205) * inf + 0.1441 * div;
//}
//
//
//void ML_LinearRegression(string type_inst, string taille, string p_criteria){
//
//	string id_type_inst = "0";
//	if(type_inst.compare("C") == 0)
//		id_type_inst = "1";
//
//
//	vector< float > PopSize = {0.02, 0.082, 0.102, 0.153, 0.204, 0.306, 0.408, 0.51, 0.612, 0.816, 1.02};
//	vector< float > Budget = {0.005, 0.01, 0.013, 0.015, 0.02, 0.025, 0.03, 0.035, 0.04, 0.045, 0.05, 0.06, 0.07, 0.085, 0.095, 0.11, 0.12, 0.135, 0.145,
//			0.16, 0.17, 0.185, 0.195, 0.205, 0.21, 0.22, 0.245, 0.255, 0.305, 0.355, 0.455, 0.505, 0.605, 0.705, 0.8, 0.855, 0.955, 1.005};
//	vector< float > Information = {1.0, 0.889, 0.778, 0.667, 0.556, 0.456, 0.451, 0.444, 0.333, 0.313, 0.222, 0.167, 0.133, 0.129, 0.111, 0.089, 0.056, 0.048,
//			0.041, 0.011, 0.0};
//	vector< int > Diversification = {0, 1};
//	vector< float > N = {0.0, 0.111, 0.222, 0.333, 0.444, 0.556, 0.667, 0.778, 0.889, 1.0};
//
//	string filename = "./Data/Evaluation"+p_criteria+"/"+type_inst+"/"+taille+"/predicted_value.eval";
//	ofstream fic_write(filename);
//	fic_write<<"Type, Size, Instance, Budget, PopSize, Info, nb_evaluation, AVG_dist, MaxMin, PR, Diversification"<<endl;
//
//	for(auto i : N){
//
//		for(auto s : PopSize){
//
//			for(auto b : Budget){
//
//				for(auto info : Information){
//
//					for(auto d : Diversification){
//
//						float predicted_avg_min = -1, PR = -1, MaxMin = -1;
//						F_prediction_A100(s, b, info, d, i, predicted_avg_min, PR, MaxMin);
//						fic_write<<id_type_inst+", "+taille+", "+to_string(i)+", "+to_string(b)+", "+to_string(s)+", "+to_string(info)+", 0, "
//								+to_string(predicted_avg_min)+", "+to_string(PR)+", "+to_string(MaxMin)+", "+to_string(d)<<endl;
//					}
//
//				}
//			}
//		}
//	}
//}



