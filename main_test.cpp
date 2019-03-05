
#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>

using namespace std;


int main(int argc, char ** argv){


	string filename = "./Instances_Knapsack/Type_A/100_items/2KP100-TA-0.dat";


	string line;
	char buff[100];
	int i = 0;
	vector< tuple<float, vector< float> > > Items_information;

	vector< float > line_value;

	ifstream fic(filename.c_str());

	if (!(fic) or filename.find(".dat") == std::string::npos){
		cerr<<"Error occurred"<<endl;
	}


	//comments
	getline(fic,line);
	while( line[0] == 'c' )
		getline(fic,line);

	//number of items
	int n_items = 0;
	if( line[0] == 'n')
		sscanf(line.c_str(),"%s %d",buff,&n_items);

	Items_information.resize(n_items);

	//comments
	getline(fic,line);
	while( line[0] == 'c' )
		getline(fic,line);

	//items information


	while(line[0] == 'i'){

		line.erase(line.begin());
		char *cline = new char[line.length() + 1]; // or
		std::strcpy(cline, line.c_str());

		line_value.clear();
		char * pch = strtok (cline," 	");
		while (pch != NULL){
			line_value.push_back(atof(pch));
			pch = strtok (NULL, " 	");
		}

		float weight = line_value[0];

		line_value.erase(line_value.begin());

		Items_information[i] = make_tuple(weight,line_value);


		getline(fic,line);
		i++;
	}

	//number of criteria
	int p_criteria = 0;
	p_criteria = line_value.size();

	//comments
	while( line[0] == 'c' )
		getline(fic,line);


	//total capacity
	float Backpack_capacity = 0;
	if( line[0] == 'W' )
		sscanf(line.c_str(),"%s %f",buff,&Backpack_capacity);



//	for(int i = 0; i < n_items; i++){
//		cout << std::get<0>(Items_information[i]) << endl;
//		for(int j = 0; j < p_criteria; j++)
//			cout << std::get<1>(Items_information[i])[j] << " ";
//		cout<<endl;
//	}
	return 0;
}
