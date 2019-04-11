
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
	MainKnapsack* mainLSStructure;									// pointer to the main structure (for information)


public:

	//CONSTRUCTOR
	AlternativeKnapsack(set<int> items, MainKnapsack* mStruct, vector< vector< float > > WS_matrix);
//	~AlternativeKnapsack();
	//GETTERS
	float get_weight(){ return weight; }

	//ALGORITHMS
	void enumerate_neighborhood(set<int> & curr_BP, set<int> &item_OUT, float bp_weight, map< float, int, greater <float> > ratio_items);
	map< float, int, greater <float> > generate_ordered_ratio_items(set<int> set_items);



	//OVERLOADED METHODS
	/**
	 * 1  current alternative dominates paramter alt
	 * 0  incomparable
	 * -1 paramter alt dominates current alternative
	 */
	int dominates_objective_space(Alternative* alt);
	int dominates_decision_space(Alternative* alt);
	vector< Alternative* > get_neighborhood();
	void update_objective_vector();
	inline int get_nb_items(){
		int nb = 0;
		for(int i = 0; i < (int)alternatives.size(); i++)
			if( alternatives[i] == 1)
				nb++;
		return nb;
	};

	inline bool contains_items(Alternative * alt){
		for(int i = 0; i < (int)alternatives.size(); i++)
			if((alternatives[i] != alt->get_alternatives()[i])   and  (alt->get_alternatives()[i] == 1) )
				return false;
		return true;
	};




};

#endif
