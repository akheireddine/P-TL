
#ifndef ____ALTERNATIVE___
#define ____ALTERNATIVE___



#include <vector>
#include <set>


using namespace std;


class Alternative {

protected:
	int id_alt;
	vector< int > alternatives;
	vector< float > criteria_values;
	vector< float > objective_values;
	vector< Alternative* > neighborhood;
//	LSStructure * mainLSStructure;

public:
	//constructor
//	Alternative(set<int> items, LSStructure* mStruct);

	vector< float > get_objective_values(){ return objective_values; };
	vector< float > get_criteria_values() { return criteria_values; };
	int get_id(){ return id_alt; };

	virtual vector< Alternative* > get_neighborhood() = 0;
	virtual int dominates(Alternative* alt) = 0;
	virtual void print_alternative() = 0;
	virtual void print_objective_values() = 0;



};





#endif
