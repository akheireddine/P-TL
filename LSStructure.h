
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


#include "Alternative.h"


using namespace std;




class LSStructure {

protected :

	list< Alternative * > OPT_Solution;              //SAVE OPT FRONT FOUND
	vector< vector < float > > WS_matrix;			// matrix A  of aggreation functions
	int n_objective;
	int p_criteria;									// Number of criteria
	list< Alternative* > Population;				// current set of non-dominated alternatives during the solving process
	string filename_instance;					    // instance pathname
	string num_instance;
	string type_instance;

public:
//	~LSStructure(){
//		for(list< Alternative* >::iterator i = OPT_Solution.begin(); i != OPT_Solution.end(); ++i){ delete (*i);}
//		for(list< Alternative* >::iterator i = Population.begin(); i != Population.end(); ++i){ delete (*i);}
//
//	};

	virtual void readFilenameInstance(string filename) = 0;
	virtual void readWS_Matrix(string filename) = 0;
	virtual list< Alternative * > MOLS(double starting_time_sec) = 0;
	virtual void write_solution(string filename) = 0;
	virtual void GenerateInitialPopulation(int size_population) = 0;

	//GETTERS
	int get_p_criteria(){ return p_criteria; };
	int get_n_objective(){ return n_objective; };
	string get_filename_isntance(){ return filename_instance; };
	vector< vector< float > > get_WS_matrix(){ return WS_matrix; };
	list<Alternative* > get_OPT_Solution(){ return OPT_Solution; };

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
