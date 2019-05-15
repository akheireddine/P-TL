
#ifndef __KNAPSACK_STRUCT__
#define __KNAPSACK_STRUCT__




#include "LSStructure.h"
#include "AlternativeKnapsack.h"



class MainKnapsack : public LSStructure{

protected:

	float Backpack_capacity = 0;							// capacity ofthe backpack
	int n_items;											// number of items
	map<string, shared_ptr< AlternativeKnapsack > > dic_Alternative;


public :
	//information about each item : (key:weight : value:utility list for each criteria)
	vector< tuple<float, vector< float> > > Items_information;

	//constructor
	MainKnapsack(string filename, int init_population_size , string matrix_filename="PARETO");
	MainKnapsack( int population_size_init, string filename, string matrix_filename="PARETO");

	~MainKnapsack(){
		for(map<string, shared_ptr< AlternativeKnapsack > > ::iterator it = dic_Alternative.begin(); it != dic_Alternative.end(); ++it)
			dic_Alternative[(*it).first].reset();
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

//	bool Update_Archive_Threshold_Accepting(Alternative* p, list< Alternative* > &set_SOL);
	void update_alternatives(list< string > &set_Alt, bool Pareto);

	void filter_efficient_set();
	void filter_efficient_set_decision_space();

	void HYBRID_WS_PLS(double starting_time_sec, int ITER);
	void HYBRID_PLS_WS(double starting_time_sec, int ITER);

	list< shared_ptr< Alternative > > MOLS(double starting_time_sec,int ITER);
	list< shared_ptr< Alternative > > MOLS_Cst_PSize(double starting_time_sec, int UB_Population_size);
	list< shared_ptr< Alternative > > MOLS_local_Archive(double starting_time_sec);




//	list< Alternative * > MOLS1(double starting_time_sec);
//	list< Alternative * > MOLS1_Cst_PSize(double starting_time_sec, int UB_Population_size);



	void Limit_number_accepting_N(list< string > & dominated_solutions, int upper_bound);
	void Distribution_proba(list< string > & dominated_solutions, int upper_bound);
	void Threshold_Accepting_AVG(list< string > & dominated_solutions, list< string > & population, int upper_bound);
	void Simulated_Annealing(list< string > & dominated_solutions, list< string > & population, int upper_bound);


	//EVALUATION
	void save_new_point(string filename, shared_ptr< Alternative > alt);


	//STATIC METHOD
	static void Generate_random_Population(string filename, int number_of_individu);




	//functions to overload
	void readFilenameInstance(string filename);
	void readWS_Matrix(string filename);
	list< shared_ptr< Alternative > > MOLS(double starting_time_sec);
	void write_solution(string filename);
	void GenerateInitialPopulation(int size_population);


};


#endif
