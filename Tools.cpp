


#include "Tools.h"


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
	srand(time(NULL));


	for(int i =0; i < n_w - 1; i++){
		float wi = rand()*1.0/RAND_MAX;

		while(wi + sum > 1){
			wi = rand();
		}

		sum += wi;
		weighted_sum.push_back(wi);
	}

	weighted_sum.push_back(1 - sum);

	return weighted_sum;
}




void Tools::generate_random_WS(string filename, int nb_criteria){

	vector<float > weighted_sum = generate_random_WS_aggregator(nb_criteria);

	ofstream fic(filename);
	for(int i = 0; i < weighted_sum.size(); i++)
		fic<<weighted_sum[i]<<endl;

	fic.close();

}





