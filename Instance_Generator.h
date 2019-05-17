

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Instance_Generator {

public:

	static void random_instances(int n_items, int p_criteria,string path, int nb_instances );

	static string write_content(vector< string > weights, vector< vector< string > > utilities, string Weight);


};
