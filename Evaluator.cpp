

#include "Evaluator.h"
#include <ilcplex/ilocplex.h>
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





//void Evaluator::update_covered_PFrontPL(){
//
//
//	PFront.clear();
//
//	vector< float > minus(p_criteria, -1);
//	vector< float > maxus(p_criteria, -1);
//
//
//	for(int i = 0; i < n_objective; i++){
//		vector< float > obj, extrem_solution;
//
//		for(int j = 0; j < p_criteria; j++){
//			obj.push_back(WS_matrix[j][i]);
//		}
//
//		extrem_solution = OPT_Alternative_PLNE(obj);
//
//		for(int j = 0; j < p_criteria; j++){
//			if( minus[j] == -1    or   extrem_solution[j] < minus[j] )
//				minus[j] = extrem_solution[j];
//
//			if(maxus[j] == -1     or   maxus[j] < extrem_solution[j])
//				maxus[j] = extrem_solution[j];
//		}
//
//	}
//
//	for(vector< vector< float > >::iterator it = PF_Efficient.begin(); it != PF_Efficient.end(); ++it){
//
//		if( Tools::in_search_space(*it,minus, maxus) )
//			PFront.push_back(*it);
//	}
//
////	cout<<"PF/PE   : "<<PFront.size()<<" / "<<PF_Efficient.size()<<endl;
//}




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



void Evaluator::save_evolution_indicators(list< vector< float > > OPT_Solution, string filename_instance, int info, int sizer, float time_cpu, int pop_size){

	float d1 = average_distance_D1(OPT_Solution);

	ofstream fic(filename_instance+"_"+to_string(info)+"_"+to_string(sizer)+".ev",ios::app);
	fic<<d1<< " "<<pop_size<<" "<<time_cpu<<" "<<cpt_k<<endl;;
	fic.close();
}


void Evaluator::evaluate_PF(list< vector< float > > OPT_Solution, int sizer, int info, float time_cpu){

	eval_values[sizer][info][0] += evaluate_Dist_ratio(OPT_Solution);
//	eval_values[sizer][info][1] += ;   STD
	eval_values[sizer][info][2] += time_cpu;

	eval_values[sizer][info][3] += average_distance_D1(OPT_Solution);
	eval_values[sizer][info][4] += maximum_distance_D2(OPT_Solution);
	eval_values[sizer][info][5] += PR_D3(OPT_Solution);

	cpt_k++;
//	cout<<"OPT/PF   : "<<OPT_Solution.size()<<" / "<<PFront.size()<<endl;

}

void Evaluator::save_PF_evaluation_map(){


	ofstream fic_write(indicator_file.c_str(), ios::app);

	for(map<int, map < int, vector< float > > >::iterator iter = eval_values.begin(); iter != eval_values.end(); ++iter){

		for(map < int, vector< float > >::iterator step = (*iter).second.begin(); step != (*iter).second.end(); ++step){

			for(int i = 0; i < 3; i++){
				eval_values[(*iter).first][(*step).first][i] *= 1.0 / K_replication;
				fic_write<<eval_values[(*iter).first][(*step).first][i]<<" ";
			}
			fic_write<<(*step).first<<"  ";


			for(int i = 3; i < (int) (*step).second.size(); i++){
				eval_values[(*iter).first][(*step).first][i] *= 1.0 / K_replication;
				fic_write<<eval_values[(*iter).first][(*step).first][i]<<" ";
			}
			fic_write<<(*step).first<<endl;
		}
		Tools::separate_results(indicator_file,"_____"+to_string((*iter).first));
	}
	fic_write.close();


	//REINITIALIZE PARAMETERS
	eval_values.clear();
	cpt_k=0;

}


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


void Evaluator::save_information(string file_population, string save_path, string format){

	system(("if [ ! -d "+save_path+" ]; then mkdir -p "+save_path+"; fi").c_str());

	vector< float > indicator(8,0.);


	for(int k = 0; k < K_replication; k++){
		string file_extension = file_population+"/Pop_"+to_string(k)+".pop";
		ifstream fic_read(file_extension);
		string line;
		vector< float > vector_line;
		list< vector< float > > Population;
		vector< float > time_exec;
		vector< int > index;
		int nb_iteration = 0.;

		if (!(fic_read) or file_extension.find(".pop") == std::string::npos){
			cerr<<"Error occurred save information from .pop file"<<endl;
		}


		while(!fic_read.eof()){
			getline(fic_read,line);
			if (line.size() == 0)
				continue;

			vector_line = Tools::decompose_line_to_float_vector(line);
			vector< float > criteria_value(vector_line.begin(), vector_line.begin() + p_criteria);
			Population.push_back( criteria_value);
			time_exec.push_back( *(vector_line.begin() + p_criteria ) );
//			index.push_back( *(vector_line.begin() + p_criteria + 1));
			nb_iteration++;
		}

		update_covered_OPT_Solution(Population);

		indicator[0] += evaluate_Dist_ratio(Population);
		indicator[1] += 0;
		indicator[2] += time_exec.back();      // LAST ONE
		indicator[3] += nb_iteration;
		indicator[4] += average_distance_D1(Population);
		indicator[5] += maximum_distance_D2(Population);
		indicator[6] += PR_D3(Population);
		indicator[7] += Population.size();
		fic_read.close();
	}


	ofstream fic_write((save_path+"/K_"+to_string(K_replication)+"."+format).c_str(), ios::app);

	for(int i = 0; i < (int) indicator.size(); i++){
		indicator[i] *= 1.0 / K_replication;
		fic_write<<indicator[i]<<" ";
	}

	fic_write<<endl;
	fic_write.close();

}



//evolution of INDICATORS with time
void Evaluator::save_other_information(string file_population, string save_path, string format){

	system(("if [ ! -d "+save_path+" ]; then mkdir -p "+save_path+"; fi").c_str());

	vector< float > indicator(6,0.);


	for(int k = 0; k < K_replication; k++){
		string file_extension = file_population+"/Pop_"+to_string(k)+".pop";
		ifstream fic_read(file_extension);
		string line;
		vector< float > vector_line;
		list< vector< float > > Population;
		vector< float > time_exec;
		vector< int > index;

		if (!(fic_read) or file_extension.find(".pop") == std::string::npos){
			cerr<<"Error occurred save information from .pop file"<<endl;
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

		int i_start = 0;
		for(int i = 0; i < (int)index.size(); i++){

			if( index[i] != index[i + 1] or (i == (int)index.size() -1 )){

				list< vector <float > >::iterator it_pop_start = Population.begin(), it_pop_end = Population.begin();
				advance(it_pop_start, i_start);
				advance(it_pop_end,i + 1);

				list< vector <float > > curr_Population( it_pop_start, it_pop_end);

				update_covered_OPT_Solution(curr_Population);

//				indicator[0] = evaluate_Dist_ratio(curr_Population);
//				indicator[1] = 0;
				indicator[2] = time_exec[i];		      // LAST ONE
				indicator[3] = average_distance_D1(curr_Population);
				indicator[4] = maximum_distance_D2(curr_Population);
				indicator[5] = PR_D3(curr_Population);


				ofstream fic_write((save_path+"/K_"+to_string(k)+"."+format).c_str(), ios::app);

				for(int j = 2; j < (int) indicator.size(); j++)
					fic_write<<indicator[j]<<" ";

				fic_write<<k<<endl;
				fic_write.close();

				i_start = i + 1;
			}

		}


		fic_read.close();
	}

}



void Evaluator::compute_avg_type_instances(string evaluation_save_path, string method_name, string format, int k_replic, int nb_instances, vector< int > ub_values, vector< int >  Info ){

//	system(("if [ ! -d "+evaluation_save_path+" ]; then mkdir -p "+evaluation_save_path+"; fi").c_str());

	vector< vector< float > > part_indic(ub_values.size(), vector< float >(Info.size(), 0.) );
	vector< vector< vector< float > > > indicator(7, part_indic );


	for(int n = 0; n < nb_instances; n++){
		string file_extension = evaluation_save_path+"/T"+to_string(n)+"/"+method_name+"/K_"+to_string(k_replic)+"."+format;
		ifstream fic_read(file_extension);
		string line;
		vector< float > vector_line;

		if (!(fic_read) or file_extension.find(format) == std::string::npos){
			cerr<<"Error occurred compute avg type instaces "<<endl;
		}

		int size = 0;
		int info = 0;
		while(!fic_read.eof()){
			getline(fic_read,line);
			if (line.size() == 0)
				continue;

			if(line.find("#__________") != std::string::npos  or line.find("__________") != std::string::npos){
				size = (size + 1)%ub_values.size();
				info = 0;
				continue;
			}

			vector_line = Tools::decompose_line_to_float_vector(line);

			indicator[0][size][info] += vector_line[0];
			indicator[1][size][info] += vector_line[1];
			indicator[2][size][info] += vector_line[2];
			indicator[3][size][info] += vector_line[3];
			indicator[4][size][info] += vector_line[4];
			indicator[5][size][info] += vector_line[5];
			indicator[6][size][info] += vector_line[6];

			info++;
		}

		fic_read.close();
	}

	ofstream fic_write((evaluation_save_path+"/AVG_K_"+to_string(k_replic)+"."+format).c_str(), ios::app);

	for(int j = 0; j < (int)ub_values.size(); j++){
		for(int l = 0; l < (int)Info.size(); l++ ){
			for(int i = 0; i < (int)indicator.size(); i++){
				indicator[i][j][l] *= 1.0 / nb_instances;
				fic_write<<indicator[i][j][l]<<" ";
			}
			if(l < (int)Info.size() - 1)
				fic_write<<endl;
		}

		fic_write<<endl<<"__________"<<ub_values[j]<<"__"<<method_name<<endl;
	}

	fic_write<<endl<<endl;;
	fic_write.close();

}




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

#define PI 3.14159265


float Evaluator::compute_information_rate(){


	vector<vector<float > > matrix = WS_matrix;
	float uv = 0, u_norme = 0, v_norme = 0;
	//compute angle

	if(p_criteria == 2){

		for(int i = 0; i < 2 ; i++){
			uv += matrix[i][0] * matrix[i][1] ;
			u_norme += matrix[i][0] * matrix[i][0];
			v_norme += matrix[i][1] * matrix[i][1];
		}
		if( sqrt(u_norme * v_norme) == 0 ) return 0;

		float degree = acos(uv*1.0 / sqrt(u_norme * v_norme)) * 180.0 / PI;
		return degree;

	}

	//compute volume
	if(p_criteria == 3){
		vector< vector<float > > matrix = WS_matrix;
		vector<float> lengths(3,0);
		float maxus, minus;

		for(int i = 0; i < 3; i++){
			maxus = -1, minus = -1;
			for(int j = 0; j < n_objective; j++){
				if( WS_matrix[i][j] < minus   or minus == -1 )
					minus = WS_matrix[i][j];
				if( WS_matrix[i][j] > maxus or maxus == -1)
					maxus = WS_matrix[i][j];
			}

			lengths[i] = abs(maxus - minus);

		}

		return lengths[0] * lengths[1] * lengths[2];
	}



	//compute MONTE CARLO APPORIXMATION
	return -1;
}



















//void Evaluator::write_coeff_functions(string filename){
//
//	ofstream fic(filename.c_str(), ios::app);
//
//	fic<<endl<<"Optimal solution :"<<endl;
//	fic<<"("; for(int i = 0; i < mainProblem->get_p_criteria(); i++) fic<< OPT_Alternative->get_criteria(i) <<", "; fic<<")"<<endl;
//	fic<<endl<<"Matrice des objectives & Optimal solution:"<<endl;
//
//	for(int i = 0; i < mainProblem->get_p_criteria(); i++){
//		fic<<"   ";
//		for(int j = 0; j < mainProblem->get_n_objective(); j++)
//			fic<<to_string(mainProblem->get_WS_matrix()[i][j])<< " ";
//		fic<<endl;
//	}
//	fic<<endl;
//
//	fic.close();
//
//}
//
//
//void Evaluator::write_objective_OPT_information(){
//
//	write_coeff_functions(dist_time_file);
//	write_coeff_functions(pf_indicators_file);
//
//}
