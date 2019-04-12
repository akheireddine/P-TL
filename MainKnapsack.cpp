
#include <set>

#include "MainKnapsack.h"
#define TIMEOUT 240

//#define __PRINT__







MainKnapsack::MainKnapsack(string filename, int init_population_size , string matrix_filename){

	filename_instance = filename;

	readFilenameInstance(filename_instance);

	readWS_Matrix(matrix_filename);

	GenerateInitialPopulation(init_population_size);

//	readInitPopulationFile(init_population_filename);




}


/**
 * ************************************************* READING PART (INITIALIZATION)  *************************************************
 */









void MainKnapsack::readFilenameInstance(string filename){

	string line;
	char buff[100];
	int i = 0;

	vector< float > line_value;

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
#ifdef __PRINT__
	cout<<"Information sur l'instance : "<<endl;
	cout<<"   Instance de taille ("<<to_string(n_items)<<")"<<endl;
	cout<<"   Capacité du sac-à-dos ("<<to_string(Backpack_capacity)<<")"<<endl;
	cout<<"   Nombre de criètres ("<<to_string(p_criteria)<<")"<<endl;
#endif
	fic.close();


	vector<float>().swap(line_value);
}


void MainKnapsack::readWS_Matrix(string filename){

	WS_matrix.clear();
	WS_matrix.resize(0);

	if(filename.find("PARETO") != std::string::npos)
		change_to_pareto_selection();

	else {
		ifstream fic(filename.c_str());
		string line;
		int i = 0;
		if (!(fic) or filename.find(".csv") == std::string::npos){
			cerr<<"Error occurred readWS_Matrix"<<endl;
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

#ifdef __PRINT__
	cout<<"   Matrice des objectives :"<<endl;
	for(int i = 0; i < p_criteria; i++){
		cout<<"   ";
		for(int j = 0; j < n_objective; j++)
			cout<<WS_matrix[i][j]<< " ";
		cout<<endl;
	}
#endif
}


void MainKnapsack::write_solution(string filename){

	ofstream fic(filename.c_str());

	for(list< Alternative *>::iterator alt = OPT_Solution.begin(); alt != OPT_Solution.end(); alt++){
		for(int i = 0; i < p_criteria; i++)
			fic<< (*alt)->get_criteria_values()[i]<< " ";
		fic<<endl;
	}
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
		AlternativeKnapsack * alt = new AlternativeKnapsack(individu, this, WS_matrix);
		Population.push_back(alt);
		set<int>().swap(individu);
	}
	vector<int>().swap(all_items);


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








//Filter the final archive (objective space)
void MainKnapsack::filter_efficient_set(){

	list< Alternative* > fixed_opt_set(OPT_Solution.begin(),OPT_Solution.end());
	for(list< Alternative* >::iterator el1 = fixed_opt_set.begin(); el1 != fixed_opt_set.end(); ++el1){
		for(list< Alternative* >::iterator el2 = fixed_opt_set.begin(); el2 != fixed_opt_set.end(); ++el2){
			if((*el1)->get_id() == (*el1)->get_id())
				continue;
			if( (*el1)->dominates_objective_space(*el2) == 1){
				OPT_Solution.erase(el2);
				delete (*el2);
			}
			else if((*el1)->dominates_objective_space(*el2) == -1){
				OPT_Solution.erase(el1);
				delete (*el1);
			}

		}
	}
}

//Filter the final archive (decision spaec)
void MainKnapsack::filter_efficient_set_decision_space(){

	list< Alternative* > fixed_opt_set(OPT_Solution.begin(),OPT_Solution.end());
	for(list< Alternative* >::iterator el1 = fixed_opt_set.begin(); el1 != fixed_opt_set.end(); ++el1){
		for(list< Alternative* >::iterator el2 = fixed_opt_set.begin(); el2 != fixed_opt_set.end(); ++el2){

			if((*el1)->get_id() == (*el1)->get_id())
				continue;

			int value = (*el1)->dominates_decision_space(*el2);

			if( value  == 1){
				OPT_Solution.erase(el2);
				delete (*el2);
			}
			else if( value == -1){
				OPT_Solution.erase(el1);
				delete (*el1);
			}

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

	while( (Population.size() > 0)  and ((clock() / CLOCKS_PER_SEC) - starting_time_sec <= TIMEOUT ) ){
		nb_iteration++;
		//get first element
		alt = Population.front();

		//save_new_point(filename_instance+".expl",alt);

		vector<Alternative *> current_neighbors = alt->get_neighborhood();

		for(vector< Alternative* >::iterator neighbor = current_neighbors.begin(); neighbor != current_neighbors.end(); ++neighbor){
			//Prefiltrage
			if( alt->dominates_objective_space(*neighbor) != 1 )
				Update_Archive(*neighbor,Local_front);
		}


		for(list< Alternative* >::iterator new_alt = Local_front.begin(); new_alt != Local_front.end(); ++new_alt){
			//Filtrage global
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


	list<Alternative*>().swap(Local_front);

	return OPT_Solution;
}



list< Alternative * > MainKnapsack::MOLS(double starting_time_sec,int steps){

	Alternative* alt;
	list< Alternative* > Local_front(0);

	int nb_iteration=0;

	//First initialization
	for(list< Alternative* >::iterator p = Population.begin(); p != Population.end(); ++p)
		Update_Archive(*p,OPT_Solution);


	while((Population.size() > 0)  and ((clock() /CLOCKS_PER_SEC) - starting_time_sec <= TIMEOUT )   and (nb_iteration < steps)){
		nb_iteration++;
		//get first element
		alt = Population.front();

		//save_new_point(filename_instance+".expl",alt);

		vector<Alternative *> current_neighbors = alt->get_neighborhood();

		for(vector< Alternative* >::iterator neighbor = current_neighbors.begin(); neighbor != current_neighbors.end(); ++neighbor){
			//Prefiltrage
			if( alt->dominates_objective_space(*neighbor) != 1 )
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

	list<Alternative*>().swap(Local_front);

	return OPT_Solution;
}



list< Alternative * > MainKnapsack::MOLS_Population_Size_FIXE(double starting_time_sec, int UB_Population_size){

	Alternative* alt;
	vector< Alternative* > Local_front(0);
	vector< Alternative* > Dominated_alt(0);
	int front_size = Population.size();

	int nb_iteration=0;

	//First initialization
	for(list< Alternative* >::iterator p = Population.begin(); p != Population.end(); ++p)
//		Update_Archive(*p,OPT_Solution);
		OPT_Solution.push_back(*p);

	int step = 0;

	while( Population.size() > 0  and ((clock() / CLOCKS_PER_SEC) - starting_time_sec <= TIMEOUT ) ){
		nb_iteration++;
		front_size--;

		alt = Population.front();
		Population.pop_front();

		save_new_point(filename_instance+"_"+to_string(UB_Population_size)+"_"+to_string(step)+".expl",alt);

		vector<Alternative *> current_neighbors = alt->get_neighborhood();

		for(vector< Alternative* >::iterator neighbor = current_neighbors.begin(); neighbor != current_neighbors.end(); ++neighbor){
			//if neighbor is dominated add to Local_front
			if( alt->dominates_objective_space(*neighbor) == 1 )
				Dominated_alt.push_back(*neighbor);
			else
				Local_front.push_back(*neighbor);
		}

		if( front_size == 0 ){
			int pop_size = 0;
			random_shuffle( Local_front.begin(), Local_front.end() );
			for(vector< Alternative* >::iterator new_alt = Local_front.begin(); new_alt != Local_front.end(); ++new_alt){
				if( pop_size < UB_Population_size and Update_Archive(*new_alt, OPT_Solution) ){
					Population.push_back(*new_alt);
					pop_size++;
				}
				else if( !Update_Archive(*new_alt, OPT_Solution) )
					Dominated_alt.push_back(*new_alt);
			}

			int i = 0;
			random_shuffle( Dominated_alt.begin(), Dominated_alt.end() );
			cout<<"NON DOMINATED : "<<pop_size;

			while(pop_size < UB_Population_size and (i < 0 ) and pop_size > 0) { // (int)Dominated_alt.size())){
				OPT_Solution.push_back(Dominated_alt[i]);
				Population.push_back(Dominated_alt[i]);
				i++;
				pop_size++;
			}
			cout<<"    DOMINATED : "<<pop_size<<endl;

			front_size = ( UB_Population_size < (int)Population.size() ) ? UB_Population_size : (int)Population.size();     //SAME AS POPULATION SIZE
			Local_front.clear();
			Dominated_alt.clear();
			step++;
			cout<<"Population size dn : "<<Population.size()<<endl;
		}

	}

	cout<<"Number of iteration "<<nb_iteration<<endl;

	filter_efficient_set();

//	write_solution(filename_instance+".sol");
	write_solution(filename_instance+"_"+to_string(UB_Population_size)+".sol");

	vector<Alternative*>().swap(Local_front);
	vector<Alternative*>().swap(Dominated_alt);

	return OPT_Solution;
}

















void MainKnapsack::HYBRID_WS_PLS(double starting_time_sec,int steps){

	//WS
	MOLS(starting_time_sec,steps);

	Population = OPT_Solution;

	change_to_pareto_selection();
	//PLS
#ifdef __PRINT__
	cout<<"   Matrice des objectives :"<<endl;
	for(int i = 0; i < p_criteria; i++){
		cout<<"   ";
		for(int j = 0; j < n_objective; j++)
			cout<<WS_matrix[i][j]<< " ";
		cout<<endl;
	}
#endif
	MOLS(starting_time_sec);

}


void MainKnapsack::HYBRID_PLS_WS(double starting_time_sec, int steps){

	//PLS
	change_to_pareto_selection();

	MOLS(starting_time_sec,steps);

	Population = OPT_Solution;

	//WS

	update_alternatives(Population);
	cout<<"Number of solution found with PLS : "<<OPT_Solution.size()<<endl;

	MOLS(starting_time_sec);
	cout<<"Number of solution found with WS : "<<OPT_Solution.size()<<endl;

}













/**
 * ************************************************* UPDATE PART *************************************************
 */




void MainKnapsack::update_alternatives(list<Alternative*> &set_Alt){

	for(list<Alternative*>::iterator alt = set_Alt.begin(); alt != set_Alt.end(); ++alt ){
		vector<float> ws_random = Tools::generate_random_restricted_WS_aggregator(p_criteria, WS_matrix);
		vector<vector<float> > ws_matrix(p_criteria,vector<float>());
		for(int i = 0; i < p_criteria; i++)
			ws_matrix[i].push_back(ws_random[i]);

		(*alt)->set_local_WS_matrix(ws_matrix);
		(*alt)->update_objective_vector();
	}

}






bool MainKnapsack::Update_Archive(Alternative* p, list< Alternative* > &set_SOL){

	vector< Alternative* > to_remove;
	int dom_val;

	for(list< Alternative* >::iterator alt = set_SOL.begin(); alt != set_SOL.end(); ++alt){

		dom_val = (*alt)->dominates_objective_space(p);
		if(dom_val == 1)			// alt dominates p
			return false;

		else if( dom_val == -1 )   // p dominates alt
			to_remove.push_back(*alt);
	}

	for(vector< Alternative* >::iterator rm = to_remove.begin(); rm != to_remove.end(); ++rm){
		set_SOL.remove(*rm);
	}

	set_SOL.push_back(p);

	vector<Alternative*>().swap(to_remove);
	return true;
}







//#define Alpha_SA 0.9      // in 0.8 <= alpha <= 1


bool MainKnapsack::Update_Archive_Threshold_Accepting(Alternative* p, list< Alternative* > &set_SOL){

	bool is_dominated = false;
	vector< Alternative* > to_remove;
	int dom_val, nb_alt_composed_of = 0;

	for(list< Alternative* >::iterator alt = set_SOL.begin(); alt != set_SOL.end(); ++alt){

		dom_val = (*alt)->dominates_objective_space(p);

		if(dom_val == 1){			// alt dominates p
			is_dominated = true;
			if((*alt)->contains_items(p))
				nb_alt_composed_of++;
		}

		else if( dom_val == -1 )   // p dominates alt
			to_remove.push_back(*alt);
	}


	//*****************************************************************//
	if(is_dominated){

//		T_SA *= Alpha_SA;
//		float u = rand()*1.0/RAND_MAX;
//		float delta = (1+nb_alt_composed_of)*1.0 / (n_items - p->get_nb_items());
//		cout<<"TSA  "<<T_SA<<"     DELTA  "<<delta<<"   u "<<u<<"   exp "<<exp(- delta/T_SA)<<endl;

//		ofstream fic("DELTA_SIMULATED_ANNEALING.txt",ios::app);
//		fic<<delta<<endl;
//		fic.close();

//		if ( u >= exp(-delta/T_SA) )
//			return false;
	}
	//*****************************************************************//


	for(vector< Alternative* >::iterator rm = to_remove.begin(); rm != to_remove.end(); ++rm){
		set_SOL.remove(*rm);
	}

	set_SOL.push_back(p);

	vector<Alternative*>().swap(to_remove);
	return true;
}







































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
//		AlternativeKnapsack* alt = new AlternativeKnapsack(set_items, this, WS_matrix);
//		Population.push_back(alt);
//
//	}
//	cout<<"   Taille de la population initiale ("<<to_string(Population.size())<<")"<<endl;
//
//	if( Population.size() == 0){
//		set<int> empt;
//		AlternativeKnapsack *alt = new AlternativeKnapsack(empt, this, WS_matrix);
//		Population.push_back(alt);
//	}
//	fic.close();
//}





