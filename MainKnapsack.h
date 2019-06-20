
#ifndef __KNAPSACK_STRUCT__
#define __KNAPSACK_STRUCT__



class MainKnapsack;

#include "LSStructure.h"
#include "AlternativeKnapsack.h"




extern list<set<int>> init_population;

extern string INFO;
extern int k_replication;





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


	//SETTERS
	void set_WS_matrix(vector< vector< float > > new_ws){
		n_objective = new_ws.size();
		p_criteria = new_ws[0].size();
		WS_matrix.resize(p_criteria);
		for(int i = 0 ; i < p_criteria; i++)
			WS_matrix[i] = new_ws[i];
	};


	//READ FILES
//	void readInitPopulationFile(string filename);

	//RESOLUTION
	bool Update_Archive(shared_ptr< Alternative > p, list< shared_ptr< Alternative > >  &set_SOL);
	bool Update_LocalArchive(shared_ptr< Alternative > p, list< string > &set_SOL);


	bool Update_Archive(shared_ptr< Alternative > p, list< shared_ptr< Alternative > > &set_SOL, list<string> & population);



	void update_alternatives(list< string > &set_Alt, bool Pareto);
	void update_WS_matrix_Population();


	void HYBRID_WS_PLS(double starting_time_sec, int ITER);
	void HYBRID_PLS_WS(double starting_time_sec, int ITER);
	void SWITCH_PLS_WS(double starting_time_sec, int ITER_PLS, int ITER_WS);

	void MOLS_SWITCH_OBJECTIVE(double starting_time_sec, int UB_Population_size, vector< string > Informations);


	void MOLS(double starting_time_sec,int ITER);
	void MOLS_Cst_PSize(double starting_time_sec, int UB_Population_size);
	void MOLS_local_Archive(double starting_time_sec);
	void MOLS_Cst_PSize_RS(double starting_time_sec, int UB_Population_size);
	void MOLS_Cst_PSize_OS(double starting_time_sec, int UB_Population_size);
//	void MOLS_Cst_PSize_FAIR(double starting_time_sec, int UB_Population_size);




	void Random_Selection(list< string > & dominated_solutions, list< string > & population, int upper_bound);
	void Ordered_Selection(list< string > & dominated_solutions, list< string > & population, int upper_bound);

	//EVALUATION
	void save_information(string filename, vector< float > criteria_vect, float time_cpu, int index);

	//STATIC METHOD
	static void Generate_random_Population(shared_ptr< Evaluator > evaluator, int number_of_individu);


	void update_extrem_point(vector< float > extrem1, float & epsi, vector< float > point_eval, vector< float > & extrem2);



	//functions to overload
	void initializeInformation(shared_ptr< Evaluator > evaluator);
	void MOLS(double starting_time_sec);
	void GenerateInitialPopulation(int size_population);


};


#endif
