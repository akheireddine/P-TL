

#include "AlternativeKnapsack.h"
#include "MainKnapsack.h"


using namespace std;

static int id = 0;


AlternativeKnapsack::AlternativeKnapsack(set<int> items, MainKnapsack* mStruct){
	id_alt = id++;
	mainLSStructure = mStruct;
	neighborhood.clear();
	alternatives.resize(mainLSStructure->get_n_items(),0);
	criteria_values.resize(mainLSStructure->get_p_criteria(), 0);
	objective_values.resize(mainLSStructure->get_n_objective(), 0);
	weight = 0;


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
			objective_values[i] += WS_matrix[j][i] * criteria_values[j];
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
	bool AdomB = false, BdomA = false;

	vector< float > obj_alt = alt->get_objective_values();

	for(i = 0; i < objective_values.size(); i++){

		if( objective_values[i] < obj_alt[i] )									// MAXIMIZATION DES OBJECTIFS ! ! !
			BdomA = true;

		else if ( objective_values[i] > obj_alt[i] )
			AdomB = true;

		if( AdomB and BdomA)
			return 0;
	}

	if ( BdomA and !AdomB)
		return -1;


	// AdomB and !BdomA   or   !AdomB and !BdomA
	return 1;
}



void AlternativeKnapsack::enumerate_neighborhood(set<int> & curr_BP, set<int> &item_OUT, float bp_weight, map< float, int, greater <float> > ratio_items){

	float BP_capacity = mainLSStructure->get_capacity();

	for(set<int>::iterator elem = item_OUT.begin(); elem != item_OUT.end(); ++elem){

		float weight_neighbor = bp_weight + mainLSStructure->get_weight_of(*elem);

		if ( weight_neighbor > BP_capacity)
			continue;

		set<int> new_neighbor(curr_BP.begin(),curr_BP.end());
		new_neighbor.insert(*elem);

		for(map<float,int, greater <float> >::iterator best_ratio = ratio_items.begin(); best_ratio != ratio_items.end(); ++best_ratio){
			int id_object = (*best_ratio).second;
			if( (id_object == *elem) or ((weight_neighbor + mainLSStructure->get_weight_of(id_object)) > BP_capacity))
				continue;
			new_neighbor.insert(id_object);
			weight_neighbor += mainLSStructure->get_weight_of(id_object);
		}

		AlternativeKnapsack * alt = new AlternativeKnapsack(new_neighbor, mainLSStructure );

		neighborhood.push_back(alt);

	}
}



vector< Alternative* > AlternativeKnapsack::get_neighborhood(){

	set< int > In_BP, Out_BP;
	map< float, int, greater <float> > ratio_items;

	for(int i = 0; i < alternatives.size(); i++){
		if( alternatives[i] == 1)
			In_BP.insert(i);
		else{
			Out_BP.insert(i);

			float aggregate_func_val_item = 0;
			for(int j = 0; j < mainLSStructure->get_p_criteria(); j++){
				aggregate_func_val_item += (1.0/mainLSStructure->get_p_criteria()) * mainLSStructure->get_utility(i,j);
			}
			float val_key = aggregate_func_val_item / mainLSStructure->get_weight_of(i);
			ratio_items[val_key] = i;
		}
	}

	for(set< int >::iterator in = In_BP.begin(); in != In_BP.end(); ++in){
		float new_weight = weight - mainLSStructure->get_weight_of(*in);
		set< int > in_tmp(In_BP.begin(),In_BP.end());

		in_tmp.erase(*in);
		enumerate_neighborhood(in_tmp,Out_BP, new_weight, ratio_items);
	}



	return neighborhood;
}


































