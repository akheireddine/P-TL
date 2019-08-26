

#include "AlternativeKnapsack.h"
#include "MainKnapsack.h"

using namespace std;




AlternativeKnapsack::AlternativeKnapsack(set<int> items, MainKnapsack * mStruct, vector< vector<float > > WS_matrix){

	id_alt = Tools::decode_set_items(items,mStruct->get_n_items());
	mainLSStructure = mStruct;
	nb_objective = WS_matrix[0].size();
	local_WS_matrix = WS_matrix;

	neighborhood.clear();
	criteria_values.resize(mainLSStructure->get_p_criteria(), 0);
	objective_values.resize( nb_objective , 0);
	weight = 0;

	for(set<int>::iterator o = items.begin(); o != items.end(); ++o){

		weight += mainLSStructure->get_weight_of(*o);

		for(int i = 0; i < mainLSStructure->get_p_criteria(); i++){
			criteria_values[i] += mainLSStructure->get_utility(*o,i);
		}
	}

	for(int i = 0; i <nb_objective; i++){
		for(int j = 0; j < mainLSStructure->get_p_criteria(); j++){
			objective_values[i] += local_WS_matrix[j][i] * criteria_values[j];
		}
	}

}


AlternativeKnapsack::AlternativeKnapsack(string id_alternative, MainKnapsack * mStruct, vector< vector<float > > WS_matrix){

	id_alt = id_alternative;
	set<int> items;
	for(int i = 0; i < (int)id_alternative.length(); i++)
		if(id_alternative[i] == '1')
			items.insert(i);

	mainLSStructure = mStruct;
	nb_objective = WS_matrix[0].size();
	local_WS_matrix = WS_matrix;

	neighborhood.clear();
	criteria_values.resize(mainLSStructure->get_p_criteria(), 0);
	objective_values.resize( nb_objective , 0);
	weight = 0;

	for(set<int>::iterator o = items.begin(); o != items.end(); ++o){

		weight += mainLSStructure->get_weight_of(*o);

		for(int i = 0; i < mainLSStructure->get_p_criteria(); i++){
			criteria_values[i] += mainLSStructure->get_utility(*o,i);
		}
	}

	for(int i = 0; i <nb_objective; i++){
		for(int j = 0; j < mainLSStructure->get_p_criteria(); j++){
			objective_values[i] += local_WS_matrix[j][i] * criteria_values[j];
		}
	}

}





//LOCAL WS and ARCHIVE
AlternativeKnapsack::AlternativeKnapsack(string id_alternative, MainKnapsack * mStruct, vector< vector<float > > WS_matrix, list< shared_ptr< Alternative > > Archive){

	id_alt = id_alternative;
	set<int> items;
	for(int i = 0; i < (int)id_alternative.length(); i++)
		if(id_alternative[i] == '1')
			items.insert(i);

	mainLSStructure = mStruct;
	nb_objective = WS_matrix[0].size();
	local_WS_matrix = WS_matrix;
	local_Archive = Archive;

	neighborhood.clear();
	criteria_values.resize(mainLSStructure->get_p_criteria(), 0);
	objective_values.resize( nb_objective , 0);
	weight = 0;

	for(set<int>::iterator o = items.begin(); o != items.end(); ++o){

		weight += mainLSStructure->get_weight_of(*o);

		for(int i = 0; i < mainLSStructure->get_p_criteria(); i++){
			criteria_values[i] += mainLSStructure->get_utility(*o,i);
		}
	}

	for(int i = 0; i <nb_objective; i++){
		for(int j = 0; j < mainLSStructure->get_p_criteria(); j++){
			objective_values[i] += local_WS_matrix[j][i] * criteria_values[j];
		}
	}

}



void AlternativeKnapsack::set_local_WS_matrix(vector<vector<float > > matrix){
	local_WS_matrix = matrix;
	nb_objective = local_WS_matrix[0].size();
	update_objective_vector();
}

void AlternativeKnapsack::update_objective_vector(){

	objective_values.clear();
	objective_values.resize(nb_objective, 0);

	for(int i = 0; i < nb_objective; i++){
		for(int j = 0; j < mainLSStructure->get_p_criteria(); j++){
			objective_values[i] += local_WS_matrix[j][i] * criteria_values[j];
		}
	}
}


int AlternativeKnapsack::dominates_objective_space(shared_ptr< Alternative > alt){

	bool AdomB = false, BdomA = false;

	vector< float > obj_alt = alt->get_objective_values();

	for(int i = 0; i < (int)objective_values.size(); i++){

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


int AlternativeKnapsack::dominates_decision_space(shared_ptr< Alternative > alt){

	bool AdomB = false, BdomA = false;
	int i = 0;

	vector< float > crit_alt = alt->get_criteria_values();

	for(i = 0; i < mainLSStructure->get_p_criteria(); i++){

		if( criteria_values[i] < crit_alt[i] )									// MAXIMIZATION DES OBJECTIFS ! ! !
			BdomA = true;

		else if ( criteria_values[i] > crit_alt[i] )
			AdomB = true;

		if( AdomB and BdomA)
			return 0;
	}

	if ( BdomA and !AdomB)
		return -1;


	// AdomB and !BdomA   or   !AdomB and !BdomA
	return 1;
}


void AlternativeKnapsack::enumerate_neighborhood(set<int> curr_BP, set<int> item_OUT,  float bp_weight, map< float, int, greater <float> > ratio_items){

	float weight_neighbor = bp_weight ;
	float BP_capacity = mainLSStructure->get_capacity();
	int id_object;


	for(set<int>::iterator elem = item_OUT.begin(); elem != item_OUT.end(); ++elem){

		weight_neighbor = bp_weight;

		set<int> new_neighbor(curr_BP.begin(),curr_BP.end());

		if ( weight_neighbor + mainLSStructure->get_weight_of(*elem) <= BP_capacity ){
			weight_neighbor += mainLSStructure->get_weight_of(*elem);
			new_neighbor.insert(*elem);
		}

		for(map<float,int, greater <float> >::iterator best_ratio = ratio_items.begin(); best_ratio != ratio_items.end(); ++best_ratio){

			id_object = (*best_ratio).second;

			if( (id_object == *elem) or ((weight_neighbor + mainLSStructure->get_weight_of(id_object)) > BP_capacity))
				continue;

			new_neighbor.insert(id_object);
			weight_neighbor += mainLSStructure->get_weight_of(id_object);
		}
//		AlternativeKnapsack * alt = new AlternativeKnapsack(new_neighbor, mainLSStructure, local_WS_matrix );

		string alt = Tools::decode_set_items(new_neighbor,mainLSStructure->get_n_items());

		neighborhood.insert(alt);
	}

}



map< float, int, greater <float> > AlternativeKnapsack::generate_ordered_ratio_items(set<int> set_items){

	map< float, int, greater <float> > ratio_items;

	//RANDOM WEIGHTS
	vector<float> ws_aggr_utility = Tools::generate_random_WS_aggregator(mainLSStructure->get_p_criteria());

	//EQ TO DM PREFERENCES
//	vector<float> ws_aggr_utility = Tools::readWS_DM("weighted_DM_preferences.ks");



	//IN DOMAIN DEFINITION
//	vector<float> ws_aggr_utility = Tools::generate_random_restricted_WS_aggregator(mainLSStructure->get_p_criteria(), local_WS_matrix);
//	vector<float> ws_aggr_utility = Tools::generate_random_restricted_WS_aggregator_PL(mainLSStructure->get_p_criteria(), local_WS_matrix);





//	cout<<"______________"<<endl;
//	cout<<Tools::print_vector(ws_aggr_utility)<<endl;
//	cout<<"______________="<<endl;
	for(set<int>::iterator i = set_items.begin(); i != set_items.end(); ++i){

		float aggregate_func_val_item = 0;

		for(int j = 0; j < (int)ws_aggr_utility.size(); j++)
			aggregate_func_val_item += ws_aggr_utility[j] * mainLSStructure->get_utility(*i,j);

		float val_key = aggregate_func_val_item / mainLSStructure->get_weight_of(*i)*1.0;
		ratio_items[val_key] = *i;
	}

	return ratio_items;
}



set< string > AlternativeKnapsack::get_neighborhood(){

	set< int > In_BP, Out_BP;

	for(int i = 0; i < mainLSStructure->get_n_items(); i++){
		if( id_alt[i] == '1')
			In_BP.insert(i);
		else
			Out_BP.insert(i);
	}


	map< float, int, greater <float> > ratio_items;

//	for(int z = 0 ; z < 10; z++){
		for(set< int >::iterator in = In_BP.begin(); in != In_BP.end(); ++in){

			ratio_items = generate_ordered_ratio_items(Out_BP);

			float new_weight = weight - mainLSStructure->get_weight_of(*in);
			set< int > in_tmp(In_BP.begin(),In_BP.end());

			in_tmp.erase(*in);
			enumerate_neighborhood(in_tmp, Out_BP, new_weight, ratio_items);

		}
//	}


	if(In_BP.size() == 0){
		ratio_items = generate_ordered_ratio_items(Out_BP);
		enumerate_neighborhood(In_BP, Out_BP, weight, ratio_items);
	}



	return neighborhood;
}














