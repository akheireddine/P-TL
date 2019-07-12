
#ifndef __KNAPSACK_ALT__
#define __KNAPSACK_ALT__


#include <map>
#include <iostream>
#include "Alternative.h"
#include "Tools.h"

class MainKnapsack;

using namespace std;



class AlternativeKnapsack : public Alternative{

protected :
	float weight;													// total weight of the alternative
	MainKnapsack * mainLSStructure;									// pointer to the main structure (for information)

public:

	//CONSTRUCTOR DESTRUCTOR
	AlternativeKnapsack(set<int> items, MainKnapsack * mStruct, vector< vector< float > > WS_matrix);
	AlternativeKnapsack(string id_alternative, MainKnapsack * mStruct, vector< vector<float > > WS_matrix);
	AlternativeKnapsack(string id_alternative, MainKnapsack * mStruct, vector< vector<float > > WS_matrix, list< shared_ptr< Alternative > > Archive);
	~AlternativeKnapsack(){  };
//	if(mainLSStructure.use_count() > 1){ mainLSStructure.reset(); }

	//GETTERS
	float get_weight(){ return weight; };

	//ALGORITHMS
	void enumerate_neighborhood(set<int> curr_BP, set<int> item_OUT, float bp_weight, map< float, int, greater <float> > ratio_items);
	map< float, int, greater <float> > generate_ordered_ratio_items(set<int> set_items);



	//OVERLOADED METHODS
	/**
	 * 1  current alternative dominates paramter alt
	 * 0  incomparable
	 * -1 paramter alt dominates current alternative
	 */
	int dominates_objective_space(shared_ptr< Alternative > alt);
	int dominates_decision_space(shared_ptr< Alternative > alt);
	set< string > get_neighborhood();
	void update_objective_vector();
	void set_local_WS_matrix(vector<vector<float > > matrix);

	inline int get_nb_items(){
		int nb = 0;
		for(int i = 0; i < (int)id_alt.length(); i++)
			if( id_alt[i] == '1')
				nb++;
		return nb;
	};

	inline bool contains_items(shared_ptr< Alternative > alt){
		for(int i = 0; i < (int)id_alt.length(); i++)
			if((id_alt[i] != alt->get_id_alt()[i])   and  (alt->get_id_alt()[i] == '1') )
				return false;
		return true;
	};




};

#endif
