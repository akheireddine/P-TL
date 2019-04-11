
#ifndef __KNAPSACK_STRUCT__
#define __KNAPSACK_STRUCT__




#include "LSStructure.h"
#include "AlternativeKnapsack.h"


class MainKnapsack : public LSStructure{

protected:

	float Backpack_capacity = 0;							// capacity ofthe backpack
	int n_items;											// number of items
	double T_SA;


public :
	//information about each item : (key:weight : value:utility list for each criteria)
	vector< tuple<float, vector< float> > > Items_information;

	//constructor
	MainKnapsack(string filename, int init_population_size , string matrix_filename="PARETO");
//	~MainKnapsack(){ delete this; };
	//GETTERS
	int get_n_items(){ return n_items; };
	float get_weight_of(int i) { return std::get<0>(Items_information[i]); };
	float get_utility(int i, int j) { return std::get<1>(Items_information[i])[j]; };
	float get_capacity(){ return Backpack_capacity; };

	//READ FILES
//	void readInitPopulationFile(string filename);

	//RESOLUTION
	bool Update_Archive(Alternative* p, list< Alternative* > &set_SOL);
	bool Update_Archive_Simulated_Annealing(Alternative* p, list< Alternative* > &set_SOL);
	void update_alternatives(list<Alternative*> &set_Alt);

	void filter_efficient_set();
	void filter_efficient_set_decision_space();

	void HYBRID_WS_PLS(double starting_time_sec, int steps);
	void HYBRID_PLS_WS(double starting_time_sec, int steps);
	list< Alternative * > MOLS(double starting_time_sec,int steps);
	list< Alternative * > MOLS_NO_FILTERING(double starting_time_sec);
	list< Alternative * > MOLS_Simulated_Annealing(double starting_time_sec);



	//EVALUATION
	void save_new_point(string filename, Alternative * alt);





	//functions to overload
	void readFilenameInstance(string filename);
	void readWS_Matrix(string filename);
	list< Alternative * > MOLS(double starting_time_sec);
	void write_solution(string filename);
	void GenerateInitialPopulation(int size_population);


};


#endif
