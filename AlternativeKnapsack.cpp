


#include "Alternative.h"



AlternativeKnapsack::AlternativeKnapsack(Set<int> objects, MainKnapsack * mknapsack){

	mainKnapsack = mknapsack;
	neighborhood.clean();
	alternative.resize(mknapsack.get_n_items(),0);

	for(Set<int>::iterator o = objects.begin(); o != objects.end(); o++){
		alternative[*o] = 1;
		weight += mknapsack.get_weight_of(*o);
		for(int i = 0; i < mknapsack.get_p_criteria(); i++){
			criteria_values[i] += mknapsack.get_utility(*o,i);
		}
	}

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
