




#include "LSStructure.h"


class MainKnapsack : public LSStructure{
private:
	float Backpack_capacity;
	int n_items;

public :

	//information about each item : (weight, utility list for each criteria)
	vector< tuple<float, vector< float> > > Items_information;

	int get_n_items(){ return n_items; };
	float get_weight_of(int i) { return std::get<0>(Items_information[i]); };
	float get_utility(int i, int j) { return std::get<1>(Items_information[i])[j]; };
	float get_capacity(){ return Backpack_capacity; };

	void readInitPopulationFile(string filename);


};
