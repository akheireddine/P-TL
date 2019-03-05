


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

	vector< int > In_BP, Out_BP;

	for(int i = 0; i < alternatives.size(); i++){
		if( alternatives[i] == 1)
			In_BP.push_back(i);
		else
			Out_BP.push_back(i);
	}

	float weight_neighbor = weight;
	Set<int> set_neighbor;

	for(vector< int >::iterator in = In_BP.begin(); in != In_BP.end(); in++){									//REMOVE ITEM

		set_neighbor(In_BP.begin(),In_BP.end());         // OOU   std::set<int> first (myints,myints+5);   // set with 5 ints
		weight_neighbor = weight - mainLSStructure->get_weight_of(*in);
		set_neighbor.erase(*in);


		for(int i = 0; i < Out_BP.size(); i++){																// ADD ITEM UNTILL FULL

			Set< int > fill_bp(set_neighbor.begin(), set_neighbor.end());
			float weight_alt = weight_neighbor;

			if( weight_alt + mainLSStructure->get_weight_of(Out_BP[i]) > main.LSStructure->get_capacity())
				continue;

			fill_bp.push_back(Out_BP[i]);
			weight_alt += mainLSStructure->get_weight_of(Out_BP[i]);

			for(int j = i + 1; j < Out_BP.size(); j++){

				if( weight_alt + mainLSStructure->get_weight_of(Out_BP[j]) > main.LSStructure->get_capacity())
						continue;

				fill_bp.push_back(Out_BP[j]);
				weight_alt += mainLSStructure->get_weight_of(Out_BP[j]);
			}

			Alternative *alt = AlternativeKnapsack(fill_bp, mainLSStructure);
			neighborhood.push_back(alt);

		}
	}








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

	if(weight == mainLSStructure->get_capacity())
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
