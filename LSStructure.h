


#include "Alternative.h"


class LSStructure {
private :
	list< Alternative * > OPT_Solution;
	vector< vector < float >> WS_matrix;
	int n_objective;
	int p_criteria;
	list< Alternative* > Population;

public:
	void readFilenameInstance(string filename);
	void readWS_Matrix(string filename);
	vector< Alternative * > MOLS();


	int get_p_criteria(){ return p_criteria; };
	int get_n_objective(){ return n_objective; };
	vector< vector< float > > get_WS_matrix(){ return WS_matrix; };

};



class MainKnapsack : LSStructure{
private:
	float Backpack_capacity;
	int n_items;

public :

	//information about each item : (weight, utility list for each criteria)
	vector< tuple<float, vector< float> > > Items_information;

	int get_n_items(){ return n_items; };
	float get_weight_of(int i) { return std::get<0>(Items_information[i]); };
	float get_utility(int i, int j) { return std::get<1>(Items_information[i])[j]; };

	void readInitPopulationFile(string filename);


}
