
#ifndef ____ALTERNATIVE___
#define ____ALTERNATIVE___



#include <vector>
#include <set>
#include <algorithm>
#include <list>
#include <memory>

using namespace std;


class Alternative {

protected:
	string id_alt;															//unique ID
	int nb_objective;
//	vector< int > alternatives;											//vector 1/0 of present items (=1) or absent (=0)
	vector< float > criteria_values;									//vector of criteria value
	vector< float > objective_values;									// objectives values
	set< string > neighborhood;								//Neighborhood set
	vector< vector< float > > local_WS_matrix;							//local direction of optimization
	list< shared_ptr< Alternative > > local_Archive;
	//	LSStructure * mainLSStructure;
public:

	virtual ~Alternative(){
	};

	//GETTERS
	inline string get_id_alt(){ return id_alt; };
	inline float get_criteria(int i ){ return criteria_values[i]; };
	inline vector< float > get_objective_values(){ return objective_values; };
	inline vector< float > get_criteria_values() { return criteria_values; };
	inline vector< vector< float > > get_local_WS_matrix(){ return local_WS_matrix;};
	inline list< shared_ptr< Alternative > > get_local_Archive(){ return local_Archive; };
	//SETTERS
	inline void set_local_WS_matrix(vector<vector<float > > matrix){ local_WS_matrix = matrix; nb_objective = local_WS_matrix[0].size();};
	inline void set_local_Archive(list< shared_ptr< Alternative > > opt_sol){ local_Archive.clear(); local_Archive = opt_sol; };
//	inline void add_alt_local_Archive(string new_alt){ local_Archive.push_back(new_alt); };

	//ABSTRACT METHOD
	virtual set< string > get_neighborhood() = 0;
	virtual int dominates_objective_space(shared_ptr< Alternative > alt) = 0;
	virtual int dominates_decision_space(shared_ptr< Alternative > alt) = 0;
	virtual void update_objective_vector() = 0;
	virtual int get_nb_items() = 0;
	virtual bool contains_items(shared_ptr< Alternative > alt) = 0;

	//PRINT
	inline void print_alternative(){ cout<<"("; for(int i = 0; i < (int)id_alt.length(); i++) cout<< id_alt[i] <<", "; cout<<")"<<endl; };
	inline void print_objective_values(){ cout<<"("; for(int i = 0; i < (int)objective_values.size(); i++) cout<< objective_values[i] <<", "; cout<<")   "; };
	inline void print_criteria_values(){ cout<<"("; for(int i = 0; i < (int)criteria_values.size(); i++) cout<< criteria_values[i] <<", "; cout<<")"<<endl; };
	inline void print_local_WS_matrix(){ for(int i = 0; i < (int)local_WS_matrix.size(); i++) { for(int j = 0; j < (int)local_WS_matrix[i].size();j++) cout<< local_WS_matrix[i][j] <<"   "; cout<<endl; } };

};





#endif
