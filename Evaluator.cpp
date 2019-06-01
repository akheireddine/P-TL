

#include "Evaluator.h"
#include <ilcplex/ilocplex.h>
//#define __PRINT__


Evaluator::Evaluator(string filename, string WS_DM_preferences, string SDT_file, string PFI_file){

	filename_instance = filename;

	readFilenameInstance(filename_instance);

	dist_time_file = SDT_file;
	pf_indicators_file = PFI_file;

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

}




bool Evaluator::in_search_space(vector<float> v,vector<float> minus, vector<float> maxus){

	for(int j = 0; j < p_criteria; j++)
		if( (v[j] < minus[j] )  or (v[j] > maxus[j]) )
				return false;

	return true;

}



void Evaluator::readParetoFront(){

	string file_extension = filename_instance+".eff";
	ifstream fic(file_extension.c_str());
	string line;
	vector< float > vector_pareto_objective;

	if (!(fic) or file_extension.find(".eff") == std::string::npos){
		cerr<<"Error occurred paretofront"<<endl;
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


	string file_extension = filename_instance+".eff";
	ifstream fic(file_extension.c_str());
	string line;
	vector< float > vector_pareto_objective;

	if (!(fic) or file_extension.find(".eff") == std::string::npos){
		cerr<<"Error occurred paretofront"<<endl;
	}

	PFront.clear();

	vector< float > minus(p_criteria, -1);
	vector< float > maxus(p_criteria, -1);


	for(int i = 0; i < n_objective; i++){
		vector< float > obj, extrem_solution;

		for(int j = 0; j < p_criteria; j++){
			obj.push_back(WS_matrix[j][i]);
		}

		extrem_solution = OPT_Alternative_PLNE(obj);

		for(int j = 0; j < p_criteria; j++){
			if( minus[j] == -1    or   extrem_solution[j] < minus[j] )
				minus[j] = extrem_solution[j];

			if(maxus[j] == -1     or   maxus[j] < extrem_solution[j])
				maxus[j] = extrem_solution[j];
		}

	}

	for(vector< vector< float > >::iterator it = PF_Efficient.begin(); it != PF_Efficient.end(); ++it){

		if( in_search_space(*it,minus, maxus) )
			PFront.push_back(*it);
	}

//	cout<<PFront.size()<<" / "<<PF_Efficient.size()<<endl;


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

	char *cline, *pch;
	int i;
	WS_matrix.clear();
	WS_matrix.resize(0);

	ifstream fic(filename.c_str());
	string line;
	i = 0;

	if (!(fic) or filename.find(".csv") == std::string::npos){
		cerr<<"Error occurred readWS_Matrix EVALUATOR"<<endl;
	}

//	WS_matrix.resize(p_criteria,vector< float >());

	while( !fic.eof() ){

		getline(fic,line);

		cline = new char[line.length() + 1]; // or
		std::strcpy(cline, line.c_str());

		pch = strtok (cline," 	,;");

		vector< float > ws_line;

		while (pch != NULL){
			ws_line.push_back(atof(pch));
			pch = strtok (NULL, " 	,;");
		}
		i++;
		if(ws_line.size() > 0)
			WS_matrix.push_back(ws_line);
	}

	p_criteria = WS_matrix.size();

	n_objective = WS_matrix[0].size();

}


/**
 * ************************************************* EVALUATION PART *************************************************
 */



//Get minimum gap from OPT_Alternative and save the objective values in vect_criteria
float Evaluator::nearest_alternative(vector< float > & vect_criteria ){

	ifstream fic((filename_instance+".sol").c_str());

	vector< float > criteria_val(p_criteria,0);
	vector< float >tmp_criteria_values;

	float min_ratio = -1, tmp_ratio = 1;
	string line;

	while(!fic.eof()){

		getline(fic,line);

		if(line.size() == 0)
			continue;

		tmp_criteria_values = Tools::decompose_line_to_float_vector(line);

		tmp_ratio = Tools::get_ratio(tmp_criteria_values, OPT_Alternative, WS_DM_vector);

		if( (min_ratio == -1) or (tmp_ratio < min_ratio) ){
			min_ratio = tmp_ratio;
			criteria_val = tmp_criteria_values;
		}

		if( min_ratio == 0 )  // equal to DMs preferences
			break;

	}

	fic.close();
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
float Evaluator::evaluate_Dist_ratio(){

	string line;
	vector<float> vector_criteria;

	//Get minimum objective values difference between the best alternative and WS-MOLS front computed
	float min_mols_ratio = nearest_alternative(vector_criteria);
#ifdef __PRINT__
	cout<<"Solution found in (efficient) front "<<endl;
	cout<<"   ratio ( "<<min_mols_ratio<<" )"<<endl;
	cout<<"   vector objective ( "<<Tools::print_vector(vector_criteria)<<" )"<<endl;
#endif

	return min_mols_ratio;

}


vector< float > Evaluator::evaluate_standard_deviation_from_OPT_point(){

	ifstream fic((filename_instance+".sol").c_str());

	vector< float > tmp_criteria_values;

	float tmp_ratio = 1.;
	vector< float > st_deviation;

	string line;

	while(!fic.eof()){

		getline(fic,line);

		if(line.size() == 0)
			continue;

		tmp_criteria_values = Tools::decompose_line_to_float_vector(line);

		tmp_ratio = Tools::get_ratio(tmp_criteria_values, OPT_Alternative, WS_DM_vector);

		st_deviation.push_back(tmp_ratio);

	}

	fic.close();

	return st_deviation;
}



/**
 * ************************************************* PF MEASUREMENT PART *************************************************
 */

float Evaluator::PR_D3(list< shared_ptr< Alternative > > OPT_Solution){

	int opt_size_front = 0, nb_found = 0;

	vector< shared_ptr< Alternative > > tmp_opt(OPT_Solution.begin(),OPT_Solution.end());

	for(list< vector<float > >::iterator pareto_sol = PFront.begin(); pareto_sol != PFront.end(); ++pareto_sol){
		for(vector< shared_ptr< Alternative > >::iterator alt = tmp_opt.begin(); alt != tmp_opt.end(); ++alt){
			if( Tools::equal_vectors((*alt)->get_criteria_values(),*pareto_sol) ){
				nb_found += 1;
				tmp_opt.erase(alt);
				break;
			}
		}
		opt_size_front++;
	}

	vector< shared_ptr< Alternative > >().swap(tmp_opt);

	return nb_found*100.0/opt_size_front;
}

float Evaluator::average_distance_D1(list< shared_ptr< Alternative > > OPT_Solution){

	float min_dist = -1;
	float avg_dist = 0.;


//	cout<<"============================================="<<endl;
//	for(auto t : OPT_Solution){
//		cout<<Tools::print_vector(t->get_objective_values())<<endl;
//	}
//
//
//	cout<<"PFront : "<<PFront.size()<<"    OPT SOL found  : "<<OPT_Solution.size()<<endl;

//	cout<<"avg_dist  : "<<avg_dist<<endl;

	for(list< vector<float > >::iterator pareto_sol = PFront.begin(); pareto_sol != PFront.end(); ++pareto_sol){
		min_dist = -1;

		for(list< shared_ptr< Alternative > >::iterator eff_sol = OPT_Solution.begin(); eff_sol != OPT_Solution.end(); ++eff_sol){

			float euclid_dist_tmp = Tools::euclidian_distance((*eff_sol)->get_criteria_values(), *pareto_sol);
			if(euclid_dist_tmp < min_dist  or min_dist == -1)
				min_dist = euclid_dist_tmp;
		}

		avg_dist += min_dist;

	}
//	cout<<"avg_dist  : "<<avg_dist<<endl;
//	cout<<"============================================="<<endl;

	return avg_dist/PFront.size();
}


float Evaluator::maximum_distance_D2(list< shared_ptr< Alternative > > OPT_Solution){
	float min_dist = -1;
	float max_dist_PF = 0.;

	for(list< vector<float > >::iterator pareto_sol = PFront.begin(); pareto_sol != PFront.end(); ++pareto_sol){
		min_dist = -1;
		for(list< shared_ptr< Alternative > >::iterator eff_sol = OPT_Solution.begin(); eff_sol != OPT_Solution.end(); ++eff_sol){
			float euclid_dist_tmp = Tools::euclidian_distance((*eff_sol)->get_criteria_values(), *pareto_sol);
			if(euclid_dist_tmp < min_dist  or min_dist == -1)
				min_dist = euclid_dist_tmp;
		}

		if( max_dist_PF < min_dist)
			max_dist_PF = min_dist;
	}

	return max_dist_PF;
}

void Evaluator::evaluate_PF(MainKnapsack * knaps, float time_cpu){

	time += time_cpu;

	Point_indicators[0] += evaluate_Dist_ratio();

	vector<float> tmp_std = evaluate_standard_deviation_from_OPT_point();

//	merge(tmp_std.begin(),tmp_std.end(),std.begin(),std.end(),std.begin());

	PF_indicators[0] += average_distance_D1(knaps->get_OPT_Solution());

	PF_indicators[1] += maximum_distance_D2(knaps->get_OPT_Solution());

	PF_indicators[2] += PR_D3(knaps->get_OPT_Solution());

	K_replication++;

	cout<<"time : "<<time<<endl;
	cout<<Tools::print_vector(Point_indicators)<<endl;
	cout<<Tools::print_vector(PF_indicators)<<endl;

}



void Evaluator::save_PF_evaluation(){

	ofstream fic_write(dist_time_file.c_str(), ios::app);

	for(int i = 0; i < (int) Point_indicators.size(); i++){
		Point_indicators[i] *= 1.0 / K_replication;
		fic_write<<Point_indicators[i]<<" ";
	}

	fic_write<<time/K_replication*1.0<<" ";

	fic_write<<endl;
	fic_write.close();


	ofstream fic2_write(pf_indicators_file.c_str(), ios::app);

	for(int i = 0; i < (int) PF_indicators.size(); i++){
		PF_indicators[i] *= 1.0 / K_replication;
		fic2_write<<PF_indicators[i]<<" ";
	}
	fic2_write<<endl;
	fic2_write.close();

	cout<<"K = "<<K_replication<<endl;


	//REINITIALIZE PARAMETERS
	time = 0;
	Point_indicators.clear();
	Point_indicators.resize(2,0);
	PF_indicators.clear();
	PF_indicators.resize(3,0);
	K_replication = 0;

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
