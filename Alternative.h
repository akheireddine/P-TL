
#ifndef ____ALTERNATIVE___
#define ____ALTERNATIVE___



#include <vector>
#include <set>


using namespace std;


class Alternative {

protected:
	int id_alt;															//unique ID
	int nb_objective;
	vector< int > alternatives;											//vector 1/0 of present items (=1) or absent (=0)
	vector< float > criteria_values;									//vector of criteria value
	vector< float > objective_values;									// objectives values
	vector< Alternative* > neighborhood;								//Neighborhood set
	vector< vector< float > > local_WS_matrix;							//local direction of optimization
	//	LSStructure * mainLSStructure;
public:
	static int id;

	//GETTERS
	int get_id(){ return id_alt; };
	inline vector< float > get_objective_values(){ return objective_values; };
	inline vector< float > get_criteria_values() { return criteria_values; };
	inline float get_criteria(int i ){ return criteria_values[i]; };
	inline vector< vector< float > > get_local_WS_matrix(){ return local_WS_matrix;};
	//SETTERS
	inline void set_local_WS_matrix(vector<vector<float > > matrix){ local_WS_matrix = matrix; nb_objective = local_WS_matrix[0].size();};

	//ABSTRACT METHOD
	virtual vector< Alternative* > get_neighborhood() = 0;
	virtual int dominates_objective_space(Alternative* alt) = 0;
	virtual int dominates_decision_space(Alternative* alt) = 0;
	virtual void update_objective_vector() = 0;

	//PRINT
	inline void print_alternative(){ cout<<"("; for(int i = 0; i < alternatives.size(); i++) cout<< alternatives[i] <<", "; cout<<")"<<endl;};
	inline void print_objective_values(){ cout<<"("; for(int i = 0; i < objective_values.size(); i++) cout<< objective_values[i] <<", "; cout<<")   "; };
	inline void print_criteria_values(){ cout<<"("; for(int i = 0; i < criteria_values.size(); i++) cout<< criteria_values[i] <<", "; cout<<")"<<endl; };
	inline void print_local_WS_matrix(){ for(int i = 0; i < local_WS_matrix.size(); i++) { for(int j = 0; j < local_WS_matrix[i].size();j++) cout<< local_WS_matrix[i][j] <<"   "; cout<<endl; }
	};




};





#endif
