


#include "Alternative.h"



AlternativeKnapsack::AlternativeKnapsack(Set<int> items, MainKnapsack * mknapsack){

	mainLSStructure = mknapsack;
	neighborhood.clear();
	alternatives.resize(mainLSStructure->get_n_items(),0);
	criteria_values.resize(mainLSStructure->get_p_criteria(), 0);
	objective_values.resize(mainLSStructure->get_n_objective(), 0);

	WS_matrix = mainLSStructure->get_WS_matrix();

	for(Set<int>::iterator o = items.begin(); o != items.end(); o++){
		alternatives[*o] = 1;
		weight += mainLSStructure->get_weight_of(*o);
		for(int i = 0; i < mainLSStructure->get_p_criteria(); i++){
			criteria_values[i] += mainLSStructure->get_utility(*o,i);
		}
	}

	for(int i = 0; i < mainLSStructure->get_n_objective(); i++){
		for(int j = 0; j < mainLSStructure->get_p_criteria(); j++){
			objective_values[i] += WS_matrix[i][j] * criteria_values[j];
		}
	}

}

bool AlternativeKnapsack::dominates(Alternative* alt){

	vector<float> ob_alt = alt->get_objective_values();

	for(int i = 0; i < objective_values.size(); i++){
		if( objective_values[i] < ob_alt[i])											// MAXIMIZATION DES OBJECTIFS ! ! !
			return false;
	}
	return true;
}



vector< AlternativeKnapsack * > AlternativeKnapsack::get_neighborhood(){
	if(neighborhood.size() > 0)
		return neighborhood;

	add_object_neighborhood();
	remove_object_neighborhood();

	return neighborhood;
}

void copy_alternative(vector<int> src, vector<int> &dest){
	dest.resize(src.size(),0);
	for(int i = 0; i < src.size(); i++)
		dest[i] = src[i];
}

void remove_object_neighborhood(){



}

void add_object_neighborhood(){

	if(weight >= Backpack_weight)
		return;
//
//	vector< int > alternative_neighbor(n_objects,0);
//	copy_alternative(alternative,alternative_neighbor);
//	int weight_neighbor = weight;
//
//	for(int i = 0; i < n_objects; i++){
//
//		alternative_neighbor[i] = alternative[i];
//
//		if( (alternative_neighbor[i] == 1) or ( (weight_neighbor + Object_information[i]["weight"]) > Backpack_weight) )
//			continue;
//
//		alternative_neighbor[i] = 1;
//		weight_neighbor += Object_information[i]["weight"];
//
//		for(int j = i + 1; j < n_objects; j++){
//			if( alternative_neighbor[j] != 1 and (weight_neighbor + Object_information[j]["weight"]) <= Backpack_weight){
//				alternative[j] = 1;
//				weight_neighbor += Object_information[j]["weight"];
//			}
//		}
//	}
}
