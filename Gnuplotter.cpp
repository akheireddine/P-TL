
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

	gp<<"plot \""<<filename1<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 2 w linespoints ls 1 title \""<<filename1<<"\"\n";

	gp<<"replot \""<<filename2<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 2 w linespoints ls 2 title \""<<filename2<<"\"\n";

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




void Gnuplotter::Comparison_Plot_INDICATORS(string filename1, string filename2,string type_inst, string size_inst){

	Gnuplot gp;

	gp<<"set colorsequence podo\n";

	gp<<"set style line 1 lt 2 lw 1.8 pt 1 ps 0.8 dt 1\n";
	gp<<"set style line 2 lt 3 lw 1.8 pt 2 ps 0.8 dt 2\n";


	gp<<"set grid\n";
	gp<<"do for[j=0:9]{\n";

	gp<<"plot \""<<filename1<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 1 w linespoints ls 1 title \""<<filename1<<"\"\n";

	gp<<"replot \""<<filename2<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 1 w linespoints ls 2 title \""<<filename2<<"\"\n";

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

	gp<<"plot \""<<filename1<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 2 w linespoints ls 1 title \""<<filename1<<"\"\n";

	gp<<"replot \""<<filename2<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 2 w linespoints ls 2 title \""<<filename2<<"\"\n";

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

	gp<<"plot \""<<filename1<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using (log($3)) w linespoints ls 1 title \""<<filename1<<"\"\n";

	gp<<"replot \""<<filename2<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using (log($3)) w linespoints ls 2 title \""<<filename2<<"\"\n";

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
