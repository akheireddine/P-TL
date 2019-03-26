
#ifndef __KNAPSACK_STRUCT__
#define __KNAPSACK_STRUCT__




#include "LSStructure.h"
#include "AlternativeKnapsack.h"


class MainKnapsack : public LSStructure{

protected:

	float Backpack_capacity = 0;							// capacity ofthe backpack
	int n_items;											// number of items
	vector< vector<float> > ParetoFront;					// Optimal pareto front from .eff
	AlternativeKnapsack * OPT_Alternative;
public :

	//information about each item : (key:weight : value:utility list for each criteria)
	vector< tuple<float, vector< float> > > Items_information;

	//constructor
	MainKnapsack(string filename,string type_inst, string num_inst, int init_population_size , string matrix_filename="PARETO");

	//GETTERS
	int get_n_items(){ return n_items; };
	float get_weight_of(int i) { return std::get<0>(Items_information[i]); };
	float get_utility(int i, int j) { return std::get<1>(Items_information[i])[j]; };
	float get_capacity(){ return Backpack_capacity; };

	//READ FILES
//	void readInitPopulationFile(string filename);
	void write_coeff_functions(string filename );

	//RESOLUTION
	bool Update_Archive(Alternative* p, list< Alternative* > &set_SOL);
	void filter_efficient_set();
	void HYBRID_WS_PLS(double starting_time_sec, int steps);
	list< Alternative * > MOLS(double starting_time_sec,int steps);


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
