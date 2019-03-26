
#include <set>

#include "MainKnapsack.h"
#define TIMEOUT 180


MainKnapsack::MainKnapsack(string filename,string type_inst, string num_inst, int init_population_size , string matrix_filename){

	filename_instance = filename;
	type_instance = type_inst;
	num_instance = num_inst;

	readFilenameInstance(filename_instance);

	readWS_Matrix(matrix_filename);

	GenerateInitialPopulation(init_population_size);

//	readInitPopulationFile(init_population_filename);


}


/**
 * ************************************************* READING PART (INITIALIZATION)  *************************************************
 */

//void MainKnapsack::readInitPopulationFile(string filename){
//
//	Population.clear();
//	ifstream fic(filename.c_str());
//
//
//	if (!(fic) or filename.find(".ks") == std::string::npos){
//		cerr<<"Error occurred"<<endl;
//	}
//
//	string line;
//	float total_weight;
//
//	while(!fic.eof()){
//		total_weight = 0;
//
//		getline(fic,line);
//
//		if( line.size() == 0)
//			continue;
//
//		set<int> set_items;
//		char *cline = new char[line.length() + 1];
//		std::strcpy(cline, line.c_str());
//
//		char * pch = strtok (cline," 	,");
//		while (pch != NULL){
//			set_items.insert(atoi(pch));
//			total_weight += std::get<0>(Items_information[atoi(pch)]);
//			pch = strtok (NULL, " 	,");
//		}
//
//		if(total_weight > Backpack_capacity){
//			cerr<<"Not feasable initialization"<<endl;
//			exit(1);
//		}
//
//		AlternativeKnapsack* alt = new AlternativeKnapsack(set_items, this);
//		Population.push_back(alt);
//
//	}
//	cout<<"   Taille de la population initiale ("<<to_string(Population.size())<<")"<<endl;
//
//	if( Population.size() == 0){
//		set<int> empt;
//		AlternativeKnapsack *alt = new AlternativeKnapsack(empt, this);
//		Population.push_back(alt);
//	}
//	fic.close();
//}




void MainKnapsack::readFilenameInstance(string filename){

	string line;
	char buff[100];
	int i = 0;

	vector< float > line_value;

//	ostringstream FileName;
//	FileName.str("");
//	FileName <<filename.c_str()<<".dat";
//	ifstream fic(FileName.str());

	ifstream fic((filename+".dat").c_str());

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

	cout<<"Information sur l'instance : "<<endl;
	cout<<"   Instance de taille ("<<to_string(n_items)<<")"<<endl;
	cout<<"   Capacité du sac-à-dos ("<<to_string(Backpack_capacity)<<")"<<endl;
	cout<<"   Nombre de criètres ("<<to_string(p_criteria)<<")"<<endl;

	fic.close();
}


void MainKnapsack::readWS_Matrix(string filename){

	if(filename.find("PARETO") != std::string::npos)
		change_to_pareto_selection();

	else {
		ifstream fic(filename.c_str());
		string line;
		int i = 0;
		if (!(fic) or filename.find(".csv") == std::string::npos){
			cerr<<"Error occurred fileMatrix"<<endl;
		}

		WS_matrix.resize(p_criteria,vector< float >());

		while( !fic.eof() and i < p_criteria){
			WS_matrix[i].clear();
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
	}

	n_objective = WS_matrix[0].size();


	cout<<"   Matrice des objectives :"<<endl;
	for(int i = 0; i < p_criteria; i++){
		cout<<"   ";
		for(int j = 0; j < n_objective; j++)
			cout<<WS_matrix[i][j]<< " ";
		cout<<endl;
	}
}


void MainKnapsack::write_solution(string filename){

	ofstream fic(filename.c_str());

	for(list< Alternative *>::iterator alt = OPT_Solution.begin(); alt != OPT_Solution.end(); alt++){
		for(int i = 0; i < p_criteria; i++)
			fic<< (*alt)->get_criteria_values()[i]<< " ";
		fic<<endl;
	}
}


void MainKnapsack::write_coeff_functions(string filename ){

	ofstream fic(filename.c_str(), ios::app);

	fic<<endl<<"Optimal solution :"<<endl;
	fic<<"("; for(int i = 0; i < p_criteria; i++) fic<< OPT_Alternative->get_criteria(i) <<", "; fic<<")"<<endl;
	fic<<endl<<"Matrice des objectives & Optimal solution:"<<endl;

	for(int i = 0; i < p_criteria; i++){
		fic<<"   ";
		for(int j = 0; j < n_objective; j++)
			fic<<to_string(WS_matrix[i][j])<< " ";
		fic<<endl;
	}
	fic<<endl;

	fic.close();
}


void MainKnapsack::GenerateInitialPopulation(int size_population){

	float bp = 0;

	vector<int> all_items;

	for(int i = 0; i < n_items; i++)
		all_items.push_back(i);

	for (int i = 0; i < size_population; i++){
		bp = 0;
		set<int> individu;
		list<int> items(all_items.begin(), all_items.end());

		while(bp < Backpack_capacity  and (items.size() != 0)  and (rand()*1.0/RAND_MAX) < 0.7){
			list<int>::iterator iteratour = items.begin();
			advance(iteratour, rand()%items.size() );

			int itm = *iteratour;// items[ rand()%items.size() ];
			items.remove( itm );

			if ( (get_weight_of(itm) + bp) > Backpack_capacity )
				continue;

			individu.insert(itm);
			bp += get_weight_of(itm);
		}
		AlternativeKnapsack * alt = new AlternativeKnapsack(individu, this);
		Population.push_back(alt);
	}

}


void MainKnapsack::save_new_point(string filename, Alternative * alt){
	ofstream fic(filename.c_str(),ios::app);

	for(int i = 0; i < p_criteria; i++)
		fic<< alt->get_criteria_values()[i]<< " ";
	fic<<endl;

	fic.close();
}

/**
 * ************************************************* SOLVING PART *************************************************
 */




//Filter the final archive
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


list< Alternative * > MainKnapsack::MOLS(double starting_time_sec){

	Alternative* alt;
	list< Alternative* > Local_front(0);

	int nb_iteration=0;

	//First initialization
	for(list< Alternative* >::iterator p = Population.begin(); p != Population.end(); ++p)
		Update_Archive(*p,OPT_Solution);


	while((Population.size() > 0)  and ((clock() /CLOCKS_PER_SEC) - starting_time_sec <= TIMEOUT ) ){
		nb_iteration++;
		//get first element
		alt = Population.front();
		save_new_point(filename_instance+".expl",alt);

		vector<Alternative *> current_neighbors = alt->get_neighborhood();

		for(vector< Alternative* >::iterator neighbor = current_neighbors.begin(); neighbor != current_neighbors.end(); ++neighbor){
			//Prefiltrage
			if( alt->dominates(*neighbor) != 1 )
				Update_Archive(*neighbor,Local_front);
		}

		for(list< Alternative* >::iterator new_alt = Local_front.begin(); new_alt != Local_front.end(); ++new_alt){
			//Filter OPT_Solution set
			if ( Update_Archive(*new_alt, OPT_Solution) )
				Population.push_back(*new_alt);
		}

		//remove first element
		Population.pop_front();
		Local_front.clear();

	}

	cout<<"Number of iteration "<<nb_iteration<<endl;

	filter_efficient_set();

	write_solution(filename_instance+".sol");

	return OPT_Solution;
}




list< Alternative * > MainKnapsack::MOLS(double starting_time_sec,int steps){

	Alternative* alt;
	list< Alternative* > Local_front(0);

	int nb_iteration=0;

	//First initialization
	for(list< Alternative* >::iterator p = Population.begin(); p != Population.end(); ++p)
		Update_Archive(*p,OPT_Solution);


	while((Population.size() > 0)  and ((clock() /CLOCKS_PER_SEC) - starting_time_sec <= TIMEOUT )  and nb_iteration < steps){
		nb_iteration++;
		//get first element
		alt = Population.front();
		save_new_point(filename_instance+".expl",alt);

		vector<Alternative *> current_neighbors = alt->get_neighborhood();

		for(vector< Alternative* >::iterator neighbor = current_neighbors.begin(); neighbor != current_neighbors.end(); ++neighbor){
			//Prefiltrage
			if( alt->dominates(*neighbor) != 1 )
				Update_Archive(*neighbor,Local_front);
		}

		for(list< Alternative* >::iterator new_alt = Local_front.begin(); new_alt != Local_front.end(); ++new_alt){
			//Filter OPT_Solution set
			if ( Update_Archive(*new_alt, OPT_Solution) or  (rand()*1.0/RAND_MAX) < 0.5 )
				Population.push_back(*new_alt);
		}

		//remove first element
		Population.pop_front();
		Local_front.clear();

	}

	cout<<"Number of iteration "<<nb_iteration<<endl;

	filter_efficient_set();

	write_solution(filename_instance+".sol");

	return OPT_Solution;
}



void MainKnapsack::HYBRID_WS_PLS(double starting_time_sec,int steps){

	//WS
	MOLS(starting_time_sec,steps);

	Population = OPT_Solution;

	change_to_pareto_selection();
	//PLS
	MOLS(starting_time_sec);

}


bool MainKnapsack::Update_Archive(Alternative* p, list< Alternative* > &set_SOL){

	vector< Alternative* > to_remove;
	int dom_val;

	for(list< Alternative* >::iterator alt = set_SOL.begin(); alt != set_SOL.end(); ++alt){

		dom_val = (*alt)->dominates(p);
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























