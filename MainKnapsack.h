
#ifndef __KNAPSACK_STRUCT__
#define __KNAPSACK_STRUCT__




#include "LSStructure.h"
#include "AlternativeKnapsack.h"


class MainKnapsack : public LSStructure{

protected:

	float Backpack_capacity = 0;							// capacity ofthe backpack
	int n_items;											// number of items
	map<string, AlternativeKnapsack * > dic_Alternative;


public :
	//information about each item : (key:weight : value:utility list for each criteria)
	vector< tuple<float, vector< float> > > Items_information;

	//constructor
	MainKnapsack(string filename, int init_population_size , string matrix_filename="PARETO");
	MainKnapsack( int population_size_init, string filename, string matrix_filename="PARETO");

	~MainKnapsack(){
		for(map<string, AlternativeKnapsack* >::iterator it = dic_Alternative.begin(); it != dic_Alternative.end(); ++it)
			delete dic_Alternative[(*it).first];
	};

	//GETTERS
	int get_n_items(){ return n_items; };
	float get_weight_of(int i) { return std::get<0>(Items_information[i]); };
	float get_utility(int i, int j) { return std::get<1>(Items_information[i])[j]; };
	float get_capacity(){ return Backpack_capacity; };

	//READ FILES
//	void readInitPopulationFile(string filename);

	//RESOLUTION
	bool Update_Archive(Alternative* p, list< Alternative* > &set_SOL);
	bool Update_Archive(Alternative* p, list< string > &set_SOL);

	bool Update_Archive_Threshold_Accepting(Alternative* p, list< Alternative* > &set_SOL);
	void update_alternatives(list< string > &set_Alt);

	void filter_efficient_set();
	void filter_efficient_set_decision_space();

	void HYBRID_WS_PLS(double starting_time_sec, int steps);
	void HYBRID_PLS_WS(double starting_time_sec, int steps);
	list< Alternative * > MOLS(double starting_time_sec,int steps);
	list< Alternative * > MOLS1_Cst_PSize(double starting_time_sec, int UB_Population_size);
	list< Alternative * > MOLS2_Cst_PSize(double starting_time_sec, int UB_Population_size);




	list< Alternative * > MOLS1(double starting_time_sec);
	list< Alternative * > MOLS2(double starting_time_sec);


	void Limit_number_N(vector< string > dominated_solutions);
	void Distribution_proba(vector< string > dominated_solutions);


	//EVALUATION
	void save_new_point(string filename, Alternative * alt);


	//STATIC METHOD
	static void Generate_random_Population(string filename, int number_of_individu);




	//functions to overload
	void readFilenameInstance(string filename);
	void readWS_Matrix(string filename);
	list< Alternative * > MOLS(double starting_time_sec);
	void write_solution(string filename);
	void GenerateInitialPopulation(int size_population);


};


#endif
