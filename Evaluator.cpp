

#include "Evaluator.h"
#include <ilcplex/ilocplex.h>
#include <dirent.h>

//#define __PRINT__


Evaluator::Evaluator(string filename, string WS_DM_preferences, string INDIC_file){

	filename_instance = filename;

	readFilenameInstance(filename_instance);

	indicator_file = INDIC_file;

	WS_DM_vector = Tools::readWS_DM(WS_DM_preferences);

	readParetoFront();


#ifdef __PRINT__
	cout<<"----------------------- EVALUATION ----------------------"<<endl;
#endif

	OPT_Alternative = OPT_Alternative_PLNE(WS_DM_vector);

#ifdef __PRINT__
	cout<<"Preference du décideur ([ " << Tools::print_vector(WS_DM_vector) <<" ]) : "<<endl;
	cout<<"    "<< Tools::print_vector(OPT_Alternative)<<endl;
#endif


#ifdef __PRINT__
	cout<<"----------------------- END EVALUATION ----------------------"<<endl<<endl;
#endif

	Point_indicators.resize(2,0);
	PF_indicators.resize(3,0);
	time = 0;
	K_replication = 0;
	cpt_k = 0;

}


Evaluator::Evaluator(string filename, string WS_DM_preferences, string INDIC_file, vector<int> sizes, vector<int> information_rate, int K){

	filename_instance = filename;

	readFilenameInstance(filename_instance);

	indicator_file = INDIC_file;

	WS_DM_vector = Tools::readWS_DM(WS_DM_preferences);

	readParetoFront();

	OPT_Alternative = OPT_Alternative_PLNE(WS_DM_vector);

	K_replication = K;
	cpt_k = 0;

	for(auto t : sizes ){
		map< int, vector< float > > info_map;
		for(auto c : information_rate ){
			vector<float> new_vec(6,0);
			info_map[c] = new_vec;
		}
		eval_values[t] = info_map;
	}

}





void Evaluator::readParetoFront(){

	string file_extension = filename_instance+".eff";
	ifstream fic(file_extension.c_str());
	string line;
	vector< float > vector_pareto_objective;

	if (!(fic) or file_extension.find(".eff") == std::string::npos){
		cerr<<"Error occurred paretofront1"<<endl;
	}

	PF_Efficient.clear();

	while(!fic.eof()){

		getline(fic,line);
		if (line.size() == 0)
			continue;

		vector_pareto_objective = Tools::decompose_line_to_float_vector(line);
		PF_Efficient.push_back(vector_pareto_objective);
	}

}








void Evaluator::update_covered_PFront(){

	PFront.clear();

	for(vector< vector< float > >::iterator it = PF_Efficient.begin(); it != PF_Efficient.end(); ++it){

		bool dominated = false;
		list< vector< float  > > to_rm;
		vector< float > it_trans = Tools::transform(*it, WS_matrix);

		for(list< vector< float > >::iterator e = PFront.begin(); e != PFront.end(); ++e){

			vector< float > e_trans = Tools::transform(*e, WS_matrix);

			int val =  Tools::dominates(e_trans,it_trans);
			if( val == 1 ){
				dominated = true;
				break;
			}
			else if( val == -1)
				to_rm.push_back(*e);
		}

		if( !dominated ){
			for(list< vector< float > >::iterator rm = to_rm.begin(); rm != to_rm.end(); ++rm){
				PFront.remove(*rm);
			}
			PFront.push_back(*it);
		}
	}

//	ofstream fic_write(("INFO_"+to_string(INFO)+"_OPT_S60_T2").c_str(), ios::app);
//	for(auto t : PFront){
//		fic_write<<Tools::print_vector(t)<<endl;
//	}

//	cout<<"PF/PE   : "<<PFront.size()<<" / "<<PF_Efficient.size()<<endl;
}



//OPTIONAL
void Evaluator::update_covered_OPT_Solution(list< vector< float > > & Opt_Solution){

	bool dominated;

	list< vector< float > > tmp_opt(Opt_Solution.begin(), Opt_Solution.end());

	Opt_Solution.clear();

	for(list< vector< float > >::iterator it = tmp_opt.begin(); it != tmp_opt.end(); ++it){

		dominated = false;
		list< vector< float  > > to_rm;
		vector< float > it_trans = Tools::transform(*it, WS_matrix);

		for(list< vector< float > >::iterator e = Opt_Solution.begin(); e != Opt_Solution.end(); ++e){

			vector< float > e_trans = Tools::transform(*e, WS_matrix);

			int val =  Tools::dominates(e_trans,it_trans);
			if( val == 1 ){
				dominated = true;
				break;
			}
			else if( val == -1)
				to_rm.push_back(*e);
		}
		if( !dominated ){
			for(list< vector< float > >::iterator rm = to_rm.begin(); rm != to_rm.end(); ++rm){
				Opt_Solution.remove(*rm);
			}
			Opt_Solution.push_back(*it);
		}
	}


//	ofstream fic_write(("INFO_"+to_string(INFO)+"_V1_S60").c_str(), ios::app);
//	for(auto t : Opt_Solution){
//		fic_write<<Tools::print_vector(t)<<endl;
//	}
//
//	fic_write.close();
//

//	cout<<"OPT/PE   : "<<Opt_Solution.size()<<" / "<<PFront.size()<<endl;
}





void Evaluator::readFilenameInstance(string filename){

	string line;
	char buff[100];
	int i = 0;
	float weight;
	char *cline, *pch;
	vector< float > line_value;

	ifstream fic((filename+".dat").c_str());

	//comments
	getline(fic,line);
	while( line[0] == 'c' )
		getline(fic,line);

	//number of items
	int n_items = 0;
	if( line[0] == 'n')
		sscanf(line.c_str(),"%s %d",buff,&n_items);

	Items_information.resize(n_items);

	//comments
	getline(fic,line);
	while( line[0] == 'c' )
		getline(fic,line);

	//items information


	while(line[0] == 'i'){

		line.erase(line.begin());
		cline = new char[line.length() + 1]; // or
		std::strcpy(cline, line.c_str());

		line_value.clear();
		pch = strtok (cline," 	");
		while (pch != NULL){
			line_value.push_back(atof(pch));
			pch = strtok (NULL, " 	");
		}

		weight = line_value[0];

		line_value.erase(line_value.begin());

		Items_information[i] = make_tuple(weight,line_value);


		getline(fic,line);
		i++;
	}

	//number of criteria
	p_criteria = 0;
	p_criteria = line_value.size();

	//comments
	while( line[0] == 'c' )
		getline(fic,line);


	//total capacity
	if( line[0] == 'W' )
		sscanf(line.c_str(),"%s %f",buff,&Backpack_capacity);



#ifdef __PRINT__
	cout<<"Information sur l'instance : "<<endl;
	cout<<"   Instance de taille ("<<to_string(n_items)<<")"<<endl;
	cout<<"   Capacité du sac-à-dos ("<<to_string(Backpack_capacity)<<")"<<endl;
	cout<<"   Nombre de criètres ("<<to_string(p_criteria)<<")"<<endl;
#endif
	fic.close();

}


void Evaluator::readWS_matrix(string filename){

	WS_matrix = Tools::readMatrix(filename);

	p_criteria = WS_matrix.size();

	n_objective = WS_matrix[0].size();

}


/**
 * ************************************************* EVALUATION PART *************************************************
 */



//Get minimum gap from OPT_Alternative and save the objective values in vect_criteria
float Evaluator::nearest_alternative(vector< float > & vect_criteria, list< vector< float > > OPT_Solution ){

	vector< float > criteria_val;
	vector< float >tmp_criteria_values;
	float min_ratio = -1, tmp_ratio = -1;


	for(list< vector< float > >::iterator it = OPT_Solution.begin(); it != OPT_Solution.end(); ++it){

		tmp_ratio = Tools::get_ratio((*it), OPT_Alternative, WS_DM_vector);

		if( (min_ratio == -1) or (tmp_ratio < min_ratio) ){
			min_ratio = tmp_ratio;
			criteria_val = tmp_criteria_values;
		}
	}
	vect_criteria = criteria_val;
	return min_ratio;
}


//Get optima values of objective with WS aggregator
vector< float > Evaluator::OPT_Alternative_PLNE(vector<float> WS_vector){

	int n_item = Items_information.size();
	IloEnv   env;
	IloModel model(env);
	vector<IloNumVar > x( n_item );
	IloRangeArray Constraints(env);

	//VARIABLES
	for(int i = 0; i < n_item; i++){
		x[i] = IloNumVar(env, 0.0, 1.0, ILOINT);
		ostringstream varname;
		varname.str("");
		varname<<"x_"<<i;
		x[i].setName(varname.str().c_str());
	}

	//CONSTRAINTS
	IloExpr c1(env);

	for(int j = 0; j < n_item ; j++)
		c1 += x[j] * get_weight_of(j);

	Constraints.add(c1 <= Backpack_capacity );

	model.add(Constraints);

	//OBJECTIVE
	IloObjective obj=IloAdd(model, IloMaximize(env));

	for(int i = 0; i < n_item; i++){
		float coeff = 0.;
		for(int j = 0; j < p_criteria ; j++)
			  coeff += get_utility(i,j) * WS_vector[j];

		obj.setLinearCoef(x[i], coeff);
	}

//	cout<<obj<<endl;

	//SOLVE
	IloCplex cplex(model);

	cplex.setOut(env.getNullStream());


	if ( !cplex.solve() ) {
		 env.error() << "Failed to optimize LP" << endl;
		 exit(1);
	}

	//GET SOLUTION CLASS
//	set< int > items;
//	for(int i = 0; i < n_item; i++){
//		if( cplex.getValue(x[i]) > 0)
//			items.insert(i);
//	}
//
//	shared_ptr<AlternativeKnapsack> opt_alt = make_shared<AlternativeKnapsack>(items, mainProblem, WS_matrix);



	//GET SOLUTION CRITERIA VALUE
	vector< float > opt_alt(p_criteria,0);
	for(int i = 0; i < n_item; i++){
		if( cplex.getValue(x[i]) > 0){
			for(int j = 0; j < p_criteria; j++)
				opt_alt[j] += get_utility(i,j);
		}
	}

	env.end();

	return opt_alt;
}


//Evaluation the quality of PLS and WS-PLS solutions to DMs real preferences
float Evaluator::evaluate_Dist_ratio(list< vector< float > > OPT_Solution){

	string line;
	vector<float> vector_criteria;

	//Get minimum objective values difference between the best alternative and WS-MOLS front computed
	float min_mols_ratio = nearest_alternative(vector_criteria, OPT_Solution);
#ifdef __PRINT__
	cout<<"Solution found in (efficient) front "<<endl;
	cout<<"   ratio ( "<<min_mols_ratio<<" )"<<endl;
	cout<<"   vector objective ( "<<Tools::print_vector(vector_criteria)<<" )"<<endl;
#endif

	return min_mols_ratio;

}


vector< float > Evaluator::evaluate_standard_deviation_from_OPT_point(){

	vector< float > st_deviation;

//	ifstream fic((filename_instance+"_"+to_string(INFO)+"_"+to_string(UB_Size)+".sol").c_str());
//
//	vector< float > tmp_criteria_values;
//
//	float tmp_ratio = 1.;
//
//	string line;
//
//	while(!fic.eof()){
//
//		getline(fic,line);
//
//		if(line.size() == 0)
//			continue;
//
//		tmp_criteria_values = Tools::decompose_line_to_float_vector(line);
//
//		tmp_ratio = Tools::get_ratio(tmp_criteria_values, OPT_Alternative, WS_DM_vector);
//
//		st_deviation.push_back(tmp_ratio);
//
//	}
//
//	fic.close();

	return st_deviation;
}



/**
 * ************************************************* PF MEASUREMENT PART *************************************************
 */

float Evaluator::PR_D3(list< vector< float > > OPT_Solution){

	int opt_size_front = 0, nb_found = 0;

	list< vector< float > > tmp_opt(OPT_Solution.begin(),OPT_Solution.end());

	for(list< vector<float > >::iterator pareto_sol = PFront.begin(); pareto_sol != PFront.end(); ++pareto_sol){
		for(list< vector< float > >::iterator alt = tmp_opt.begin(); alt != tmp_opt.end(); ++alt){
			if( Tools::equal_vectors((*alt),*pareto_sol) ){
				nb_found += 1;
				tmp_opt.erase(alt);
				break;
			}
		}
		opt_size_front++;
	}


	return nb_found*100.0/(int)PFront.size();
}


float Evaluator::average_distance_D1(list< vector< float > > OPT_Solution){

	float min_dist = -1;
	float avg_dist = 0.;


	for(list< vector<float > >::iterator pareto_sol = PFront.begin(); pareto_sol != PFront.end(); ++pareto_sol){
		min_dist = -1;

		vector< float > vector_null((*pareto_sol).size(),0);

		for(list< vector< float > >::iterator eff_sol = OPT_Solution.begin(); eff_sol != OPT_Solution.end(); ++eff_sol){

			float euclid_dist_tmp = Tools::euclidian_distance((*eff_sol), *pareto_sol);
			if(euclid_dist_tmp < min_dist  or min_dist == -1)
				min_dist = euclid_dist_tmp;
		}

		avg_dist += min_dist;

	}

	if(OPT_Solution.empty()){
		cout<<" NOT FOUND "<<PFront.size()<<endl;
		return 0;
	}

//	cout<<"avg_dist  : "<<avg_dist<<endl;
//	cout<<"============================================="<<endl;

	return avg_dist/PFront.size();
}


float Evaluator::maximum_distance_D2(list< vector< float > > OPT_Solution){
	float min_dist = -1;
	float max_dist_PF = 0.;

	for(list< vector<float > >::iterator pareto_sol = PFront.begin(); pareto_sol != PFront.end(); ++pareto_sol){
		min_dist = -1;
		for(list< vector< float > >::iterator eff_sol = OPT_Solution.begin(); eff_sol != OPT_Solution.end(); ++eff_sol){
			float euclid_dist_tmp = Tools::euclidian_distance((*eff_sol), *pareto_sol);
			if(euclid_dist_tmp < min_dist  or min_dist == -1)
				min_dist = euclid_dist_tmp;
		}

		if( max_dist_PF < min_dist)
			max_dist_PF = min_dist;
	}

	return max_dist_PF;
}




void Evaluator::readPopulation_File(string file_population, list< vector< float > > & Population,vector< float > & time_exec, vector< int > & index ){

	ifstream fic_read(file_population);
	string line;
	vector< float > vector_line;
	Population.clear();
	time_exec.clear();
	index.clear();

	if (!(fic_read) or file_population.find(".pop") == std::string::npos){
		cerr<<"Error occurred save readPopulation_File from .pop file"<<endl;
	}


	while(!fic_read.eof()){
		getline(fic_read,line);
		if (line.size() == 0)
			continue;

		vector_line = Tools::decompose_line_to_float_vector(line);
		vector< float > criteria_value(vector_line.begin(), vector_line.begin() + p_criteria);
		Population.push_back( criteria_value);
		time_exec.push_back( *(vector_line.begin() + p_criteria ) );
		index.push_back( *(vector_line.begin() + p_criteria + 1));
	}

	fic_read.close();


}


map< int, vector< vector< float > > > readEvaluationFile(string filename, int budget, int inst_name){

	ifstream fic_read(filename);

	if (!(fic_read)){
		cerr<<"Error occurred readEvaluationFile "<<endl;
	}

	//"Type, Size, Instance, Budget, PopSize, Info, nb_evaluation, AVG_dist, MaxMin, PR, Diversification"<<endl;


	string line;
	vector< float > vector_line;
	map< int, vector< vector< float > > > indicator;//(UB_values, vector< vector< float > >(Informations));

	int size = 0;

	int size_index = 4;
	int budget_index = 3;
	int inst_id_index = 2;

	while(!fic_read.eof()){
		getline(fic_read,line);
		vector_line = Tools::decompose_line_to_float_vector(line);
		if (line.size() == 0  or  vector_line[budget_index] != budget  or  vector_line[inst_id_index] != inst_name)
			continue;
		size = vector_line[size_index];
		indicator[size].push_back(vector_line);
	}
	fic_read.close();

	return indicator;
}

/**
 * ************************************************* EVALUATE POPULATION *************************************************
 */


void Evaluator::evaluate_PF(list< vector< float > > OPT_Solution,  float time_cpu){

	time += time_cpu;

	Point_indicators[0] += evaluate_Dist_ratio(OPT_Solution);

//	Point_indicators[1] += evaluate_standard_deviation_from_OPT_point();

	PF_indicators[0] += average_distance_D1(OPT_Solution);

	PF_indicators[1] += maximum_distance_D2(OPT_Solution);

	PF_indicators[2] += PR_D3(OPT_Solution);

	K_replication++;

	cpt_k=K_replication;

}


void Evaluator::save_PF_evaluation(){

	ofstream fic_write(indicator_file.c_str(), ios::app);

	for(int i = 0; i < (int) Point_indicators.size(); i++){
		Point_indicators[i] *= 1.0 / K_replication;
		fic_write<<Point_indicators[i]<<" ";
	}

	fic_write<<time/K_replication*1.0<<"  ";


	for(int i = 0; i < (int) PF_indicators.size(); i++){
		PF_indicators[i] *= 1.0 / K_replication;
		fic_write<<PF_indicators[i]<<" ";
	}
	fic_write<<endl;
	fic_write.close();


	//REINITIALIZE PARAMETERS
	time = 0;
	Point_indicators.clear();
	Point_indicators.resize(2,0);
	PF_indicators.clear();
	PF_indicators.resize(3,0);
	K_replication = 0;
	cpt_k=0;

}

/**
 * ************************************************* SAVE FROM POPULATION FILE *************************************************
 */


void Evaluator::save_information(string file_population, string save_path, string format, vector< string > Informations,
		vector< int > UB_Population, vector<int> Budget, int inst_name, int type_instance, string taille, int div){

	system(("if [ ! -d "+save_path+" ]; then mkdir -p "+save_path+"; fi").c_str());

	string filesave = save_path+"/K_"+to_string(K_replication)+"."+format;
	ofstream fic_write(filesave.c_str(),  ios::app);
//	fic_write<<"Type, Size, Instance, Budget, PopSize, Info, nb_evaluation, AVG_dist, MaxMin, PR, Diversification"<<endl;

	vector<float> info_rate;
	for(size_t i = 0; i < Informations.size(); i++){
		set_WS_matrix(Tools::readMatrix(Informations[i]));
		info_rate.push_back( Tools::compute_information_rate(WS_matrix, p_criteria) );
	}

	for(auto b : Budget){

		for(auto ub : UB_Population){

			for(size_t i = 0; i < Informations.size(); i++){

//				if(i == 0){
					set_WS_matrix(Tools::readMatrix(Informations[i]));

					update_covered_PFront();
//				}

				vector< float > indicator(8,0.);
				int nb_interaction = 0;

				DIR *rep;
				const char* dirname;
				string file_extension, dirstr;
				if(ub == -1){
//					dirstr = file_population+"/"+to_string(i);
//					dirstr = file_population+"/"+to_string(i)+"/"+to_string(b);
					dirstr = file_population+"/"+to_string(b);
//					dirstr = file_population;
				}else{
					dirstr = file_population+"/"+to_string(ub);
//					dirstr = file_population+"/"+to_string(ub)+"/0";
//					dirstr = file_population+"/"+to_string(ub)+"/"+to_string(i);
				}

				dirname = dirstr.c_str();
				cout<<"Dirname : "<<dirstr<<endl;
				rep = opendir(dirname);
				struct dirent *filename;
				int k = 0;
				while ((filename = readdir(rep)) and k < K_replication) {

					file_extension = dirstr+"/"+filename->d_name;

					if(file_extension.find(".pop")  == std::string::npos)
						continue;

					k++;

					list< vector< float > > Population;
					vector< float > time_exec;
					vector< int > index; //INFO

					readPopulation_File(file_extension, Population, time_exec, index);

					int nb_iteration = Population.size();

					if( b != -1   and (int)Population.size() > b ){
						Population.resize(b) ;

						nb_iteration = Population.size();
						update_covered_OPT_Solution(Population);

						indicator[0] += evaluate_Dist_ratio(Population);
						indicator[1] += 0;
						indicator[2] += time_exec[ b - 1 ];
						indicator[3] += nb_iteration;

						nb_interaction += index[b - 1];
					}
					else {

						update_covered_OPT_Solution(Population);

						indicator[0] += evaluate_Dist_ratio(Population);
						indicator[1] += 0;
						indicator[2] += time_exec.back();      // LAST ONE
						indicator[3] += nb_iteration;

						nb_interaction += index.back();
					}
					indicator[4] += average_distance_D1(Population);
					indicator[5] += maximum_distance_D2(Population);
					indicator[6] += PR_D3(Population);
					indicator[7] += Population.size();

				}
				closedir(rep);

				fic_write<<type_instance<<", "<<taille<<", "<<inst_name<<", "<<b<<", "<<ub<<", "<<info_rate[i];
				for(size_t j = 3; j < indicator.size() - 1; j++){
					indicator[j] *= 1.0 / K_replication;
					fic_write<<", "<<indicator[j];
				}
				fic_write<<", "<<div;
				fic_write<<", "<<indicator[2]*1.0/K_replication;
				fic_write<<", "<<nb_interaction*1.0/K_replication<<endl;
			}
		}
	}


	fic_write.close();

}






//evolution of INDICATORS with time
void Evaluator::save_other_information(string file_population, string save_path, string format){

	system(("if [ ! -d "+save_path+" ]; then mkdir -p "+save_path+"; fi").c_str());

	vector< float > indicator(4,0.);


	for(int k = 0; k < K_replication; k++){
		string file_extension = file_population+"/Pop_"+to_string(k)+".pop";
		list< vector< float > > Population;
		vector< float > time_exec;
		vector< int > index;

		readPopulation_File(file_extension, Population, time_exec, index);

		int i_start = 0;
		for(int i = 0; i < (int)index.size(); i++){

			if( index[i] != index[i + 1] or (i == (int)index.size() -1 )){

				list< vector <float > >::iterator it_pop_start = Population.begin(), it_pop_end = Population.begin();
				advance(it_pop_start, i_start);
				advance(it_pop_end,i + 1);

				list< vector <float > > curr_Population( it_pop_start, it_pop_end);

				update_covered_OPT_Solution(curr_Population);

				indicator[0] = time_exec[i];		      // LAST ONE
				indicator[1] = average_distance_D1(curr_Population);
				indicator[2] = maximum_distance_D2(curr_Population);
				indicator[3] = PR_D3(curr_Population);


				ofstream fic_write((save_path+"/K_"+to_string(k)+"."+format).c_str(), ios::app);

				for(int j = 0; j < (int) indicator.size(); j++)
					fic_write<<indicator[j]<<" ";

				fic_write<<k<<endl;
				fic_write.close();

				i_start = i + 1;
			}

		}
	}

}



void Evaluator::save_best_parameters(string filename_instance, string format_in, string format_out, vector< float > I, vector< int > sizer,
		vector< int > budget, int inst_name){

	string fic_read = filename_instance+"/K_"+to_string(K_replication)+"."+format_in;

	string file_to_write = filename_instance+"/K_"+to_string(K_replication)+"."+format_out;

	ofstream fic_write(file_to_write, ios::app);

//	fic_write<<"Type,  Size,  Instance,  Budget,  PopSize,  Info,  nb_evaluation,  AVG_dist,  MaxMin,  PR,  Diversification"<<endl;


	int info_index = 5;
	int avg_dist_index = 7;
	for(auto b : budget){
		map< int, vector< vector< float > > > dic_file = readEvaluationFile(fic_read, b, inst_name);

		for(auto j : sizer) {

			for(auto i : I){
				vector< float > best_line_indicator(11,-1);
				for(size_t a = 0; a < dic_file[j].size(); a++){
//
					if( best_line_indicator[avg_dist_index] == -1  or (dic_file[j][a][avg_dist_index] < best_line_indicator[avg_dist_index] and dic_file[j][a][info_index] == i ) ){
						best_line_indicator = dic_file[j][a];
					}
				}
				fic_write<<best_line_indicator[0]<<", "<<best_line_indicator[1]<<", "<<inst_name<<", "<<b<<", "<<j<<", "<<i<<", "<<best_line_indicator[avg_dist_index - 1]<<", "<<best_line_indicator[avg_dist_index]<<", "<<
					best_line_indicator[avg_dist_index + 1]<<", "<<best_line_indicator[avg_dist_index + 2]<<", "<<best_line_indicator[avg_dist_index + 3]<<endl;
			}
		}
	}
	fic_write.close();
}

void Evaluator::best_algo_parametrized(string save_data, string filename_algo, string format_in, string format_out
		,int inst_name,int budget){

	string fic_read = filename_algo+"/K_"+to_string(K_replication)+"."+format_in;

	ofstream fic_write(save_data+"/K_"+to_string(K_replication)+"."+format_out,ios::app);
//	fic_write<<"Type,  Size,  Instance,  Budget,  PopSize,  Info,  nb_evaluation,  AVG_dist,  MaxMin,  PR,  Diversification"<<endl;


	map< int, vector< vector< float > > > dic_algo = readEvaluationFile(fic_read, budget, inst_name);
	vector< float > best_line_indicator(11, -1);

	int avg_dist_index = 7;

	for(map< int, vector< vector< float > > >::iterator s = dic_algo.begin() ; s != dic_algo.end(); ++s){

		vector< vector< float > > val = (*s).second;

		for(size_t a = 0; a < val.size(); a++){

			vector< float > vect_line = val[a];

			if( best_line_indicator[avg_dist_index] == -1  or (vect_line[avg_dist_index] < best_line_indicator[avg_dist_index] ) ){
				best_line_indicator = vect_line;
			}

		}
	}

	for(size_t i = 0; i < best_line_indicator.size() - 1; i++)
		fic_write<<best_line_indicator[i]<<", ";
	fic_write<<best_line_indicator.back()<<endl;



//		vector< vector< float > > val2 = dic_algo2[(*s).first];
//		for(size_t i = 0; i < best_line_indicator.size(); i++){
//			bool div_tmp = true;
//
//			if( val1[i][avg_dist_index] < val2[i][avg_dist_index] ){
//				div_tmp = false;
//				curr_opt = val1[i][avg_dist_index];
//			} else
//				curr_opt = val2[i][avg_dist_index];
//
//			if( d1_opt == -1  or curr_opt < d1_opt ){
//				d1_opt = curr_opt;
//				opt_size = (*s).first;
//				div = (div_tmp)? "1" : "0" ;
//				info = ( div_tmp )? val2[i][info_index] : val1[i][info_index];
//				best_line_indicator = ( div_tmp )? val2[i] : val1[i];
//			}
//		}
//	}
//
//
//	fic_write<<best_line_indicator[0]<<", "<<best_line_indicator[1]<<", "<<budget<<", "<<inst_name<<", "<<div<<", "<<opt_size<<", "<<info<<", "<<best_line_indicator[avg_dist_index]<<", "<<
//		best_line_indicator[avg_dist_index + 1 ]<<", "<<best_line_indicator[avg_dist_index + 2]<<endl;

}


void Evaluator::compute_avg_type_instances(string evaluation_save_path, string method_name, string format,
		int k_replic, int nb_instances, vector< int > ub_values, vector< int >  Info, vector< int > Budget ){

//	system(("if [ ! -d "+evaluation_save_path+" ]; then mkdir -p "+evaluation_save_path+"; fi").c_str());

	vector< vector< float > > indicator(12, vector< float >(Info.size(),0) );
//	fic<<"Type, Size, Instance, Budget, PopSize, Info, nb_evaluation, AVG_dist, MaxMin, PR, Diversification, Time"<<endl;


	string file_extension = evaluation_save_path+"/K_"+to_string(k_replic)+"."+format;
	ifstream fic_read(file_extension);
	string line;
	vector< float > vector_line;

	cout<<file_extension<<endl;
	if (!(fic_read) or file_extension.find(format) == std::string::npos){
		cerr<<"Error occurred compute avg type instaces "<<endl;
	}

	int info = 0;

	ofstream fic_write((evaluation_save_path+"/AVG_K_"+to_string(k_replic)+"."+format).c_str(), ios::app);


	for(auto div : {0}){
		for(auto b : Budget){
			for(auto ub : ub_values ){
				if( b == -1){
					while(!fic_read.eof()){
						getline(fic_read,line);
						if (line.size() == 0  or line.find("Type,") != std::string::npos)
							continue;

						vector_line = Tools::decompose_line_to_float_vector(line);

						if( (ub != vector_line[4])   or  (vector_line[10] != div) )
							continue;

						for(size_t j = 0 ; j < indicator.size(); j++)
							indicator[j][info] += vector_line[j];

						info= (info+1)%Info.size();
					}


					for(size_t l = 0; l < Info.size(); l++ ){
						for(size_t i = 0; i < indicator.size(); i++){
							indicator[i][l] *= 1.0 / nb_instances;
							fic_write<<indicator[i][l]<<" ";
							indicator[i][l] = 0;
						}
						if(l < Info.size() - 1)
							fic_write<<endl;
					}
//						fic_write<<endl<<"__________"<<ub<<"__"<<method_name<<endl;
					fic_write<<endl;
				}

				else{
					while(!fic_read.eof()){
						getline(fic_read,line);
						if (line.size() == 0  or line.find("Type,") != std::string::npos)
							continue;


						vector_line = Tools::decompose_line_to_float_vector(line);

						if(b != vector_line[3]    or  (ub != vector_line[4])  or  (vector_line[10] != div) )
							continue;

						for(size_t j = 0 ; j < indicator.size(); j++){
							indicator[j][info] += vector_line[j];
						}
						info= (info+1)%Info.size();
					}


					for(size_t l = 0; l < Info.size(); l++ ){
						for(size_t i = 0; i < indicator.size(); i++){
							indicator[i][l] *= 1.0 / nb_instances;
							fic_write<<indicator[i][l]<<" ";
							indicator[i][l] = 0;
						}
						if(l < Info.size() - 1)
							fic_write<<endl;
//						fic_write<<endl<<"__________"<<ub<<"__"<<method_name<<endl;
					}
					fic_write<<endl<<endl;
				}//end else
				fic_read.clear();
				fic_read.seekg(0, ios::beg);
			}
		}
	}
	fic_read.close();
	fic_write.close();
}


/**
 * ************************************************* LEARNING PART *************************************************
*/

//void Evaluator::indicator_value(string save_file, int inst_size, vector< int > sizer, vector< int > budgets,
//		vector< string > Informations, int k_init){
//
//
//	system(("if [ ! -d "+save_path+" ]; then mkdir -p "+save_path+"; fi").c_str());
//
//	vector< float > indicator(5,0.);
//
//	for(auto iter : sizer){
//		int i_step = 0 ;
//		for(auto step : Informations){
//			eval_ks->set_WS_matrix(Tools::readMatrix(step);
//			eval_ks->update_covered_PFront();
//
//			for(int i = 0; i < budgets.size(); i++){
//				for(int k = k_init; k < K_replication + k_init; k++){
//					string file_extension = file_population+"/Pop_"+to_string(k)+".pop";
//					list< vector< float > > Population;
//					vector< float > time_exec;
//					vector< int > index;
//
//					readPopulation_File(file_extension, Population, time_exec, index);
//
//
//					if( budgets[i] > Population.size()){
//						budgets[i] = Population.size();
//					}
//
//					list< vector< float > > curr_Population_budget(*Population.begin(),*(Population.begin() + budgets[i]))
//					update_covered_OPT_Solution(curr_Population_budget);
//
//					indicator[0] += average_distance_D1(curr_Population_budget);
//					indicator[1] += maximum_distance_D2(curr_Population_budget);
//					indicator[2] += PR_D3(curr_Population_budget);
//					indicator[3] += time_exec[ budgets[i] - 1 ];   				   // LAST ONE
//					indicator[4] += curr_Population_budget.size();
//				}
//
//
//				ofstream fic_write((save_path+"/"+to_string(iter)+"/"+to_string(i_step)+"/Learning_K_"+to_string(K_replication)+"."+format).c_str(), ios::app);
//
//				for(int i = 0; i < (int) indicator.size(); i++){
//					indicator[i] *= 1.0 / K_replication;
//					fic_write<<indicator[i]<<" ";
//				}
//
//				fic_write<<endl;
//				fic_write.close();
//			}
//			i_step++;
//		}
//	}
//}




/**
 * ************************************************* INFORMATION RATE PART *************************************************
*/


void Evaluator::compute_information_rate_front(){

	int nb_criteria = p_criteria;
	vector< float > inf_intervalls(nb_criteria,-1);
	vector< float > sup_intervalls(nb_criteria,-1);
	vector< vector< float > > lexmaxs(nb_criteria);

	for(int i = 0; i < n_objective; i++){

		lexmaxs[i] = OPT_Alternative_PLNE(WS_matrix[i]);

		cout<<Tools::print_vector(lexmaxs[i] )<<endl;

		for(int j =0; j < nb_criteria; j++){

			float value_criteria = lexmaxs[i][j];
			if( (inf_intervalls[j] > value_criteria )   or  (inf_intervalls[j] == -1) )
				inf_intervalls[j] = value_criteria;

			if( (sup_intervalls[j] < value_criteria)   or  (sup_intervalls[j] == -1) )
				sup_intervalls[j] = value_criteria;

		}
	}

	cout<<" INF SUP INTERVALLS"<<endl;
	cout<<Tools::print_vector(inf_intervalls)<<endl;
	cout<<Tools::print_vector(sup_intervalls)<<endl;

	int cpt = 0;
	bool contained;

	for(int i = 0; i < (int)PF_Efficient.size(); i++){
		vector<float> vect_alt = PF_Efficient[i];

		contained = true;
		for(int j = 0; j < nb_criteria; j++ ){

			if( (vect_alt[j] < inf_intervalls[j])  or  (vect_alt[j] > sup_intervalls[j]) )
				contained = false;
		}
		if(contained)
			cpt++;
	}


	cout<<"______________________________________________"<<endl;
	cout<<cpt<<"   :  "<<cpt*100.0/PF_Efficient.size()<<endl;
	cout<<"______________________________________________"<<endl;


}





















