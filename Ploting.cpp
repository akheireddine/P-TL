

#include "Ploting.h"
#include "gnuplot-iostream.h"
#include <boost/tuple/tuple.hpp>




void Ploting::plot_minimum_distance_to_opt(LSStructure *mainStruct){

	int p_criteria = mainStruct->get_p_criteria();
	Gnuplot gp;
	string line;
	vector<float> min(p_criteria,-1), max(p_criteria,-1);
	vector< vector< float > > coordinates(p_criteria,vector< float >());

	string file_extension = mainStruct->get_filename_isntance()+".eval";
	ifstream fic(file_extension.c_str());

	if (!(fic) or file_extension.find(".eval") == std::string::npos){
		cerr<<"Error occurred plot min distance"<<endl;
	}

	while(!fic.eof()){

		getline(fic,line);
		if (line.size() == 0)
			continue;

		vector< float > vector_objective = Tools::decompose_line_to_float_vector(line);

		for(int j = 0; j < p_criteria; j++){

			coordinates[j].push_back(vector_objective[j]);

			if(min[j] > vector_objective[j] or min[j] == -1)
				min[j] = vector_objective[j];
			if(max[j] < vector_objective[j] or max[j] == -1)
				max[j] = vector_objective[j];
		}
	}

	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange ["<<min[0]<<":"<<max[0]"]\nset yrange ["<<min[1]<<":"<<max[1]<<"]\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
//	gp << "plot '-' with vectors title 'pts_A', '-' with vectors title 'pts_B'\n";
	gp << "plot '-' with vectors title 'coordinates'\n";
//	gp.send1d(pts_A);
	gp.send1d(boost::make_tuple(coordinates[0],coordinates[1]));

}
