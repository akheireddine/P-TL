
#ifndef __KNAPSACK_ALT__
#define __KNAPSACK_ALT__



#include "Alternative.h"
#include <iostream>
#include <map>

class MainKnapsack;

using namespace std;



class AlternativeKnapsack : public Alternative{
protected :
	float weight;
	MainKnapsack* mainLSStructure;


public:
	AlternativeKnapsack(set<int> items, MainKnapsack* mStruct);

	float get_weight(){ return weight; }

//	void improving_initial_population();
	void enumerate_neighborhood(set<int> & curr_BP, set<int> &item_OUT, float bp_weight, map< float, int, greater <float> > ratio_items);




	int dominates(Alternative* alt);
	vector< Alternative* > get_neighborhood();


	inline void print_alternative(){
		cout<<"(";
		for(int i = 0; i < alternatives.size(); i++)
			cout<< alternatives[i] <<", ";
		cout<<")"<<endl;
	};

	inline void print_objective_values(){
		cout<<"(";
		for(int i = 0; i < objective_values.size(); i++)
			cout<< objective_values[i] <<", ";
		cout<<")   ";
	};

	inline void print_criteria_values(){
		cout<<"(";
		for(int i = 0; i < criteria_values.size(); i++)
			cout<< criteria_values[i] <<", ";
		cout<<")"<<endl;
	};





};

#endif
