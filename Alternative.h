
#ifndef ____ALTERNATIVE___
#define ____ALTERNATIVE___



#include <vector>
#include <set>


using namespace std;


class Alternative {

protected:
	int id_alt;															//unique ID
	vector< int > alternatives;											//vector 1/0 of present items (=1) or absent (=0)
	vector< float > criteria_values;									//vector of criteria value
	vector< float > objective_values;
	vector< Alternative* > neighborhood;								//vector of alternative neighbors
//	LSStructure * mainLSStructure;

public:

	~Alternative(){
		for(int i =0; i < neighborhood.size(); i++) free(neighborhood[i]);
	};

	//GETTERS
	int get_id(){ return id_alt; };
	vector< float > get_objective_values(){ return objective_values; };
	vector< float > get_criteria_values() { return criteria_values; };

	virtual vector< Alternative* > get_neighborhood() = 0;
	virtual int dominates(Alternative* alt) = 0;

//	virtual void print_alternative() = 0;
//	virtual void print_objective_values() = 0;



};





#endif
