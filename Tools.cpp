


#include "Tools.h"
#include <iostream>



float Tools::euclidian_distance(vector<float> v1, vector<float> v2){
	float dist = 0;

	for(int i = 0; i < v1.size(); i++)
		dist += (v1[i] - v2[i]) * (v1[i] - v2[i]);

	dist = sqrt(dist);

	return dist;
}


float Tools::get_ratio(vector<float> v, vector<float> v_opt, vector<float> weights){
	float v_w = 0, v_w_opt = 0;
	for(int i = 0; i < weights.size(); i++){
		v_w += weights[i] * v[i];
		v_w_opt += weights[i] * v_opt[i];
	}
	return (v_w_opt - v_w)/v_w_opt;                            //VALEURS POSITIVE
}


bool Tools::equal_vectors(vector<float> v1, vector<float> v2){
	for(int i = 0; i < v1.size(); i++)
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
	for(int i = 0 ; i < v.size(); i++)
		str += to_string(v[i]) + " ";

	return str;
}


vector<float> Tools::generate_random_WS_aggregator(int n_w){

	float sum = 0;
	vector<float> weighted_sum;
//	srand(time(NULL));

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


	for(int i = 0; i < weighted_sum.size(); i++)
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

	Tools::cpt++;
}

void Tools::update_indicators(float D1, float D2, float D3){
	Tools::indicator_avg[0] += D1;
	Tools::indicator_avg[1] += D2;
	Tools::indicator_avg[2] += D3;
}


void Tools::save_average_dist_time(string filename){

	ofstream fic_write(filename.c_str(), ios::app);
	for(int i = 0; i < Tools::dist_time_avg.size(); i++){
		Tools::dist_time_avg[i] = Tools::dist_time_avg[i]*1.0/cpt;
		fic_write<<Tools::dist_time_avg[i]<<" ";
	}
	fic_write<<endl;
	fic_write.close();

	Tools::dist_time_avg.clear();
}

void Tools::save_average_indicator(string filename){

	ofstream fic_write(filename.c_str(), ios::app);
	for(int i = 0; i < indicator_avg.size(); i++){
		Tools::indicator_avg[i] = Tools::indicator_avg[i]*1.0/cpt;
		fic_write<<Tools::indicator_avg[i]<<" ";
	}
	fic_write<<endl;
	fic_write.close();
	Tools::indicator_avg.clear();

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
