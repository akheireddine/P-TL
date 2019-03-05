
#ifndef ____ALTERNATIVE___
#define ____ALTERNATIVE___


#include "LSStructure.h"


class Alternative {

private:
	vector< int > alternatives;
	vector< float > criteria_values;
	vector< float > objective_values;
	vector< Alternative* > neighborhood;
	LSStructure * mainLSStructure;

public:
	vector< float > get_objective_values(){ return objective_values; };
	vector< float > get_criteria_values() { return criteria_values; };
	vector< Alternative* > get_neighborhood();

	bool dominates(Alternative* alt);


};




class AlternativeKnapsack : Alternative{
private :
	float weight;

};

#endif
