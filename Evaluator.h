#ifndef ___EVALUATOR___
#define ___EVALUATOR___


//#include "AlternativeKnapsack.h"
#include "MainKnapsack.h"


class Evaluator{
private:

	string filename_instance;
	vector<vector< float > > PFront;
	string PF_filename;
	Alternative * OPT_Alternative;
	vector<float > WS_DM_vector;

	MainKnapsack * mainProblem;


public:

	//CONSTRUCTOR
	Evaluator(string filename, LSStructure * problemInstance, string WS_DM_preferences,string dist_time_file, float time, string pf_indicators_file);



	//READ FILES
	void readParetoFront();


	//INTERN OPERATIONS
	vector<float> get_objective_values(vector<float> v_src);
	bool is_dominated(vector<float> v);




	//EVALUATION
	float nearest_alternative(vector< float > & vect_criteria );
	void OPT_Alternative_PLNE(string WS_DM_preferences);
	void evaluate_Dist_Time(string dist_time_file, float time);
	void evaluate_PF(string pf_indicators_file);


	//INDICATORS
	float average_distance_D1();
	float maximum_distance_D2();
	float PR_D3();



};


















#endif
