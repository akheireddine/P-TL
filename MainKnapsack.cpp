
#include <set>
#include <ilcplex/ilocplex.h>

#include "MainKnapsack.h"



#include <sstream>      // std::ostringstream

MainKnapsack::MainKnapsack(string filename, string pref_filename, string init_population_filename){

	filename_instance = filename;

	readFilenameInstance(filename_instance);

	readWS_Matrix(pref_filename);

	readInitPopulationFile(init_population_filename);

}


void MainKnapsack::readInitPopulationFile(string filename){

	ifstream fic(filename.c_str());


	if (!(fic) or filename.find(".ks") == std::string::npos){
		cerr<<"Error occurred"<<endl;
	}

	string line;
	float total_weight;

	while(!fic.eof()){
		total_weight = 0;
		getline(fic,line);

		set<int> set_items;
		char *cline = new char[line.length() + 1];
		std::strcpy(cline, line.c_str());

		char * pch = strtok (cline," 	,");
		while (pch != NULL){
			set_items.insert(atoi(pch));
			total_weight += std::get<0>(Items_information[atoi(pch)]);
			pch = strtok (NULL, " 	,");
		}

		if(total_weight > Backpack_capacity){
			cerr<<"Not feasable initialization"<<endl;
			exit(1);
		}
		AlternativeKnapsack* alt = new AlternativeKnapsack(set_items, this);
		Population.push_back(alt);
	}

	if( Population.size() == 0){
		set<int> empt;
		AlternativeKnapsack *alt = new AlternativeKnapsack(empt, this);
		Population.push_back(alt);
	}

	fic.close();
}


void MainKnapsack::readFilenameInstance(string filename){

	string line;
	char buff[100];
	int i = 0;

	vector< float > line_value;

	ostringstream FileName;
	FileName.str("");
	FileName <<filename.c_str()<<".dat";
	ifstream fic(FileName.str());


	//comments
	getline(fic,line);
	while( line[0] == 'c' )
		getline(fic,line);

	//number of items
	n_items = 0;
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
		char *cline = new char[line.length() + 1]; // or
		std::strcpy(cline, line.c_str());

		line_value.clear();
		char * pch = strtok (cline," 	");
		while (pch != NULL){
			line_value.push_back(atof(pch));
			pch = strtok (NULL, " 	");
		}

		float weight = line_value[0];

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



	fic.close();
}


void MainKnapsack::readWS_Matrix(string filename){

	ifstream fic(filename.c_str());
	string line;
	int i = 0;
	if (!(fic) or filename.find(".csv") == std::string::npos){
		cerr<<"Error occurred fileMatrix"<<endl;
	}

	WS_matrix.resize(p_criteria,vector< float >());

	while( !fic.eof() and i < p_criteria){

		getline(fic,line);

		char *cline = new char[line.length() + 1]; // or
		std::strcpy(cline, line.c_str());

		char * pch = strtok (cline," 	,;");
		while (pch != NULL){
			WS_matrix[i].push_back(atof(pch));
			pch = strtok (NULL, " 	,;");
		}
		i++;
	}

	n_objective = WS_matrix[0].size();


}


void MainKnapsack::write_solution(){

	ostringstream FileName;
	FileName.str("");
//	string dat_format = ".dat";
//	filename_instance.replace(filename_instance.find(dat_format,dat_format.length(),".sol"));
	FileName <<filename_instance.c_str()<<".sol";
	ofstream fic(FileName.str().c_str());
	cout<<"============================="<<endl;
	for(list< Alternative *>::iterator alt = OPT_Solution.begin(); alt != OPT_Solution.end(); alt++){
		for(int i = 0; i < n_objective; i++){
			fic<< (*alt)->get_objective_values()[i]<< " ";
			cout<< (*alt)->get_objective_values()[i]<< " ";
		}
		fic <<endl;
		cout<<endl;
	}
}


float euclidien_distance(vector<float> v1, vector<float> v2){

	float dist = 0;

	for(int i = 0; i < v1.size(); i++)
		dist += (v1[i] - v2[i]) * (v1[i] - v2[i]);

	dist = sqrt(dist);

	return dist;
}

void print_vector(vector<float> v){
	for(int i = 0 ; i < v.size(); i++)
		cout<<v[i]<<" ";
	cout<<endl;
}

float MainKnapsack::nearest_alternative(string filename, vector<float> opt_values){

	int number_of_objective = opt_values.size();
	ifstream fic(filename.c_str());

	vector< float > obj_val(number_of_objective,0);
	float min_dist = -1, tmp_dist = 0;
	int i;
	string line;
	cout<<filename<<endl;

	while(!fic.eof()){

		i = 0;
		vector< float >tmp_obj(number_of_objective,0);

		getline(fic,line);

		char *cline = new char[line.length() + 1]; // or
		std::strcpy(cline, line.c_str());

		char * pch = strtok (cline," 	,;");
		while (pch != NULL){
			tmp_obj[i++] = atof(pch);
			pch = strtok (NULL, " 	,;");
		}

		tmp_dist = euclidien_distance(tmp_obj, opt_values);

		if( min_dist == -1 or tmp_dist < min_dist ){
			min_dist = tmp_dist;
			obj_val = tmp_obj;
		}

		if( min_dist == 0 )
			break;
	}

	fic.close();
	print_vector(obj_val);
	return min_dist;

}


vector< float > MainKnapsack::solve_plne_ws_function(vector<float> weighted_sum){

	IloEnv   env;
	IloModel model(env);
	vector<IloNumVar > x(n_items);
	IloRangeArray Constraints(env);

	//VARIABLES
	for(int i = 0; i < n_items; i++){
		x[i] = IloNumVar(env, 0.0, 1.0, ILOINT);
		ostringstream varname;
		varname.str("");
		varname<<"x_"<<i;
		x[i].setName(varname.str().c_str());
	}

	//CONSTRAINTS
	IloExpr c1(env);

	for(int j = 0; j < n_items ; j++)
		c1 += x[j] * get_weight_of(j);

	Constraints.add(c1 <= Backpack_capacity );

	model.add(Constraints);

	//OBJECTIVE
	IloObjective obj=IloAdd(model, IloMaximize(env));

	for(int i = 0; i < n_items; i++){
		float coeff = 0.;
		for(int j = 0; j < p_criteria ; j++)
			  coeff += get_utility(i,j) * weighted_sum[j];

		obj.setLinearCoef(x[i], coeff);
	}


	//SOLVE
	IloCplex cplex(model);

	cplex.setOut(env.getNullStream());

	if ( !cplex.solve() ) {
		 env.error() << "Failed to optimize LP" << endl;
		 exit(1);
	}

//	env.out() << "Solution status = " << cplex.getStatus() << endl;
//	env.out() << "Solution value  = " << cplex.getObjValue() << endl;

	//GET SOLUTION
	set< int > items;
	for(int i = 0; i < n_items; i++){
		if( cplex.getValue(x[i]) > 0)
			items.insert(i);
	}

	env.end();

	AlternativeKnapsack * alt = new AlternativeKnapsack(items, this);

	return alt->get_objective_values();
}


void MainKnapsack::evaluate_solutions(string weighted_DM_preferences,float time){

	ifstream fic_read(weighted_DM_preferences.c_str());
	string line;
	int i = 0;
	if (!(fic_read) or weighted_DM_preferences.find(".ks") == std::string::npos){
		cerr<<"Error occurred eval_sol"<<endl;
	}

	//read WS_DMs_preference
	vector<float > weight_DM(p_criteria,0);

	getline(fic_read,line);
	char *cline = new char[line.length() + 1]; // or
	std::strcpy(cline, line.c_str());

	char * pch = strtok (cline," 	,;");
	while (pch != NULL and i < p_criteria){
		weight_DM[i] = atof(pch);
		pch = strtok (NULL, " 	,;");
		i++;
	}

	//get best alternative according to WS_DM
	vector< float > opt_values = solve_plne_ws_function(weight_DM);
//	cout<<"OPT VAL : ";
//	print_vector(opt_values);

	//Get minimum objective values difference between the best alternative and PLS front computed
	float min_eff_dist = nearest_alternative(filename_instance+".eff",opt_values);
//	cout<<"min eff dist VAL "<<min_eff_dist<<endl;

	//Get minimum objective values difference between the best alternative and WS-MOLS front computed
	float min_mols_dist = nearest_alternative(filename_instance+".sol",opt_values);
//	cout<<"min mols dist VAL "<<min_mols_dist<<endl;


	//write evaluation
	ostringstream FileName;
	FileName.str("");
	FileName <<filename_instance.c_str() << ".eval";
	ofstream fic(FileName.str(), ios::app);

	fic<<min_mols_dist<<","<<min_eff_dist<<","<<time<<endl;

	fic.close();
}



void MainKnapsack::filter_efficient_set(){

	list< Alternative* > fixed_opt_set(OPT_Solution.begin(),OPT_Solution.end());
	for(list< Alternative* >::iterator el1 = fixed_opt_set.begin(); el1 != fixed_opt_set.end(); ++el1){
		for(list< Alternative* >::iterator el2 = fixed_opt_set.begin(); el2 != fixed_opt_set.end(); ++el2){
			if((*el1)->get_id() == (*el2)->get_id())
				continue;
			if( (*el1)->dominates(*el2) == 1)
				OPT_Solution.erase(el2);
			else if((*el1)->dominates(*el2) == -1)
				OPT_Solution.erase(el1);

		}
	}
}


list< Alternative * > MainKnapsack::MOLS(){

	Alternative* alt;
	list< Alternative* > Local_front(0);
	//First initialization

	for(list< Alternative* >::iterator p = Population.begin(); p != Population.end(); ++p){
		Update_Archive(*p,OPT_Solution);
	}

	while(Population.size() > 0){

		//get first element
		alt = Population.front();

		vector<Alternative *> current_neighbors = alt->get_neighborhood();

		for(vector< Alternative* >::iterator neighbor = current_neighbors.begin(); neighbor != current_neighbors.end(); ++neighbor){

			if( alt->dominates(*neighbor) != 1 )
				Update_Archive(*neighbor,Local_front);
		}

		for(list< Alternative* >::iterator new_alt = Local_front.begin(); new_alt != Local_front.end(); ++new_alt){

			if ( Update_Archive(*new_alt, OPT_Solution) ){
				Population.push_back(*new_alt);
			}

		}
		//remove first element
		Population.pop_front();
		Local_front.clear();
	}

	filter_efficient_set();

	write_solution();

	return OPT_Solution;
}


bool MainKnapsack::Update_Archive(Alternative* p, list< Alternative* > &set_SOL){

	vector< Alternative* > to_remove;
	bool dominated = false;

	for(list< Alternative* >::iterator alt = set_SOL.begin(); alt != set_SOL.end(); ++alt){

		int dom_val = (*alt)->dominates(p);
		if(dom_val == 1){			// alt dominates p
			dominated = true;
//			return false;
		}
		else if( dom_val == -1 )   // p dominates alt
			to_remove.push_back(*alt);
	}

	for(vector< Alternative* >::iterator rm = to_remove.begin(); rm != to_remove.end(); ++rm)
		set_SOL.remove(*rm);


	if( dominated )
		return false;

	set_SOL.push_back(p);
	return true;
}








