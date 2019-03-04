


#include "Alternative.h"


class LSStructure {
private :
	vector< int > OPT_Solution;
	A WF_matrix;
	int p_criteria;
	vector< Alternative* > initial_population;

public:
	vector< Alternative * > MOLS();
	void readFilenameInstance(string filename);
	int get_p_criteria(){ return p_criteria; };

};



class MainKnapsack : LSStructure{
private:
	float Backpack_capacity;
	int n_items;

public :

	//information about each item : (weight, utility list for each criteria)
	vector< tuple<float, vector< float> > > Items_information;

	int get_n_items(){ return n_items; };
	float get_weight_of(int i) { return get<0>(Items_information[i]); };
	float get_utility(int i, int j) { return get<1>(Items_information[i][j]); };

}
