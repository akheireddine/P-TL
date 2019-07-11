
#include <set>



#include "MainKnapsack.h"


#define TIMEOUT 6000  //10min
#define N 20
#define P 0.005
#define DIVERSIFICATION 1
#define alpha 0.999

//#define __PRINT__



MainKnapsack::MainKnapsack( shared_ptr< Evaluator > evaluator, int population_size_init, string filename, bool generate_population){

	filename_population = filename;

	initializeInformation(evaluator);

	if( generate_population )
		GenerateInitialPopulation(population_size_init);
	else{
		for(int i = 0; i < population_size_init ; i++){
			set<int> individu = init_population.front();
			init_population.pop_front();
			string id_alt = Tools::decode_set_items(individu, n_items);
			Population.push_back(id_alt);
			init_population.push_back(individu);
		}
	}

}


/**
 * ************************************************* READING PART (INITIALIZATION)  *************************************************
 */


void MainKnapsack::initializeInformation(shared_ptr< Evaluator > evaluator){

	Items_information = evaluator->Items_information;

	WS_matrix = evaluator->get_WS_matrix();

	n_items = Items_information.size();

	n_objective = WS_matrix[0].size();

	p_criteria = WS_matrix.size();

	Backpack_capacity = evaluator->get_capacity();
}


void MainKnapsack::Generate_random_Population(shared_ptr< Evaluator > evaluator, int number_of_individu){

	init_population.clear();

	vector< tuple<float, vector< float> > > Items_information = evaluator->Items_information;

	int n_item =  Items_information.size();

	float Backpack_capacity = evaluator->get_capacity();



	/************************************* GENERATION *************************************/

	float bp = 0;
	set<int> individu;
	vector<int> all_items;

	for(int i = 0; i < n_item; i++)
		all_items.push_back(i);


	for (int i = 0; i < number_of_individu; i++){
		individu.clear();

	    std::mt19937 g(rand());
	    shuffle( all_items.begin(), all_items.end(), g);

		bp = 0;
		int cpt = 0;
		while(bp < Backpack_capacity and  cpt < (int)all_items.size()){

			int itm = all_items[cpt];
			cpt++;

			float weight_itm = get<0>(Items_information[itm]);

			if ( (weight_itm + bp) > Backpack_capacity )
				continue;

			individu.insert(itm);
			bp += weight_itm;
		}

//		for(set<int>::iterator it = individu.begin(); it != individu.end(); ++it)
//			cout<<*it<<"  ";
//		cout<<endl<<endl;
		init_population.push_back(individu);

	}
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
		dic_Alternative[ id_alt ] = make_shared< AlternativeKnapsack >( individu, this, WS_matrix);
		Population.push_back(id_alt);
	}

}



/**
 * ************************************************* SAVING PART (INFORMAITONS)  *************************************************
 */

void MainKnapsack::save_information(string filename, vector< float > criteria_vect, float time_cpu, int index){

//	const char * exist_dir = ("if [ ! -d "+filename+" ]; then mkdir -p "+filename+"; fi").c_str();
//	system(exist_dir);

	system(("if [ ! -d "+filename+" ]; then mkdir -p "+filename+"; fi").c_str());


	string extends_file = filename+"/Pop_"+to_string(k_replication)+".pop";

	ofstream fic(extends_file.c_str(),ios::app);

	fic<<Tools::print_vector(criteria_vect)<<" "<<time_cpu<<" "<<index<<endl;

	fic.close();
}

void MainKnapsack::save_information(string filename, vector< float > criteria_vect, float time_cpu, int index, int ub){

//	const char * exist_dir = ("if [ ! -d "+filename+" ]; then mkdir -p "+filename+"; fi").c_str();
//	system(exist_dir);

	system(("if [ ! -d "+filename+" ]; then mkdir -p "+filename+"; fi").c_str());


	string extends_file = filename+"/Pop_"+to_string(k_replication)+".pop";

	ofstream fic(extends_file.c_str(),ios::app);

	fic<<Tools::print_vector(criteria_vect)<<" "<<time_cpu<<" "<<index<<" "<<ub<<endl;

	fic.close();
}






/**
 * ************************************************* SOLVING PART *************************************************
 */





void MainKnapsack::Random_Selection(list< string > & dominated_solutions, list< string > & population, int upper_bound){

	set< string > to_rm;
	int min_bound = ( upper_bound != -1 )? upper_bound: dominated_solutions.size();
	min_bound = ( (int)dominated_solutions.size() < min_bound) ? (int)dominated_solutions.size() : min_bound;

	if( min_bound > (int)dominated_solutions.size()  ){
		Tools::shuffle_list(dominated_solutions);
	}

	int cpt = 0;
	for(list< string >::iterator it = dominated_solutions.begin(); it != dominated_solutions.end(); ++it){
		if( cpt < min_bound    ){// and   (dic_Alternative[ *it ].use_count() > 0)
			cpt++;
			string alt_name = *it;
			shared_ptr< AlternativeKnapsack > p_alt = dic_Alternative[ alt_name ];
			population.push_back( p_alt->get_id_alt() );
			to_rm.insert(alt_name);
		}
	}

	for(set< string >::iterator it = to_rm.begin(); to_rm.end() != it ; ++it){
		dominated_solutions.remove(*it);
	}
}




float f(vector<float> ws, vector<float> criteria){
	float res = 0;
	for(int i = 0; i < (int)ws.size(); i++)
		res += ws[i] * criteria[i];

	return res;
}


void MainKnapsack::Ordered_Selection(list< string > & dominated_solutions, list< string > & population, int upper_bound){

	map< float, string, less<float> > ratio_items;

	vector<float> random_ws = Tools::generate_random_restricted_WS_aggregator(p_criteria, WS_matrix);

	for(list< string >::iterator  i = dominated_solutions.begin(); i != dominated_solutions.end(); ++i){

		shared_ptr< AlternativeKnapsack > p_alt = dic_Alternative[*i];


//		//AVERAGE TA
//		float aggreg_value = 0;
//		for(list< shared_ptr< Alternative > >::iterator alt_opt = Archive.begin(); alt_opt != Archive.end(); ++alt_opt){
//			aggreg_value +=  (f(random_ws, (*alt_opt)->get_criteria_values()) - f(random_ws, p_alt->get_criteria_values() ));
//		}
//
//		float val_key = abs( aggreg_value*1.0 / (int)Archive.size() );



		//MIN TA
		float aggreg_value = -1;
		for(list< shared_ptr< Alternative > >::iterator alt_opt = Archive.begin(); alt_opt != Archive.end(); ++alt_opt){
			float val =  abs(f(random_ws, (*alt_opt)->get_criteria_values()) - f(random_ws, p_alt->get_criteria_values() ));
			if(aggreg_value == -1   or  (val < aggreg_value)  )
				aggreg_value =  val;
		}
		float val_key = aggreg_value;



//		cout<<"   key : "<<val_key<<endl;

		ratio_items[val_key] = p_alt->get_id_alt();
	}

	//LEARNING
//	float Ta_tmp = 0.0;
//	for(map< float, string >::iterator i = ratio_items.begin(); i != ratio_items.end(); ++i){
//		Ta_tmp += (*i).first;
//	}
//	Ta_tmp /= ratio_items.size();
//
//	if( (Ta_tmp * alpha < Ta)  or (Ta == -1)){
//		Ta = Ta_tmp * alpha ;
//	}
//	else
//		Ta *= alpha;


	int cpt= 0;
	int min_bound = (upper_bound != -1)? upper_bound : (int)dominated_solutions.size();
	min_bound = ( (int)dominated_solutions.size() < min_bound) ? (int)dominated_solutions.size() : min_bound;
	for(map< float, string, less<float> >::iterator i = ratio_items.begin(); i != ratio_items.end(); ++i){

		if( (cpt < min_bound)    ){//and   ((*i).first <= Ta)   ){
			shared_ptr< AlternativeKnapsack > p_alt = dic_Alternative[(*i).second];
			population.push_back( p_alt->get_id_alt());
			dominated_solutions.remove((*i).second);
			cpt++;
		}
	}


}










void MainKnapsack::MOLS(double starting_time_sec){

	int index = 0;
	shared_ptr< AlternativeKnapsack > alt;
	list< string > Local_front;
	int nb_iteration=0;
	int new_pop = 0;


	//First initialization NO FILTERING
	for(list< string >::iterator p = Population.begin(); p != Population.end(); ++p){
		dic_Alternative[ *p ] = make_shared< AlternativeKnapsack >( *p, this, WS_matrix);
		Archive.push_back( dic_Alternative[ *p ] );
	}

	index++;

	while( !Population.empty()  and ((clock() / CLOCKS_PER_SEC) - starting_time_sec <= TIMEOUT ) ){
		nb_iteration++;

		alt = dic_Alternative[ Population.front() ];
		Population.pop_front();


		save_information(filename_population+"/MOLS/"+INFO, alt->get_criteria_values(), ((clock()* 1./CLOCKS_PER_SEC) - starting_time_sec), index );

		set< string > current_neighbors  = alt->get_neighborhood();

		for(set< string >::iterator id_neighbor = current_neighbors.begin(); id_neighbor != current_neighbors.end(); ++id_neighbor){

			shared_ptr< AlternativeKnapsack > neighbor;

			if( dic_Alternative.find(*id_neighbor) != dic_Alternative.end() )
				continue;
			else
				dic_Alternative[*id_neighbor] = make_shared< AlternativeKnapsack >( *id_neighbor, this, alt->get_local_WS_matrix());


			neighbor = dic_Alternative[*id_neighbor];


			//Prefiltrage
			if( alt->dominates_objective_space(neighbor) != 1 ){
				Update_LocalArchive(neighbor,Local_front);
			}
			else{
				dic_Alternative[*id_neighbor].reset();
//				dic_Alternative.erase(*id_neighbor);
			}
			neighbor.reset();
		}

		alt.reset();


		//filter
		for(list< string >::iterator id_new_alt = Local_front.begin(); id_new_alt != Local_front.end(); ++id_new_alt){
			shared_ptr< AlternativeKnapsack > new_alt = dic_Alternative[*id_new_alt];
			if( Update_Archive(new_alt, Archive) ){
				Population.push_back(*id_new_alt);
				new_pop++;
			}
			new_alt.reset();
		}


		if( ((int)Population.size() - new_pop ) == 0){
			new_pop = 0;
			index++;
		}


		for(map<string, shared_ptr< AlternativeKnapsack > >::iterator it = dic_Alternative.begin(); it != dic_Alternative.end(); ++it){
			if( find(Population.begin(), Population.end(), (*it).first) == Population.end()  and (*it).second.use_count() == 1 )
				(*it).second.reset();
		}

		Local_front.clear();
		Tools::shuffle_list(Population);
	}

	cout<<"Number of iteration "<<nb_iteration<<endl;

	OPT_Solution.clear();
	for(list< shared_ptr< Alternative > >::iterator it = Archive.begin(); it != Archive.end(); ++it){
		OPT_Solution.push_back((*it)->get_criteria_values());
	}
}







void MainKnapsack::MOLS_Cst_PSize(double starting_time_sec, int UB_Population_size){


	shared_ptr< AlternativeKnapsack > alt;
	list< string > Local_front;
	list< string > next_Population;
	int nb_iteration = 0, index = 0;


	//First initialization
	for(list< string >::iterator p = Population.begin(); p != Population.end(); ++p){
		dic_Alternative[ *p ] = make_shared< AlternativeKnapsack >( *p, this, WS_matrix );
		Archive.push_back( dic_Alternative[ *p ] );
	}



	while( !Population.empty() and ((clock() / CLOCKS_PER_SEC) - starting_time_sec <= TIMEOUT ) ){
		nb_iteration++;

		alt = dic_Alternative[ Population.front() ];
		Population.pop_front();

		save_information(filename_population+"/MOLS_PSize/"+to_string(UB_Population_size)+"/"+INFO, alt->get_criteria_values(), ((clock()* 1./CLOCKS_PER_SEC) - starting_time_sec), index );

		set< string > current_neighbors = alt->get_neighborhood();

		for(set< string >::iterator id_neighbor = current_neighbors.begin(); id_neighbor != current_neighbors.end(); ++id_neighbor){

			shared_ptr< AlternativeKnapsack > neighbor;

			if( dic_Alternative.find(*id_neighbor) != dic_Alternative.end() )
				continue;
			else
				dic_Alternative[*id_neighbor] = make_shared< AlternativeKnapsack >( *id_neighbor, this, alt->get_local_WS_matrix());

			neighbor = dic_Alternative[*id_neighbor];

			//Prefiltrage
			if( alt->dominates_objective_space(neighbor) != 1 )
				Update_LocalArchive(neighbor,Local_front);
			else
				dic_Alternative[*id_neighbor].reset();
			neighbor.reset();
		}

		alt.reset();


		if( (int)Local_front.size() >= (UB_Population_size - (int)next_Population.size()) ){
			Tools::shuffle_list(Local_front);
		}

		for(list< string >::iterator id_new_alt = Local_front.begin(); id_new_alt != Local_front.end(); ++id_new_alt){

			shared_ptr< AlternativeKnapsack > new_alt = dic_Alternative[*id_new_alt];

			list< shared_ptr<Alternative> > local_Archive( Archive.begin(), Archive.end());

			if( Update_Archive(new_alt, local_Archive, next_Population) and  (int)next_Population.size() < UB_Population_size ){
				next_Population.push_back(*id_new_alt);
				Archive = local_Archive;
			}
			else
				dic_Alternative[*id_new_alt].reset();
			new_alt.reset();
		}


		if( Population.empty() ){


			// ADD NON-DOMINATED SOLUTIONS TO Population
			for(list< string >::iterator it = next_Population.begin(); it != next_Population.end(); ++it)
				if( dic_Alternative[*it].use_count() != 0)  //could be dominated by a solution in a different Local front list
					Population.push_back(*it);

			map<string, shared_ptr< AlternativeKnapsack > > tmp_dic_Alternative = dic_Alternative;
			for(map<string, shared_ptr< AlternativeKnapsack > >::iterator it = tmp_dic_Alternative.begin(); it != tmp_dic_Alternative.end(); ++it){
				if( find(Population.begin(), Population.end(), (*it).first) == Population.end()  and (*it).second.use_count() == 1 ){
					(*it).second.reset();
//					dic_Alternative.erase((*it).first);
				}
			}

			next_Population.clear();
			index++;

			Tools::shuffle_list(Population);
		}

		Local_front.clear();
	}

	cout<<"Number of iteration "<<nb_iteration<<endl;

	OPT_Solution.clear();
	for(list< shared_ptr< Alternative > >::iterator it = Archive.begin(); it != Archive.end(); ++it){
		OPT_Solution.push_back((*it)->get_criteria_values());
	}
}


void MainKnapsack::MOLS_Cst_PSize_RS(double starting_time_sec, int UB_Population_size){


	shared_ptr< AlternativeKnapsack > alt;
	list< string > Local_front;
	list< string > Dominated_alt;
	list< string > next_Population;
	int nb_iteration = 0, index = 0;

	int limit_no_improvment = 2;


	//First initialization
	for(list< string >::iterator p = Population.begin(); p != Population.end(); ++p){
		dic_Alternative[ *p ] = make_shared< AlternativeKnapsack >( *p, this, WS_matrix );
		Archive.push_back( dic_Alternative[ *p ] );
	}


	while( !Population.empty() and ((clock() / CLOCKS_PER_SEC) - starting_time_sec <= TIMEOUT ) ){
		nb_iteration++;

		alt = dic_Alternative[ Population.front() ];
		Population.pop_front();

		save_information(filename_population+"/MOLS_PSize_DIV/RS/"+to_string(UB_Population_size)+"/"+INFO, alt->get_criteria_values(), ((clock()* 1./CLOCKS_PER_SEC) - starting_time_sec), index );

		set< string > current_neighbors = alt->get_neighborhood();

		for(set< string >::iterator id_neighbor = current_neighbors.begin(); id_neighbor != current_neighbors.end(); ++id_neighbor){

			shared_ptr< AlternativeKnapsack > neighbor;

			if( dic_Alternative.find(*id_neighbor) != dic_Alternative.end() )
				continue;
			else
				dic_Alternative[*id_neighbor] = make_shared< AlternativeKnapsack >( *id_neighbor, this, alt->get_local_WS_matrix());

			neighbor = dic_Alternative[*id_neighbor];

			//Prefiltrage
			if( alt->dominates_objective_space(neighbor) != 1 ){
				Update_LocalArchive(neighbor,Local_front);
			}
			else
				Dominated_alt.push_back(*id_neighbor);

			neighbor.reset();
		}

		alt.reset();


		if( (int)Local_front.size() >= (UB_Population_size - (int)next_Population.size()) ){
			Tools::shuffle_list(Local_front);
		}


		for(list< string >::iterator id_new_alt = Local_front.begin(); id_new_alt != Local_front.end(); ++id_new_alt){

			shared_ptr< AlternativeKnapsack > new_alt = dic_Alternative[*id_new_alt];

			// a solution in LOcal_front could be non-dominated in the Archive but the next_Population size has exceeded UB_Population
			list< shared_ptr<Alternative> > local_Archive ( Archive.begin(), Archive.end());

			if( Update_Archive(new_alt, local_Archive, next_Population) and  (int)next_Population.size() < UB_Population_size ){
				next_Population.push_back(*id_new_alt);
				Archive = local_Archive;
			}
			else {
				Dominated_alt.push_back(*id_new_alt);
			}

			new_alt.reset();
		}



		if( Population.empty() ){

			// ADD NON-DOMINATED SOLUTIONS TO Population
			for(list< string >::iterator it = next_Population.begin(); it != next_Population.end(); ++it)
				if( dic_Alternative[*it].use_count() != 0)  //could be dominated by a solution in a different Local front list
					Population.push_back(*it);


			//ATTEMPT TO ADD DOMINATED SOLUTIONS TO Population
			if( Population.empty() )
				limit_no_improvment--;
			else
				limit_no_improvment =  2;

			int to_add = ( UB_Population_size - (int)Population.size() ) ;
			if( to_add > 0  and   ( (limit_no_improvment > 0) or !Population.empty() ) ){
//				Ordered_Selection(Dominated_alt, Population, to_add);
				Random_Selection(Dominated_alt,Population, to_add);
			}

			map<string, shared_ptr< AlternativeKnapsack > > tmp_dic_Alternative = dic_Alternative;
			for(map<string, shared_ptr< AlternativeKnapsack > >::iterator it = tmp_dic_Alternative.begin(); it != tmp_dic_Alternative.end(); ++it){
				if( find(Population.begin(), Population.end(), (*it).first) == Population.end()  and (*it).second.use_count() == 1 ){
					(*it).second.reset();
					dic_Alternative.erase((*it).first);
				}
			}

			Dominated_alt.clear();
			next_Population.clear();
			index++;
			Tools::shuffle_list(Population);
		}

		Local_front.clear();
	}

	cout<<"Number of iteration "<<nb_iteration<<endl;

	OPT_Solution.clear();
	for(list< shared_ptr< Alternative > >::iterator it = Archive.begin(); it != Archive.end(); ++it){
		OPT_Solution.push_back((*it)->get_criteria_values());
	}

}


void MainKnapsack::MOLS_Cst_PSize_OS(double starting_time_sec, int UB_Population_size){


	shared_ptr< AlternativeKnapsack > alt;
	list< string > Local_front;
	list< string > Dominated_alt;
	list< string > next_Population;
	int nb_iteration = 0, index = 0;

	int limit_no_improvment = 2;


	//First initialization
	for(list< string >::iterator p = Population.begin(); p != Population.end(); ++p){
		dic_Alternative[ *p ] = make_shared< AlternativeKnapsack >( *p, this, WS_matrix );
		Archive.push_back( dic_Alternative[ *p ] );
	}


	while( !Population.empty() and ((clock() / CLOCKS_PER_SEC) - starting_time_sec <= TIMEOUT ) ){
		nb_iteration++;

		alt = dic_Alternative[ Population.front() ];
		Population.pop_front();

		save_information(filename_population+"/MOLS_PSize_DIV/OS/"+to_string(UB_Population_size)+"/"+INFO, alt->get_criteria_values(), ((clock()* 1./CLOCKS_PER_SEC) - starting_time_sec), index );

		set< string > current_neighbors = alt->get_neighborhood();

		for(set< string >::iterator id_neighbor = current_neighbors.begin(); id_neighbor != current_neighbors.end(); ++id_neighbor){

			shared_ptr< AlternativeKnapsack > neighbor;

			if( dic_Alternative.find(*id_neighbor) != dic_Alternative.end() )
				continue;
			else
				dic_Alternative[*id_neighbor] = make_shared< AlternativeKnapsack >( *id_neighbor, this, alt->get_local_WS_matrix());

			neighbor = dic_Alternative[*id_neighbor];

			//Prefiltrage
			if( alt->dominates_objective_space(neighbor) != 1 ){
				Update_LocalArchive(neighbor,Local_front);
			}
			else
				Dominated_alt.push_back(*id_neighbor);

			neighbor.reset();
		}

		alt.reset();


		if( (int)Local_front.size() >= (UB_Population_size - (int)next_Population.size()) ){
			Tools::shuffle_list(Local_front);
		}


		for(list< string >::iterator id_new_alt = Local_front.begin(); id_new_alt != Local_front.end(); ++id_new_alt){

			shared_ptr< AlternativeKnapsack > new_alt = dic_Alternative[*id_new_alt];

			// a solution in LOcal_front could be non-dominated in the Archive but the next_Population size has exceeded UB_Population
			list< shared_ptr<Alternative> > local_Archive ( Archive.begin(), Archive.end());

			if( Update_Archive(new_alt, local_Archive, next_Population) and  (int)next_Population.size() < UB_Population_size ){
				next_Population.push_back(*id_new_alt);
				Archive = local_Archive;
			}
			else {
				Dominated_alt.push_back(*id_new_alt);
			}

			new_alt.reset();
		}



		if( Population.empty() ){

			// ADD NON-DOMINATED SOLUTIONS TO Population
			for(list< string >::iterator it = next_Population.begin(); it != next_Population.end(); ++it)
				if( dic_Alternative[*it].use_count() != 0)  //could be dominated by a solution in a different Local front list
					Population.push_back(*it);


			//ATTEMPT TO ADD DOMINATED SOLUTIONS TO Population
			if( Population.empty() )
				limit_no_improvment--;
			else
				limit_no_improvment =  2;

			int to_add = ( UB_Population_size - (int)Population.size() ) ;
			if( to_add > 0  and   ( (limit_no_improvment > 0) or !Population.empty() ) ){
				Ordered_Selection(Dominated_alt, Population, to_add);
			}

			map<string, shared_ptr< AlternativeKnapsack > > tmp_dic_Alternative = dic_Alternative;
			for(map<string, shared_ptr< AlternativeKnapsack > >::iterator it = tmp_dic_Alternative.begin(); it != tmp_dic_Alternative.end(); ++it){
				if( find(Population.begin(), Population.end(), (*it).first) == Population.end()  and (*it).second.use_count() == 1 ){
					(*it).second.reset();
					dic_Alternative.erase((*it).first);
				}
			}


			Dominated_alt.clear();
			next_Population.clear();
			index++;
			Tools::shuffle_list(Population);
		}

		Local_front.clear();
	}

	cout<<"Number of iteration "<<nb_iteration<<endl;

	OPT_Solution.clear();
	for(list< shared_ptr< Alternative > >::iterator it = Archive.begin(); it != Archive.end(); ++it){
		OPT_Solution.push_back((*it)->get_criteria_values());
	}

}










/**
 * ************************************************* OTHER METHODS *************************************************
 */



void MainKnapsack::MOLS(double starting_time_sec,int ITER){

	int index = 0;
	shared_ptr< AlternativeKnapsack > alt;
	list< string > Local_front;
	int nb_iteration=0;
	int new_pop = 0;


	//First initialization NO FILTERING
	for(list< string >::iterator p = Population.begin(); p != Population.end(); ++p){
		dic_Alternative[ *p ] = make_shared< AlternativeKnapsack >( *p, this, WS_matrix);
		Archive.push_back( dic_Alternative[ *p ] );
	}

	index++;

	while( !Population.empty()  and ((clock() / CLOCKS_PER_SEC) - starting_time_sec <= TIMEOUT )  and  ( nb_iteration < ITER ) ){
		nb_iteration++;

		alt = dic_Alternative[ Population.front() ];
		Population.pop_front();




		set< string > current_neighbors  = alt->get_neighborhood();

//		if( common_neighbors.find( alt->get_id_alt( ) ) != common_neighbors.end() )
//			current_neighbors = common_neighbors[alt->get_id_alt()];
//
//		else{
//			current_neighbors = alt->get_neighborhood();
//			common_neighbors[alt->get_id_alt()] = current_neighbors;
//		}

		for(set< string >::iterator id_neighbor = current_neighbors.begin(); id_neighbor != current_neighbors.end(); ++id_neighbor){

			shared_ptr< AlternativeKnapsack > neighbor;

			if( dic_Alternative.find(*id_neighbor) != dic_Alternative.end() )
				continue;

			else
				dic_Alternative[*id_neighbor] = make_shared< AlternativeKnapsack >( *id_neighbor, this, alt->get_local_WS_matrix());


			neighbor = dic_Alternative[*id_neighbor];


			//Prefiltrage
			if( alt->dominates_objective_space(neighbor) != 1 ){
				Update_LocalArchive(neighbor,Local_front);
			}
			else{
				dic_Alternative[*id_neighbor].reset();
//				dic_Alternative.erase(*id_neighbor);
			}
			neighbor.reset();
		}

		alt.reset();


		for(list< string >::iterator id_new_alt = Local_front.begin(); id_new_alt != Local_front.end(); ++id_new_alt){

			shared_ptr< AlternativeKnapsack > new_alt = dic_Alternative[*id_new_alt];

			if( Update_Archive(new_alt, Archive) ){
				Population.push_back(*id_new_alt);
				new_pop++;
			}

		}

		if( ((int)Population.size() - new_pop ) == 0){
			new_pop = 0;
			index++;
		}





		for(map<string, shared_ptr< AlternativeKnapsack > >::iterator it = dic_Alternative.begin(); it != dic_Alternative.end(); ++it){
			if( find(Population.begin(), Population.end(), (*it).first) == Population.end()  and (*it).second.use_count() == 1 )
				(*it).second.reset();
		}

		Local_front.clear();
	}

	cout<<"Number of iteration "<<nb_iteration<<endl;

	OPT_Solution.clear();
	for(list< shared_ptr< Alternative > >::iterator it = Archive.begin(); it != Archive.end(); ++it){
		OPT_Solution.push_back((*it)->get_criteria_values());
	}

}

void MainKnapsack::HYBRID_WS_PLS(double starting_time_sec,int ITER){

	//WS
	MOLS(starting_time_sec,ITER);

	//MUST CLEAN CURRENT POPULATION AND REPLACE IT WITH OPT SOLUTION
//	Population.clear();
	for(list< shared_ptr<Alternative> >::iterator alt = Archive.begin(); alt != Archive.end(); ++alt)
		Population.push_back((*alt)->get_id_alt());
	Archive.clear();

	change_to_pareto_selection();

	update_alternatives(Population,true);

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


void MainKnapsack::HYBRID_PLS_WS(double starting_time_sec, int ITER){

	//PLS
	MOLS(starting_time_sec,ITER);

	//MUST CLEAN DICT ALTERNATIVE AND KEEP OPT SOLUTION
//	Population.clear();
	for(list< shared_ptr<Alternative> >::iterator alt = Archive.begin(); alt != Archive.end(); ++alt)
		Population.push_back((*alt)->get_id_alt());

	//WS
	update_alternatives(Population,false);

	cout<<"Number of solution found with PLS : "<<Archive.size()<<endl;
	Archive.clear();

	MOLS(starting_time_sec);
	cout<<"Number of solution found with WS : "<<Archive.size()<<endl;
}


void MainKnapsack::SWITCH_PLS_WS(double starting_time_sec, int ITER_PLS, int ITER_WS){


	int index = 0;

	for(list< string >::iterator p = Population.begin(); p != Population.end(); ++p){
		dic_Alternative[ *p ] = make_shared< AlternativeKnapsack >( *p, this, WS_matrix);
		Archive.push_back( dic_Alternative[ *p ] );
	}

	while( !Population.empty()  and ((clock() / CLOCKS_PER_SEC) - starting_time_sec <= TIMEOUT ) ){


		//PLS
		update_alternatives(Population,true);

		MOLS(starting_time_sec,ITER_PLS);

		cout<<"PLS : "<<Archive.size()<<endl;

		index++;

//		MUST CLEAN DICT ALTERNATIVE AND KEEP OPT SOLUTION
		for(list< shared_ptr<Alternative> >::iterator alt = Archive.begin(); alt != Archive.end(); ++alt)
			if( find(Population.begin(), Population.end() , (*alt)->get_id_alt()) == Population.end())
				Population.push_back((*alt)->get_id_alt());

		Archive.clear();

		//WS
		update_alternatives(Population,false);
		MOLS(starting_time_sec,Population.size() + ITER_WS);

		if(ITER_WS > 2)
			ITER_WS -= 1;
		cout<<"WS : "<<Archive.size()<<endl;

	}

}




void MainKnapsack::update_extrem_point(vector< float > extrem1, float & epsi, vector< float > point_eval, vector< float > & extrem2){

	float val = Tools::euclidian_distance(extrem1,point_eval);
	if( epsi < val )
		epsi = val;
	extrem2 = point_eval;
}


#define epsilon 10

void MainKnapsack::MOLS_SWITCH_OBJECTIVE(double starting_time_sec, vector< int > UB_Population_list, vector< string > Informations){

	shared_ptr< AlternativeKnapsack > alt;
	list< string > Local_front;
	list< string > Dominated_alt;
	list< string > next_Population;
	int nb_iteration = 0, index = 0;
	int cpt_info = 0;

	int surcharge = 3, souscharge = 5;
	vector< float > extrem_point(n_objective,0.), snd_extrem_point(n_objective,0.);
	float curr_epsilon = 0.;

	int UB_Population_size = UB_Population_list[0];
	int ub_pop = 0;

	int limit_no_improvment = 2;

	//First initialization
	for(list< string >::iterator p = Population.begin(); p != Population.end(); ++p){
		dic_Alternative[ *p ] = make_shared< AlternativeKnapsack >( *p, this, WS_matrix );
		Archive.push_back( dic_Alternative[ *p ] );
		update_extrem_point(extrem_point, curr_epsilon, dic_Alternative[ *p ]->get_objective_values(), snd_extrem_point) ;
	}


	extrem_point = snd_extrem_point;
	curr_epsilon = 0.;


	while( !Population.empty() and ((clock() / CLOCKS_PER_SEC) - starting_time_sec <= TIMEOUT ) ){
		nb_iteration++;

		alt = dic_Alternative[ Population.front() ];
		Population.pop_front();

		update_extrem_point(extrem_point, curr_epsilon, alt->get_objective_values(), snd_extrem_point) ;

//		save_information(filename_population+"/MOLS_SWITCH_OBJECTIVE/"+to_string(UB_Population_size), alt->get_criteria_values(), ((clock()* 1./CLOCKS_PER_SEC) - starting_time_sec), index );
		save_information(filename_population+"/"+INFO, alt->get_criteria_values(), ((clock()* 1./CLOCKS_PER_SEC) - starting_time_sec), index, UB_Population_size );

		set< string > current_neighbors = alt->get_neighborhood();

		for(set< string >::iterator id_neighbor = current_neighbors.begin(); id_neighbor != current_neighbors.end(); ++id_neighbor){

			shared_ptr< AlternativeKnapsack > neighbor;

			if( dic_Alternative.find(*id_neighbor) != dic_Alternative.end() )
				continue;
			else
				dic_Alternative[*id_neighbor] = make_shared< AlternativeKnapsack >( *id_neighbor, this, alt->get_local_WS_matrix());

			neighbor = dic_Alternative[*id_neighbor];

			//Prefiltrage
			if( alt->dominates_objective_space(neighbor) != 1 ){
				Update_LocalArchive(neighbor,Local_front);
			}
			else{
				dic_Alternative[*id_neighbor].reset();
//				Dominated_alt.push_back(*id_neighbor);
			}
			neighbor.reset();
		}

		alt.reset();


		if( (int)Local_front.size() >= (UB_Population_size - (int)next_Population.size()) ){
			Tools::shuffle_list(Local_front);
		}


		for(list< string >::iterator id_new_alt = Local_front.begin(); id_new_alt != Local_front.end(); ++id_new_alt){

			shared_ptr< AlternativeKnapsack > new_alt = dic_Alternative[*id_new_alt];

			// a solution in LOcal_front could be non-dominated in the Archive but the next_Population size has exceeded UB_Population
			list< shared_ptr<Alternative> > local_Archive ( Archive.begin(), Archive.end());

			if( Update_Archive(new_alt, local_Archive, next_Population) and  (int)next_Population.size() < UB_Population_size ){
				next_Population.push_back(*id_new_alt);
				Archive = local_Archive;
			}
			else {
//				Dominated_alt.push_back(*id_new_alt);
				dic_Alternative[*id_new_alt].reset();

			}

			new_alt.reset();
		}



		if( Population.empty() ){

			// ADD NON-DOMINATED SOLUTIONS TO Population
			for(list< string >::iterator it = next_Population.begin(); it != next_Population.end(); ++it)
				if( dic_Alternative[*it].use_count() != 0)  //could be dominated by a solution in a different Local front list
					Population.push_back(*it);


//			ATTEMPT TO ADD DOMINATED SOLUTIONS TO Population
			if( Population.empty() )
				limit_no_improvment--;
			else
				limit_no_improvment =  2;

			int to_add = ( UB_Population_size - (int)Population.size() ) ;
			if( to_add > 0  and   ( (limit_no_improvment > 0) or !Population.empty() ) ){
				Ordered_Selection(Dominated_alt, Population, to_add);
			}

			map<string, shared_ptr< AlternativeKnapsack > > tmp_dic_Alternative = dic_Alternative;
			for(map<string, shared_ptr< AlternativeKnapsack > >::iterator it = tmp_dic_Alternative.begin(); it != tmp_dic_Alternative.end(); ++it){
				if( find(Population.begin(), Population.end(), (*it).first) == Population.end()  and (*it).second.use_count() == 1 ){
					(*it).second.reset();
					dic_Alternative.erase((*it).first);
				}
			}

/*
 *  	********************			UPDATE INFORMATION
 */
//			surcharge = ((int)Population.size() < UB_Population_size) ? surcharge : (surcharge - 1);
//			souscharge = ((int)Population.size() < UB_Population_size) ? (souscharge - 1) : souscharge;
//
//			cout<<"surchange : "<<surcharge<< "  souscharge :"<<souscharge<<endl;
//			cout<<"  POP/UB : "<<Population.size()<<"/"<<UB_Population_size<<endl;
//			if( (souscharge == 0) and cpt_info > 0 ){
//				cpt_info--;
//				cout<<"1 : Iteration_"<<cpt_info<<endl;
//				set_WS_matrix(Tools::readMatrix(Informations[cpt_info]));
//				update_WS_matrix_Population();
//				souscharge = 5;
//			}
//
//			if( (surcharge == 0) and cpt_info < (int)Informations.size() - 1 ){ //curr_epsilon < epsilon  and cpt_info > 0){
//				cpt_info++;
//				cout<<"2 : Iteration_"<<cpt_info<<endl;
//				set_WS_matrix(Tools::readMatrix(Informations[cpt_info]));
//				update_WS_matrix_Population();
//				surcharge = 3;
//			} else if ( surcharge == 0 and cpt_info >= (int)Informations.size() - 1 )
//				surcharge = 3;
//			else if (souscharge == 0 and cpt_info == 0)
//				souscharge = 5;
//			extrem_point = snd_extrem_point;
//			curr_epsilon = 0.;
/*
 *  	********************			UPDATE INFORMATION
 */


/*
 *  	*****************************************			UPDATE UB_SIZE
 */
//			surcharge = ((int)Population.size() < UB_Population_size) ? surcharge : (surcharge - 1);
//			if( (surcharge == 0) and ub_pop < (int)UB_Population_list.size() - 1 ){
//				ub_pop++;
//				UB_Population_size = UB_Population_list[ub_pop];
//				cout<<"Size : "<<UB_Population_list[ub_pop]<<endl;
//				surcharge = 3;
//			}

			surcharge = ((int)Population.size() > UB_Population_size) ? surcharge : (surcharge - 1);
			if( (surcharge == 0) and ub_pop < (int)UB_Population_list.size() - 1 ){
				ub_pop++;
				UB_Population_size = UB_Population_list[ub_pop];
				cout<<"Size : "<<UB_Population_list[ub_pop]<<endl;
				surcharge = 3;
			}
/*
 *  	*****************************************			UPDATE UB_SIZE
 */


			Dominated_alt.clear();
			next_Population.clear();
			index++;
			Tools::shuffle_list(Population);
		}

		Local_front.clear();
	}

	cout<<"Number of iteration "<<nb_iteration<<endl;

	OPT_Solution.clear();
	for(list< shared_ptr< Alternative > >::iterator it = Archive.begin(); it != Archive.end(); ++it){
		OPT_Solution.push_back((*it)->get_criteria_values());
	}
}



void MainKnapsack::MOLS_local_Archive(double starting_time_sec){

	shared_ptr< AlternativeKnapsack > alt;
	list< string > Local_front;
	list< string > Dominated_alt;
	int nb_iteration=0;
	int new_pop = 0, index = 0;

	//First initialization NO FILTERING

	for(list< string >::iterator p = Population.begin(); p != Population.end(); ++p){
//		dic_Alternative[ *p ] = new AlternativeKnapsack( *p , this, WS_matrix);;
		(dic_Alternative[ *p ])->set_local_Archive(Archive);

	}
//	index++;


	while( !Population.empty()  and ((clock() / CLOCKS_PER_SEC) - starting_time_sec <= TIMEOUT ) ){

		nb_iteration++;

		alt = dic_Alternative[ Population.front() ];
		Population.pop_front();


		set< string > current_neighbors = alt->get_neighborhood();

		for(set< string >::iterator id_neighbor = current_neighbors.begin(); id_neighbor != current_neighbors.end(); ++id_neighbor){

			shared_ptr< AlternativeKnapsack > neighbor;

			//already explorated
			if( dic_Alternative.find(*id_neighbor) != dic_Alternative.end() )
				continue;

			else{
				dic_Alternative[*id_neighbor] = make_shared< AlternativeKnapsack >( *id_neighbor, this, alt->get_local_WS_matrix(), alt->get_local_Archive());
				neighbor = dic_Alternative[*id_neighbor];
			}

			//Prefiltrage
			if( alt->dominates_objective_space(neighbor) != 1 ){
				Update_LocalArchive(neighbor,Local_front);
			}
			else
				Dominated_alt.push_back(*id_neighbor);
		}


		for(list< string >::iterator id_new_alt = Local_front.begin(); id_new_alt != Local_front.end(); ++id_new_alt){

			shared_ptr< AlternativeKnapsack > new_alt = dic_Alternative[*id_new_alt];

			list< shared_ptr< Alternative > > archive_tmp = new_alt->get_local_Archive();
			//RECREER LES LOCAL ALT ARCHIVES !!!!!!!!!!!!!!!
			if( Update_Archive(new_alt, archive_tmp ) ){
				Population.push_back(*id_new_alt);
				new_alt->set_local_Archive(archive_tmp);
				new_pop++;
			}
			else{
				Dominated_alt.push_back(*id_new_alt);
			}
		}

		if( ((int)Population.size() - new_pop ) == 0){
			new_pop = 0;
			index++;
		}

		//GIVE CHANCE TO BAAAAD SOLUTIONS WHEN THERE STILL OPTIMAL ONES TO EXPLORE
//		if( !Population.empty() and  ((rand()*1.0/RAND_MAX) < (DIVERSIFICATION ))  ){
//			int bef_add = (int)Population.size();
////			Limit_number_accepting_N(Dominated_alt, -1);
//
////			Distribution_proba(Dominated_alt, -1);
////
//			Threshold_Accepting_AVG(Dominated_alt,Population, -1);
////
////				Threshold_Accepting_BASIC(Dominated_alt, -1);
//
//
//			new_pop += ((int)Population.size() - bef_add);
//
//		}


		for(list< string >::iterator it = Dominated_alt.begin(); it != Dominated_alt.end(); ++it){
			dic_Alternative[(*it)].reset();
		}

		Local_front.clear();
		Dominated_alt.clear();

	}

	cout<<"Number of iteration "<<nb_iteration<<endl;

	for(map<string, shared_ptr< AlternativeKnapsack > >::iterator it = dic_Alternative.begin(); it != dic_Alternative.end(); ++it){

		if(dic_Alternative[(*it).first].use_count() > 1 )
			Archive.push_back((*it).second);

	}

	OPT_Solution.clear();
	for(list< shared_ptr< Alternative > >::iterator it = Archive.begin(); it != Archive.end(); ++it){
		OPT_Solution.push_back((*it)->get_criteria_values());
	}

}








/**
 * ************************************************* UPDATE PART *************************************************
 */


void MainKnapsack::update_WS_matrix_Population(){
	//Pareto uncertainty
	for(list< string >::iterator id_alt = Population.begin(); id_alt != Population.end(); ++id_alt ){
		shared_ptr< AlternativeKnapsack > alt = (dic_Alternative[*id_alt]);
		alt->set_local_WS_matrix(WS_matrix);
		alt->update_objective_vector();
	}
}



void MainKnapsack::update_alternatives(list< string > &set_Alt, bool Pareto){
	//Pareto uncertainty
	if(Pareto){
		for(list< string >::iterator id_alt = set_Alt.begin(); id_alt != set_Alt.end(); ++id_alt ){
			shared_ptr< AlternativeKnapsack > alt = (dic_Alternative[*id_alt]);
			alt->set_local_WS_matrix(WS_matrix);
			alt->update_objective_vector();

		}
	}


	//one WS
	else {
		for(list< string >::iterator id_alt = set_Alt.begin(); id_alt != set_Alt.end(); ++id_alt ){

			shared_ptr< AlternativeKnapsack > alt = (dic_Alternative[*id_alt]);

			vector<float> ws_random = Tools::generate_random_restricted_WS_aggregator(p_criteria, WS_matrix); //Tools::readWS_DM("weighted_DM_preferences.ks"); //
			vector<vector<float> > ws_matrix(p_criteria,vector<float>());

			for(int i = 0; i < p_criteria; i++)
				ws_matrix[i].push_back(ws_random[i]);

			alt->set_local_WS_matrix(ws_matrix);
			alt->update_objective_vector();

		}
	}
}



bool MainKnapsack::Update_Archive(shared_ptr< Alternative > p, list< shared_ptr< Alternative > > &set_SOL){

	vector< shared_ptr< Alternative > > to_remove;
	int dom_val;


	for(list< shared_ptr< Alternative > >::iterator alt = set_SOL.begin(); alt != set_SOL.end(); ++alt){

		dom_val = (*alt)->dominates_objective_space(p);


		if( (dom_val == 1) or (*alt)->get_id_alt().compare(p->get_id_alt()) == 0)			// alt dominates p or already exists in set_SOL
			return false;

		else if( dom_val == -1 )   // p dominates alt
			to_remove.push_back(*alt);
	}

	for(vector< shared_ptr< Alternative > >::iterator rm = to_remove.begin(); rm != to_remove.end(); ++rm){
		//could be a solution in the Population and we want to explore it anyway
		set_SOL.remove(*rm);
		(*rm).reset();
	}

	set_SOL.push_back(p);

	return true;
}



bool MainKnapsack::Update_LocalArchive(shared_ptr< Alternative > p, list< string > &set_SOL){

	vector< string > to_remove;
	int dom_val;


	for(list< string >::iterator id_alt = set_SOL.begin(); id_alt != set_SOL.end(); ++id_alt){

		shared_ptr< AlternativeKnapsack > alt = dic_Alternative[*id_alt];
		dom_val = alt->dominates_objective_space(p);

		if( (dom_val == 1) or alt->get_id_alt().compare(p->get_id_alt()) == 0){			// alt dominates p or already exists in set_SOL
			return false;
		}

		else if( dom_val == -1 ){   // p dominates alt
			to_remove.push_back(*id_alt);
		}
	}



	for(vector< string >::iterator rm = to_remove.begin(); rm != to_remove.end(); ++rm){
		set_SOL.remove(*rm);
	}
	set_SOL.push_back(p->get_id_alt());

	return true;
}



bool MainKnapsack::Update_Archive(shared_ptr< Alternative > p, list< shared_ptr< Alternative > > &set_SOL, list<string> &population){

	vector< shared_ptr< Alternative > > to_remove;
	int dom_val;


	for(list< shared_ptr< Alternative > >::iterator alt = set_SOL.begin(); alt != set_SOL.end(); ++alt){

		dom_val = (*alt)->dominates_objective_space(p);


		if( (dom_val == 1) or (*alt)->get_id_alt().compare(p->get_id_alt()) == 0)			// alt dominates p or already exists in set_SOL
			return false;

		else if( dom_val == -1 )   // p dominates alt
			to_remove.push_back(*alt);
	}

	for(vector< shared_ptr< Alternative > >::iterator rm = to_remove.begin(); rm != to_remove.end(); ++rm){
		//could be a solution in the Population and we want to explore it anyway
		population.remove((*rm)->get_id_alt());
		set_SOL.remove(*rm);
		(*rm).reset();
	}

	set_SOL.push_back(p);

	return true;
}






























//void MainKnapsack::MOLS_Cst_PSize_FAIR(double starting_time_sec, int UB_Population_size){
//
//
//	shared_ptr< AlternativeKnapsack > alt;
//	list< string > Local_front;
//	list< string > Dominated_alt;
//	list< string > next_Population;
//	vector< list< string > > explored_alt;
//
//	int nb_iteration = 0, step = 0;
//
//	int limit_no_improvment = 2;
//
//
//	//First initialization
//	for(list< string >::iterator p = Population.begin(); p != Population.end(); ++p){
//		dic_Alternative[ *p ] = make_shared< AlternativeKnapsack >( *p, this, WS_matrix );
//		Archive.push_back( dic_Alternative[ *p ] );
//	}
//
//
//	while( !Population.empty()  and ((clock() / CLOCKS_PER_SEC) - starting_time_sec <= TIMEOUT ) ){
//		nb_iteration++;
//
//
//		alt = dic_Alternative[ Population.front() ];
//		Population.pop_front();
//
//
//		set< string > current_neighbors = alt->get_neighborhood();
//
//
//		for(set< string >::iterator id_neighbor = current_neighbors.begin(); id_neighbor != current_neighbors.end(); ++id_neighbor){
//
//			shared_ptr< AlternativeKnapsack > neighbor;
//
//			if( dic_Alternative.find(*id_neighbor) != dic_Alternative.end() )
//				continue;
//			else
//				dic_Alternative[*id_neighbor] = make_shared< AlternativeKnapsack >( *id_neighbor, this, alt->get_local_WS_matrix());
//
//
//			neighbor = dic_Alternative[*id_neighbor];
//
//
//			//Prefiltrage
//			if( alt->dominates_objective_space(neighbor) != 1 ){
//				Update_LocalArchive(neighbor,Local_front);
//			}
//			else{
//				Dominated_alt.push_back(*id_neighbor);
//			}
//			neighbor.reset();
//		}
//
//		alt.reset();
//
//		if( (int)Local_front.size() >= (UB_Population_size - (int)next_Population.size()) ){
//			Tools::shuffle_list(Local_front);
//		}
//
//
//		for(list< string >::iterator id_new_alt = Local_front.begin(); id_new_alt != Local_front.end(); ++id_new_alt){
//
//			shared_ptr< AlternativeKnapsack > new_alt = dic_Alternative[*id_new_alt];
//
//			// a solution in LOcal_front could be non-dominated in the Archive but the next_Population size has exceeded UB_Population
//			list< shared_ptr<Alternative> > local_Archive ( Archive.begin(), Archive.end());
//
//			if( Update_Archive(new_alt, local_Archive, next_Population) and  (int)next_Population.size() < UB_Population_size ){
//				next_Population.push_back(*id_new_alt);
//				Archive = local_Archive;
//			}
//			else {
//				Dominated_alt.push_back(*id_new_alt);
//			}
//			new_alt.reset();
//		}
//
//
//
//		list< string > neighbors_alt;
//
//		//ATTEMPT TO ADD DOMINATED SOLUTIONS TO Population
//
//		int to_add = ( UB_Population_size - (int)next_Population.size() ) ;
//		if( to_add > 0  and   ( (limit_no_improvment > 0) or !next_Population.empty() ) ){
////			Ordered_Selection(Dominated_alt, neighbors_alt, to_add);
//			Random_Selection(Dominated_alt, neighbors_alt, to_add);
//		}
//
//		explored_alt.push_back(neighbors_alt);
//
//
//		if( Population.empty() ){
//
//			if( next_Population.empty() )
//				limit_no_improvment--;
//			else
//				limit_no_improvment =  2;
//
//
//
//
//			if( (limit_no_improvment == 0) and next_Population.empty() )
//				continue;
//
//
//			int i = 0, no_improvement = 0;
//
//			while( (int)next_Population.size() < UB_Population_size and ( no_improvement < (int)explored_alt.size() ) ){
//
//				if( !explored_alt[i].empty() ){
//					next_Population.push_back( explored_alt[i].front() );
//					explored_alt[i].pop_front();
//					no_improvement = 0;
//				}
//				else
//					no_improvement++;
//
//				i = (i+1) %(explored_alt.size());
//			}
//
//			Tools::shuffle_list(next_Population);
//
//
//			for(list< string >::iterator it = next_Population.begin(); it != next_Population.end(); ++it)
//				if( dic_Alternative[*it].use_count() != 0)  //could be dominated by a solution in a different Local front list
//					Population.push_back(*it);
//
//
//
////			map<string, shared_ptr< AlternativeKnapsack > >::iterator tmp_dic_alt = dic_Alternative;
//			for(map<string, shared_ptr< AlternativeKnapsack > >::iterator it = dic_Alternative.begin(); it != dic_Alternative.end(); ++it){
//				if( find(Population.begin(), Population.end(), (*it).first) == Population.end()  and (*it).second.use_count() == 1 ){
//					(*it).second.reset();
//					dic_Alternative.erase((*it).first);
//				}
//			}
//
//
//			next_Population.clear();
//			next_Population.resize(0);
//			explored_alt.clear();
//			explored_alt.shrink_to_fit();
//			step++;
//		}
//
//		Dominated_alt.clear();
//		Dominated_alt.resize(0);
//		Local_front.clear();
//		Local_front.resize(0);
//	}
//
//	cout<<"Number of iteration "<<nb_iteration<<endl;
//}






//list< Alternative * > MainKnapsack::MOLS1(double starting_time_sec){
//
//	AlternativeKnapsack* alt;
//	vector< string > Local_front(0);
//	vector< string > Dominated_alt(0);
//	int nb_iteration = 0;
//	int step = 0;
//
//	//First initialization
//	for(list< string >::iterator p = Population.begin(); p != Population.end(); ++p){
//		Archive.push_back( dic_Alternative[ *p ] );
//		step++;
//	}
//
//
//	while( !Population.empty()  and ((clock() / CLOCKS_PER_SEC) - starting_time_sec <= TIMEOUT ) ){
//		nb_iteration++;
//
//		alt = dic_Alternative[ Population.front() ];
//		Population.pop_front();
//
//
//		set< string > current_neighbors = alt->get_neighborhood();
//
//		for(set< string >::iterator id_neighbor = current_neighbors.begin(); id_neighbor != current_neighbors.end(); ++id_neighbor){
//
//			AlternativeKnapsack * neighbor;
//			if( dic_Alternative.find(*id_neighbor) != dic_Alternative.end())
////				neighbor = dic_Alternative[*id_neighbor];
//				continue;
//			else{
//				dic_Alternative[*id_neighbor] = new AlternativeKnapsack(*id_neighbor, this, WS_matrix);
//				neighbor = dic_Alternative[*id_neighbor];
//			}
//			//if neighbor is dominated add to Local_front
//			if( alt->dominates_objective_space(neighbor) == 1 )
//				Dominated_alt.push_back(*id_neighbor);
//			else
//				Local_front.push_back(*id_neighbor);
//
//		}
//
//		if( Population.empty() ){
//
//			random_shuffle( Local_front.begin(), Local_front.end() );
//
//			for(vector< string >::iterator id_new_alt = Local_front.begin(); id_new_alt != Local_front.end(); ++id_new_alt){
//
//				AlternativeKnapsack * new_alt = dic_Alternative[*id_new_alt];
//
//				if( Update_Archive(new_alt, Archive) ){
//					Population.push_back(*id_new_alt);
//				}
//				else{
//					Dominated_alt.push_back(*id_new_alt);
//				}
//			}
//
//			//GIVE CHANCE TO BAAAAD SOLUTIONS WHEN THERE STILL OPTIMAL ONES TO EXPLORE
////			if( !Population.empty() and  ((rand()*1.0/RAND_MAX) < DIVERSIFICATION)  ){
////				Limit_number_accepting_N(Dominated_alt, -1);
////
//////				Distribution_proba(Dominated_alt, -1);
//////
//////				Threshold_Accepting_AVG(Dominated_alt, -1);
//////
//////				Threshold_Accepting_BASIC(Dominated_alt, -1);
////
////			}
//
//			Local_front.clear();
//			Dominated_alt.clear();
//			step++;
//		}
//	}
//
//	cout<<"Number of iteration "<<nb_iteration<<endl;
//
//	filter_efficient_set_decision_space();
//
//	return Archive;
//
//}





//void MainKnapsack::Threshold_Accepting_AVG(list< string > & dominated_solutions, list< string > & population, int upper_bound){
//
//	map< float, string, less<float> > ratio_items;
//
//
//	vector<float> random_ws = Tools::generate_random_restricted_WS_aggregator(p_criteria, WS_matrix);
//
//	for(list< string >::iterator  i = dominated_solutions.begin(); i != dominated_solutions.end(); ++i){
//
//		shared_ptr< AlternativeKnapsack > p_alt = dic_Alternative[*i];
//
//		//		//AVERAGE TA
////		float aggreg_value = -1;
////		for(list< shared_ptr< Alternative > >::iterator alt_opt = Archive.begin(); alt_opt != Archive.end(); ++alt_opt){
////			aggreg_value +=  (f(random_ws, (*alt_opt)->get_criteria_values()) - f(random_ws, p_alt->get_criteria_values() ));
////		}
////
////		float val_key = abs( aggreg_value*1.0 / (int)Archive.size() );
//
//
//		//MIN TA
//		float aggreg_value = -1;
//		for(list< shared_ptr< Alternative > >::iterator alt_opt = Archive.begin(); alt_opt != Archive.end(); ++alt_opt){
//			float val =  abs(f(random_ws, (*alt_opt)->get_criteria_values()) - f(random_ws, p_alt->get_criteria_values() ));
//			if(aggreg_value == -1   or  (val < aggreg_value)  )
//				aggreg_value =  val;
//		}
//		float val_key = aggreg_value;
//
//
//
//
////		if(val_key <= Ta)
//			ratio_items[val_key] = p_alt->get_id_alt();
//	}
//
//
//
//	int cpt= 0;
//	int min_bound = (upper_bound != -1)? upper_bound : (int)dominated_solutions.size();
//	min_bound = ( (int)dominated_solutions.size() < min_bound) ? (int)dominated_solutions.size() : min_bound;
//	for(map< float, string, less<float> >::iterator i = ratio_items.begin(); i != ratio_items.end(); ++i){
//
//		if( cpt < min_bound){
//			shared_ptr< AlternativeKnapsack > p_alt = dic_Alternative[(*i).second];
//			population.push_back( p_alt->get_id_alt());
//			dominated_solutions.remove((*i).second);
//			cpt++;
//		}
//		else
//			break;
//	}
//
//	Ta *= alpha;
//}
