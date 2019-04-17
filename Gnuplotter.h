
#ifndef GNUPLOT_H
#define GNUPLOT_H

#include <string>


using namespace std;

#pragma once



class Gnuplotter{

public:
	static void Comparison_Plot_DIST_TIME(string filename1, string filename2,string type_inst, string size_inst,string t1, string t2);
	static void Comparison_Plot_INDICATORS(string filename1, string filename2,string type_inst, string size_inst);




};

#endif
