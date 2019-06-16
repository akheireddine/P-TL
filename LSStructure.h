
#ifndef ___LocalSearchStruct___
#define ___LocalSearchStruct___


#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <list>
#include <memory>

#include "Alternative.h"

class Evaluator;

#include "Evaluator.h"



using namespace std;




class LSStructure {

protected :

	list< shared_ptr<Alternative> > Archive;              //current Archive
	list< vector< float > > OPT_Solution;
	vector< vector < float > > WS_matrix;			// matrix A  of aggreation functions
	int n_objective;
	int p_criteria;									// Number of criteria
	list< string > Population;				// current set of non-dominated alternatives during the solving process
	string filename_population;					    // instance pathname

public:
	virtual ~LSStructure(){
		for(int i = 0; i < (int) WS_matrix.size(); i++){
			WS_matrix[i].clear();
			WS_matrix[i].shrink_to_fit();
		}
		WS_matrix.clear();
		WS_matrix.shrink_to_fit();

		for(list< shared_ptr< Alternative > > ::iterator it = Archive.begin(); it != Archive.end(); ++it){
			(*it).reset();
		}

		Archive.clear();
		Population.clear();
		OPT_Solution.clear();
	};

	void initializeInformation(shared_ptr< Evaluator > evaluator);
	virtual void MOLS(double starting_time_sec) = 0;
	virtual void GenerateInitialPopulation(int size_population) = 0;

	//GETTERS
	int get_p_criteria(){ return p_criteria; };
	int get_n_objective(){ return n_objective; };
	string get_filename_instance(){ return filename_population; };
	vector< vector< float > > get_WS_matrix(){ return WS_matrix; };
	list< vector< float > > get_OPT_Solution(){ return OPT_Solution; };

	inline void change_to_pareto_selection(){

		WS_matrix.resize(p_criteria,vector< float >());
		n_objective = p_criteria;
		for(int i = 0 ; i < p_criteria; i++){
			WS_matrix[i].clear();
			for(int j = 0; j < p_criteria; j++){
				if( i == j)
					WS_matrix[i].push_back(1.);
				else
					WS_matrix[i].push_back(0.);
			}
		}

	};


};




#endif
