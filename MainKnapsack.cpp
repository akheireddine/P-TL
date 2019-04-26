
#include <set>

#include "MainKnapsack.h"
#define TIMEOUT 240

#define N 10
#define P 0.4
//#define __PRINT__





extern list<set<int>> init_population;
extern int INFO;


MainKnapsack::MainKnapsack(string filename, int init_population_size , string matrix_filename){

	filename_instance = filename;

	readFilenameInstance(filename_instance);

	readWS_Matrix(matrix_filename);

	GenerateInitialPopulation(init_population_size);

}


MainKnapsack::MainKnapsack( int population_size_init, string filename, string matrix_filename){

	filename_instance = filename;

	readFilenameInstance(filename_instance);

	readWS_Matrix(matrix_filename);

	for(int i = 0; i < population_size_init ; i++){
		set<int> individu = init_population.front();
		string id_alt = Tools::decode_set_items(individu, n_items);
		dic_Alternative[ id_alt ] = new AlternativeKnapsack(individu, this, WS_matrix);;
		Population.push_back(id_alt);
	}

}


/**
 * ************************************************* READING PART (INITIALIZATION)  *************************************************
 */


void MainKnapsack::Generate_random_Population(string filename, int number_of_individu){

	int n_item;
	float Backpack_capacity = 0;
	vector< tuple<float, vector< float> > > Items_information;

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
	n_item = 0;
	if( line[0] == 'n')
		sscanf(line.c_str(),"%s %d",buff,&n_item);

	Items_information.resize(n_item);

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

	//comments
	while( line[0] == 'c' )
		getline(fic,line);

	//total capacity
	if( line[0] == 'W' )
		sscanf(line.c_str(),"%s %f",buff,&Backpack_capacity);

	/************************************* GENERATION *************************************/

	float bp = 0;
	set<int> individu;
	vector<int> all_items(n_item);
	list<int>::iterator iteratour;

	for(int i = 0; i < n_item; i++)
		all_items.push_back(i);

	for (int i = 0; i < number_of_individu; i++){
		bp = 0;
		individu.clear();
		list<int> items(all_items.begin(), all_items.end());

		while(bp < Backpack_capacity  and (items.size() != 0)  ){//and (rand()*1.0/RAND_MAX) < 0.8){
			iteratour = items.begin();
			advance(iteratour, rand()%items.size() );

			int itm = *iteratour;// items[ rand()%items.size() ];
			items.remove( itm );

			float weight_itm = get<0>(Items_information[itm]);

			if ( (weight_itm + bp) > Backpack_capacity )
				continue;

			individu.insert(itm);
			bp += weight_itm;
		}

		init_population.push_back(individu);

	}
}




void MainKnapsack::readFilenameInstance(string filename){

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

//	delete [] cline;
//	delete [] pch;
}


void MainKnapsack::readWS_Matrix(string filename){

	char *cline, *pch;
	int i;
	WS_matrix.clear();
	WS_matrix.resize(0);

	if(filename.find("PARETO") != std::string::npos)
		change_to_pareto_selection();

	else {
		ifstream fic(filename.c_str());
		string line;
		i = 0;

		if (!(fic) or filename.find(".csv") == std::string::npos){
			cerr<<"Error occurred readWS_Matrix"<<endl;
		}

		WS_matrix.resize(p_criteria,vector< float >());

		while( !fic.eof() and i < p_criteria){
			WS_matrix[i].clear();
			getline(fic,line);

			cline = new char[line.length() + 1]; // or
			std::strcpy(cline, line.c_str());

			pch = strtok (cline," 	,;");
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

//	delete cline;
//	delete pch;
}



void MainKnapsack::GenerateInitialPopulation(int size_population){

	float bp = 0;
	set<int> individu;
	vector<int> all_items(n_items);
	list<int>::iterator iteratour;

	Population.clear();
	for(int i = 0; i < n_items; i++)
		all_items.push_back(i);

	for (int i = 0; i < size_population; i++){
		bp = 0;
		individu.clear();
		list<int> items(all_items.begin(), all_items.end());

		while(bp < Backpack_capacity  and (items.size() != 0) ){// and (rand()*1.0/RAND_MAX) < 0.7){
			iteratour = items.begin();
			advance(iteratour, rand()%items.size() );

			int itm = *iteratour;// items[ rand()%items.size() ];
			items.remove( itm );

			if ( (get_weight_of(itm) + bp) > Backpack_capacity )
				continue;

			individu.insert(itm);
			bp += get_weight_of(itm);
		}
		string id_alt = Tools::decode_set_items(individu, n_items);
		dic_Alternative[ id_alt ] = new AlternativeKnapsack(individu, this, WS_matrix);;
		Population.push_back(id_alt);
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

	vector<Alternative*> to_rm;

	for(list< Alternative* >::iterator el1 = OPT_Solution.begin(); el1 != OPT_Solution.end(); ++el1){

		for(list< Alternative* >::iterator el2 = OPT_Solution.begin(); el2 != OPT_Solution.end(); ++el2){

			if( ((*el1)->get_id_alt()).compare((*el2)->get_id_alt()) == 0 )
				continue;

			int value = (*el1)->dominates_objective_space(*el2);

			if( value == 1){
				to_rm.push_back(*el2);
			}
			else if( value == -1){
				to_rm.push_back(*el1);
			}
		}
	}

	for(int i = 0; i < (int)to_rm.size(); i++)
		OPT_Solution.remove(to_rm[i]);

}

//Filter the final archive (decision spaec)
void MainKnapsack::filter_efficient_set_decision_space(){

	vector<Alternative*> to_rm;
	for(list< Alternative* >::iterator el1 = OPT_Solution.begin(); el1 != OPT_Solution.end(); ++el1){
		for(list< Alternative* >::iterator el2 = OPT_Solution.begin(); el2 != OPT_Solution.end(); ++el2){
			if( ((*el1)->get_id_alt()).compare((*el2)->get_id_alt()) == 0 )
				continue;

			int value = (*el1)->dominates_decision_space(*el2);

			if( value  == 1){
				to_rm.push_back(*el2);
			}
			else if( value == -1){
				to_rm.push_back(*el1);
			}
		}
	}

	for(int i = 0; i < (int)to_rm.size(); i++)
		OPT_Solution.remove(to_rm[i]);

}


list< Alternative * > MainKnapsack::MOLS(double starting_time_sec){
	return OPT_Solution;
}


list< Alternative * > MainKnapsack::MOLS(double starting_time_sec,int steps){
//	Alternative* alt;
//	list< Alternative* > Local_front(0);
//
//	int nb_iteration=0;
//
//	//First initialization
//	for(list< Alternative* >::iterator p = Population.begin(); p != Population.end(); ++p)
//		Update_Archive(*p,OPT_Solution);
//
//
//	while((Population.size() > 0)  and ((clock() /CLOCKS_PER_SEC) - starting_time_sec <= TIMEOUT )   and (nb_iteration < steps)){
//		nb_iteration++;
//		//get first element
//		alt = Population.front();
//
//		//save_new_point(filename_instance+".expl",alt);
//
//		vector<Alternative *> current_neighbors = alt->get_neighborhood();
//
//		for(vector< Alternative* >::iterator neighbor = current_neighbors.begin(); neighbor != current_neighbors.end(); ++neighbor){
//			//Prefiltrage
//			if( alt->dominates_objective_space(*neighbor) != 1 )
//				Update_Archive(*neighbor,Local_front);
//		}
//
//		for(list< Alternative* >::iterator new_alt = Local_front.begin(); new_alt != Local_front.end(); ++new_alt){
//			//Filter OPT_Solution set
//			if ( Update_Archive(*new_alt, OPT_Solution) )
//				Population.push_back(*new_alt);
//		}
//
//		//remove first element
//		Population.pop_front();
//		Local_front.clear();
//
//	}
//
//	cout<<"Number of iteration "<<nb_iteration<<endl;
//
//	filter_efficient_set();
//
//	write_solution(filename_instance+".sol");
//
//	list<string>().swap(Local_front);

	return OPT_Solution;
}










void MainKnapsack::Limit_number_accepting_N(vector< string > dominated_solutions, int upper_bound){

	random_shuffle( dominated_solutions.begin(), dominated_solutions.end() );
	int min_bound = ( upper_bound != -1 )? upper_bound: N;
	for(int i = 0; i < min_bound; i++){
		AlternativeKnapsack* alt = dic_Alternative[dominated_solutions[i]];
		Population.push_back( alt->get_id_alt() );
		OPT_Solution.push_back(alt);
	}
}




void MainKnapsack::Distribution_proba(vector< string > dominated_solutions){
	random_shuffle( dominated_solutions.begin(), dominated_solutions.end() );

	for(int i = 0; i < (int)dominated_solutions.size(); i++){

		if( rand()*1.0/RAND_MAX < P){
			AlternativeKnapsack* alt = dic_Alternative[dominated_solutions[i]];
			Population.push_back( alt->get_id_alt());
			OPT_Solution.push_back(alt);
		}
	}

}



//void MainKnapsack::Threshold_Accepting_BASIC(vector< string > dominated_solutions){
//
//}
//
//
//void MainKnapsack::Threshold_Accepting_AVG(vector< string > dominated_solutions){
//	vector<float> random_ws = Tools::generate_random_restricted_WS_aggregator(p_criteria, WS_Matrix);
//
//	for(int i = 0; i < dominated_solutions.size(); i++){
//
//		float aggreg_value = 0;
//
//		for(int j = 0; j < OPT_Solution.size(); j++){
//
//			aggreg_value += f(random_ws, )
//
//		}
//
//		if( aggreg_value*1.0 / OPT_Solution.size()  <= Ta){
//			AlternativeKnapsack* alt = dic_Alternative[dominated_solutions[i]];
//			Population.push_back( alt->get_id_alt());
//			OPT_Solution.push_back(alt);
//		}
//
//
//	}

//}



list< Alternative * > MainKnapsack::MOLS1(double starting_time_sec){

	AlternativeKnapsack* alt;
	vector< string > Local_front(0);
	vector< string > Dominated_alt(0);
	int nb_iteration=0;
	int step = 0, new_pop = 0;

	//First initialization
	for(list< string >::iterator p = Population.begin(); p != Population.end(); ++p){
		save_new_point(filename_instance+"_VARIABLE_MOLS1_"+to_string(step)+".expl", dic_Alternative[ *p ] );
		OPT_Solution.push_back( dic_Alternative[ *p ] );
		step++;
	}


	while( !Population.empty()  and ((clock() / CLOCKS_PER_SEC) - starting_time_sec <= TIMEOUT ) ){
		nb_iteration++;

		alt = dic_Alternative[ Population.front() ];
		Population.pop_front();

		if(nb_iteration > 1)
//			save_new_point(filename_instance+"_VARIABLE_"+to_string(step)+"_"+to_string(INFO)+".expl",alt);
			save_new_point(filename_instance+"_VARIABLE_MOLS1_"+to_string(step)+".expl",alt);

		set< string > current_neighbors = alt->get_neighborhood();

		for(set< string >::iterator id_neighbor = current_neighbors.begin(); id_neighbor != current_neighbors.end(); ++id_neighbor){

			AlternativeKnapsack * neighbor;
			if( dic_Alternative.find(*id_neighbor) != dic_Alternative.end())
				neighbor = dic_Alternative[*id_neighbor];
			else{
				dic_Alternative[*id_neighbor] = new AlternativeKnapsack(*id_neighbor, this, WS_matrix);
				neighbor = dic_Alternative[*id_neighbor];
			}
			//if neighbor is dominated add to Local_front
			if( alt->dominates_objective_space(neighbor) == 1 )
				Dominated_alt.push_back(*id_neighbor);
			else
				Local_front.push_back(*id_neighbor);

		}

		if( Population.empty() ){
//			random_shuffle( Local_front.begin(), Local_front.end() );

			for(vector< string >::iterator id_new_alt = Local_front.begin(); id_new_alt != Local_front.end(); ++id_new_alt){

				AlternativeKnapsack * new_alt = dic_Alternative[*id_new_alt];

				if( Update_Archive(new_alt, OPT_Solution) ){
					Population.push_back(*id_new_alt);
					new_pop++;
				}
				else{
					Dominated_alt.push_back(*id_new_alt);
				}
			}

			//GIVE CHANCE TO BAAAAD SOLUTIONS WHEN THERE STILL OPTIMAL ONES TO EXPLORE
			if( !Population.empty() ){
				int bef_add = (int)Population.size();
				Limit_number_accepting_N(Dominated_alt, -1);

//				Distribution_proba(Dominated_alt, -1);
//
//				Threshold_Accepting_AVG(Dominated_alt, -1);
//
//				Threshold_Accepting_BASIC(Dominated_alt, -1);


				new_pop += ((int)Population.size() - bef_add);

			}


			if( ((int)Population.size() - new_pop ) == 0){
				new_pop = 0;
				step++;
			}

			Local_front.clear();
			Dominated_alt.clear();
			step++;
		}
	}

	cout<<"Number of iteration "<<nb_iteration<<endl;

	filter_efficient_set_decision_space();

//	write_solution(filename_instance+"_UNSIZED"+".sol");
	write_solution(filename_instance+".sol");

	return OPT_Solution;

}

list< Alternative * > MainKnapsack::MOLS2(double starting_time_sec){

	AlternativeKnapsack* alt;
	vector< string > Local_front;
	vector< string > Dominated_alt;
	int nb_iteration=0;
	int step = 0, new_pop = 0;

	//First initialization
	for(list< string >::iterator p = Population.begin(); p != Population.end(); ++p){
		save_new_point(filename_instance+"_VARIABLE_"+to_string(step)+".expl", dic_Alternative[ *p ] );
		OPT_Solution.push_back( dic_Alternative[ *p ] );
		step++;
	}


	while( Population.size() > 0  and ((clock() / CLOCKS_PER_SEC) - starting_time_sec <= TIMEOUT ) ){
		nb_iteration++;

		alt = dic_Alternative[ Population.front() ];
		Population.pop_front();

		if(nb_iteration > 1)
			save_new_point(filename_instance+"_VARIABLE_"+to_string(step)+".expl",alt);

		set< string > current_neighbors = alt->get_neighborhood();

		for(set< string >::iterator id_neighbor = current_neighbors.begin(); id_neighbor != current_neighbors.end(); ++id_neighbor){

			AlternativeKnapsack * neighbor;
			if( dic_Alternative.find(*id_neighbor) != dic_Alternative.end())
				neighbor = dic_Alternative[*id_neighbor];
			else{
				dic_Alternative[*id_neighbor] = new AlternativeKnapsack(*id_neighbor, this, WS_matrix);
				neighbor = dic_Alternative[*id_neighbor];
			}
			//if neighbor is dominated add to Local_front
//			if( alt->dominates_objective_space(neighbor) == 1 )
//				Dominated_alt.push_back(*id_neighbor);
//			else
//				Local_front.push_back(*id_neighbor);


			//Prefiltrage
			if( alt->dominates_objective_space(neighbor) != 1 ){
				list< string > tmp_LF(Local_front.begin(),Local_front.end());
				Update_Archive(neighbor,tmp_LF);
				Local_front.clear();
				Local_front.resize(tmp_LF.size());
				copy(tmp_LF.begin(), tmp_LF.end(), Local_front.begin());

			}
			else
				Dominated_alt.push_back(*id_neighbor);
		}


		for(vector< string >::iterator id_new_alt = Local_front.begin(); id_new_alt != Local_front.end(); ++id_new_alt){

			AlternativeKnapsack * new_alt = dic_Alternative[*id_new_alt];

			if( Update_Archive(new_alt, OPT_Solution) ){
				Population.push_back(*id_new_alt);
				new_pop++;
			}
			else{
				Dominated_alt.push_back(*id_new_alt);
			}
		}

		if( ((int)Population.size() - new_pop ) == 0){
			new_pop = 0;
			step++;
		}

		//GIVE CHANCE TO BAAAAD SOLUTIONS WHEN THERE STILL OPTIMAL ONES TO EXPLORE
		if( !Population.empty() ){
			int bef_add = (int)Population.size();
			Limit_number_accepting_N(Dominated_alt, -1);

//				Distribution_proba(Dominated_alt, -1);
//
//				Threshold_Accepting_AVG(Dominated_alt, -1);
//
//				Threshold_Accepting_BASIC(Dominated_alt, -1);


			new_pop += ((int)Population.size() - bef_add);

		}

		Local_front.clear();
		Dominated_alt.clear();

	}

	cout<<"Number of iteration "<<nb_iteration<<endl;

	filter_efficient_set_decision_space();

//	write_solution(filename_instance+"_UNSIZED"+".sol");
	write_solution(filename_instance+".sol");

	return OPT_Solution;
}





list< Alternative * > MainKnapsack::MOLS1_Cst_PSize(double starting_time_sec, int UB_Population_size){

	AlternativeKnapsack* alt;
	vector< string > Local_front;
	vector< string > Dominated_alt;
	int nb_iteration=0;
	int step = 0, update = 0;

	//First initialization
	for(list< string >::iterator p = Population.begin(); p != Population.end(); ++p){
		save_new_point(filename_instance+"_"+to_string(UB_Population_size)+"_MOLS1_"+to_string(step)+".expl", dic_Alternative[ *p ]);
		OPT_Solution.push_back( dic_Alternative[ *p ] );
		step++;
	}


	while( !Population.empty()  and ((clock() / CLOCKS_PER_SEC) - starting_time_sec <= TIMEOUT ) ){

		nb_iteration++;

		alt = dic_Alternative[ Population.front() ];
		Population.pop_front();


		if(nb_iteration > 1)
//			save_new_point(filename_instance+"_"+to_string(UB_Population_size)+"_"+to_string(step)+".expl", alt );
			save_new_point(filename_instance+"_"+to_string(UB_Population_size)+"_MOLS1_"+to_string(step)+".expl",alt);

		update++;
		if( update >= UB_Population_size ){
			step++;
			update=0;
		}


		set< string > current_neighbors = alt->get_neighborhood();

		for(set< string >::iterator id_neighbor = current_neighbors.begin(); id_neighbor != current_neighbors.end(); ++id_neighbor){

			AlternativeKnapsack * neighbor;
			if( dic_Alternative.find(*id_neighbor) != dic_Alternative.end())
				neighbor = dic_Alternative[*id_neighbor];
			else{
				dic_Alternative[*id_neighbor] = new AlternativeKnapsack(*id_neighbor, this, WS_matrix);
				neighbor = dic_Alternative[*id_neighbor];
			}
			//if neighbor is dominated add to Dominated_alt
			if( alt->dominates_objective_space(neighbor) == 1 )
				Dominated_alt.push_back(*id_neighbor);
			else
				Local_front.push_back(*id_neighbor);

		}

		if( Population.empty() ){

			random_shuffle( Local_front.begin(), Local_front.end() );

			for(vector< string >::iterator id_new_alt = Local_front.begin(); id_new_alt != Local_front.end(); ++id_new_alt){

				AlternativeKnapsack * new_alt = dic_Alternative[*id_new_alt];

				if( (int)Population.size() < UB_Population_size ){

					if( Update_Archive(new_alt, OPT_Solution) ){
						Population.push_back(*id_new_alt);
					}
					else{
						Dominated_alt.push_back(*id_new_alt);
					}
				}
			}

			//GIVE CHANCE TO BAAAAD SOLUTIONS WHEN THERE STILL OPTIMAL ONES TO EXPLORE
			if( !Population.empty() ){
				Limit_number_accepting_N(Dominated_alt, (UB_Population_size - (int)Population.size()) );

//				Distribution_proba(Dominated_alt, (UB_Population_size - (int)Population.size()) );
//
//				Threshold_Accepting_AVG(Dominated_alt, (UB_Population_size - (int)Population.size()) );
//
//				Threshold_Accepting_BASIC(Dominated_alt, (UB_Population_size - (int)Population.size()) );

			}

			Local_front.clear();
			Dominated_alt.clear();
		}
	}

	cout<<"Number of iteration "<<nb_iteration<<endl;

	filter_efficient_set_decision_space();

	write_solution(filename_instance+".sol");
//	write_solution(filename_instance+"_"+to_string(UB_Population_size)+".sol");

	return OPT_Solution;
}


list< Alternative * > MainKnapsack::MOLS2_Cst_PSize(double starting_time_sec, int UB_Population_size){

	AlternativeKnapsack* alt;
	vector< string > Local_front;
	vector< string > Dominated_alt;
	int nb_iteration=0;
	int step = 0, update = 0;

	//First initialization
	for(list< string >::iterator p = Population.begin(); p != Population.end(); ++p){
//		save_new_point(filename_instance+"_"+to_string(UB_Population_size)+"_"+to_string(step)+".expl", dic_Alternative[ *p ]);
		save_new_point(filename_instance+"_"+to_string(UB_Population_size)+"_MOLS2_"+to_string(step)+".expl", dic_Alternative[ *p ]);
		OPT_Solution.push_back( dic_Alternative[ *p ] );
		step++;
	}


	while( Population.size() > 0  and ((clock() / CLOCKS_PER_SEC) - starting_time_sec <= TIMEOUT ) ){
		nb_iteration++;

		alt = dic_Alternative[ Population.front() ];
		Population.pop_front();

		if(nb_iteration > 1)
//			save_new_point(filename_instance+"_"+to_string(UB_Population_size)+"_"+to_string(step)+".expl", alt );
			save_new_point(filename_instance+"_"+to_string(UB_Population_size)+"_MOLS2_"+to_string(step)+".expl",alt);


		set< string > current_neighbors = alt->get_neighborhood();

		for(set< string >::iterator id_neighbor = current_neighbors.begin(); id_neighbor != current_neighbors.end(); ++id_neighbor){

			AlternativeKnapsack * neighbor;
			if( dic_Alternative.find(*id_neighbor) != dic_Alternative.end())
				neighbor = dic_Alternative[*id_neighbor];
			else{
				dic_Alternative[*id_neighbor] = new AlternativeKnapsack(*id_neighbor, this, WS_matrix);
				neighbor = dic_Alternative[*id_neighbor];
			}
			//if neighbor is dominated add to Local_front
//			if( alt->dominates_objective_space(neighbor) == 1 )
//				Dominated_alt.push_back(*id_neighbor);
//			else
//				Local_front.push_back(*id_neighbor);


			//Prefiltrage
			if( alt->dominates_objective_space(neighbor) != 1 ){
				list< string > tmp_LF(Local_front.begin(),Local_front.end());
				Update_Archive(neighbor,tmp_LF);
				Local_front.clear();
				Local_front.resize(tmp_LF.size());
				copy(tmp_LF.begin(), tmp_LF.end(), Local_front.begin());

			}
			else
				Dominated_alt.push_back(*id_neighbor);

		}


		for(vector< string >::iterator id_new_alt = Local_front.begin(); id_new_alt != Local_front.end(); ++id_new_alt){

			AlternativeKnapsack * new_alt = dic_Alternative[*id_new_alt];

			if( (int)Population.size() < UB_Population_size ){
				if( Update_Archive(new_alt, OPT_Solution) ){
					Population.push_back(*id_new_alt);
				}
				else{
					Dominated_alt.push_back(*id_new_alt);
				}
			}
		}

		update++;

		if( update == UB_Population_size ){
			step++;
			update=0;
		}

		Local_front.clear();
		Dominated_alt.clear();

	}

	cout<<"Number of iteration "<<nb_iteration<<endl;

	filter_efficient_set_decision_space();

//	write_solution(filename_instance+"_UNSIZED"+".sol");
	write_solution(filename_instance+".sol");

	return OPT_Solution;

}





void MainKnapsack::HYBRID_WS_PLS(double starting_time_sec,int steps){

	//WS
	MOLS(starting_time_sec,steps);

	//MUST CLEAN DICT ALTERNATIVE AND KEEP OPT SOLUTION
	Population.clear();
	for(list<Alternative* >::iterator alt = OPT_Solution.begin(); alt != OPT_Solution.end(); ++alt)
		Population.push_back((*alt)->get_id_alt());
	OPT_Solution.clear();

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

	//MUST CLEAN DICT ALTERNATIVE AND KEEP OPT SOLUTION
	Population.clear();
	for(list<Alternative* >::iterator alt = OPT_Solution.begin(); alt != OPT_Solution.end(); ++alt)
		Population.push_back((*alt)->get_id_alt());
	OPT_Solution.clear();

	//WS
	update_alternatives(Population);
	cout<<"Number of solution found with PLS : "<<OPT_Solution.size()<<endl;

	MOLS(starting_time_sec);
	cout<<"Number of solution found with WS : "<<OPT_Solution.size()<<endl;
}













/**
 * ************************************************* UPDATE PART *************************************************
 */




void MainKnapsack::update_alternatives(list< string > &set_Alt){

	for(list< string >::iterator id_alt = set_Alt.begin(); id_alt != set_Alt.end(); ++id_alt ){

		vector<float> ws_random = Tools::generate_random_restricted_WS_aggregator(p_criteria, WS_matrix);
		vector<vector<float> > ws_matrix(p_criteria,vector<float>());

		for(int i = 0; i < p_criteria; i++)
			ws_matrix[i].push_back(ws_random[i]);

		AlternativeKnapsack * alt = (dic_Alternative[*id_alt]);
		alt->set_local_WS_matrix(ws_matrix);
		alt->update_objective_vector();
	}

}





//																						TOSEEEEEEEEEEEE
bool MainKnapsack::Update_Archive(Alternative* p, list< Alternative* > &set_SOL){

	vector< Alternative* > to_remove;
	int dom_val;

	for(list< Alternative* >::iterator alt = set_SOL.begin(); alt != set_SOL.end(); ++alt){

		dom_val = (*alt)->dominates_objective_space(p);

		if( (dom_val == 1) or (*alt)->get_id_alt().compare(p->get_id_alt()) == 0)			// alt dominates p or already exists in set_SOL
			return false;

		else if( dom_val == -1 )   // p dominates alt
			to_remove.push_back(*alt);
	}

	for(vector< Alternative* >::iterator rm = to_remove.begin(); rm != to_remove.end(); ++rm)
		set_SOL.remove(*rm);

	set_SOL.push_back(p);

	vector<Alternative*>().swap(to_remove);
	return true;
}



bool MainKnapsack::Update_Archive(Alternative* p, list< string > &set_SOL){

	vector< string > to_remove;
	int dom_val;

	for(list< string >::iterator id_alt = set_SOL.begin(); id_alt != set_SOL.end(); ++id_alt){

		AlternativeKnapsack * alt = dic_Alternative[*id_alt];
		dom_val = alt->dominates_objective_space(p);

		if( (dom_val == 1) or alt->get_id_alt().compare(p->get_id_alt()) == 0)			// alt dominates p or already exists in set_SOL
			return false;

		else if( dom_val == -1 )   // p dominates alt
			to_remove.push_back(*id_alt);
	}

	for(vector< string >::iterator rm = to_remove.begin(); rm != to_remove.end(); ++rm)
		set_SOL.remove(*rm);

	set_SOL.push_back(p->get_id_alt());

	return true;
}




//#define Alpha_SA 0.9      // in 0.8 <= alpha <= 1


bool MainKnapsack::Update_Archive_Threshold_Accepting(Alternative* p, list< Alternative* > &set_SOL){

	bool is_dominated = false;
	vector< Alternative* > to_remove;
	int dom_val, nb_alt_composed_of = 0;

	for(list< Alternative* >::iterator alt = set_SOL.begin(); alt != set_SOL.end(); ++alt){

		dom_val = (*alt)->dominates_objective_space(p);

		if(dom_val == 1){			// alt dominates p             WAT ABOUT EXISTENCY
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







































