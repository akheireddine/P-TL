

#include "Evaluator.h"
#include <ilcplex/ilocplex.h>
#define __PRINT__

Evaluator::Evaluator(string filename, MainKnapsack * problemInstance, string WS_DM_preferences,
		string DT_file, float time, string PFI_file){

	filename_instance = filename;
	mainProblem = problemInstance;

	dist_time_file = DT_file;
	pf_indicators_file = PFI_file;

	WS_DM_vector = Tools::readWS_DM(WS_DM_preferences);

	readParetoFront();

#ifdef __PRINT__
	cout<<"----------------------- EVALUATION ----------------------"<<endl;
#endif

	OPT_Alternative = OPT_Alternative_PLNE(WS_DM_vector);

#ifdef __PRINT__
	cout<<"Preference du décideur ([ " << Tools::print_vector(WS_DM_vector) <<" ]) : "<<endl;
	cout<<"    "<< Tools::print_vector(OPT_Alternative->get_criteria_values())<<endl;
#endif


	evaluate_Dist_Time(dist_time_file, time);
	evaluate_PF(pf_indicators_file);


#ifdef __PRINT__
	cout<<"----------------------- END EVALUATION ----------------------"<<endl<<endl;
#endif



}





void Evaluator::write_coeff_functions(string filename){

	ofstream fic(filename.c_str(), ios::app);

	fic<<endl<<"Optimal solution :"<<endl;
	fic<<"("; for(int i = 0; i < mainProblem->get_p_criteria(); i++) fic<< OPT_Alternative->get_criteria(i) <<", "; fic<<")"<<endl;
	fic<<endl<<"Matrice des objectives & Optimal solution:"<<endl;

	for(int i = 0; i < mainProblem->get_p_criteria(); i++){
		fic<<"   ";
		for(int j = 0; j < mainProblem->get_n_objective(); j++)
			fic<<to_string(mainProblem->get_WS_matrix()[i][j])<< " ";
		fic<<endl;
	}
	fic<<endl;

	fic.close();

}


void Evaluator::write_objective_OPT_information(){

	write_coeff_functions(dist_time_file);
	write_coeff_functions(pf_indicators_file);

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

	list< vector<float > > cp_PF(PFront.begin(), PFront.end());

	for(list< vector<float > >::iterator k = cp_PF.begin(); k != cp_PF.end(); ++k){

		bool dominated = false, dominates = false;
		vector<float > pf_alt = *k ;

		for(int i = 0; i < (int)pf_alt.size(); i++){

			if( v[i] < pf_alt[i] )									// MAXIMIZATION DES OBJECTIFS ! ! !
				dominated = true;

			else if ( v[i] > pf_alt[i] )
				dominates = true;
		}

		if ( dominated and !dominates)
			return true;
		else if ( !dominated and dominates )
			PFront.remove(*k);
	}

	list<vector<float>>().swap(cp_PF);

	return false;
}



void Evaluator::readParetoFront(){

	string file_extension = filename_instance+".eff";
	ifstream fic(file_extension.c_str());
	string line;
	vector< float > vector_pareto_objective, transformed_objective;

	if (!(fic) or file_extension.find(".eff") == std::string::npos){
		cerr<<"Error occurred paretofront"<<endl;
	}

	PFront.clear();
	PF_Efficient.clear();
	while(!fic.eof()){

		getline(fic,line);
		if (line.size() == 0)
			continue;

		vector_pareto_objective = Tools::decompose_line_to_float_vector(line);
		PF_Efficient.push_back(vector_pareto_objective);
		transformed_objective = get_objective_values(vector_pareto_objective);

		if( !is_dominated(transformed_objective) )
			PFront.push_back(vector_pareto_objective);

	}

	vector<float>().swap(transformed_objective);
	vector<float>().swap(vector_pareto_objective);
}


/**
 * ************************************************* EVALUATION PART *************************************************
 */



//Get minimum gap from OPT_Alternative and save the objective values in vect_criteria
float Evaluator::nearest_alternative(vector< float > & vect_criteria ){

	ifstream fic((filename_instance+".sol").c_str());

	vector< float > criteria_val(mainProblem->get_p_criteria(),0);
	vector< float >tmp_criteria_values;

	float min_ratio = -1, tmp_ratio = 1;
	string line;

	while(!fic.eof()){

		getline(fic,line);

		if(line.size() == 0)
			continue;

		tmp_criteria_values = Tools::decompose_line_to_float_vector(line);

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
AlternativeKnapsack * Evaluator::OPT_Alternative_PLNE(vector<float> WS_vector){

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
			  coeff += mainProblem->get_utility(i,j) * WS_vector[j];

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

	AlternativeKnapsack * opt_alt = new AlternativeKnapsack(items, mainProblem, mainProblem->get_WS_matrix());


	set< int >().swap(items);

	return opt_alt;
}


//Evaluation the quality of PLS and WS-PLS solutions to DMs real preferences
void Evaluator::evaluate_Dist_Time(string dist_time_file, float time){

	string line;
	vector<float> vector_criteria;

	//Get minimum objective values difference between the best alternative and WS-MOLS front computed
	float min_mols_ratio = nearest_alternative(vector_criteria);
#ifdef __PRINT__
	cout<<"Solution found in (efficient) front "<<endl;
	cout<<"   ratio ( "<<min_mols_ratio<<" )"<<endl;
	cout<<"   vector objective ( "<<Tools::print_vector(vector_criteria)<<" )"<<endl;
#endif

	Tools::update_dist_time(min_mols_ratio,time);

//	ofstream fic(dist_time_file,ios::app);
//	//"./Data/DistTime/"+type_instance+"/I"+num_instance+"_"+to_string(mainProblem->get_n_items())+".eval", ios::app);
//	fic<<min_mols_ratio<<","<<time<<endl;
//
//
//	fic.close();

	vector< float >().swap(vector_criteria);

}




/**
 * ************************************************* PF MEASUREMENT PART *************************************************
 */

float Evaluator::PR_D3(){

	int opt_size_front = 0, nb_found = 0;
	list<Alternative* > OPT_Solution = mainProblem->get_OPT_Solution();

	vector< Alternative* > tmp_opt(OPT_Solution.begin(),OPT_Solution.end());

	for(list< vector<float > >::iterator pareto_sol = PFront.begin(); pareto_sol != PFront.end(); ++pareto_sol){
		for(vector< Alternative* >::iterator alt = tmp_opt.begin(); alt != tmp_opt.end(); ++alt){
			if( Tools::equal_vectors((*alt)->get_criteria_values(),*pareto_sol) ){
				nb_found += 1;
				tmp_opt.erase(alt);
				break;
			}
		}
		opt_size_front++;
	}

	vector< Alternative* >().swap(tmp_opt);

	return nb_found*100.0/opt_size_front;
}

float Evaluator::average_distance_D1(){

	float min_dist = -1;
	float avg_dist = 0.;
	list<Alternative* > OPT_Solution = mainProblem->get_OPT_Solution();

	for(list< vector<float > >::iterator pareto_sol = PFront.begin(); pareto_sol != PFront.end(); ++pareto_sol){
		min_dist = -1;

		for(list<Alternative*>::iterator eff_sol = OPT_Solution.begin(); eff_sol != OPT_Solution.end(); ++eff_sol){

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
	list<Alternative* > OPT_Solution = mainProblem->get_OPT_Solution();

	for(list< vector<float > >::iterator pareto_sol = PFront.begin(); pareto_sol != PFront.end(); ++pareto_sol){
		min_dist = -1;
		for(list<Alternative*>::iterator eff_sol = OPT_Solution.begin(); eff_sol != OPT_Solution.end(); ++eff_sol){
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

//	ofstream write_fic(pf_indicators_file,ios::app);
//	//"./Data/ParetoFront/"+type_instance+"/I"+num_instance+"_"+to_string(mainProblem->get_n_items())+".front", ios::app);
//
//	write_fic<<D1<<","<<D2<<","<<D3<<endl;
//
//	write_fic.close();

}





/**
 * ************************************************* INFORMATION RATE PART *************************************************
 */



void Evaluator::compute_information_rate_front(){

	int nb_criteria = mainProblem->get_p_criteria();
	vector< float > inf_intervalls(nb_criteria,-1);
	vector< float > sup_intervalls(nb_criteria,-1);
	vector<AlternativeKnapsack* > lexmaxs(nb_criteria);

	for(int i = 0; i < mainProblem->get_n_objective(); i++){

		lexmaxs[i] = OPT_Alternative_PLNE(mainProblem->get_WS_matrix()[i]);

		cout<<Tools::print_vector(lexmaxs[i]->get_criteria_values())<<endl;

		for(int j =0; j < nb_criteria; j++){

			float value_criteria = lexmaxs[i]->get_criteria_values()[j];
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


	vector< float >().swap(inf_intervalls);
	vector< float >().swap(sup_intervalls);
	vector<  AlternativeKnapsack* >().swap(lexmaxs);


}

#define PI 3.14159265




float Evaluator::compute_information_rate(){


	vector<vector<float > > matrix = mainProblem->get_WS_matrix();
	float uv = 0, u_norme = 0, v_norme = 0;
	//compute angle

	if(mainProblem->get_p_criteria() == 2){

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
	if(mainProblem->get_p_criteria() == 3){
		vector< vector<float > > matrix = mainProblem->get_WS_matrix();
		vector<float> lengths(3,0);
		float maxus, minus;

		for(int i = 0; i < 3; i++){
			maxus = -1, minus = -1;
			for(int j = 0; j < mainProblem->get_n_objective(); j++){
				if( matrix[i][j] < minus   or minus == -1 )
					minus = matrix[i][j];
				if( matrix[i][j] > maxus or maxus == -1)
					maxus = matrix[i][j];
			}

			lengths[i] = abs(maxus - minus);

		}

		return lengths[0] * lengths[1] * lengths[2];
	}



	//compute MONTE CARLO APPORIXMATION
return -1;




}
