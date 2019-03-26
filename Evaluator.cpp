

#include "Evaluator.h"
#include <ilcplex/ilocplex.h>


Evaluator::Evaluator(string filename, LSStructure * problemInstance, string WS_DM_preferences,
		string dist_time_file, float time, string pf_indicators_file){


	mainProblem = problemInstance;
	readParetoFront();

	cout<<"----------------------- EVALUATION ----------------------"<<endl;

	OPT_Alternative_PLNE(WS_DM_preferences);



}

vector<float> Evaluator::get_objective_values(vector<float> v_src){

	vector<float> v_dest(v_src.size(),0);

	vector<vector<float > > ws_mat = mainProblem->get_WS_matrix();

	for(int i = 0; i < mainProblem->get_n_objective(); i++){
		for(int j = 0; j < mainProblem->get_p_criteria(); j++)
			v_dest[i] += v_src[j] * ws_mat[j][i];
	}

	return v_dest;
}



bool Evaluator::is_dominated(vector<float> v){

	for(int k = 0; k < PFront.size(); k++){

		bool dominated = false, dominates = false;
		vector<float > pf_alt = PFront[k];

		for(int i = 0; i < pf_alt.size(); i++){

			if( v[i] < pf_alt[i] )									// MAXIMIZATION DES OBJECTIFS ! ! !
				dominated = true;

			else if ( v[i] > pf_alt[i] )
				dominates = true;
		}

		if ( dominated and !dominates)
			return true;
	}

	return false;
}



void Evaluator::readParetoFront(){

	string file_extension = filename_instance+".eff";
	ifstream fic(file_extension.c_str());
	string line;

	if (!(fic) or file_extension.find(".eff") == std::string::npos){
		cerr<<"Error occurred paretofront"<<endl;
	}

	PFront.clear();

	while(!fic.eof()){

		getline(fic,line);
		if (line.size() == 0)
			continue;

		vector< float > vector_pareto_objective = Tools::decompose_line_to_float_vector(line);
		vector< float > transformed_objective = get_objective_values(vector_pareto_objective);

		if( !is_dominated(transformed_objective) )
			PFront.push_back(vector_pareto_objective);
	}

}


/**
 * ************************************************* EVALUATION PART *************************************************
 */



//Get minimum gap from OPT_Alternative and save the objective values in vect_criteria
float Evaluator::nearest_alternative(vector< float > & vect_criteria ){

	ifstream fic((filename_instance+".sol").c_str());

	vector< float > criteria_val(mainProblem->get_p_criteria(),0);
	float min_ratio = -1, tmp_ratio = 1;
	string line;

	while(!fic.eof()){

		getline(fic,line);

		if(line.size() == 0)
			continue;

		vector< float >tmp_criteria_values = Tools::decompose_line_to_float_vector(line);

		tmp_ratio = Tools::get_ratio(tmp_criteria_values, OPT_Alternative->get_criteria_values(), WS_DM_vector);

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
void Evaluator::OPT_Alternative_PLNE(string WS_DM_preferences){


	ifstream fic_read(WS_DM_preferences.c_str());
	string line;
	vector<float > WS_DM_vector;


	if (!(fic_read) or WS_DM_preferences.find(".ks") == std::string::npos){
		cerr<<"Error occurred eval_sol"<<endl;
	}
	//read WS_DMs_preference
	getline(fic_read,line);

	WS_DM_vector = Tools::decompose_line_to_float_vector(line);



	IloEnv   env;
	IloModel model(env);
	vector<IloNumVar > x(mainProblem->get_n_items());
	IloRangeArray Constraints(env);

	//VARIABLES
	for(int i = 0; i < mainProblem->get_n_items(); i++){
		x[i] = IloNumVar(env, 0.0, 1.0, ILOINT);
		ostringstream varname;
		varname.str("");
		varname<<"x_"<<i;
		x[i].setName(varname.str().c_str());
	}

	//CONSTRAINTS
	IloExpr c1(env);

	for(int j = 0; j < mainProblem->get_n_items() ; j++)
		c1 += x[j] * mainProblem->get_weight_of(j);

	Constraints.add(c1 <= mainProblem->get_capacity() );

	model.add(Constraints);

	//OBJECTIVE
	IloObjective obj=IloAdd(model, IloMaximize(env));

	for(int i = 0; i < mainProblem->get_n_items(); i++){
		float coeff = 0.;
		for(int j = 0; j < mainProblem->get_p_criteria() ; j++)
			  coeff += mainProblem->get_utility(i,j) * WS_DM_vector[j];

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

	//GET SOLUTION
	set< int > items;
	for(int i = 0; i < mainProblem->get_n_items(); i++){
		if( cplex.getValue(x[i]) > 0)
			items.insert(i);
	}
	env.end();

	OPT_Alternative = new AlternativeKnapsack(items, this);

	cout<<"Preference du décideur ([ " << Tools::print_vector(WS_DM_vector) <<" ]) : "<<endl;
	cout<<"    "<< Tools::print_vector(OPT_Alternative->get_criteria_values())<<endl;

}


//Evaluation the quality of PLS and WS-PLS solutions to DMs real preferences
void Evaluator::evaluate_Dist_Time(string dist_time_file, float time){

	string line;
	int i = 0;
	vector<float> vector_criteria;

	//Get minimum objective values difference between the best alternative and WS-MOLS front computed
	float min_mols_ratio = nearest_alternative(vector_criteria);
	cout<<"Solution found in (efficient) front "<<endl;
	cout<<"   ratio ( "<<min_mols_ratio<<" )"<<endl;
	cout<<"   vector objective ( "<<Tools::print_vector(vector_criteria)<<" )"<<endl;


//	write evaluation
	ofstream fic(dist_time_file,ios::app);
	//"./Data/DistTime/"+type_instance+"/I"+num_instance+"_"+to_string(mainProblem->get_n_items())+".eval", ios::app);
	fic<<min_mols_ratio<<","<<time<<endl;

	Tools::update_dist_time(min_mols_ratio,time);
	cout<<"----------------------- END EVALUATION ----------------------"<<endl<<endl;

	fic.close();
}




/**
 * ************************************************* PF MEASUREMENT PART *************************************************
 */

float Evaluator::PR_D3(){

	int opt_size_front = 0, nb_found = 0;

	vector< Alternative* > tmp_opt(mainProblem->get_OPT_Solution().begin(),mainProblem->get_OPT_Solution().end());

	for(vector< vector<float > >::iterator pareto_sol = PFront.begin(); pareto_sol != PFront.end(); ++pareto_sol){
		for(vector< Alternative* >::iterator alt = tmp_opt.begin(); alt != tmp_opt.end(); ++alt){
			if( Tools::equal_vectors((*alt)->get_criteria_values(),*pareto_sol) ){
				nb_found += 1;
				tmp_opt.erase(alt);
				break;
			}
		}
		opt_size_front++;
	}

	return nb_found*100.0/opt_size_front;
}

float Evaluator::average_distance_D1(){

	float min_dist = -1;
	float avg_dist = 0.;

	for(vector< vector<float > >::iterator pareto_sol = PFront.begin(); pareto_sol != PFront.end(); ++pareto_sol){
		min_dist = -1;
		for(list<Alternative*>::iterator eff_sol = mainProblem->get_OPT_Solution().begin(); eff_sol != mainProblem->get_OPT_Solution().end(); ++eff_sol){
			float euclid_dist_tmp = Tools::euclidian_distance((*eff_sol)->get_criteria_values(), *pareto_sol);
			if(euclid_dist_tmp < min_dist  or min_dist == -1)
				min_dist = euclid_dist_tmp;
		}

		avg_dist += min_dist;
	}

	return avg_dist/ PFront.size();
}

float Evaluator::maximum_distance_D2(){
	float min_dist = -1;
	float max_dist_PF = 0.;

	for(vector< vector<float > >::iterator pareto_sol = PFront.begin(); pareto_sol != PFront.end(); ++pareto_sol){
		min_dist = -1;
		for(list<Alternative*>::iterator eff_sol = mainProblem->get_OPT_Solution().begin(); eff_sol != mainProblem->get_OPT_Solution().end(); ++eff_sol){
			float euclid_dist_tmp = Tools::euclidian_distance((*eff_sol)->get_criteria_values(), *pareto_sol);
			if(euclid_dist_tmp < min_dist  or min_dist == -1)
				min_dist = euclid_dist_tmp;
		}

		if( max_dist_PF < min_dist)
			max_dist_PF = min_dist;
	}

	return max_dist_PF;
}

void Evaluator::evaluate_PF(string pf_indicators_file){

	float D1 = average_distance_D1();
	float D2 = maximum_distance_D2();
	float D3 = PR_D3();

	Tools::update_indicators(D1,D2,D3);

	ofstream write_fic(pf_indicators_file,io::app);
	//"./Data/ParetoFront/"+type_instance+"/I"+num_instance+"_"+to_string(mainProblem->get_n_items())+".front", ios::app);

	write_fic<<D1<<","<<D2<<","<<D3<<endl;

	write_fic.close();

}


