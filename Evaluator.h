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


	vector< tuple<float, vector< float> > > Items_information;
	vector< vector< float > > WS_matrix;
	float p_criteria;
	float n_objective;
	float Backpack_capacity;



	static float avg_time, avg_std;
	static float cpt;
	static float D1, D2, D3, dist, time, std;

public:




	//CONSTRUCTOR
//	Evaluator(string filename, string WS_matrix_file, string WS_DM_preferences, string DT_file, float time, string PFI_file);
	Evaluator(string filename, string WS_DM_preferences, string SDT_file, string PFI_file);
	~Evaluator(){
		OPT_Alternative.reset();
	};

	//GETTERS
	string get_filename_instance(){ return filename_instance; };
	list< vector<float > > get_PFront(){ return PFront; };
	int get_p_criteria(){ return p_criteria; };
	int get_n_objective(){ return n_objective; };

	//READ FILES
	void readParetoFront();
	void readWS_matrix(string filename);


	//INTERN OPERATIONS
	bool in_search_space(vector<float> v,vector<float> minus, vector<float> maxus);




	//EVALUATION
	float nearest_alternative(vector< float > & vect_criteria );
	shared_ptr<AlternativeKnapsack> OPT_Alternative_PLNE(vector<float> WS_vector);
	float evaluate_Dist_ratio(string dist_time_file);
	void evaluate_PF(shared_ptr< MainKnapsack > knaps, float time_cpu);
	vector< float > evaluate_standard_deviation_from_OPT_point();

	void save_PF_evaluation();



	void compute_information_rate_front();
	float compute_information_rate();


	//INDICATORS
	float average_distance_D1(list< shared_ptr< Alternative > > OPT_Solution);
	float maximum_distance_D2(list< shared_ptr< Alternative > > OPT_Solution);
	float PR_D3(list< shared_ptr< Alternative > > OPT_Solution)



};


















#endif
