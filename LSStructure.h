
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

public:

	virtual void readFilenameInstance(string filename) = 0;
	virtual void readWS_Matrix(string filename) = 0;
	virtual list< Alternative * > MOLS(double START_TIME) = 0;
	virtual void write_solution() = 0;

	//GETTERS
	int get_p_criteria(){ return p_criteria; };
	int get_n_objective(){ return n_objective; };
	vector< vector< float > > get_WS_matrix(){ return WS_matrix; };

};




#endif
