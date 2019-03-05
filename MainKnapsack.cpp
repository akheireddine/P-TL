

#include "LSStructure.h"


MainKnapsack::MainKnapsack(string filename, string pref_filename, string init_population_filename){

	readFilenameInstance(filename);

	readInitPopulationFile(init_population_filename);

	readWS_Matrix(pref_filename);

}


void MainKnapsack::readInitPopulationFile(string filename){

	ifstream fic(filename.c_str());
	string line;
	float total_weight;

	while(!fic.eof()){

		total_weight = 0;
		getline(fic,line);

		Set<int> set_items;
		char *cline = new char[line.length() + 1];
		std::strcpy(cline, line.c_str());

		char * pch = strtok (cline," 	,");
		while (pch != NULL){
			set_items.push_back(atoi(pch));
			total_weight += std::get<0>(Items_information[atoi(pch)]);
			pch = strtok (NULL, " 	,");
		}

		if(total_weight > Backpack_capacity){
			cerr<<"Not feasable initialization"<<endl;
			exit(1);
		}
		AlternativeKnapsack * alt = AlternativeKnapsack(set_items, this);
		Population.push_back(alt);

	}

	fic.close();
}




void MainKnapsack::readFilenameInstance(string filename){

	string line;
	char buff[100];
	int i = 0;

	vector< float > line_value;

	ifstream fic(filename.c_str());

	if (!(fic) or filename.find(".ks") == std::string::npos){
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


	fic.close();
}


void MainKnapsack::readWS_Matrix(string filename){

	ifstream fic(filename.c_str());
	string line;
	int i = 0;
	if (!(fic) or filename.find(".csv") == std::string::npos){
		cerr<<"Error occurred"<<endl;
	}


	while( !fic.eof() and i < p_criteria){

		getline(fic,line);

		char *cline = new char[line.length() + 1]; // or
		std::strcpy(cline, line.c_str());

		WS_matrix[i].clear();
		char * pch = strtok (cline," 	,;");
		while (pch != NULL){
			WS_matrix[i].push_back(atof(pch));
			pch = strtok (NULL, " 	,;");
		}
		i++;
	}

	n_objective = WS_matrix[0].size();


}



vector< Alternative * > MainKnapsack::MOLS(){

	Alternative* alt;
	list< Alternative* > Local_front;
	//First initialization
	for(list< Alternative* >::iterator p = Population.begin(); p != Population.end(); p++){
		Update_Archive(p,OPT_Solution);
	}

	while(Population.size() > 0){

		//erase the first element
		alt = Population.pop_front();

		for(vector<Alternative *>::iterator neighbor = alt->get_neighborhood().begin(); neighbor != alt->get_neighborhood().end(); neighbor++){
			if( !alt->dominates(neighbor) )
				Update_Archive(neighbor,Local_front);
		}

		for(list< Alternative* >::iterator new_alt = Local_front.begin(); new_alt != Local_front.end(); new_alt++){
			if ( Update_Archive(*new_alt, OPT_Solution) )
				Population.push_back(*new_alt);
		}

//		Population.erase(alt);
		Local_front.clear();
	}

}


bool Update_Archive(Alternative* p, list< Alternative* > set_SOL){

	for(list< Alternative* > alt = set_SOL.begin(); alt != set_SOL.end(); alt++){
		if((*alt)->dominates(p))
			return false;
	}

	for(list< Alternative* > alt_sol = set_SOL.begin(); alt_sol != set_SOL.end(); alt_sol++){
		if(p->dominates(*alt_sol))
			set_SOL.erase(alt_sol);
	}

	set_SOL.push_back(p);

	return true;
}















