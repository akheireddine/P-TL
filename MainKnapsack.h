
#ifndef __KNAPSACK_STRUCT__
#define __KNAPSACK_STRUCT__




#include "LSStructure.h"
#include "AlternativeKnapsack.h"

class MainKnapsack : public LSStructure{
protected:
	float Backpack_capacity = 0;
	int n_items;

public :
	//constructor
	MainKnapsack(string filename, string pref_filename, string init_population_filename);

	//information about each item : (weight, utility list for each criteria)
	vector< tuple<float, vector< float> > > Items_information;

	int get_n_items(){ return n_items; };
	float get_weight_of(int i) { return std::get<0>(Items_information[i]); };
	float get_utility(int i, int j) { return std::get<1>(Items_information[i])[j]; };
	float get_capacity(){ return Backpack_capacity; };

	void readInitPopulationFile(string filename);
	bool Update_Archive(Alternative* p, list< Alternative* > &set_SOL);
	void filter_efficient_set();
	float nearest_alternative(string filename, vector<float> opt_values, vector< float >& vect_obj );
	vector< float > solve_plne_ws_function(vector<float> weighted_sum);
	void evaluate_solutions(string weighted_DM_preferences,float time);
	void pareto_front_evaluation();
	void write_coeff_functions();




	//functions to overload
	void readFilenameInstance(string filename);
	void readWS_Matrix(string filename);
	list< Alternative * > MOLS();
	void write_solution();



};


#endif
