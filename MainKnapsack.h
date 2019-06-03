
#ifndef __KNAPSACK_STRUCT__
#define __KNAPSACK_STRUCT__



class MainKnapsack;

#include "LSStructure.h"
#include "AlternativeKnapsack.h"



extern float Ta;
extern float Temperature;

extern int GRAIN;
extern map<string, set<string> > common_neighbors;


extern list<set<int>> init_population;
extern int INFO;







class MainKnapsack : public LSStructure{

protected:

	float Backpack_capacity = 0;							// capacity ofthe backpack
	int n_items;											// number of items
	map<string, shared_ptr< AlternativeKnapsack > > dic_Alternative;


public :

	vector< tuple<float, vector< float> > > Items_information;		//information about each item : (key:weight : value:utility list for each criteria)

	//constructor
	MainKnapsack( shared_ptr< Evaluator > evaluator, int population_size_init, string filename, bool generate_population=false);

	~MainKnapsack(){

		for(map<string, shared_ptr< AlternativeKnapsack > > ::iterator it = dic_Alternative.begin(); it != dic_Alternative.end(); ++it){
			dic_Alternative[(*it).first].reset();
			dic_Alternative.erase((*it).first);
		}

		for(vector< tuple<float, vector< float> > >::iterator i = Items_information.begin(); i != Items_information.end(); ++i){
			get<1>(*i).shrink_to_fit();
		}
		Items_information.shrink_to_fit();

	};

	//GETTERS
	int get_n_items(){ return n_items; };
	float get_weight_of(int i) { return std::get<0>(Items_information[i]); };
	float get_utility(int i, int j) { return std::get<1>(Items_information[i])[j]; };
	float get_capacity(){ return Backpack_capacity; };

	//READ FILES
//	void readInitPopulationFile(string filename);

	//RESOLUTION
	bool Update_Archive(shared_ptr< Alternative > p, list< shared_ptr< Alternative > > &set_SOL);
	bool Update_Archive(shared_ptr< Alternative > p, list< string > &set_SOL);


	bool Update_Archive(shared_ptr< Alternative > p, list< shared_ptr< Alternative > > &set_SOL, list<string> & population);



//	bool Update_Archive_Threshold_Accepting(Alternative* p, list< Alternative* > &set_SOL);
	void update_alternatives(list< string > &set_Alt, bool Pareto);


	void HYBRID_WS_PLS(double starting_time_sec, int ITER);
	void HYBRID_PLS_WS(double starting_time_sec, int ITER);
	void SWITCH_PLS_WS(double starting_time_sec, int ITER_PLS, int ITER_WS);


	list< shared_ptr< Alternative > > MOLS(double starting_time_sec,int ITER);
	list< shared_ptr< Alternative > > MOLS_Cst_PSize(double starting_time_sec, int UB_Population_size);
	list< shared_ptr< Alternative > > MOLS1_Cst_PSize(double starting_time_sec, int UB_Population_size);
	list< shared_ptr< Alternative > > MOLS_local_Archive(double starting_time_sec);
	list< shared_ptr< Alternative > > MOLS_Cst_PSize_Diversification(double starting_time_sec, int UB_Population_size);
	list< shared_ptr< Alternative > > MOLS_Cst_PSize_FAIR(double starting_time_sec, int UB_Population_size);




	void Random_Selection(list< string > & dominated_solutions, int upper_bound);
//	void Distribution_proba(list< string > & dominated_solutions, int upper_bound);
	void Threshold_Accepting_AVG(list< string > & dominated_solutions, list< string > & population, int upper_bound);
//	void Simulated_Annealing(list< string > & dominated_solutions, list< string > & population, int upper_bound);
	void Learning_Threshold_Accepting_AVG(list< string > & dominated_solutions, list< string > & population, int upper_bound);

	//EVALUATION
	void save_new_point(string filename, shared_ptr< Alternative > alt);
	void write_solution(string filename);

	//STATIC METHOD
	static void Generate_random_Population(shared_ptr< Evaluator > evaluator, int number_of_individu);





	//functions to overload
	void initializeInformation(shared_ptr< Evaluator > evaluator);
	list< shared_ptr< Alternative > > MOLS(double starting_time_sec);
	void GenerateInitialPopulation(int size_population);


};


#endif
