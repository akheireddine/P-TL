#ifndef ___EVALUATOR___
#define ___EVALUATOR___


//#include "AlternativeKnapsack.h"
#include "MainKnapsack.h"


class Evaluator{
private:

	string filename_instance;
	string dist_time_file;
	string pf_indicators_file;
	list< vector< float > > PFront;
	string PF_filename;
	AlternativeKnapsack * OPT_Alternative;
	vector<float > WS_DM_vector;

	MainKnapsack * mainProblem;


public:

	//CONSTRUCTOR
	Evaluator(string filename, MainKnapsack * problemInstance, string WS_DM_preferences, string DT_file, float time, string PFI_file);

	//GETTERS
	string get_filename_instance(){ return filename_instance; };

	//READ FILES
	void readParetoFront();

	//WRITE INFORMATION WS_MAT & OPT SOLUTION
	void write_objective_OPT_information();
	void write_coeff_functions(string filename);



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
