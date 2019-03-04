


using namespace std;

class Alternative {

private:
	vector< int > alternative;
	vector< float > criteria_values;
	vector< Alternative* > neighborhood;

public:
	vector< Alternative* > get_neighborhood;
	vector< float > get_criteria_values { return criteria_values; };

};







class AlternativeKnapsack : Alternative{
private :
	float weight;
	MainKnapsack * mainKnapsack;

};
