
#include "./gnuplot-iostream/gnuplot-iostream.h"
#include "Gnuplotter.h"





void Gnuplotter::Comparison_Plot_DIST_TIME(string filename1, string filename2,string type_inst, string size_inst,string t1, string t2){

	Gnuplot gp;

	gp<<"set terminal pngcairo size 1900,1100\n";
	gp<<"set output \"AVG_"<<type_inst<<"_"<<size_inst<<".png\"\n";

	gp<<"set multiplot layout 4,3 columnsfirst rowsfirst title \" {/:Bold=15 Average minium distance from optimal solution for "<<size_inst<<" items (instance "<<type_inst<<")  - Comparison plot }\"\n";

	gp<<"set colorsequence podo\n";

	gp<<"set style line 1 lt 2 lw 2 pt 1 ps 0.8 dt 1 lc rgb \"red\"\n";
	gp<<"set style line 2 lt 3 lw 2 pt 2 ps 0.8 dt 2 lc rgb \"blue\"\n";

	gp<<"set xtics ('90' 0 ,'41' 1 ,'28' 2 ,'12' 3 ,'8' 4 ,'5' 5 ,'4' 6 ,'0' 7)\n";        //TEST2
	gp<<"set xlabel \"Information rate - angle degree (°)  of the covered space \"\n";
	gp<<"set yrange [-0.001:]\n";

	gp<<"set ylabel \"Average gap (%)\"\n";

	gp<<"set grid\n";

	gp<<"do for[j=0:9]{\n";

	gp<<"set label 1 '{/:Bold=10T'.j.'}' at graph 0.05,0.95 font ',8'\n";

	gp<<"plot \""<<filename1<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 1 w linespoints ls 1 title \""<<t1<<"\" ,  \""<<filename2<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 1 w linespoints ls 2 title \""<<t2<<"\"\n";


	gp<<"}\n";



	gp<<"unset multiplot\n";
	gp<<"unset output\n";


	gp<<"set terminal pngcairo size 1900,1100\n";
	gp<<"set output \"TIME_"<<type_inst<<"_"<<size_inst<<".png\"\n";

	gp<<"set multiplot layout 4,3 columnsfirst rowsfirst title \" {/:Bold=15 Average time execution (second) for "<<size_inst<<" items ( instance "<<type_inst<<" )  - Comparison plot }\"\n";

	gp<<"set xlabel \"Information rate - angle degree (°)  of the covered space \"\n";

	gp<<"set xtics ('90' 0 ,'41' 1 ,'28' 2 ,'12' 3 ,'8' 4 ,'5' 5 ,'4' 6 ,'0' 7)\n";        //TEST2



	gp<<"set yrange [-0.001:]\n";
	gp<<"set ylabel \"Average time execution (second)\"\n";


	gp<<"set colorsequence podo\n";


	gp<<"do for[j=0:9]{\n";
		gp<<"set label 1 '{/:Bold=10T'.j.'}' at graph 0.05,0.95 font ',8'\n";
		gp<<"plot \""<<filename1<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 2 w linespoints ls 1 title \""<<t1<<"\" ,  \""<<filename2<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 2 w linespoints ls 2 title \""<<t2<<"\"\n";
	gp<<"}\n";


}



void Gnuplotter::Comparison_Plot_INDICATORS(string filename1, string filename2, string type_inst, string size_inst, string t1, string t2){

	Gnuplot gp;

	gp<<"set colorsequence podo\n";

	gp<<"set style line 1 lt 2 lw 2 pt 1 ps 0.8 dt 1 lc rgb \"red\"\n";
	gp<<"set style line 2 lt 3 lw 2 pt 2 ps 0.8 dt 2 lc rgb \"blue\"\n";
	gp<<"set terminal pngcairo size 1900,1100\n";
	gp<<"set output \"D1_"<<type_inst<<"_"<<size_inst<<".png\"\n";

	gp<<"set multiplot layout 4,3 columnsfirst rowsfirst title \" {/:Bold=15 Average minium distance Indicator for "<<size_inst<<" items ("<<type_inst<<" )  - Comparison plot }\"\n";

	gp<<"set xtics ('90' 0 ,'41' 1 ,'28' 2 ,'12' 3 ,'8' 4 ,'5' 5 ,'4' 6 ,'0' 7)\n";        //TEST2
	gp<<"set xlabel \"Information rate - angle degree (°)  of the covered space \"\n";
	gp<<"set yrange [-0.001:]\n";
	gp<<"set ylabel \"Average minimum distance \"\n";

	gp<<"set grid\n";

	gp<<"do for[j=0:9]{\n";

		gp<<"set label 1 '{/:Bold=10T'.j.'}' at graph 0.05,0.95 font ',8'\n";

		gp<<"plot \""<<filename1<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 1 w linespoints ls 1 title \""<<t1<<"\" ,  \""<<filename2<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 1 w linespoints ls 2 title \""<<t2<<"\"\n";

	gp<<"}\n";




	gp<<"unset multiplot\n";
	gp<<"unset output\n";


	gp<<"set output \"D2_"<<type_inst<<"_"<<size_inst<<".png\"\n";

	gp<<"set multiplot layout 4,3 columnsfirst rowsfirst title \" {/:Bold=15 MinMax distance Indicator for "<<size_inst<<" items ("<<type_inst<<")  - Comparison plot }\"\n";

	gp<<"set xlabel \"Information rate - angle degree (°)  of the covered space \"\n";

	gp<<"set xtics ('90' 0 ,'41' 1 ,'28' 2 ,'12' 3 ,'8' 4 ,'5' 5 ,'4' 6 ,'0' 7)\n";        //TEST2

	gp<<"set yrange [-0.001:]\n";
	gp<<"set ylabel \"Average MinMax \"\n";
	gp<<"set grid\n";


	gp<<"do for[j=0:9]{\n";
		gp<<"set label 1 '{/:Bold=10T'.j.'}' at graph 0.05,0.95 font ',8'\n";
		gp<<"plot \""<<filename1<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 2 w linespoints ls 1 title \""<<t1<<"\" ,  \""<<filename2<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 2 w linespoints ls 2 title \""<<t2<<"\"\n";
	gp<<"}\n";


	gp<<"unset multiplot\n";
	gp<<"unset output\n";


	gp<<"set output \"PR_"<<type_inst<<"_"<<size_inst<<".png\"\n";

	gp<<"set multiplot layout 4,3 columnsfirst rowsfirst title \" {/:Bold=15  Proportion of optimal solution Indicator for "<<size_inst<<" items ("<<type_inst<<")  - Comparison plot }\"\n";

	gp<<"set xlabel \"Information rate - angle degree (°)  of the covered space \"\n";

	gp<<"set xtics ('90' 0 ,'41' 1 ,'28' 2 ,'12' 3 ,'8' 4 ,'5' 5 ,'4' 6 ,'0' 7)\n";        //TEST2

	gp<<"set yrange [-0.001:]\n";
	gp<<"set ylabel \"Proportion of pareto optimal solution (%)\"\n";

	gp<<"set grid\n";


	gp<<"do for[j=0:9]{\n";
		gp<<"set label 1 '{/:Bold=10T'.j.'}' at graph 0.05,0.95 font ',8'\n";
		gp<<"plot \""<<filename1<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 3 w linespoints ls 1 title \""<<t1<<"\" ,  \""<<filename2<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 3 w linespoints ls 2 title \""<<t2<<"\"\n";
	gp<<"}\n";


}




void Gnuplotter::Comparison_Plot_VARIABLE_WS_NEIGHBORHOOD(string filename1, string filename2, string filename3, string type_inst, string size_inst,string t1, string t2, string t3){

	Gnuplot gp;

	gp<<"set terminal pngcairo size 1900,1100\n";
	gp<<"set output \"AVG_"<<type_inst<<"_"<<size_inst<<"_3WS.png\"\n";
	gp<<"set colorsequence podo\n";

	gp<<"set style line 1 lt 2 lw 2 pt 1 ps 0.8 dt 1 lc rgb \"red\"\n";
	gp<<"set style line 2 lt 3 lw 2 pt 2 ps 0.8 dt 2 lc rgb \"blue\"\n";
	gp<<"set style line 3 lt 4 lw 2 pt 3 ps 0.8 dt 6 lc rgb \"#008000\"\n";

	gp<<"set xtics ('90' 0 ,'41' 1 ,'28' 2 ,'12' 3 ,'8' 4 ,'5' 5 ,'4' 6 ,'0' 7)\n";        //TEST2
	gp<<"set xlabel \"Information rate - angle degree (°)  of the covered space \"\n";
	gp<<"set yrange [-0.001:]\n";

	gp<<"set ylabel \"Average gap (%)\"\n";

	gp<<"set grid\n";


	gp<<"set multiplot layout 4,3 columnsfirst rowsfirst title \" {/:Bold=15 Average minium distance from optimal solution for "<<size_inst<<" items (instance "<<type_inst<<")  - Comparison plot }\"\n";

	gp<<"do for[j=0:9]{\n";
		gp<<"set label 1 '{/:Bold=10T'.j.'}' at graph 0.05,0.95 font ',8'\n";

		gp<<"plot \""<<filename1<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 1 w linespoints ls 1 title \""<<t1<<"\" , "
			" \""<<filename2<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 1 w linespoints ls 2 title \""<<t2<<"\" , "
			" \""<<filename3<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 1 w linespoints ls 3 title \""<<t3<<"\" \n";
	gp<<"}\n";

	gp<<"unset multiplot\n";
	gp<<"unset output\n";


	gp<<"set output \"TIME_"<<type_inst<<"_"<<size_inst<<"_3WS.png\"\n";

	gp<<"set multiplot layout 4,3 columnsfirst rowsfirst title \" {/:Bold=15 Average time execution (second) for "<<size_inst<<" items ( instance "<<type_inst<<" )  - Comparison plot }\"\n";

	gp<<"set ylabel \"Average time execution (second)\"\n";

	gp<<"do for[j=0:9]{\n";
		gp<<"set label 1 '{/:Bold=10T'.j.'}' at graph 0.05,0.95 font ',8'\n";

		gp<<"plot \""<<filename1<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 2 w linespoints ls 1 title \""<<t1<<"\" , "
			" \""<<filename2<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 2 w linespoints ls 2 title \""<<t2<<"\" , "
			" \""<<filename3<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 2 w linespoints ls 3 title \""<<t3<<"\" \n";
	gp<<"}\n";


}







//NO EXTENSION FILENAMES
void Gnuplotter::Comparison_Plot_DIST_TIME_PSize(string filename1, string filename2,string type_inst, string size_inst,string t1
		, string t2,int init_size, int steps){

	Gnuplot gp;

	gp<<"set colorsequence podo\n";

	gp<<"set style line 1 lt 2 lw 2 pt 1 ps 0.8 dt 1 lc rgb \"red\"\n";
	gp<<"set style line 2 lt 3 lw 2 pt 2 ps 0.8 dt 2 lc rgb \"blue\"\n";



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
	gp<<"set terminal pngcairo size 1900,1100\n";
	gp<<"set output \"AVG_"<<type_inst<<"_"<<size_inst<<"_"<<algo<<".png\"\n";

	gp<<"set multiplot layout 4,3 columnsfirst rowsfirst title \" {/:Bold=15 Average minimum distance from optimal solution using "<<size_inst<<" items ( "<<type_inst<<" ) }\"\n";

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
	gp<<"set style line 11 lt 11 lw 2 pt 11 ps 0.8 dt 11 lc rgb \"#86b300\"   \n";
	gp<<"set grid\n";

	gp<<"set xtics ('90' 0 ,'41' 1 ,'28' 2 ,'12' 3 ,'8' 4 ,'5' 5 ,'4' 6 ,'0' 7)\n";        //TEST2
	gp<<"set xlabel \"Information rate - angle degree (°)  of the covered space \"\n";
	gp<<"set yrange [-0.001:]\n";

	gp<<"set ylabel \"Average gap (%)\"\n";


	gp<<"do for[i=0:0] {\n";
		gp<<"set label 1 '{/:Bold=10 T'.i.'}' at graph 0.05,0.95 font ',8'\n";

		gp<<"plot for[j=0:10:2] \""<<filename<<"_T\".i.\".eval\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 1 w linespoints ls (j+1) "
				"title \" Size_{\".(j*"<<to_string(steps)<<"+"<<to_string(init_size)<<").\"} \" \n";
	gp<<"}\n";


	gp<<"unset multiplot\n";
	gp<<"unset output\n";

	gp<<"set ylabel \"Average time execution (second)\"\n";
	gp<<"set yrange [-0.001:]\n";

	gp<<"set terminal pngcairo size 1900,1100\n";
	gp<<"set output \"TIME_"<<type_inst<<"_"<<size_inst<<"_"<<algo<<".png\"\n";

	gp<<"set multiplot layout 4,3 columnsfirst rowsfirst title \" {/:Bold=15 Average time execution (second) using "<<size_inst<<" items ( "<<type_inst<<" ) }\"\n";


	gp<<"do for[i=0:0] {\n";
		gp<<"set label 1 '{/:Bold=10 T'.i.'}' at graph 0.05,0.95 font ',8'\n";

		gp<<"plot for[j=0:10:2] \""<<filename<<"_T\".i.\".eval\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 2 w linespoints ls (j+1) "
			"title \" Size_{\".(j*"<<to_string(steps)<<"+"<<to_string(init_size)<<").\"} \" \n";
	gp<<"}\n";

}








void Gnuplotter::Plot_SEARCH_EVOLUTION(string filename, string type_inst, string size_inst,string algo,int size){


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
	gp<<"set style line 11 lt 11 lw 2 pt 11 ps 0.8 dt 11 lc rgb \"#86b300\"   \n";
	gp<<"set grid\n";

	set xlabel "x_1"
	set ylabel "x_2"



	gp<<"plot 'Instances_Knapsack/Type_A/100_items/2KP100-TA-0.eff' title 'OPT front' ,  "
			"for[i=0:2] 'Instances_Knapsack/Type_A/100_items/2KP100-TA-0_10_'.i.'.expl' using 1:2 title "iteration ".i with points ls (i+1) \n";

	#replot "Instances_Knapsack/Type_A/100_items/2KP100-TA-0_10XXXX.sol" title "final front" with points ls 14


	set title "Evolution of the search space with 100 items (random Instances A - T0 ) - Population size : 10"

	set style line 22 lc rgb "#cc1300" pt 3 ps 4
	replot "<echo '37652 41042'"   with points ls 22 title "DMs preference"

	replot
	set terminal png size 1200,900
	set output "PLOT_A_100_T0_CST_10_SIZE.png"
	replot

}











