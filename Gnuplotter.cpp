
#include "./gnuplot-iostream/gnuplot-iostream.h"
#include "Gnuplotter.h"





void Gnuplotter::Comparison_Plot_DIST_TIME(string filename1, string filename2,string type_inst, string size_inst,string t1, string t2){

	Gnuplot gp;

	gp<<"set colorsequence podo\n";

	gp<<"set style line 1 lt 2 lw 1.8 pt 1 ps 0.8 dt 1\n";
	gp<<"set style line 2 lt 3 lw 1.8 pt 2 ps 0.8 dt 2\n";



	gp<<"set grid\n";
	gp<<"do for[j=0:9]{\n";

	gp<<"plot \""<<filename1<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 1 w linespoints ls 1 title \""<<t1<<"\"\n";

	gp<<"replot \""<<filename2<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 1 w linespoints ls 2 title \""<<t2<<"\"\n";

	gp<<"set xlabel \"Information rate (%)\"\n";
	gp<<"set yrange [-0.001:]\n";

	gp<<"set ylabel \"Average gap (%)\"\n";

	gp<<"set title \"Average gap to optimum for "<<size_inst<<" items ("<<type_inst<<"  T\".j.\")  - Comparison plot\"\n";
	gp<<"replot\n";


	gp<<"set terminal pngcairo size 1200,900\n";
	gp<<"set output \"AVG_"<<type_inst<<"_"<<size_inst<<"_T\".j.\".png\"\n";
	gp<<"replot\n";
	gp<<"}\n";






	gp<<"set grid\n";
	gp<<"do for[j=0:9]{\n";

	gp<<"plot \""<<filename1<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 2 w linespoints ls 1 title \""<<t1<<"\"\n";

	gp<<"replot \""<<filename2<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 2 w linespoints ls 2 title \""<<t2<<"\"\n";

	gp<<"set xlabel \"Information rate (%)\"\n";
	gp<<"set yrange [-0.001:]\n";

	gp<<"set ylabel \"Average time execution (second)\"\n";

	gp<<"set title \"Average time execution (second) for "<<size_inst<<" items ("<<type_inst<<"  T\".j.\")  - Comparison plot\"\n";
	gp<<"replot\n";
	gp<<"set terminal pngcairo size 1200,900\n";
	gp<<"set output \"TIME"<<type_inst<<"_"<<size_inst<<"_T\".j.\".png\"\n";
	gp<<"replot\n";
	gp<<"}\n";


}



void Gnuplotter::Comparison_Plot_INDICATORS(string filename1, string filename2, string type_inst, string size_inst, string t1, string t2){

	Gnuplot gp;

	gp<<"set colorsequence podo\n";

	gp<<"set style line 1 lt 2 lw 1.8 pt 1 ps 0.8 dt 1\n";
	gp<<"set style line 2 lt 3 lw 1.8 pt 2 ps 0.8 dt 2\n";


	gp<<"set grid\n";
	gp<<"do for[j=0:9]{\n";

	gp<<"plot \""<<filename1<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 1 w linespoints ls 1 title \""<<t1<<"\"\n";

	gp<<"replot \""<<filename2<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 1 w linespoints ls 2 title \""<<t2<<"\"\n";

	gp<<"set xlabel \"Information rate (%)\"\n";
	gp<<"set yrange [-0.001:]\n";

	gp<<"set ylabel \"Average minimum distance \"\n";

	gp<<"set title \"Average minium distance Indicator for "<<size_inst<<" items ("<<type_inst<<"  T\".j.\")  - Comparison plot\"\n";
	gp<<"replot\n";


	gp<<"set terminal pngcairo size 1200,900\n";
	gp<<"set output \"D1_"<<type_inst<<"_"<<size_inst<<"_T\".j.\".png\"\n";
	gp<<"replot\n";
	gp<<"}\n";


	gp<<"set grid\n";
	gp<<"do for[j=0:9]{\n";
	gp<<"plot \""<<filename1<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 2 w linespoints ls 1 title \""<<t1<<"\"\n";

	gp<<"replot \""<<filename2<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 2 w linespoints ls 2 title \""<<t2<<"\"\n";

	gp<<"set xlabel \"Information rate (%)\"\n";
	gp<<"set yrange [-0.001:]\n";

	gp<<"set ylabel \"Average MinMax \"\n";

	gp<<"set title \"MinMax distance Indicator for "<<size_inst<<" items ("<<type_inst<<"  T\".j.\")  - Comparison plot\"\n";
	gp<<"replot\n";


	gp<<"set terminal pngcairo size 1200,900\n";
	gp<<"set output \"D2_"<<type_inst<<"_"<<size_inst<<"_T\".j.\".png\"\n";
	gp<<"replot\n";
	gp<<"}\n";




	gp<<"set grid\n";
	gp<<"do for[j=0:9]{\n";

	gp<<"plot \""<<filename1<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 3 w linespoints ls 1 title \""<<filename1<<"\"\n";

	gp<<"replot \""<<filename2<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 3 w linespoints ls 2 title \""<<filename2<<"\"\n";

	gp<<"set xlabel \"Information rate (%)\"\n";
	gp<<"set yrange [-0.001:]\n";

	gp<<"set ylabel \"LOG Proportion of pareto optimal solution (%)\"\n";

	gp<<"set title \"LOG Proportion of optimal solution Indicator for "<<size_inst<<" items ("<<type_inst<<"  T\".j.\")  - Comparison plot\"\n";
	gp<<"replot\n";


	gp<<"set terminal pngcairo size 1200,900\n";
	gp<<"set output \"PR_"<<type_inst<<"_"<<size_inst<<"_T\".j.\".png\"\n";
	gp<<"replot\n";
	gp<<"}\n";




}




//NO EXTENSION FILENAMES
void Gnuplotter::Comparison_Plot_DIST_TIME_PSize(string filename1, string filename2,string type_inst, string size_inst,string t1
		, string t2,int init_size, int steps){

	Gnuplot gp;

	gp<<"set colorsequence podo\n";

	gp<<"set style line 1 lt 2 lw 1.8 pt 1 ps 0.8 dt 1\n";
	gp<<"set style line 2 lt 3 lw 1.8 pt 2 ps 0.8 dt 2\n";



	gp<<"set grid\n";
	gp<<"do for[i=0:0]{\n";

		gp<<"size = "<<to_string(init_size)<<"\n";

		gp<<"do for[j=0:10]{\n";

			gp<<"plot \""<<filename1<<"_T\".i.\".eval\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 1 w linespoints ls 1 title \""<<t1<<"\"\n";

			gp<<"replot \""<<filename2<<"_T\".i.\".eval\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 1 w linespoints ls 2 title \""<<t2<<"\"\n";

			gp<<"set xlabel \"Information rate (%)\"\n";
			gp<<"set yrange [-0.001:]\n";

			gp<<"set ylabel \"Average gap (%)\"\n";


			gp<<"set title \"Average minimum distance from optimal solution using "<<size_inst<<" items ("<<type_inst<<"  T\".i.\")  with  Population size : \".size.\" \"\n";
			gp<<"replot\n";


			gp<<"set terminal pngcairo size 1200,900\n";
			gp<<"set output \"AVG_"<<type_inst<<"_"<<size_inst<<"_T\".i.\"_S\".size.\".png\"\n";
			gp<<"replot\n";

			gp<<"size = size + "<<to_string(steps)<<"\n";


		gp<<"}\n";

	gp<<"}\n";






	gp<<"set grid\n";
	gp<<"do for[i=0:0]{\n";

		gp<<"size = "<<to_string(init_size)<<"\n";

		gp<<"do for[j=0:10]{\n";

			gp<<"plot \""<<filename1<<"_T\".i.\".eval\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 2 w linespoints ls 1 title \""<<t1<<"\"\n";

			gp<<"replot \""<<filename2<<"_T\".i.\".eval\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 2 w linespoints ls 2 title \""<<t2<<"\"\n";

			gp<<"set xlabel \"Information rate (%)\"\n";
			gp<<"set yrange [-0.001:]\n";

			gp<<"set ylabel \"Average time execution (second)\"\n";


			gp<<"set title \"Average time execution (second) using "<<size_inst<<" items ("<<type_inst<<"  T\".i.\")  with  Population size : \".size.\" \"\n";
			gp<<"replot\n";


			gp<<"set terminal pngcairo size 1200,900\n";
			gp<<"set output \"TIME"<<type_inst<<"_"<<size_inst<<"_T\".i.\"_S\".size.\".png\"\n";
			gp<<"replot\n";

			gp<<"size = size + "<<to_string(steps)<<"\n";

		gp<<"}\n";

	gp<<"}\n";

}





//NO EXTENSION FILENAMES
void Gnuplotter::AllPlot_DIST_TIME_PSize(string filename, string type_inst, string size_inst,string algo,int init_size, int steps){

	Gnuplot gp;

	gp<<"set colorsequence podo\n";

	gp<<"set style line 1 lt 1 lw 2 pt 1 ps 0.8 dt 1\n";
	gp<<"set style line 2 lt 2 lw 2 pt 2 ps 0.8 dt 2\n";
	gp<<"set style line 3 lt 3 lw 2 pt 3 ps 0.8 dt 3 lc rgb \"#e62e00\"   \n";
	gp<<"set style line 4 lt 4 lw 2 pt 4 ps 0.8 dt 4\n";
	gp<<"set style line 5 lt 5 lw 2 pt 5 ps 0.8 dt 5\n";
	gp<<"set style line 6 lt 6 lw 2 pt 6 ps 0.8 dt 6\n";
	gp<<"set style line 7 lt 7 lw 2 pt 7 ps 0.8 dt 7\n";
	gp<<"set style line 8 lt 8 lw 2 pt 8 ps 0.8 dt 8 lc rgb \"#1a75ff\"   \n";
	gp<<"set style line 9 lt 9 lw 2 pt 9 ps 0.8 dt 9 lc rgb \"#c27982\"   \n";
	gp<<"set style line 10 lt 10 lw 2 pt 10 ps 0.8 dt 10 lc rgb \"#993366\"   \n";
	gp<<"set style line 11 lt 11 lw 2 pt 11 ps 0.8 dt 11 lc rgb \"#86b300\"   \n";;


	gp<<"set grid\n";


	gp<<"do for[i=0:9] {\n";

		gp<<"plot for[j=0:10:2] \""<<filename<<"_T\".i.\".eval\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 1 w linespoints ls (j+1) "
				"title \" Size_{\".(j*"<<to_string(steps)<<"+"<<to_string(init_size)<<").\"} \" \n";


		gp<<"set xlabel \"Information rate (%)\"\n";
		gp<<"set yrange [-0.001:]\n";

		gp<<"set ylabel \"Average gap (%)\"\n";


		gp<<"set title \"Average minimum distance from optimal solution using "<<size_inst<<" items ( "<<type_inst<<" T\".i.\" ) \" \n";
		gp<<"replot\n";

		gp<<"set terminal pngcairo size 1200,900\n";
		gp<<"set output \"AVG_"<<type_inst<<"_"<<size_inst<<"_"<<algo<<"_T\".i.\".png\"\n";
		gp<<"replot\n";


	gp<<"}\n";


	gp<<"set grid\n";

	gp<<"do for[i=0:9] {\n";

		gp<<"plot for[j=0:10:2] \""<<filename<<"_T\".i.\".eval\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 2 w linespoints ls (j+1) "
			"title \" Size_{\".(j*"<<to_string(steps)<<"+"<<to_string(init_size)<<").\"} \" \n";

		gp<<"set xlabel \"Information rate (%)\"\n";
		gp<<"set yrange [-0.003:]\n";

		gp<<"set ylabel \"Average time execution (second)\"\n";


		gp<<"set title \"Average time execution (second) using "<<size_inst<<" items ( "<<type_inst<<" T\".i.\" ) \" \n";
		gp<<"replot\n";
		gp<<"set terminal pngcairo size 1200,900\n";
		gp<<"set output \"TIME_"<<type_inst<<"_"<<size_inst<<"_"<<algo<<"_T\".i.\".png\"\n";
		gp<<"replot\n";


	gp<<"}\n";

}
