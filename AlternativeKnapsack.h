
#ifndef __KNAPSACK_ALT__
#define __KNAPSACK_ALT__



#include "Alternative.h"
#include <iostream>

class MainKnapsack;

using namespace std;



class AlternativeKnapsack : public Alternative{
protected :
	float weight;
	MainKnapsack* mainLSStructure;


public:
	AlternativeKnapsack(set<int> items, MainKnapsack* mStruct);

	float get_weight(){ return weight; }



	int dominates(Alternative* alt);
	vector< Alternative* > get_neighborhood();


	inline void print_aternative(){
		cout<<"(";
		for(int i = 0; i < alternatives.size(); i++)
			cout<< alternatives[i] <<", ";
		cout<<")"<<endl;
	}
	inline void print_objective_values(){
		cout<<"(";
		for(int i = 0; i < objective_values.size(); i++)
			cout<< objective_values[i] <<", ";
		cout<<") ";
	}





};

#endif
