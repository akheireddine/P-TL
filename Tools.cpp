


#include "Tools.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <ilcplex/ilocplex.h>
#include <cstdlib>      // std::rand, std::srand



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

	return vect;
}

string Tools::print_vector(vector<float> v){
	string str ="";
	for(int i = 0 ; i < (int)v.size(); i++)
		str += to_string(v[i]) + " ";

	return str;
}




void Tools::shuffle_list(list< string > & unshuffled_L){
	mt19937 g( rand() );

	vector<string> shuffled_L (unshuffled_L.begin(), unshuffled_L.end());
	shuffle(shuffled_L.begin(), shuffled_L.end(), g);

	unshuffled_L.clear();
	unshuffled_L.resize(0);

	for(int i = 0; i < (int)shuffled_L.size(); i++){
		unshuffled_L.push_back( shuffled_L[i] );
	}
}


//void Tools::save_std_deviation(string filename){
//	ofstream fic_write(filename.c_str(), ios::app);
//
//	float avg_ratio = accumulate(ratios_dist_to_OPT.begin(), ratios_dist_to_OPT.end(), 0) / ratios_dist_to_OPT.size() * 1.0;
//
//	if(ratios_dist_to_OPT.size() == 0){
//		fic_write<<"-nan"<<endl;
//		fic_write.close();
//		Tools::ratios_dist_to_OPT.clear();
//		return;
//	}
//
//
//	float val = 1.0/ratios_dist_to_OPT.size();
//
//	for(int i = 0; i < (int)ratios_dist_to_OPT.size(); i++)
//		val += ( ratios_dist_to_OPT[i] - avg_ratio ) * ( ratios_dist_to_OPT[i] - avg_ratio );
//
//	fic_write<<sqrt(val)<<"  ";
//
//
//	for(int i = 0; i < (int)Tools::dist_time_avg.size(); i++){
//		Tools::dist_time_avg[i] = Tools::dist_time_avg[i]*1.0/cpt_count;
//		fic_write<<Tools::dist_time_avg[i]<<"  ";
//	}
//	fic_write<<endl;
//
//	fic_write.close();
//
//	Tools::ratios_dist_to_OPT.clear();
//}



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



/***
 * **************************************************************************************************
 */


vector< float > Tools::transform(vector< float > src, vector< vector< float > > ws_matrix){
	vector< float > dest(src.size(),0);
	for(int i = 0; i < (int)ws_matrix[0].size(); i++){
		for(int j = 0; j < (int)src.size() ; j++){
			dest[i] += ws_matrix[j][i] * src[j];
		}
	}
	return dest;
}

bool Tools::in_search_space(vector<float> v,vector<float> minus, vector<float> maxus){
	for(int j = 0; j < (int)v.size(); j++)
		if( (v[j] < minus[j] )  or (v[j] > maxus[j]) )
				return false;
	return true;
}

/***
 * **************************************************************************************************
 */



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


vector<float> Tools::generate_random_restricted_WS_aggregator(int p_criteria, vector< vector< float > > ws_matrix){

	vector<float> weighted_sum(p_criteria);


	//mono-objective
	if(ws_matrix[0].size() == 1){
		for(size_t i = 0; i < ws_matrix[0].size(); i++)
		weighted_sum[i] = ws_matrix[0][i];
	}

	//more than one objective
	else if(p_criteria == 2){
//		const auto [minus, maxus] = minmax_element(begin(ws_matrix[0]), end(ws_matrix[0]));
		float minus = *(min_element(ws_matrix[0].begin(), ws_matrix[0].end()) );
		float maxus = *(max_element(ws_matrix[0].begin(), ws_matrix[0].end()) );

		int rando = rand();

		float wi =  static_cast <float> (rando)*1.0 /( static_cast <float> (RAND_MAX / (maxus - minus ))) + minus ;
		weighted_sum[0] = wi ;
		weighted_sum[1] =  1.0 - wi ;
	}

	else{

		vector< float > rand_value;
		vector< float > feasible_ws;

		for(int i = 0; i < p_criteria - 1; i++){
			float rando_val =  static_cast <float> (rand())*1.0 /( static_cast <float> (RAND_MAX) );
			rand_value.push_back( rando_val  );
		}
		rand_value.push_back(0); rand_value.push_back(1.);

		sort(rand_value.begin(), rand_value.end());

		for(size_t i = 0; i < rand_value.size() - 1; i++)
			feasible_ws.push_back( rand_value[i+1] - rand_value[i]);

		for(int i = 0; i < p_criteria; i++){
			float val = 0.;

			for(size_t j = 0; j < feasible_ws.size(); j++)
				val += ws_matrix[i][j] * feasible_ws[j] * 1.0;

			weighted_sum[i] = val ;
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


vector< vector< float > > Tools::readMatrix(string filename){

	char *cline, *pch;

	vector< vector <float > >WS_matrix;

	ifstream fic(filename.c_str());
	string line;

	if (!(fic) ){
		cerr<<"Error occurred readMatrix Tools"<<endl;
	}

	while( !fic.eof() ){

		getline(fic,line);

		cline = new char[line.length() + 1]; // or
		std::strcpy(cline, line.c_str());

		pch = strtok (cline," 	,;");

		vector< float > ws_line;

		while (pch != NULL){
			ws_line.push_back(atof(pch));
			pch = strtok (NULL, " 	,;");
		}
		if(ws_line.size() > 0)
			WS_matrix.push_back(ws_line);
	}


	return WS_matrix;
}






string Tools::decode_set_items(set<int> items, int nb_items){
	string s ="";
	for(int i = 0; i < nb_items; i++)
		s+= (items.find(i) != items.end())?"1":"0";

	return s;
}





int Tools::dominates(vector< float > e1, vector< float > e2){

	bool dominated = false, dominates = false;

	for(int i = 0; i < (int)e1.size() ; i++){
		if(e1[i] < e2[i])
			dominated = true;
		else if (e1[i] > e2[i])
			dominates = true;

		if(dominates and dominated)
			return 0;
	}
	if(dominated and !dominates)
		return -1;

	//dominates and !dominated  OR  !dominated and !dominates
	return 1;
}

















//void Tools::update_dist_time(float dist_min,float time){
//	Tools::dist_time_avg[0] += dist_min*100;
//	Tools::dist_time_avg[1] += time;
//
//	Tools::cpt_count++;
//
//
//}
//
//void Tools::update_indicators(float D1, float D2, float D3){
////	cout<<"BEF D1 : "<<Tools::indicator_avg[0]<<endl;
//
//	Tools::indicator_avg[0] += D1;
//	Tools::indicator_avg[1] += D2;
//	Tools::indicator_avg[2] += D3;
//
//
//}
//
//void Tools::add_dist_to_OPT(float ratio){
//
//	ratios_dist_to_OPT.push_back(ratio);
//}




//void Tools::save_average_dist_time(string filename){
//
//	ofstream fic_write(filename.c_str(), ios::app);
//	for(int i = 0; i < (int)Tools::dist_time_avg.size(); i++){
//		Tools::dist_time_avg[i] = Tools::dist_time_avg[i]*1.0/cpt_count;
//		fic_write<<Tools::dist_time_avg[i]<<" ";
//	}
//	fic_write<<endl;
//	fic_write.close();
//
//	Tools::dist_time_avg.clear();
//	Tools::dist_time_avg.resize(2,0);
//
//}

//void Tools::save_average_indicator(string filename){
//
//	ofstream fic_write(filename.c_str(), ios::app);
//
//	for(int i = 0; i < (int)indicator_avg.size(); i++){
//		Tools::indicator_avg[i] = Tools::indicator_avg[i]*1.0/cpt_count;
//		fic_write<<Tools::indicator_avg[i]<<" ";
//	}
//	fic_write<<endl;
//	fic_write.close();
//
//
//	Tools::indicator_avg.clear();
//	Tools::indicator_avg.resize(3,0);
//
//
//
//}



