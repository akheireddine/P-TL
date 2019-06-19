


#include "Instance_Generator.h"

#include <random>
#include <fstream>
#include <ilcplex/ilocplex.h>


#define LO_W 2
#define HI_W 25

#define LO_U 10
#define HI_U 35

#define N_WS 100

Instance_Generator::Instance_Generator(int n, int p, int nb_inst){
	p_criteria = p;
	n_items = n;
	nb_instances = nb_inst;
}

void Instance_Generator::random_instances(string path){

	system(("if [ ! -d "+path+" ]; then mkdir -p "+path+"; fi").c_str());


	for(int i = 10; i < nb_instances+10; i++){
		int Weight = 0;

		string filename = "2KP"+to_string(n_items)+"-TA-"+to_string(i);

		vector< string > weights(n_items);
		vector< vector< string > > utilities(n_items,vector< string >(p_criteria) );

		//RANDOM GENERATION
		for(int n = 0; n < n_items; n++){
			int rand_weight = LO_W +  (rand()) /( (RAND_MAX/(HI_W-LO_W)));
			weights[n] = to_string(rand_weight);

			Weight += rand_weight;

			for(int p = 0; p < p_criteria; p++){
				int rand_utility = LO_U + (rand()) /((RAND_MAX/(HI_U-LO_U)));
				utilities[n][p] = to_string(rand_utility);
			}
		}

		Weight /= n_items;
		string content = write_content(weights, utilities, to_string(Weight));

		ofstream fic((path+"/"+filename+".dat").c_str());

		fic<<content<<endl;
		fic.close();

		set_Efficient_front(filename);
	}

}





string Instance_Generator::write_content(vector< string > weights, vector< vector< string > > utilities, string Weight){

	string content = "n "+to_string(n_items)+"\n";

	content += "c  w \n";

	for(int i = 0; i < n_items; i++ ){

		content += "i "+weights[i];

		for(int j = 0; j < p_criteria; j++){

			content +=" 	 "+utilities[i][j];
		}

		content +="\n";
	}

	content += "c c\n";

	content += "W "+Weight+"\n";

	content += "c end of file\n";


	return content;
}




void Instance_Generator::readFile(string filename){

	string line;
	char buff[100];
	int i = 0;
	float weight;
	char *cline, *pch;
	vector< float > line_value;

	ifstream fic((filename+".dat").c_str());

	//comments
	getline(fic,line);
	while( line[0] == 'c' )
		getline(fic,line);

	//number of items

	if( line[0] == 'n')
		sscanf(line.c_str(),"%s %d",buff,&n_items);

	Items_information.resize(n_items);

	//comments
	getline(fic,line);
	while( line[0] == 'c' )
		getline(fic,line);

	//items information


	while(line[0] == 'i'){

		line.erase(line.begin());
		cline = new char[line.length() + 1]; // or
		std::strcpy(cline, line.c_str());

		line_value.clear();
		pch = strtok (cline," 	");
		while (pch != NULL){
			line_value.push_back(atof(pch));
			pch = strtok (NULL, " 	");
		}

		weight = line_value[0];

		line_value.erase(line_value.begin());

		Items_information[i] = make_tuple(weight,line_value);


		getline(fic,line);
		i++;
	}

	//number of criteria
	p_criteria = line_value.size();

	//comments
	while( line[0] == 'c' )
		getline(fic,line);


	//total capacity
	if( line[0] == 'W' )
		sscanf(line.c_str(),"%s %f",buff,&Backpack_capacity);

	fic.close();

}


//Get optima values of objective with WS aggregator
vector< float > Instance_Generator::PL_WS(vector<float> WS_vector){

	int n_item = Items_information.size();
	IloEnv   env;
	IloModel model(env);
	vector<IloNumVar > x( n_item );
	IloRangeArray Constraints(env);

	//VARIABLES
	for(int i = 0; i < n_item; i++){
		x[i] = IloNumVar(env, 0.0, 1.0, ILOINT);
		ostringstream varname;
		varname.str("");
		varname<<"x_"<<i;
		x[i].setName(varname.str().c_str());
	}

	//CONSTRAINTS
	IloExpr c1(env);

	for(int j = 0; j < n_item ; j++)
		c1 += x[j] * get_weight_of(j);

	Constraints.add(c1 <= Backpack_capacity );

	model.add(Constraints);

	//OBJECTIVE
	IloObjective obj=IloAdd(model, IloMaximize(env));

	for(int i = 0; i < n_item; i++){
		float coeff = 0.;
		for(int j = 0; j < Instance_Generator::p_criteria ; j++)
			  coeff += get_utility(i,j) * WS_vector[j];

		obj.setLinearCoef(x[i], coeff);
	}


	//SOLVE
	IloCplex cplex(model);

	cplex.setOut(env.getNullStream());


	if ( !cplex.solve() ) {
		 env.error() << "Failed to optimize LP Instance_Generator" << endl;
		 exit(1);
	}

	//GET SOLUTION CRITERIA VALUE
	vector< float > opt_alt(Instance_Generator::p_criteria,0);
	for(int i = 0; i < n_item; i++){
		if( cplex.getValue(x[i]) > 0){
			for(int j = 0; j < Instance_Generator::p_criteria; j++)
				opt_alt[j] += get_utility(i,j);
		}
	}

	env.end();

	return opt_alt;
}



void Instance_Generator::set_Efficient_front(string filename){

	vector< vector< float > > efficient_solution;
	string output = filename+".eff";

	readFile(filename);

	cout<<p_criteria<<endl;
	vector< vector< float > >  pareto(p_criteria);
	vector< float > random_ws;

	for(int i = 0 ; i < p_criteria; i++){
		for(int j = 0; j < p_criteria; j++){
			if( i == j)
				pareto[i].push_back(1.);
			else
				pareto[i].push_back(0.);
		}
	}
	cout<<pareto.size()<<endl;

	for(int i = 0; i < p_criteria; i++)
		cout<<Tools::print_vector(pareto[i])<<endl;

	for(int i = 0; i < N_WS; i++){
		random_ws =  Tools::generate_random_restricted_WS_aggregator(p_criteria,pareto);
		cout<<"toto2"<<endl;

		efficient_solution.push_back(PL_WS(random_ws));
		cout<<"toto3"<<endl;

	}


	vector< vector< float > > tmp_sol(efficient_solution.begin(),efficient_solution.end());


	for(vector< vector< float > >::iterator e1 = tmp_sol.begin(); e1 != tmp_sol.end(); ++e1){
		for(vector< vector< float > >::iterator e2 = tmp_sol.begin(); e2 != tmp_sol.end(); ++e2){

			int val =  Tools::dominates(*e1,*e2);
			if( val == 1 )
				efficient_solution.erase(e2);
			else if( val == -1){
				efficient_solution.erase(e1);
				break;
			}
		}

	}


	ofstream fic_write(output.c_str());

	for(auto t : efficient_solution)
		fic_write<<Tools::print_vector(t)<<endl;

	fic_write.close();
}
