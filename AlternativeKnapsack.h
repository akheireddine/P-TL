
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
	AlternativeKnapsack(set<int> items, MainKnapsack* mStruct);
	~AlternativeKnapsack(){
//		delete this;
	};
	//GETTERS
	float get_weight(){ return weight; }

	void enumerate_neighborhood(set<int> & curr_BP, set<int> &item_OUT, float bp_weight, map< float, int, greater <float> > ratio_items);


	map< float, int, greater <float> > generate_ordered_ratio_items(set<int> set_items);



	//OVERLOADED METHODS
	vector< Alternative* > get_neighborhood();
	/**
	 * 1  current alternative dominates paramter alt
	 * 0  incomparable
	 * -1 paramter alt dominates current alternative
	 */
	int dominates(Alternative* alt);
	void update();


	inline void print_alternative(){ cout<<"("; for(int i = 0; i < alternatives.size(); i++) cout<< alternatives[i] <<", "; cout<<")"<<endl;};

	inline void print_objective_values(){ cout<<"("; for(int i = 0; i < objective_values.size(); i++) cout<< objective_values[i] <<", "; cout<<")   "; };

	inline void print_criteria_values(){ cout<<"("; for(int i = 0; i < criteria_values.size(); i++) cout<< criteria_values[i] <<", "; cout<<")"<<endl; };

	inline float get_criteria(int i ){ return criteria_values[i]; };


};

#endif
