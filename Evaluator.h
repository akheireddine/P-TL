#ifndef ___EVALUATOR___
#define ___EVALUATOR___



#include "MainKnapsack.h"
#include <map>




extern int UB_Size;

using namespace std;


class Evaluator{
private:

	string filename_instance;
	string indicator_file;
	list< vector< float > > PFront;                 //covered pareto front
	string PF_filename;
	vector< float > OPT_Alternative;
	vector<vector<float > > PF_Efficient;
	vector<float > WS_DM_vector;


	vector< vector< float > > WS_matrix;
	float p_criteria;
	float n_objective;
	float Backpack_capacity;



	int K_replication;
	int cpt_k = 0;
	float time;
	vector< float > PF_indicators, Point_indicators;


	map<int, map < int, vector< float > > > eval_values;                          // {size : { INFO : vector of SUM indicators } }


public:

	vector< tuple<float, vector< float> > > Items_information;

	//CONSTRUCTOR
	Evaluator(string filename, string WS_DM_preferences, string INDIC_file="");
	Evaluator(string filename, string WS_DM_preferences, string INDIC_file, vector<int> sizes, vector<int> information_rate, int K);

	~Evaluator(){

		for(list< vector< float > >::iterator i = PFront.begin(); i != PFront.end(); ++i){
			(*i).clear();
			(*i).shrink_to_fit();
		}

		PFront.resize(0);

		for(int i = 0; i < (int) PF_Efficient.size(); i++)
			PF_Efficient.shrink_to_fit();
		PF_Efficient.shrink_to_fit();

		OPT_Alternative.shrink_to_fit();


		for(vector< tuple<float, vector< float> > >::iterator i = Items_information.begin(); i != Items_information.end(); ++i){
			get<1>(*i).shrink_to_fit();
		}
		Items_information.shrink_to_fit();

		for(int i = 0; i < (int) WS_matrix.size(); i++){
			WS_matrix[i].clear();
			WS_matrix[i].shrink_to_fit();
		}
		WS_matrix.clear();
		WS_matrix.shrink_to_fit();

	};

	//SETTERS
	void set_K_replication(int k){ K_replication = k;};
	void set_indicator_file(string new_file){ indicator_file = new_file; };
	//GETTERS
	string get_filename_instance(){ return filename_instance; };
	list< vector<float > > get_PFront(){ return PFront; };
	int get_p_criteria(){ return p_criteria; };
	int get_n_objective(){ return n_objective; };
	float get_weight_of(int i) { return std::get<0>(Items_information[i]); };
	float get_utility(int i, int j) { return std::get<1>(Items_information[i])[j]; };
	float get_capacity(){ return Backpack_capacity; };
	vector< vector< float > > get_WS_matrix(){ return WS_matrix; };



	//READ FILES
	void readParetoFront();
//	void readParetoFront_locally();

	void update_covered_PFront();
	void readFilenameInstance(string filename);

	void readWS_matrix(string filename);


	//INTERN OPERATIONS
//	bool in_search_space(vector<float> v,vector<float> minus, vector<float> maxus);




	//EVALUATION
	float nearest_alternative(vector< float > & vect_criteria, list< vector< float > > OPT_Solution);
	vector< float > OPT_Alternative_PLNE(vector<float> WS_vector);
	float evaluate_Dist_ratio(list< vector< float > > OPT_Solution);


	void evaluate_PF(list< vector< float > > OPT_Solution, float time_cpu);
	void evaluate_PF(list< vector< float > > OPT_Solution, int sizer, int info, float time_cpu);
	vector< float > evaluate_standard_deviation_from_OPT_point();

	void save_PF_evaluation();
	void save_PF_evaluation_map();



	void compute_information_rate_front();
	float compute_information_rate();


	//INDICATORS
	float average_distance_D1(list< vector< float > > OPT_Solution);
	float maximum_distance_D2(list< vector< float > > OPT_Solution);
	float PR_D3(list< vector< float > > OPT_Solution);



	void update_covered_OPT_Solution(list< vector< float > > & Opt_Solution);


	void save_evolution_indicators(list< vector< float > > OPT_Solution, string filename_instance, int info, int sizer, float time_cpu, int pop_size);



	void save_information(string file_population, string save_path, string format);
	void save_other_information(string file_population, string save_path, string format);
	static void compute_avg_type_instances(string evaluation_save_path, string method_name, string format, int k_replic
			, int nb_instances, vector< int > ub_values, vector< int > Info );


};


















#endif
