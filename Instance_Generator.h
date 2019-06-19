#ifndef __INST_GENERATOR__
#define __INST_GENERATOR__


#include <iostream>
#include <string>
#include <vector>
#include "Tools.h"
#include <map>

using namespace std;

class Instance_Generator {
private :
	 float Backpack_capacity;
	 int n_items;
	 int p_criteria ;
	 int nb_instances;

	 vector< tuple<float, vector< float> > > Items_information;
public:

	Instance_Generator(int n, int p, int nb_inst);

	void random_instances(string path);

	string write_content(vector< string > weights, vector< vector< string > > utilities, string Weight);

	void readFile(string filename);

	vector< float > PL_WS(vector<float> WS_vector);

	void set_Efficient_front(string filename);

	float get_weight_of(int i) { return std::get<0>(Items_information[i]); };

	float get_utility(int i, int j) { return std::get<1>(Items_information[i])[j]; };
};



#endif
