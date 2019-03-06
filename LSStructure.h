
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
	list< Alternative * > OPT_Solution;
	vector< vector < float > > WS_matrix;
	int n_objective;
	int p_criteria;
	list< Alternative* > Population;
	string filename_instance;

public:
	virtual void readFilenameInstance(string filename) = 0;
	virtual void readWS_Matrix(string filename) = 0;
	virtual list< Alternative * > MOLS() = 0;
	virtual void write_solution() = 0;



	int get_p_criteria(){ return p_criteria; };
	int get_n_objective(){ return n_objective; };
	vector< vector< float > > get_WS_matrix(){ return WS_matrix; };

};




#endif
