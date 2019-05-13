#ifndef ___EVALUATOR___
#define ___EVALUATOR___


#include "MainKnapsack.h"


class Evaluator{
private:

	string filename_instance;
	string dist_time_file;
	string pf_indicators_file;
	list< vector< float > > PFront;                 //covered pareto front
	string PF_filename;
	shared_ptr<AlternativeKnapsack> OPT_Alternative;
	vector<vector<float > > PF_Efficient;
	vector<float > WS_DM_vector;

	MainKnapsack * mainProblem;


public:

	//CONSTRUCTOR
	Evaluator(string filename, MainKnapsack * problemInstance, string WS_DM_preferences, string DT_file, float time, string PFI_file);
	~Evaluator(){
		OPT_Alternative.reset();
		delete mainProblem;
	};

	//GETTERS
	string get_filename_instance(){ return filename_instance; };
	list< vector<float > > get_PFront(){ return PFront; };


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
	shared_ptr<AlternativeKnapsack> OPT_Alternative_PLNE(vector<float> WS_vector);
	void evaluate_Dist_Time(string dist_time_file, float time);
	void evaluate_PF(string pf_indicators_file);
	void compute_information_rate_front();
	float compute_information_rate();


	//INDICATORS
	float average_distance_D1();
	float maximum_distance_D2();
	float PR_D3();



};


















#endif
