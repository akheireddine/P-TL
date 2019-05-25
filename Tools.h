#ifndef __TOOLS__
#define __TOOLS__

#include <math.h>
#include <stdio.h>
#include <cstring>
#include <string>
#include <vector>
#include <ostream>
#include <fstream>
#include <set>
#include <list>
#pragma once




using namespace std;


class Tools{



public:

	static vector< float > dist_time_avg;
	static vector< float > indicator_avg;
	static int cpt_count;
	static vector< float > ratios_dist_to_OPT;


	static float euclidian_distance(vector<float> v1, vector<float> v2);
	static float get_ratio(vector<float> v, vector<float> v_opt, vector<float> weights);
	static bool equal_vectors(vector<float> v1, vector<float> v2);
	static vector< float > decompose_line_to_float_vector(string line);
	static string print_vector(vector<float> v);
	static vector<float> generate_random_WS_aggregator(int n_w);
	static void generate_random_WS(string filename, int nb_criteria);
	static void compute_average_column_files(string filename, int nb_column);
	static void copy_into(string src_filename, string dest_filename);
	static void save_average_dist_time(string filename);
	static void save_average_indicator(string filename);
	static void update_dist_time(float dist_min,float time);
	static void update_indicators(float D1, float D2, float D3);
	static void separate_results(string filename, string separator);
	static vector<float> readWS_DM(string WS_DM_preferences);
	static vector<float> generate_random_restricted_WS_aggregator(int p_criteria, vector< vector< float > > ws_matrix);
	static string decode_set_items(set<int> items, int nb_items);

	static void skip(list< set< int > > & list_skiper, int n);


	static void add_dist_to_OPT(float ratio);
	static void save_std_deviation(string filename);


//	static void save_information_in(string filename, string smthing);
//	static vector<float> generate_random_restricted_WS_aggregator_PL(int p_criteria, vector< vector< float > > ws_matrix);


};

#endif
