
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

using namespace std;


class LSStructure {
private :
	list< Alternative * > OPT_Solution;
	vector< vector < float >> WS_matrix;
	int n_objective;
	int p_criteria;
	list< Alternative* > Population;
	string filename_instance;

public:
	void readFilenameInstance(string filename);
	void readWS_Matrix(string filename);
	vector< Alternative * > MOLS();
	void write_solution(string filename_instance);



	int get_p_criteria(){ return p_criteria; };
	int get_n_objective(){ return n_objective; };
	vector< vector< float > > get_WS_matrix(){ return WS_matrix; };

};


#include "Alternative.h"


#endif
