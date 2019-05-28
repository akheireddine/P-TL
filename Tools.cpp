


#include "Tools.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <ilcplex/ilocplex.h>
#include <cstdlib>      // std::rand, std::srand



void Tools::skip(list< set< int > > &list_skiper, int n){
	for(int i = 0; i < n ; i++){
		set<int> val = list_skiper.front();
		list_skiper.pop_front();
		list_skiper.push_back(val);
	}
}

float Tools::euclidian_distance(vector<float> v1, vector<float> v2){
	float dist = 0;

	for(int i = 0; i < (int)v1.size(); i++)
		dist += ((v1[i] - v2[i]) * (v1[i] - v2[i]));

	dist = sqrt(dist);

	return dist;
}


float Tools::get_ratio(vector<float> v, vector<float> v_opt, vector<float> weights){
	float v_w = 0, v_w_opt = 0;
	for(int i = 0; i < (int)weights.size(); i++){
		v_w += weights[i] * v[i];
		v_w_opt += weights[i] * v_opt[i];
	}
	return (v_w_opt - v_w)/v_w_opt;                            //VALEURS POSITIVE
}


bool Tools::equal_vectors(vector<float> v1, vector<float> v2){
	for(int i = 0; i < (int)v1.size(); i++)
		if ( abs(v1[i] -  v2[i]) > 0.001 )
			return false;
	return true;
}


vector< float > Tools::decompose_line_to_float_vector(string line){

	char *cline = new char[line.length() + 1];
	int i = 0;
	vector< float > vect;
	strcpy(cline, line.c_str());

	char * pch = strtok (cline," 	,;");
	while (pch != NULL ){
		vect.push_back(atof(pch));
		pch = strtok (NULL, " 	,;");
		i++;
	}

//	delete [] cline;
//	delete [] pch;

	return vect;
}

string Tools::print_vector(vector<float> v){
	string str ="";
	for(int i = 0 ; i < (int)v.size(); i++)
		str += to_string(v[i]) + " ";

	return str;
}


vector<float> Tools::generate_random_WS_aggregator(int n_w){

	float sum = 0;
	vector<float> weighted_sum;
//	srand(time(NULL));

	if(n_w == 2){
		float wi = rand()*1.0/RAND_MAX;

		weighted_sum.push_back(wi);
		weighted_sum.push_back(1.0 - wi);
		return weighted_sum;
	}

	for(int i =0; i < n_w - 1; i++){
		float wi = rand()*1.0/RAND_MAX;

		while(wi + sum > 1){
			wi = rand();
		}

		sum += wi;
		weighted_sum.push_back(wi);
	}

	weighted_sum.push_back(1.0 - sum);

	return weighted_sum;
}


void Tools::generate_random_WS(string filename, int nb_criteria){

	vector<float > weighted_sum = generate_random_WS_aggregator(nb_criteria);

	ofstream fic(filename.c_str());


	for(int i = 0; i < (int)weighted_sum.size(); i++)
		fic<<weighted_sum[i]<<endl;

	fic.close();

}



void Tools::compute_average_column_files(string filename, int nb_column){

	vector< float > avg_columns(nb_column,0);
	int cpt = 0;
	ifstream fic(filename.c_str());
	string line;

	while(!fic.eof()){

		getline(fic,line);
		if (line.size() == 0)
			continue;

		vector< float > vect_line = decompose_line_to_float_vector(line);

		for(int i = 0; i < nb_column; i++)
			avg_columns[i] += vect_line[i];

		cpt++;
	}

	fic.close();



	ofstream fic_write(filename.c_str(), ios::app);
	fic_write<<"________________________"<<endl;
	for(int i = 0; i < nb_column; i++){
		avg_columns[i] = avg_columns[i]*1.0/cpt;
		fic_write<<to_string(avg_columns[i])<<" ";
	}

	fic_write<<endl;

	fic_write.close();
}

void Tools::update_dist_time(float dist_min,float time){
	Tools::dist_time_avg[0] += dist_min*100;
	Tools::dist_time_avg[1] += time;

	Tools::cpt_count++;


}

void Tools::update_indicators(float D1, float D2, float D3){
//	cout<<"BEF D1 : "<<Tools::indicator_avg[0]<<endl;

	Tools::indicator_avg[0] += D1;
	Tools::indicator_avg[1] += D2;
	Tools::indicator_avg[2] += D3;


}

void Tools::add_dist_to_OPT(float ratio){

	ratios_dist_to_OPT.push_back(ratio);
}


void Tools::save_std_deviation(string filename){
	ofstream fic_write(filename.c_str(), ios::app);

	float avg_ratio = accumulate(ratios_dist_to_OPT.begin(), ratios_dist_to_OPT.end(), 0) / ratios_dist_to_OPT.size() * 1.0;

	if(ratios_dist_to_OPT.size() == 0){
		fic_write<<"-nan"<<endl;
		fic_write.close();
		Tools::ratios_dist_to_OPT.clear();
		return;
	}


	float val = 1.0/ratios_dist_to_OPT.size();

	for(int i = 0; i < (int)ratios_dist_to_OPT.size(); i++)
		val += ( ratios_dist_to_OPT[i] - avg_ratio ) * ( ratios_dist_to_OPT[i] - avg_ratio );

	fic_write<<sqrt(val)<<endl;
	fic_write.close();

	Tools::ratios_dist_to_OPT.clear();
}

void Tools::save_average_dist_time(string filename){

	ofstream fic_write(filename.c_str(), ios::app);
	for(int i = 0; i < (int)Tools::dist_time_avg.size(); i++){
		Tools::dist_time_avg[i] = Tools::dist_time_avg[i]*1.0/cpt_count;
		fic_write<<Tools::dist_time_avg[i]<<" ";
	}
	fic_write<<endl;
	fic_write.close();

	Tools::dist_time_avg.clear();
	Tools::dist_time_avg.resize(2,0);

}

void Tools::save_average_indicator(string filename){

	ofstream fic_write(filename.c_str(), ios::app);

	for(int i = 0; i < (int)indicator_avg.size(); i++){
		Tools::indicator_avg[i] = Tools::indicator_avg[i]*1.0/cpt_count;
		fic_write<<Tools::indicator_avg[i]<<" ";
	}
	fic_write<<endl;
	fic_write.close();


	Tools::indicator_avg.clear();
	Tools::indicator_avg.resize(3,0);



}


void Tools::separate_results(string filename, string separator){
	ofstream fic_write(filename.c_str(), ios::app);
	fic_write<<separator<<endl;
	fic_write.close();
}

void Tools::copy_into(string src_filename, string dest_filename){

	ifstream src(src_filename.c_str());
	ofstream dest(dest_filename.c_str());

	string line;

	while(!src.eof()){

		getline(src,line);
		dest<<line<<endl;
	}

	src.close();
	dest.close();
}




vector<float> Tools::generate_random_restricted_WS_aggregator(int p_criteria, vector< vector< float > > ws_matrix){
	float sum = 0.0, big_max = -1;
	vector<float> weighted_sum(p_criteria);
	vector<pair<float, float > > min_max(p_criteria,pair<float,float>());

	if(p_criteria == 2){
//		const auto [minus, maxus] = minmax_element(begin(ws_matrix[0]), end(ws_matrix[0]));
		float minus = *(min_element(ws_matrix[0].begin(), ws_matrix[0].end()) );
		float maxus = *(max_element(ws_matrix[0].begin(), ws_matrix[0].end()) );

		int rando = rand();

		float wi =  static_cast <float> (rando)*1.0 /( static_cast <float> (RAND_MAX / (maxus - minus ))) + minus ;
		weighted_sum[0] = wi ;
		weighted_sum[1] =  1.0 - wi ;
	}

	else{
		for(int i = 0; i < p_criteria ; i++){
			float minus = *(min_element(ws_matrix[0].begin(), ws_matrix[0].end()) );
			float maxus = *(max_element(ws_matrix[0].begin(), ws_matrix[0].end()) );

			min_max[i] = make_pair (minus, maxus);
		}

		for(int i =0; i < p_criteria ; i++){

			float wi =  static_cast <float> (rand())*1.0 /( static_cast <float> (RAND_MAX / (min_max[i].second - min_max[i].first))) + min_max[i].first ;
			for(int j = i+1; j < p_criteria ; j++){
				if( big_max < min_max[j].second or big_max==-1 )
					big_max = min_max[j].second;
			}
			while(  (1 - (wi+sum))  > big_max ){
				wi =  static_cast <float> (rand())*1.0 /( static_cast <float> (RAND_MAX / (min_max[i].second - min_max[i].first))) + min_max[i].first ;
			}

			sum += wi;
			weighted_sum[i] = wi;
		}
	}

//	cout<<print_vector(weighted_sum)<<endl;
	return weighted_sum;
}






vector<float> Tools::readWS_DM(string WS_DM_preferences){

	ifstream fic_read(WS_DM_preferences.c_str());
	string line;


	if (!(fic_read) or WS_DM_preferences.find(".ks") == std::string::npos){
		cerr<<"Error occurred readWS_DM"<<endl;
	}
	//read WS_DMs_preference
	getline(fic_read,line);

	return Tools::decompose_line_to_float_vector(line);

}







string Tools::decode_set_items(set<int> items, int nb_items){
	string s ="";
	for(int i = 0; i < nb_items; i++)
		s+= (items.find(i) != items.end())?"1":"0";

	return s;
}









//vector<float> Tools::generate_random_restricted_WS_aggregator_PL(int p_criteria, vector< vector< float > > ws_matrix){
//
//	IloEnv   env;
//	IloModel model(env);
//	vector<IloNumVar > w(p_criteria);
//	IloRangeArray Constraints(env);
//	vector<float> weighted_sum(p_criteria);
//
//	//VARIABLES
//	for(int i = 0; i < p_criteria; i++){
//
//		const auto [minus, maxus] = minmax_element(begin(ws_matrix[i]), end(ws_matrix[i]));
//		w[i] = IloNumVar(env,*minus, *maxus, ILOFLOAT);
//		ostringstream varname;
//		varname.str("");
//		varname<<"w_"<<i;
//		w[i].setName(varname.str().c_str());
//	}
//
//	//CONSTRAINTS
//	IloExpr c1(env);
//
//	for(int j = 0; j < p_criteria ; j++)
//		c1 += w[j] ;
//	Constraints.add(c1 ==  1 );
//
//	model.add(Constraints);
//
//	//OBJECTIVE
////	IloObjective obj=IloAdd(model, IloMaximize(env));
//
////	cout<<obj<<endl;
//
//	//SOLVE
//	IloCplex cplex(model);
//
//	cplex.setOut(env.getNullStream());
//
//	if ( !cplex.solve() ) {
//		 env.error() << "Failed to optimize WEIGHTS LP" << endl;
//		 exit(1);
//	}
//
//	//GET SOLUTION
//	for(int i = 0; i < p_criteria; i++){
//			weighted_sum[i] = cplex.getValue(w[i])  ;
//	}
//	env.end();
//
////	cout<<"----------------------"<<endl<<"WEIGHTED SUM PL ["<<print_vector(weighted_sum)<<"]"<<endl<<"----------------------"<<endl;
//
//	return weighted_sum;
//
//
//}



