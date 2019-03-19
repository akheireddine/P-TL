
#ifndef __KNAPSACK_STRUCT__
#define __KNAPSACK_STRUCT__




#include "LSStructure.h"
#include "AlternativeKnapsack.h"


class MainKnapsack : public LSStructure{

protected:

	float Backpack_capacity = 0;							// capacity ofthe backpack
	int n_items;											// number of items
	vector< vector<float> > ParetoFront;					// Optimal pareto front from .eff

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
	void readParetoFront();

//	void write_coeff_functions(string type_inst);

	//RESOLUTION
	bool Update_Archive(Alternative* p, list< Alternative* > &set_SOL);
	void filter_efficient_set();
	void HYBRID_WS_PLS(double starting_time_sec);


	//EVALUATION
	float nearest_alternative(string filename, vector<float > weight_DM, vector< float > opt_values,  vector< float > & vect_obj );
	vector< float > solve_plne_ws_function(vector<float> weighted_sum);
	void evaluate_solutions(string weighted_DM_preferences,float time);
	void pareto_front_evaluation();
	void save_new_point(string filename, Alternative * alt);


	//INDICATORS
	float average_distance_D1();
	float maximum_distance_D2();
	float PR_D3();


	//functions to overload
	void readFilenameInstance(string filename);
	void readWS_Matrix(string filename);
	list< Alternative * > MOLS(double starting_time_sec);
	void write_solution(string filename);
	void GenerateInitialPopulation(int size_population);


};


#endif
