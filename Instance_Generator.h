

#include <iostream>
#include <string>
#include <vector>
#include "Tools.h"
#include <map>

using namespace std;

class Instance_Generator {
public:

	static float Backpack_capacity;
	static int n_items;
	static int p_criteria ;

	static vector< tuple<float, vector< float> > > Items_information;





	static void random_instances(int n_items, int p_criterias,string path, int nb_instances );

	static string write_content(vector< string > weights, vector< vector< string > > utilities, string Weight);

	static void readFile(string filename);

	static vector< float > PL_WS(vector<float> WS_vector);

	static void set_Efficient_front(string filename);

	static float get_weight_of(int i) { return std::get<0>(Items_information[i]); };
	static float get_utility(int i, int j) { return std::get<1>(Items_information[i])[j]; };
};
