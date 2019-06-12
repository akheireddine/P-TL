


#include "Instance_Generator.h"

#include <random>
#include <fstream>


#define LO_W 2
#define HI_W 25

#define LO_U 10
#define HI_U 35




void Instance_Generator::random_instances(int n_items, int p_criteria,string path, int nb_instances ){


	int Weight = 0;
	for(int i = 10; i < nb_instances+10; i++){

		string filename = "2KP"+to_string(n_items)+"-TA-"+to_string(i)+".dat";

		vector< string > weights(n_items);
		vector< vector< string > > utilities(n_items,vector< string >(p_criteria) );

		//RANDOM GENERATION
		for(int n = 0; n < n_items; n++){
			int rand_weight = LO_W +  (rand()) /( (RAND_MAX/(HI_W-LO_W)));
			weights[n] = to_string(rand_weight);

			Weight += rand_weight;

			for(int p = 0; p < p_criteria; p++){
				int rand_utility = LO_U + (rand()) /((RAND_MAX/(HI_U-LO_U)));
				utilities[n][p] = to_string(rand_utility);
			}
		}

		Weight /= n_items;
		string content = write_content(weights, utilities, to_string(Weight));

		ofstream fic((path+"/"+filename).c_str());

		fic<<content<<endl;
		fic.close();

	}

}





string Instance_Generator::write_content(vector< string > weights, vector< vector< string > > utilities, string Weight){

	string content = "n "+to_string(weights.size())+"\n";

	content += "c  w \n";

	for(int i = 0; i < (int)weights.size(); i++ ){

		content += "i "+weights[i];

		for(int j = 0; j < (int)utilities[i].size(); j++){

			content +=" 	 "+utilities[i][j];
		}

		content +="\n";
	}

	content += "c c\n";

	content += "W "+Weight+"\n";

	content += "c end of file\n";


	return content;
}
