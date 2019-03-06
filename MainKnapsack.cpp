
#include <set>
#include "MainKnapsack.h"



#include <sstream>      // std::ostringstream

MainKnapsack::MainKnapsack(string filename, string pref_filename, string init_population_filename){

	filename_instance = filename;

	readFilenameInstance(filename_instance);

	readWS_Matrix(pref_filename);

	readInitPopulationFile(init_population_filename);


}


void MainKnapsack::readInitPopulationFile(string filename){

	ifstream fic(filename.c_str());


	if (!(fic) or filename.find(".ks") == std::string::npos){
		cerr<<"Error occurred"<<endl;
	}

	string line;
	float total_weight;

	while(!fic.eof()){
		total_weight = 0;
		getline(fic,line);

		set<int> set_items;
		char *cline = new char[line.length() + 1];
		std::strcpy(cline, line.c_str());

		char * pch = strtok (cline," 	,");
		while (pch != NULL){
			set_items.insert(atoi(pch));
			total_weight += std::get<0>(Items_information[atoi(pch)]);
			pch = strtok (NULL, " 	,");
		}

		if(total_weight > Backpack_capacity){
			cerr<<"Not feasable initialization"<<endl;
			exit(1);
		}

		AlternativeKnapsack* alt = new AlternativeKnapsack(set_items, this);
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

	if (!(fic) or filename.find(".dat") == std::string::npos){
		cerr<<"Error occurred"<<endl;
	}


	//comments
	getline(fic,line);
	while( line[0] == 'c' )
		getline(fic,line);

	//number of items
	n_items = 0;
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
	p_criteria = 0;
	p_criteria = line_value.size();

	//comments
	while( line[0] == 'c' )
		getline(fic,line);


	//total capacity
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

	WS_matrix.resize(p_criteria,vector< float >());

	while( !fic.eof() and i < p_criteria){

		getline(fic,line);

		char *cline = new char[line.length() + 1]; // or
		std::strcpy(cline, line.c_str());

		char * pch = strtok (cline," 	,;");
		while (pch != NULL){
			WS_matrix[i].push_back(atof(pch));
			pch = strtok (NULL, " 	,;");
		}
		i++;
	}

	n_objective = WS_matrix[0].size();


}


void MainKnapsack::write_solution(){

	ostringstream FileName;
	FileName.str("");
	FileName <<filename_instance.c_str() << ".sol";
	ofstream fic(FileName.str().c_str());

	for(list< Alternative *>::iterator alt = OPT_Solution.begin(); alt != OPT_Solution.end(); alt++){
		for(int i = 0; i < n_objective; i++)
			fic<< (*alt)->get_objective_values()[i]<< " ";
		fic <<endl;
	}
}


list< Alternative * > MainKnapsack::MOLS(){

	Alternative* alt;
	list< Alternative* > Local_front;
	//First initialization
	for(list< Alternative* >::iterator p = Population.begin(); p != Population.end(); ++p){
		Update_Archive(*p,OPT_Solution);
	}

	while(Population.size() > 0){

		cout<<"Population : "<< Population.size()<<endl;
		//erase the first element
		alt = Population.front();

		vector<Alternative *> current_neighbors = alt->get_neighborhood();

		for(vector< Alternative* >::iterator neighbor = current_neighbors.begin(); neighbor != current_neighbors.end(); ++neighbor){

			cout<<"STARTING ERROR"<<endl;

			if( alt->dominates(*neighbor) != 1 ){
//				cout<<"1 NOT DOMINATE 2"<<endl;
				Update_Archive(*neighbor,Local_front);
			}

//			alt->print_objective_values();
//			cout<<"  VS  ";
//			(*neighbor)->print_objective_values();
		}

		for(list< Alternative* >::iterator new_alt = Local_front.begin(); new_alt != Local_front.end(); new_alt++){
			if ( Update_Archive(*new_alt, OPT_Solution) )
				Population.push_back(*new_alt);
		}
		Population.pop_front();
		Local_front.clear();

	}


	write_solution();

	return OPT_Solution;
}


bool MainKnapsack::Update_Archive(Alternative* p, list< Alternative* > &set_SOL){

	for(list< Alternative* >::iterator alt = set_SOL.begin(); alt != set_SOL.end(); ++alt){
		int dom_val = (*alt)->dominates(p);
		if(dom_val == 1)			// alt dominates p
			return false;
		else if( dom_val == -1 )   // p dominates alt
			set_SOL.remove(*alt);
	}

//	for(list< Alternative* >::iterator alt_sol = set_SOL.begin(); alt_sol != set_SOL.end(); ++alt_sol){
//		if(p->dominates(*alt_sol))
//			set_SOL.erase(alt_sol);
//	}

	set_SOL.push_back(p);
	cout<<" AFTER ADD SIZE : "<<set_SOL.size()<<endl;

	return true;
}















