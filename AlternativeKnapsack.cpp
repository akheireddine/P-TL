


#include "AlternativeKnapsack.h"
#include "MainKnapsack.h"


using namespace std;


AlternativeKnapsack::AlternativeKnapsack(set<int> items, MainKnapsack* mStruct){

	mainLSStructure = mStruct;
	neighborhood.clear();
	alternatives.resize(mainLSStructure->get_n_items(),0);
	criteria_values.resize(mainLSStructure->get_p_criteria(), 0);
	objective_values.resize(mainLSStructure->get_n_objective(), 0);


	vector< vector < float > > WS_matrix = mainLSStructure->get_WS_matrix();

	for(set<int>::iterator o = items.begin(); o != items.end(); ++o){

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

/**
 * 1  current alternative dominates paramter alt
 * 0  incomparable
 * -1 paramter alt dominates current alternative
 */
int AlternativeKnapsack::dominates(Alternative* alt){

	int i = 0;
	vector< float > obj_alt = alt->get_objective_values();

	for(i = 0; i < objective_values.size(); i++){
		if( objective_values[i] < obj_alt[i] and (i > 0))									// MAXIMIZATION DES OBJECTIFS ! ! !
			return -1;
	}
	if (i == objective_values.size())
		return 0;
	return 1;
}



vector< Alternative* > AlternativeKnapsack::get_neighborhood(){

	if(neighborhood.size() > 0)
		return neighborhood;

	vector< int > In_BP, Out_BP;

	for(int i = 0; i < alternatives.size(); i++){
		if( alternatives[i] == 1)
			In_BP.push_back(i);
		else
			Out_BP.push_back(i);
	}


	for(vector< int >::iterator in = In_BP.begin(); in != In_BP.end(); in++){									//REMOVE ITEM

		set<int> set_neighbor(In_BP.begin(),In_BP.end());         // OOU   std::set<int> first (myints,myints+5);   // set with 5 ints
		float weight_neighbor = weight - mainLSStructure->get_weight_of(*in);

		set_neighbor.erase(*in);


		for(int i = 0; i < Out_BP.size(); i++){																// ADD ITEM UNTILL FULL

			set< int > fill_bp(set_neighbor.begin(), set_neighbor.end());
			float weight_alt = weight_neighbor;

			if( weight_alt + mainLSStructure->get_weight_of(Out_BP[i]) > mainLSStructure->get_capacity())
				continue;

			fill_bp.insert(Out_BP[i]);
			weight_alt += mainLSStructure->get_weight_of(Out_BP[i]);

			for(int j = i + 1; j < Out_BP.size(); j++){

				if( weight_alt + mainLSStructure->get_weight_of(Out_BP[j]) > mainLSStructure->get_capacity())
						continue;

				fill_bp.insert(Out_BP[j]);
				weight_alt += mainLSStructure->get_weight_of(Out_BP[j]);
			}

			AlternativeKnapsack* alt = new AlternativeKnapsack(fill_bp, mainLSStructure);
			neighborhood.push_back(alt);

		}
	}



	return neighborhood;
}









//void copy_alternative(vector<int> src, vector<int> &dest){
//	dest.resize(src.size(),0);
//	for(int i = 0; i < src.size(); i++)
//		dest[i] = src[i];
//}









