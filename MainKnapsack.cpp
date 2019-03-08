
#include <set>
#include "MainKnapsack.h"



#include <sstream>      // std::ostringstream

MainKnapsack::MainKnapsack(string filename, string pref_filename, string init_population_filename){

	filename_instance = filename;

	readFilenameInstance(filename_instance);

	readWS_Matrix(pref_filename);

	readInitPopulationFile(init_population_filename);

//	cout<<"- Instance name     : "<<filename_instance<<endl;
//	cout<<"- Backpack capacity : "<<Backpack_capacity<<endl;
//	cout<<"- number of items   : "<<n_items<<endl;
//	cout<<"- number of criteria  : "<<p_criteria<<endl;
//	cout<<"- size of initial population : "<<Population.size()<<endl<<"  ";
//	for(list< Alternative* >::iterator i = Population.begin(); i != Population.end(); ++i ){
//		(*i)->print_alternative();
//		cout<<"  ";
//	}
//	cout<<endl;
//	cout<<"- number of objective : "<<n_objective<<endl<<"  ";
//	for(int i = 0; i < p_criteria; i++){
//		for(int j = 0; j < n_objective; j++)
//			cout<< WS_matrix[i][j] <<" ";
//		cout<<endl<<"  ";
//	}
//	cout<<endl;

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

	fic.close();
}


void MainKnapsack::readFilenameInstance(string filename){

	string line;
	char buff[100];
	int i = 0;

	vector< float > line_value;

	ifstream fic(filename.c_str());

	if (!(fic) or filename.find(".dat") == std::string::npos){
		cerr<<"Error occurred"<<endl;
	}


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
	FileName <<filename_instance.c_str() << ".sol";
	ofstream fic(FileName.str().c_str());

	for(list< Alternative *>::iterator alt = OPT_Solution.begin(); alt != OPT_Solution.end(); alt++){
		for(int i = 0; i < n_objective; i++){
			fic<< (*alt)->get_objective_values()[i]<< " ";
//			cout<< (*alt)->get_objective_values()[i]<< " ";
		}
		fic <<endl;
//		cout<<endl;
	}
}


/**
 * TODO CONTINUER !!!!!!!!!!!!!!!!!!!
 */
void MainKnapsack::evaluate_solutions(string weighted_DM_preferences){

	ifstream fic_read(weighted_DM_preferences.c_str());
	string line;
	int i = 0;
	if (!(fic_read) or weighted_DM_preferences.find(".csv") == std::string::npos){
		cerr<<"Error occurred eval_sol"<<endl;
	}

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




	ostringstream FileName;
	FileName.str("");
	FileName <<filename_instance.c_str() << ".eval";
	ofstream fic(FileName.str().c_str());

	for(list< Alternative *>::iterator alt = OPT_Solution.begin(); alt != OPT_Solution.end(); ++alt){
		vector<float > obj_val = (*alt)->get_objective_values();

	}


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
	list< Alternative* > Local_front;
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

		for(list< Alternative* >::iterator new_alt = Local_front.begin(); new_alt != Local_front.end(); new_alt++){

			if ( Update_Archive(*new_alt, OPT_Solution) ){
				Population.push_back(*new_alt);
			}

		}
		//remove first element
		Population.pop_front();
		Local_front.clear();
	}

	cout<<"OPT before filter "<<OPT_Solution.size()<<endl;
	filter_efficient_set();
	cout<<"OPT after filter "<<OPT_Solution.size()<<endl;

	write_solution();

	return OPT_Solution;
}


bool MainKnapsack::Update_Archive(Alternative* p, list< Alternative* > &set_SOL){

	vector< Alternative* > to_remove;

	for(list< Alternative* >::iterator alt = set_SOL.begin(); alt != set_SOL.end(); ++alt){

		int dom_val = (*alt)->dominates(p);
		if(dom_val == 1)			// alt dominates p
			return false;
		else if( dom_val == -1 )   // p dominates alt
			to_remove.push_back(*alt);

	}

	for(vector< Alternative* >::iterator rm = to_remove.begin(); rm != to_remove.end(); ++rm)
		set_SOL.remove(*rm);

	set_SOL.push_back(p);
	return true;
}















