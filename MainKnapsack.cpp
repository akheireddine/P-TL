
#include <set>
#include <ilcplex/ilocplex.h>


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


vector< float > MainKnapsack::OPT_Alternative_PLNE(vector<float> WS_vector){

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
 * ************************************************* DIVERSIFICATION PART *************************************************
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
	for(size_t i = 0; i < ws.size(); i++)
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







/**
 * ************************************************* SOLVING PART *************************************************
 */


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
 * ************************************************* MACHINE LEARNING - OTHER METHODS *************************************************
 */

void best_parametrization_RegLin(float &info_rate, int budget, int &div, int &pop_size, int inst_name, vector<int> UB_Population_list, vector< float > Informations){

	float PopSize_norm = 200 - 2.0; //100 - 2.0;
	float min_PopSize = 2.;

	float Info_norm = 90.0 - 0. ;

	float Budget_norm = 8020 - 20.;//4020 - 20.0;
	float min_Budget = 20.;

	float N_norm = 10 - 0;

	float avg_min = -1;


	//A-100
//	for(auto d : {0,1} ){
//		for(auto p : UB_Population_list){
//			 float val_avg =  (-0.0148) * inst_name/N_norm + (-0.1922)*(budget - min_Budget)*1.0/Budget_norm
//					 + 0.1169 * (p - min_PopSize)*1.0/PopSize_norm + 0.0249 * Info_rate*1.0/Info_norm + 0.1041 * d + 0.0524;
//			 if ( ((avg_min == -1) or (val_avg < avg_min)) and val_avg >= 0 ){
//				 div = d;
//				 avg_min = val_avg;
//				 pop_size = p;
//			 }
//		}
//	}

	//C-100
	for(auto d : {0,1} ){
		for(auto info : Informations){
			for(auto p : UB_Population_list){
				 float val_avg =  (-0.2423)*(budget - min_Budget)*1.0/Budget_norm
						 + 0.1048 * (p - min_PopSize)*1.0/PopSize_norm + 0.1467 * info*1.0/Info_norm + 0.1213 * d + 0.1017;
				 if ( ((avg_min == -1) or (val_avg < avg_min)) and val_avg >= 0 ){
					 div = d;
					 avg_min = val_avg;
					 pop_size = p;
					 info_rate = info;
				 }
			}
		}
	}


}






void MainKnapsack::MOLS_ML_RegLin(int Budget, vector<int> UB_Population_list, int inst_name, vector< float > Info_rate){

	shared_ptr< AlternativeKnapsack > alt;
	list< string > Local_front;
	list< string > Dominated_alt;
	list< string > next_Population;
	int nb_iteration = 0, index = 0;
	int limit_no_improvment = 2;


/*                          INITIALISER LES PARAMETRES                              */
	int PopSize = UB_Population_list[0] ;
	int diversification = 0;
	float info_rate = 90.;
	best_parametrization_RegLin(info_rate, Budget, diversification, PopSize, inst_name, UB_Population_list, Info_rate);



	//First initialization
	for(list< string >::iterator p = Population.begin(); p != Population.end(); ++p){
		dic_Alternative[ *p ] = make_shared< AlternativeKnapsack >( *p, this, WS_matrix );
		Archive.push_back( dic_Alternative[ *p ] );
	}


	while( !Population.empty() and  ( nb_iteration <= Budget ) ){
		nb_iteration++;

		alt = dic_Alternative[ Population.front() ];
		Population.pop_front();

		save_information(filename_population+"/"+to_string(Budget),alt->get_criteria_values(), nb_iteration, index, PopSize );

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
				Dominated_alt.push_back(*id_neighbor);
			}
			neighbor.reset();
		}

		alt.reset();


		if( (int)Local_front.size() >= (PopSize - (int)next_Population.size()) ){
			Tools::shuffle_list(Local_front);
		}


		for(list< string >::iterator id_new_alt = Local_front.begin(); id_new_alt != Local_front.end(); ++id_new_alt){

			shared_ptr< AlternativeKnapsack > new_alt = dic_Alternative[*id_new_alt];

			// a solution in LOcal_front could be non-dominated in the Archive but the next_Population size has exceeded UB_Population
			list< shared_ptr<Alternative> > local_Archive ( Archive.begin(), Archive.end());

			if( Update_Archive(new_alt, local_Archive, next_Population) and  (int)next_Population.size() < PopSize ){
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



			best_parametrization_RegLin(info_rate, (Budget - nb_iteration), diversification, PopSize, inst_name, UB_Population_list, Info_rate);

			cout<<"PopSize : "<<PopSize<<" Div : "<<diversification<< " Info : "<<info_rate<<" Budget : "<<(Budget - nb_iteration)<<endl;
//			ATTEMPT TO ADD DOMINATED SOLUTIONS TO Population
			if( diversification ){
				if( Population.empty() )
					limit_no_improvment--;
				else
					limit_no_improvment =  2;

				int to_add = ( PopSize - (int)Population.size() ) ;
				if( to_add > 0  and   ( (limit_no_improvment > 0) or !Population.empty() ) ){
					Ordered_Selection(Dominated_alt, Population, to_add);
				}
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
 * ************************************************* DYNAMIC - OTHER METHODS *************************************************
 */



void MainKnapsack::update_extrem_point(vector< float > extrem1, float & epsi, vector< float > point_eval, vector< float > & extrem2){

	float val = Tools::euclidian_distance(extrem1,point_eval);
	if( epsi < val )
		epsi = val;
	extrem2 = point_eval;
}



void MainKnapsack::MOLS_DYN_PSize(double starting_time_sec, vector< int > UB_Population_list, vector< string > Informations){

	shared_ptr< AlternativeKnapsack > alt;
	list< string > Local_front;
	list< string > next_Population;
	int nb_iteration = 0, index = 0;
	int cpt_info = 0;

	int surcharge = 3, remains_to_explore = 0;

	int UB_Population_size = UB_Population_list[0];
	int ub_pop = 0;

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

			if( Update_Archive(new_alt, local_Archive, next_Population) ){
				if((int)next_Population.size() < UB_Population_size ){
					next_Population.push_back(*id_new_alt);
					Archive = local_Archive;
				} else {
					remains_to_explore++;
				}
			}
			else {
				dic_Alternative[*id_new_alt].reset();
			}

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
					dic_Alternative.erase((*it).first);
				}
			}


/*
 *  	*****************************************			UPDATE UB_SIZE
 */
//			surcharge = (remains_to_explore > 0) ? (surcharge - 1) : surcharge;
//
//			if( (surcharge == 0) and ub_pop < (int)UB_Population_list.size() - 1 ){
//				ub_pop++;
//				UB_Population_size = UB_Population_list[ub_pop];
////				cout<<"Size : "<<UB_Population_list[ub_pop]<<" (remains : "<<remains_to_explore<<")"<<endl;
//				surcharge = 3;
//				remains_to_explore = 0;
////				if(cpt_info < (int)Informations.size() - 1 ){
////					cpt_info++;
////					cout<<"Information :"<<cpt_info<<endl;
////					set_WS_matrix(Tools::readMatrix(Informations[cpt_info]));
////					update_WS_matrix_Population();
////				}
//			}

			surcharge = (remains_to_explore > 0) ? surcharge : (surcharge - 1);
			remains_to_explore = 0;

			if( (surcharge == 0) and ub_pop < (int)UB_Population_list.size() - 1 ){
				ub_pop++;
				UB_Population_size = UB_Population_list[ub_pop];
//				cout<<"Size : "<<UB_Population_list[ub_pop]<<endl;
				surcharge = 3;
			}
/*
 *  	*****************************************			UPDATE UB_SIZE
 */


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



void MainKnapsack::MOLS_DYN_PSize_OS(double starting_time_sec, vector< int > UB_Population_list, vector< string > Informations){

	shared_ptr< AlternativeKnapsack > alt;
	list< string > Local_front;
	list< string > Dominated_alt;
	list< string > next_Population;
	int nb_iteration = 0, index = 0;

	int surcharge = 3, remains_to_explore = 0;

	int UB_Population_size = UB_Population_list[0];
	int ub_pop = 0;

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
				Dominated_alt.push_back(*id_neighbor);
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

			if( Update_Archive(new_alt, local_Archive, next_Population)){
				if((int)next_Population.size() < UB_Population_size ){
					next_Population.push_back(*id_new_alt);
					Archive = local_Archive;
				}
				else
					remains_to_explore++;
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
 *  	*****************************************			UPDATE UB_SIZE
 */
			surcharge = ( remains_to_explore > 0 )? (surcharge - 1) : surcharge;
			if( (surcharge == 0) and ub_pop < (int)UB_Population_list.size() - 1 ){
				ub_pop++;
				UB_Population_size = UB_Population_list[ub_pop];
				cout<<"Size : "<<UB_Population_list[ub_pop]<<" (remains : "<<remains_to_explore<<")"<<endl;
				surcharge = 3;
				remains_to_explore = 0;
			}

//			surcharge = (remains_to_explore > 0) ? surcharge : (surcharge - 1);
//			remains_to_explore = 0;

//			if( (surcharge == 0) and ub_pop < (int)UB_Population_list.size() - 1 ){
//				ub_pop++;
//				UB_Population_size = UB_Population_list[ub_pop];
//				cout<<"Size : "<<UB_Population_list[ub_pop]<<endl;
//				surcharge = 3;
//			}
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




void MainKnapsack::MOLS_DYN_INFO(double starting_time_sec, vector< int > UB_Population_list, vector< string > Informations){

	shared_ptr< AlternativeKnapsack > alt;
	list< string > Local_front;
	list< string > Dominated_alt;
	list< string > next_Population;
	int nb_iteration = 0, index = 0;
	int limit_no_improvment = 2;

	int info_index = 0;
	int overloadPop = 3, remains_to_explore = 0;

	int UB_Population_size = UB_Population_list[0];
	int Diversification = 0;

	//First initialization
	for(list< string >::iterator p = Population.begin(); p != Population.end(); ++p){
		dic_Alternative[ *p ] = make_shared< AlternativeKnapsack >( *p, this, WS_matrix );
		Archive.push_back( dic_Alternative[ *p ] );
	}


	cout<<"info : "<<info_index<<" Popsize : "<<UB_Population_size<<", Div : "<<Diversification<<endl;

	while( !Population.empty() and ((clock() / CLOCKS_PER_SEC) - starting_time_sec <= TIMEOUT ) ){
		nb_iteration++;

		alt = dic_Alternative[ Population.front() ];
		Population.pop_front();


		save_information(filename_population+"/"+to_string(UB_Population_size), alt->get_criteria_values(), index, info_index, UB_Population_size );

		set< string > current_neighbors = alt->get_neighborhood();

		for(set< string >::iterator id_neighbor = current_neighbors.begin(); id_neighbor != current_neighbors.end(); ++id_neighbor){

			shared_ptr< AlternativeKnapsack > neighbor;

			if( dic_Alternative.find(*id_neighbor) != dic_Alternative.end() )
				continue;
			else
				dic_Alternative[*id_neighbor] = make_shared< AlternativeKnapsack >( *id_neighbor, this, WS_matrix);

			neighbor = dic_Alternative[*id_neighbor];

			//Prefiltrage
			if( alt->dominates_objective_space(neighbor) != 1 ){
				Update_LocalArchive(neighbor,Local_front);
			}
			else{
				Dominated_alt.push_back(*id_neighbor);
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

			if( Update_Archive(new_alt, local_Archive, next_Population) ){
				if ((int)next_Population.size() < UB_Population_size ){
					next_Population.push_back(*id_new_alt);
					Archive = local_Archive;
				}
				else
					remains_to_explore++;
			}
			else {
				Dominated_alt.push_back(*id_new_alt);
			}

			new_alt.reset();
		}



		if( Population.empty() ){
/*
 *  	********************			UPDATE INFORMATION
 */
			overloadPop = (remains_to_explore > 0)? overloadPop - 1 : overloadPop;
			cout<<overloadPop<<"   "<<remains_to_explore<<endl;
			if(overloadPop == 0){
				overloadPop = 3;
				info_index = (info_index + 1 < (int)Informations.size())? info_index + 1 : info_index;

				vector< vector< float > > matrix_info = Tools::readMatrix(Informations[info_index]);
				float info_rate = Tools::compute_information_rate(matrix_info, p_criteria);
				set_WS_matrix(matrix_info);

				update_WS_matrix_Population();

				cout<<"info : "<<info_index<<" Popsize : "<<UB_Population_size<<", Div : "<<Diversification<<endl;
			}

	/*
	 *  	********************			UPDATE INFORMATION
	 */

			// ADD NON-DOMINATED SOLUTIONS TO Population
			for(list< string >::iterator it = next_Population.begin(); it != next_Population.end(); ++it)
				if( dic_Alternative[*it].use_count() != 0)  //could be dominated by a solution in a different Local front list
					Population.push_back(*it);

			if( Diversification ){
				if( Population.empty() )
					limit_no_improvment--;
				else
					limit_no_improvment =  2;

				int to_add = ( UB_Population_size - (int)Population.size() ) ;
				if( to_add > 0  and   ( (limit_no_improvment > 0) or !Population.empty() ) ){
					Ordered_Selection(Dominated_alt, Population, to_add);
				}
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




void best_parametrization_RegLin2(float Info_rate, int budget, int &div, int pop_size, int inst_name){

	float PopSize_norm = 200 - 2.0; //100 - 2.0;
	float min_PopSize = 2.;

	float Info_norm = 90.0 - 0. ;

	float Budget_norm = 8020 - 20.;//4020 - 20.0;
	float min_Budget = 20.;

	float N_norm = 10 - 0;

	float avg_min = -1;


	//A-100
//	for(auto d : {0,1} ){
//		for(auto p : UB_Population_list){
//			 float val_avg =  (-0.0148) * inst_name/N_norm + (-0.1922)*(budget - min_Budget)*1.0/Budget_norm
//					 + 0.1169 * (p - min_PopSize)*1.0/PopSize_norm + 0.0249 * Info_rate*1.0/Info_norm + 0.1041 * d + 0.0524;
//			 if ( ((avg_min == -1) or (val_avg < avg_min)) and val_avg >= 0 ){
//				 div = d;
//				 avg_min = val_avg;
//				 pop_size = p;
//			 }
//		}
//	}

	//C-100
	for(auto d : {0,1} ){
		 float val_avg =  (-0.2423)*(budget - min_Budget)*1.0/Budget_norm
				 + 0.1048 * (pop_size - min_PopSize)*1.0/PopSize_norm + 0.1467 * Info_rate*1.0/Info_norm + 0.1213 * d + 0.1017;
		 if ( ((avg_min == -1) or (val_avg < avg_min)) and val_avg >= 0 ){
			 div = d;
			 avg_min = val_avg;
		 }
	}

}

void MainKnapsack::MOLS_DYN_MULTIPLE_PARAM(int Budget, vector< int > UB_Population_list, int inst_name, vector< string > Informations){

	shared_ptr< AlternativeKnapsack > alt;
	list< string > Local_front;
	list< string > Dominated_alt;
	list< string > next_Population;
	int nb_iteration = 0, index = 0;
	int limit_no_improvment = 2;

	int info_index = 0;
	int overloadPop = 5, remains_to_explore = 0;

	int UB_Population_size = UB_Population_list[0];
	int Diversification = 0;

	//First initialization
	for(list< string >::iterator p = Population.begin(); p != Population.end(); ++p){
		dic_Alternative[ *p ] = make_shared< AlternativeKnapsack >( *p, this, WS_matrix );
		Archive.push_back( dic_Alternative[ *p ] );
	}


	cout<<"info : "<<info_index<<" Popsize : "<<UB_Population_size<<", Div : "<<Diversification<<endl;


	while( !Population.empty() and nb_iteration < Budget ){
		nb_iteration++;

		alt = dic_Alternative[ Population.front() ];
		Population.pop_front();


		save_information(filename_population+"/"+to_string(Budget), alt->get_criteria_values(), index, info_index, UB_Population_size );

		set< string > current_neighbors = alt->get_neighborhood();

		for(set< string >::iterator id_neighbor = current_neighbors.begin(); id_neighbor != current_neighbors.end(); ++id_neighbor){

			shared_ptr< AlternativeKnapsack > neighbor;

			if( dic_Alternative.find(*id_neighbor) != dic_Alternative.end() )
				continue;
			else
				dic_Alternative[*id_neighbor] = make_shared< AlternativeKnapsack >( *id_neighbor, this, WS_matrix);

			neighbor = dic_Alternative[*id_neighbor];

			//Prefiltrage
			if( alt->dominates_objective_space(neighbor) != 1 ){
				Update_LocalArchive(neighbor,Local_front);
			}
			else{
				Dominated_alt.push_back(*id_neighbor);
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

			if( Update_Archive(new_alt, local_Archive, next_Population) ){
				if ((int)next_Population.size() < UB_Population_size ){
					next_Population.push_back(*id_new_alt);
					Archive = local_Archive;
				}
				else
					remains_to_explore++;
			}
			else {
				Dominated_alt.push_back(*id_new_alt);
			}

			new_alt.reset();
		}



		if( Population.empty() ){
/*
 *  	********************			UPDATE INFORMATION
 */
			overloadPop = (remains_to_explore > 0)? overloadPop - 1 : overloadPop;
			cout<<overloadPop<<"   "<<remains_to_explore<<endl;
			if(overloadPop == 0){
				overloadPop = 5;
				info_index = (info_index + 1  < (int)Informations.size())? info_index + 1 : info_index;

				vector< vector< float > > matrix_info = Tools::readMatrix(Informations[info_index]);
				float info_rate = Tools::compute_information_rate(matrix_info, p_criteria);
				set_WS_matrix(matrix_info);

				int max_ub = UB_Population_list.back();
				UB_Population_size = (remains_to_explore > UB_Population_size * 3)?
						( (UB_Population_size * 2 > max_ub)?max_ub : (UB_Population_size*2) ) : UB_Population_size;

				best_parametrization_RegLin2(info_rate, Budget - nb_iteration, Diversification, UB_Population_size, inst_name);

				update_WS_matrix_Population();

				cout<<"info : "<<info_index<<" Popsize : "<<UB_Population_size<<", Div : "<<Diversification<<endl;

			}

	/*
	 *  	********************			UPDATE INFORMATION
	 */

			// ADD NON-DOMINATED SOLUTIONS TO Population
			for(list< string >::iterator it = next_Population.begin(); it != next_Population.end(); ++it)
				if( dic_Alternative[*it].use_count() != 0)  //could be dominated by a solution in a different Local front list
					Population.push_back(*it);

			if( Diversification ){
				if( Population.empty() )
					limit_no_improvment--;
				else
					limit_no_improvment =  2;

				int to_add = ( UB_Population_size - (int)Population.size() ) ;
				if( to_add > 0  and   ( (limit_no_improvment > 0) or !Population.empty() ) ){
					Ordered_Selection(Dominated_alt, Population, to_add);
				}
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



//********************************************  2PHASES  ********************************************
vector< float >  MainKnapsack::get_extrem_points(){
	vector< float > extrem_points(p_criteria);
	for(int i = 0; i < p_criteria; i++){
		vector< float > obj(p_criteria,0);
		obj[i] = 1;
		extrem_points[i] = OPT_Alternative_PLNE(obj)[i]*0.75;
	}
	return extrem_points;
}

bool MainKnapsack::reached_limit(vector< float > extrem_point){
	for(auto p: Population){
		vector< float > v_criteria = (dic_Alternative[ p ])->get_criteria_values();
		bool found = true;
		for(size_t i = 0; i <  v_criteria.size(); i++)
			if( v_criteria[i] > extrem_point[i] )
				found = false;
		if( found )
			return true;
	}
	return false;
}

void MainKnapsack::MOLS_DYNAMIC(double starting_time_sec, vector< int > UB_Population_list, vector< string > Informations){

	shared_ptr< AlternativeKnapsack > alt;
	list< string > Local_front;
	list< string > Dominated_alt;
	list< string > next_Population;
	int nb_iteration = 0, index = 0;

	int surcharge = 3, ub_pop = 0;

	int strategie = 1;

	int UB_Population_size = UB_Population_list[0];

	int limit_no_improvment = 2;

	//First initialization
	for(list< string >::iterator p = Population.begin(); p != Population.end(); ++p){
		dic_Alternative[ *p ] = make_shared< AlternativeKnapsack >( *p, this, WS_matrix );
		Archive.push_back( dic_Alternative[ *p ] );
	}




	vector< float > extrem_points = get_extrem_points();


	while( !Population.empty() and ((clock() / CLOCKS_PER_SEC) - starting_time_sec <= TIMEOUT ) ){
		nb_iteration++;

		alt = dic_Alternative[ Population.front() ];
		Population.pop_front();


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
				Dominated_alt.push_back(*id_neighbor);
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
				Dominated_alt.push_back(*id_new_alt);
			}

			new_alt.reset();
		}



		if( Population.empty() ){

			// ADD NON-DOMINATED SOLUTIONS TO Population
			for(list< string >::iterator it = next_Population.begin(); it != next_Population.end(); ++it)
				if( dic_Alternative[*it].use_count() != 0)  //could be dominated by a solution in a different Local front list
					Population.push_back(*it);




//			ATTEMPT TO ADD DOMINATED SOLUTIONS TO Population
//			if( Population.empty() )
//				limit_no_improvment--;
//			else
//				limit_no_improvment =  2;
//
//			int to_add = ( UB_Population_size - (int)Population.size() ) ;
//			if( to_add > 0  and   ( (limit_no_improvment > 0) or !Population.empty() ) ){
//				Ordered_Selection(Dominated_alt, Population, to_add);
//			}
//
//			map<string, shared_ptr< AlternativeKnapsack > > tmp_dic_Alternative = dic_Alternative;
//			for(map<string, shared_ptr< AlternativeKnapsack > >::iterator it = tmp_dic_Alternative.begin(); it != tmp_dic_Alternative.end(); ++it){
//				if( find(Population.begin(), Population.end(), (*it).first) == Population.end()  and (*it).second.use_count() == 1 ){
//					(*it).second.reset();
//					dic_Alternative.erase((*it).first);
//				}
//			}

/*
 *  	*****************************************			UPDATE UB_SIZE
*/
			if( strategie == 2){
					surcharge = ((int)Population.size() < UB_Population_size) ? surcharge : (surcharge - 1);
					if( (surcharge == 0) and ub_pop < (int)UB_Population_list.size() - 1 ){
						ub_pop++;
						UB_Population_size = UB_Population_list[ub_pop];
						cout<<"Size : "<<UB_Population_list[ub_pop]<<endl;
						surcharge = 3;
					}
				}
				else if( strategie == 1 ){
					if( reached_limit(extrem_points) )
						strategie = 2;
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














void MainKnapsack::MOLS_OPT_PARAMETERS(double starting_time_sec, vector< map<string, float > > OPT_Params,
		map<float,int> id_info, string information_file){

	int i = 0;
	int index = 0;
	shared_ptr< AlternativeKnapsack > alt;
	list< string > Dominated_alt;
	list< string > next_Population;
	list< string > Local_front;

	int nb_iteration=0, local_iteration = 0;
	int limit_no_improvment = 2;

	string save_point_file ="", index_info="";
	int info = -1, UB_Population_size = -1, budget = -1, div = -1;

	//First initialization NO FILTERING
	for(list< string >::iterator p = Population.begin(); p != Population.end(); ++p){
		dic_Alternative[ *p ] = make_shared< AlternativeKnapsack >( *p, this, WS_matrix);
		Archive.push_back( dic_Alternative[ *p ] );
	}

	index++;
//	"Type", "Size", "Instance", "Budget", "PopSize", "Info", "nb_evaluation", "AVG_dist", "MaxMin", "PR", "Diversification"};

	mt19937 g( rand() );

	list< int > index_params;
	vector< int > val_shuffle;
	for(size_t z = 0; z < OPT_Params.size(); z++)
		val_shuffle.push_back(z);
	shuffle(val_shuffle.begin(), val_shuffle.end(), g );

	for(auto z : val_shuffle)
		index_params.push_back(z);


	while( !index_params.empty() ) { // i < OPT_Params.size() ){

		i = index_params.front();
		index_params.pop_front();

		for(auto p : Archive){
			Population.push_back( p->get_id_alt() );
		}

		map< string, float > params = OPT_Params[i];
		i++;
		info = params["Info"];
		index_info = to_string( id_info[info] );
		set_WS_matrix( Tools::readMatrix(information_file+index_info) );
		UB_Population_size = params["PopSize"];
		budget = params["Budget"];
		div = params["Diversification"];

//		if( div == 1)
//			save_point_file = filename_population+"/MOLS_OPT_PARAMETERS/OS/"+index_info;
//		else
//		save_point_file = filename_population+"/MOLS_OPT_PARAMETERS";
		save_point_file = filename_population+"/MOLS_OPT_PARAMETERS_SHUFFLE";


		local_iteration = 0;

		for(list< string >::iterator p = Population.begin(); p != Population.end(); ++p){
			alt = dic_Alternative[ *p ];
			alt->set_local_WS_matrix(WS_matrix);
		}

		cout<<budget<<endl;

		while(local_iteration < budget and !Population.empty() and (clock() / CLOCKS_PER_SEC) - starting_time_sec <= TIMEOUT ){
			nb_iteration++;
			local_iteration++;
			alt = dic_Alternative[ Population.front() ];
			Population.pop_front();

			save_information(save_point_file, alt->get_criteria_values(), ((clock()* 1./CLOCKS_PER_SEC) - starting_time_sec), index, UB_Population_size );

			set< string > current_neighbors = alt->get_neighborhood();

			for(set< string >::iterator id_neighbor = current_neighbors.begin(); id_neighbor != current_neighbors.end(); ++id_neighbor){

				shared_ptr< AlternativeKnapsack > neighbor;

				if( dic_Alternative.find(*id_neighbor) != dic_Alternative.end() )
					continue;
				else
					dic_Alternative[*id_neighbor] = make_shared< AlternativeKnapsack >( *id_neighbor, this, WS_matrix);

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
				if( div == 1 ){
					if( Population.empty() )
						limit_no_improvment--;
					else
						limit_no_improvment =  2;

					int to_add = ( UB_Population_size - (int)Population.size() ) ;
					if( to_add > 0  and   ( (limit_no_improvment > 0) or !Population.empty() ) ){
						Ordered_Selection(Dominated_alt, Population, to_add);
					}
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
	}

	cout<<"Number of iteration "<<nb_iteration<<endl;
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



/**
 * ************************************************* OTHER ALGO PART *************************************************
 */



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

void MainKnapsack::HYBRID_WS_PLS(double starting_time_sec,int ITER){

	//WS
//	MOLS(starting_time_sec,ITER);

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
//	MOLS(starting_time_sec,ITER);

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

//		MOLS(starting_time_sec,ITER_PLS);

		cout<<"PLS : "<<Archive.size()<<endl;

		index++;

//		MUST CLEAN DICT ALTERNATIVE AND KEEP OPT SOLUTION
		for(list< shared_ptr<Alternative> >::iterator alt = Archive.begin(); alt != Archive.end(); ++alt)
			if( find(Population.begin(), Population.end() , (*alt)->get_id_alt()) == Population.end())
				Population.push_back((*alt)->get_id_alt());

		Archive.clear();

		//WS
		update_alternatives(Population,false);
//		MOLS(starting_time_sec,Population.size() + ITER_WS);

		if(ITER_WS > 2)
			ITER_WS -= 1;
		cout<<"WS : "<<Archive.size()<<endl;

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
