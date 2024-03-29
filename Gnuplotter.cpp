
#include "./gnuplot-iostream/gnuplot-iostream.h"
#include "Gnuplotter.h"





void Gnuplotter::Comparison_Plot_DIST_TIME(string filename1, string filename2,string type_inst, string size_inst,string t1, string t2){

	Gnuplot gp;

	gp<<"set terminal pngcairo size 1400,1200\n";
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


	gp<<"set terminal pngcairo size 1400,1200\n";
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

	gp<<"set terminal pngcairo size 1900,1400\n";
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

	gp<<"select = \"0 1 2 3 4 5 6 7 8 9\"\n";
	gp<<"set multiplot layout 4,3 columnsfirst rowsfirst title \" {/:Bold=15 Average minium distance from optimal solution for "<<size_inst<<" items (instance "<<type_inst<<")  - Comparison plot }\"\n";

	gp<<"do for[j in select]{\n";

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

	gp<<"do for[j in select]{\n";
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

	gp<<"set xtics ('90' 0 ,'41' 1 ,'28' 2 ,'12' 3 ,'8' 4 ,'5' 5 ,'4' 6 ,'0' 7)\n";        //TEST2
	gp<<"set xlabel \"Information rate - angle degree (°)  of the covered space \"\n";
	gp<<"set yrange [-0.001:]\n";
	gp<<"set ylabel \"Average gap (%)\"\n";

	gp<<"set terminal pngcairo size 2100,1300\n";


	gp<<"set grid\n";
	gp<<"do for[i=3:9]{\n";

		gp<<"set output \"AVG_"<<type_inst<<"_"<<size_inst<<"_T\".i.\".png\"\n";
		gp<<"set multiplot layout 3,4 columnsfirst rowsfirst title \" {/:Bold=15 Average time execution (second) for "<<size_inst<<" items ( instance "<<type_inst<<" - T\".i.\" )  - Comparison plot }\"\n";

		gp<<"size = "<<to_string(init_size)<<"\n";

		gp<<"do for[j=0:10]{\n";

			gp<<"set label 1 '{/:Bold=10 Size='.size.'}' at graph 0.05,0.95 font ',8'\n";

			gp<<"plot \""<<filename1<<"_T\".i.\".eval\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 1 w linespoints ls 1 title \""<<t1<<"\" ,"
					" \""<<filename2<<"_T\".i.\".eval\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 1 w linespoints ls 2 title \""<<t2<<"\"\n";

			gp<<"size = size + "<<to_string(steps)<<"\n";

		gp<<"}\n";

		gp<<"unset multiplot\n";
		gp<<"unset output\n";
	gp<<"}\n";




	gp<<"set ylabel \"Average time execution (second)\"\n";
	gp<<"set terminal pngcairo size 2100,1300\n";

	gp<<"set grid\n";
	gp<<"do for[i=3:9]{\n";

		gp<<"set output \"TIME_"<<type_inst<<"_"<<size_inst<<"_T\".i.\".png\"\n";
		gp<<"set multiplot layout 3,4 columnsfirst rowsfirst title \" {/:Bold=15 Average minimum distance from optimal solution using "<<size_inst<<" items ( "<<type_inst<<" - T\".i.\" ) }\"\n";

		gp<<"size = "<<to_string(init_size)<<"\n";

		gp<<"do for[j=0:10]{\n";

			gp<<"set label 1 '{/:Bold=10 Size='.size.'}' at graph 0.05,0.95 font ',8'\n";

			gp<<"plot \""<<filename1<<"_T\".i.\".eval\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 2 w linespoints ls 1 title \""<<t1<<"\","
					" \""<<filename2<<"_T\".i.\".eval\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 2 w linespoints ls 2 title \""<<t2<<"\"\n";

			gp<<"size = size + "<<to_string(steps)<<"\n";

		gp<<"}\n";
		gp<<"unset multiplot\n";
		gp<<"unset output\n";
	gp<<"}\n";

}





//NO EXTENSION FILENAMES
void Gnuplotter::AllPlot_DIST_TIME_PSize(string filename,string filename_variable, string type_inst, string size_inst,string algo,int init_size, int steps){

	Gnuplot gp;
	gp<<"set terminal pngcairo size 2400,1100\n";
	gp<<"set output \"AVG_"<<type_inst<<"_"<<size_inst<<"_"<<algo<<".png\"\n";

	gp<<"set multiplot layout 3,4 columnsfirst rowsfirst title \" {/:Bold=15 Average minimum distance from optimal solution using "<<size_inst<<" items ( "<<type_inst<<" ) }\"\n";

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
	gp<<"set style line 20 lt 1 lw 2 pt 7 ps 1.5 dt 1 lc rgb \"red\"   \n";

	gp<<"set grid\n";

	gp<<"set xtics ('90' 0 ,'41' 1 ,'28' 2 ,'12' 3 ,'8' 4 ,'5' 5 ,'4' 6 ,'0' 7)\n";        //TEST2
	gp<<"set xlabel \"Information rate - angle degree (°)  of the covered space \"\n";
//	gp<<"set yrange [-0.001:]\n";

	gp<<"set ylabel \"Average gap (%)\"\n";


	gp<<"do for[i=0:9] {\n";
		gp<<"set label 1 '{/:Bold=10 T'.i.'}' at graph 0.05,0.95 font ',8'\n";

		gp<<"plot for[j=0:10:2] \""<<filename<<"_T\".i.\".eval\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 1 w linespoints ls (j+1) "
				"title \" Size_{\".(j*"<<to_string(steps)<<"+"<<to_string(init_size)<<").\"} \" ,"
						" \""<<filename_variable<<"\" every ::(8*i + 1*i)::((i+1)*8 + 1*i) using 1 w linespoints ls 20 title 'Variable size'  \n";
	gp<<"}\n";


//	gp<<"plot for[j=0:9] \""<<filename<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 1 w linespoints ls (j+1) "
//			"title ' T_'.j \n";

	gp<<"unset multiplot\n";
	gp<<"unset output\n";

	gp<<"set ylabel \"Average time execution (second)\"\n";

	gp<<"set terminal pngcairo size 2400,1100\n";
	gp<<"set output \"TIME_"<<type_inst<<"_"<<size_inst<<"_"<<algo<<".png\"\n";

	gp<<"set multiplot layout 3,4 columnsfirst rowsfirst title \" {/:Bold=15 Average time execution (second) using "<<size_inst<<" items ( "<<type_inst<<" ) }\"\n";


	gp<<"do for[i=0:9] {\n";
		gp<<"set label 1 '{/:Bold=10 T'.i.'}' at graph 0.05,0.95 font ',8'\n";

		gp<<"plot for[j=0:10:2] \""<<filename<<"_T\".i.\".eval\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using (log($2)) w linespoints ls (j+1) "
			"title \" Size_{\".(j*"<<to_string(steps)<<"+"<<to_string(init_size)<<").\"} \" , "
				" \""<<filename_variable<<"\" every ::(8*i + 1*i)::((i+1)*8 + 1*i) using (log($2)) w linespoints ls 20 title 'Variable size'  \n";
	gp<<"}\n";



//	gp<<"plot for[j=0:9] \""<<filename<<"\" every ::(8*j + 1*j)::((j+1)*8 + 1*j) using 2 w linespoints ls (j+1) "
//			"title ' T_'.j \n";
}





void Gnuplotter::DIST_TIME_PSize_RESUM_X(string filename, string type_inst, string size_inst,string algo,int init_size, int steps){

	Gnuplot gp;
	int N_step = 21;
	gp<<"set terminal pngcairo size 1900,1400\n";

	gp<<"set colorsequence podo\n";
	gp<<"set style line 1 lt 1 lw 2 pt 1 ps 0.8 lc rgb 'red' \n";
	gp<<"set style line 2 lt 2 lw 2 pt 2 ps 0.8 lc rgb 'blue' \n";
	gp<<"set style line 3 lt 3 lw 2 pt 3 ps 0.8 lc rgb \"#e62e00\"   \n";
	gp<<"set style line 4 lt 4 lw 2 pt 4 ps 0.8 \n";
	gp<<"set style line 5 lt 5 lw 2 pt 5 ps 0.8 lc rgb \"#993366\"   \n";
	gp<<"set style line 6 lt 6 lw 2 pt 6 ps 0.8 \n";
	gp<<"set style line 7 lt 7 lw 2 pt 7 ps 0.8 \n";
	gp<<"set style line 8 lt 8 lw 2 pt 8 ps 0.8  lc rgb \"#1a75ff\"   \n";
	gp<<"set style line 9 lt 9 lw 2 pt 9 ps 0.8 lc rgb \"#c27982\"   \n";
	gp<<"set style line 10 lt 10 lw 2 pt 10 ps 0.8 lc rgb \"#993366\"   \n";
	gp<<"set style line 11 lt 11 lw 2 pt 11 ps 0.8 lc rgb \"#86b300\"   \n";
	gp<<"set style line 20 lt 1 lw 3 pt 7 ps 1.5  lc rgb \"red\"   \n";

	gp<<"set grid\n";
//	gp<<"unset key\n";
	gp<<"set key right bottom\n";

	string xtics = "";
	for(int i = 0; i < N_step ; i++){

		xtics += "'"+to_string(steps*i+init_size)+"' "+to_string(i);
//		if( i < N_step - 1 )
			xtics += ",";
		if( i == 0)
			init_size -= init_size;
	}

	gp<<"step = 0\n"; ///:INFORMATION RATE

	string filename2 = "./Data/DistTime/A/AVG_PS/I_100_AVG_PS";

	xtics += "'No-limit' "+to_string(N_step);

	gp<<"set xtics ("<<xtics<<") center offset 0,0 rotate by 75 right \n";
	gp<<"set xrange [0:"<<to_string(N_step+0.5)<<"]\n";
	gp<<"set xlabel \"Population size\"\n";
	gp<<"set yrange [-0.002:]\n";
	gp<<"set ylabel \"Average gap (%)\"\n";


	gp<<"set output \"AVG_"<<type_inst<<"_"<<size_inst<<"_"<<algo<<".png\"\n";
	gp<<"set multiplot layout 4,2 columnsfirst rowsfirst title \" {/:Bold=15 Average minimum distance from optimal solution when varying the size of the population using "<<size_inst<<" items ( "<<type_inst<<" ) }\"\n";

	gp<<"do for[i=0:7] {\n";
		gp<<"set label 1 '{/:Bold=10 T'.i.'}' at graph 0.05,0.95 font ',8'\n";
		gp<<"plot  \""<<filename<<"_T\".i.\"_\".step.\".eval\" using 1 w steps ls (1) title 'Diversification LTA',"
				" \""<<filename2<<"_T\".i.\"_\".step.\".eval\" using 1 w steps ls (2) title 'No Diversification\n";

	gp<<"}\n";



	gp<<"unset multiplot\n";
	gp<<"unset output\n";

	gp<<"set ylabel \"Average time execution (second)\"\n";

	gp<<"set output \"TIME_"<<type_inst<<"_"<<size_inst<<"_"<<algo<<".png\"\n";

	gp<<"set multiplot layout 4,2 columnsfirst rowsfirst title \" {/:Bold=15 Average time execution (second) when varying the size of the population using "<<size_inst<<" items ( "<<type_inst<<" ) }\"\n";


	gp<<"do for[i=0:7] {\n";
		gp<<"set label 1 '{/:Bold=10 T'.i.'}' at graph 0.05,0.95 font ',8'\n";
		gp<<"plot  \""<<filename<<"_T\".i.\"_\".step.\".eval\" using 2 w steps ls (1) title 'Diversification LTA',"
				" \""<<filename2<<"_T\".i.\"_\".step.\".eval\" using 2 w steps ls (2) title 'No Diversification\n";


	gp<<"}\n";





}

void Gnuplotter::INDICATORS_PSize_RESUM_X(string filename, string type_inst, string size_inst,string algo,int init_size, int steps){

	Gnuplot gp;

	gp<<"set terminal pngcairo size 1900,1400\n";


	gp<<"set colorsequence podo\n";
	gp<<"set style line 1 lt 1 lw 2 pt 1 ps 0.8 lc rgb 'red' \n";
	gp<<"set style line 2 lt 2 lw 2 pt 2 ps 0.8 lc rgb 'blue' \n";
	gp<<"set style line 3 lt 3 lw 2 pt 3 ps 0.8 lc rgb \"#e62e00\"   \n";
	gp<<"set style line 4 lt 4 lw 2 pt 4 ps 0.8 \n";
	gp<<"set style line 5 lt 5 lw 2 pt 5 ps 0.8 lc rgb \"#993366\"   \n";
	gp<<"set style line 6 lt 6 lw 2 pt 6 ps 0.8 \n";
	gp<<"set style line 7 lt 7 lw 2 pt 7 ps 0.8 \n";
	gp<<"set style line 8 lt 8 lw 2 pt 8 ps 0.8  lc rgb \"#1a75ff\"   \n";
	gp<<"set style line 9 lt 9 lw 2 pt 9 ps 0.8 lc rgb \"#c27982\"   \n";
	gp<<"set style line 10 lt 10 lw 2 pt 10 ps 0.8 lc rgb \"#993366\"   \n";
	gp<<"set style line 11 lt 11 lw 2 pt 11 ps 0.8 lc rgb \"#86b300\"   \n";
	gp<<"set style line 20 lt 1 lw 3 pt 7 ps 1.5  lc rgb \"red\"   \n";

	gp<<"set grid\n";
//	gp<<"unset key\n";
	gp<<"set key right bottom\n";

//	string xtics = "";
//	for(int i = 0; i < N_step ; i++){
//
//		xtics += "'"+to_string(steps*i+init_size)+"' "+to_string(i);
////		if( i < N_step - 1 )
//			xtics += ",";
//		if( i == 0)
//			init_size -= init_size;
//	}
//
//	xtics += "'No-limit' "+to_string(N_step);

	string filename2 = "./Data/ParetoFront/A/AVG_PS/I_100_AVG_PS";

	string xtics = "'1' 0,'2' 1,'4' 2,'6' 3,'8' 4,'10' 5,'15' 6,'20' 7,'40' 8,'60' 9,'80' 10,'100' 11,'200' 12,'No-limit' 13";//A

//	string xtics = "'1' 0,'2' 1,'4' 2,'6' 3,'10' 4,'15' 5,'20' 6,'60' 7,'100' 8,'140' 9,'200' 10,'300' 11,'No-limit' 12";//C


//	string xtics = "'1' 0,'2' 1,'5' 2,'8' 3,'10' 4,'30' 5,'60' 6,'100' 7,'150' 8,'300' 9,'250' 10,'350' 11,'No-limit' 12";//D


	gp<<"j = 50\n"; ///:INFORMATION RATE

	gp<<"set xtics ("<<xtics<<") center offset 0,0 rotate by 75 right \n";
	gp<<"set xrange [0:12]\n";
	gp<<"set xlabel \"Population size\"\n";
	gp<<"set yrange [-0.001:]\n";
	gp<<"set ylabel \"Average gap (%)\"\n";



	gp<<"set output \"D1_"<<type_inst<<"_"<<size_inst<<".png\"\n";
	gp<<"set multiplot layout 3,2 columnsfirst rowsfirst title \" {/:Bold=15 Average minimum distance from the optimal front (INDICATOR) when varying the size of the population using "<<size_inst<<" items ( "<<type_inst<<" ) }\"\n";

	gp<<"do for[i=3:3] {\n";

		gp<<"set label 1 '{/:Bold=10 T'.i.'}' at graph 0.05,0.95 font ',8'\n";
		gp<<"plot  \""<<filename<<"\".i.\"_\".j.\".front\" using 1 w steps ls (i+1) title ' ' \n";
//				" \""<<filename2<<"_T\".i.\"_\".j.\".front\" using 1 w steps ls (2) title 'No Diversification\n";

	gp<<"}\n";




	gp<<"unset multiplot\n";
	gp<<"unset output\n";


	gp<<"set ylabel \"Average MinMax distance\"\n";

	gp<<"set output \"D2_"<<type_inst<<"_"<<size_inst<<".png\"\n";

	gp<<"set multiplot layout 3,2 columnsfirst rowsfirst title \" {/:Bold=15 MaxMin distance from the optimal front (INDICATOR) when varying the size of the population using "<<size_inst<<" items ("<<type_inst<<") }\"\n";

	gp<<"do for[i=3:3] {\n";
		gp<<"set label 1 '{/:Bold=10 T'.i.'}' at graph 0.05,0.95 font ',8'\n";
		gp<<"plot  \""<<filename<<"\".i.\"_\".j.\".front\" using 2 w steps ls (i+1) title ' ' \n";
//				" \""<<filename2<<"_T\".i.\"_\".j.\".front\" using 2 w steps ls (2) title 'No Diversification\n";

	gp<<"}\n";




	gp<<"unset multiplot\n";
	gp<<"unset output\n";

	gp<<"set ylabel \"Proportion of pareto optimal solution (%)\"\n";

	gp<<"set output \"PR_"<<type_inst<<"_"<<size_inst<<".png\"\n";

	gp<<"set multiplot layout 3,2 columnsfirst rowsfirst title \" {/:Bold=15  Proportion of optimal solution (INDICATOR) when varying the size of the population using "<<size_inst<<" items ("<<type_inst<<")  }\"\n";

	gp<<"do for[i=3:3] {\n";
		gp<<"set label 1 '{/:Bold=10 T'.i.'}' at graph 0.05,0.95 font ',8'\n";
		gp<<"plot  \""<<filename<<"\".i.\"_\".j.\".front\" using 3 w steps ls (i+1) title ' ' \n";
//				" \""<<filename2<<"_T\".i.\"_\".j.\".front\" using 3 w steps ls (2) title 'No Diversification\n";

	gp<<"}\n";

}




void Gnuplotter::Plot_SEARCH_EVOLUTION(string filename, string type_inst, string size_inst,string algo, int size, int step,
		int opt_size, string opt_points_filename){

	string size_string = to_string(size);

	if( size == -1)
		size_string = "VARIABLE";

	Gnuplot gp;
	gp<<"set grid\n";
	gp<<"set colorsequence default\n";
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
	gp<<"set style line 12 lt 12 lw 2 pt 12 ps 0.8 dt 12 lc rgb \"#99cc00\"   \n";
	gp<<"set style line 13 lt 13 lw 2 pt 13 ps 0.8 dt 13 lc rgb \"#996633\"   \n";
	gp<<"set style line 14 lt 14 lw 2 pt 14 ps 0.8 dt 14 lc rgb \"#ccccff\"   \n";
	gp<<"set style line 15 lt 15 lw 2 pt 15 ps 0.8 dt 15 lc rgb \"#ff9999\"   \n";
	gp<<"set style line 16 lt 16 lw 2 pt 16 ps 0.8 dt 16 lc rgb \"#cc6666\"   \n";
	gp<<"set style line 17 lt 17 lw 2 pt 17 ps 0.8 dt 17   \n";
	gp<<"set style line 18 lt 18 lw 2 pt 18 ps 0.8 dt 18    \n";
	gp<<"set style line 19 lt 19 lw 2 pt 19 ps 0.8 dt 19    \n";
	gp<<"set style line 20 lt 20 lw 2 pt 20 ps 0.8 dt 20   \n";

	gp<<"set style line 1000 lc rgb '#cc1300' pt 3 ps 5 \n";

	gp<<"set xlabel 'x_1'\n";
	gp<<"set ylabel 'x_2'\n";
	gp<<"unset xtics \n";
	gp<<"unset ytics\n";
	gp<<"set key left bottom\n";
	gp<<"set terminal pngcairo size 1900,1400\n";

	gp<<"unset key\n";

	gp<<"do for[j=0:9] {\n";            /////////////////////////// TOMODIF





	if(size == -1 ){
//		gp<<"set terminal pngcairo size 1500,900\n";
		gp<<"set output \"PLOTTER_"<<type_inst<<"_"<<size_inst<<"_T\".j.\".png\"\n";
		size_string = "VARIABLE";

		gp<<"set title 'Evolution of the search space with "<<size_inst<<" items (Instances "<<type_inst<<" - T'.j.' ) - Variable population size' \n";

		gp<<"plot '"<<filename<<"-'.j.'.eff' title 'OPT front' ,  "
				"for[i=0:105] '"<<filename<<"-'.j.'_VARIABLE_"<<algo<<"_'.i.'.expl' using 1:2 "
						"title 'front '.i.'  (size '.(system('wc -l < "<<filename<<"-'.j.'_VARIABLE_"<<algo<<"_'.i.'.expl')).')' with points ls (i+1) ,"
				" \""<<opt_points_filename<<"\" with points ls 1000 title 'DMs preference' \n";
		gp<<"set grid\n";

	}

	else {
		gp<<"set output \"PLOTTER_"<<type_inst<<"_"<<size_inst<<"_T\".j.\".png\"\n";
		gp<<"set multiplot layout 3,4 columnsfirst rowsfirst title \" {/:Bold=15 Evolution of the local search using "<<size_inst<<" items ( "<<type_inst<<" - T\".j.\" ) }\"\n";

		gp<<"size = "<<size_string<<"\n";
		gp<<"while(size <= "<<to_string(opt_size)<<"){\n";
//			gp<<"if(size == 10 ){\n unset key}\n";
//			gp<<"else { set key }\n";
			gp<<"if( size != 1) {\n";
				gp<<"set label 1 '{/:Bold=10 Size='.(size"<<"-1"<<").'}' at graph 0.05,0.95 font ',8'\n";
			gp<<"}\n";
			gp<<"else {\n";
				gp<<"set label 1 '{/:Bold=10 Size='.(size).'}' at graph 0.05,0.95 font ',8'\n";
			gp<<"}\n";

			gp<<"plot '"<<filename<<"-'.j.'.eff' title 'OPT front' ,  "
					"for[i=3:150] '"<<filename<<"-'.j.'_'.size.'_"<<algo<<"_'.i.'.expl' using 1:2 "
					"title 'front '.i.'  (size '.(system('wc -l < "<<filename<<"-'.j.'_'.size.'_"<<algo<<"_'.i.'.expl ')).')' with points ls (i+1)"
					", \""<<opt_points_filename<<"\" with points ls 1000 title \"DMs preference\"\n";

			gp<<"size = size + "<<to_string(step)<<"\n";

		gp<<"}\n";

//		gp<<"set label 1 '{/:Bold=10 Unlimited size}' at graph 0.05,0.95 font ',8'\n";
//
//		gp<<"plot '"<<filename<<"-'.j.'.eff' title 'OPT front' ,  "
//				"for[i=1:105] '"<<filename<<"-'.j.'_VARIABLE_"<<algo<<"_'.i.'.expl' using 1:2 "
//				"title 'front '.i.'  (size '.(system('wc -l < "<<filename<<"-'.j.'_VARIABLE_"<<algo<<"_'.i.'.expl')).')' with points ls (i+1) ,"
//				" \""<<opt_points_filename<<"\" with points ls 1000 title 'DMs preference' \n";
//
//		gp<<"set grid\n";

		gp<<"unset multiplot\n";
		gp<<"unset output\n";

	}

	gp<<"}\n";


}





void Gnuplotter::Plot_SEARCH_EVOLUTION_WITH_INFO(string filename, string type_inst, string size_inst,string algo, int size, int step, int opt_size, string opt_points_filename){

	string size_string = to_string(size);

	if( size == -1)
		size_string = "VARIABLE";

	Gnuplot gp;
	gp<<"set grid\n";
	gp<<"set colorsequence default\n";
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
	gp<<"set style line 12 lt 12 lw 2 pt 12 ps 0.8 dt 12 lc rgb \"#99cc00\"   \n";
	gp<<"set style line 13 lt 13 lw 2 pt 13 ps 0.8 dt 13 lc rgb \"#996633\"   \n";
	gp<<"set style line 14 lt 14 lw 2 pt 14 ps 0.8 dt 14 lc rgb \"#ccccff\"   \n";
	gp<<"set style line 15 lt 15 lw 2 pt 15 ps 0.8 dt 15 lc rgb \"#ff9999\"   \n";
	gp<<"set style line 16 lt 16 lw 2 pt 16 ps 0.8 dt 16 lc rgb \"#cc6666\"   \n";
	gp<<"set style line 17 lt 17 lw 2 pt 17 ps 0.8 dt 17   \n";
	gp<<"set style line 18 lt 18 lw 2 pt 18 ps 0.8 dt 18    \n";
	gp<<"set style line 19 lt 19 lw 2 pt 19 ps 0.8 dt 19    \n";
	gp<<"set style line 20 lt 20 lw 2 pt 20 ps 0.8 dt 20   \n";

	gp<<"set style line 1000 lc rgb '#cc1300' pt 3 ps 5 \n";

	gp<<"set xlabel 'x_1'\n";
	gp<<"set ylabel 'x_2'\n";
	gp<<"unset xtics \n";
	gp<<"unset ytics\n";
//	gp<<"set key left bottom\n";


	gp<<"set terminal pngcairo size 1500,900\n";


	gp<<"do for[j=0:0]{\n";






	if(size == -1 ){
		gp<<"set output \"INFO_"<<type_inst<<"_"<<size_inst<<"_T\".j.\".png\"\n";
		gp<<"set multiplot layout 2,4 columnsfirst rowsfirst  title 'Evolution of the search space with different information rate - "<<size_inst<<" items (Instances "<<type_inst<<" - T'.j.' ) - Variable population size'\n";

		size_string = "VARIABLE";
		gp<<"unset key\n";
		gp<<"do for[step=0:7]{\n";
			gp<<"label = 0\n";
			gp<<"if (step==0){ label = 90 }\n if (step == 1){ label = 41}\n if (step == 2 ) { label = 28 }\n if (step == 3) { label = 12}"
					"\n if ( step == 4 ) { label = 8}\n if (step == 5) { label = 5 }\n if (step == 6) { label=4 }\n";
			gp<<"set label 1 '{/:Bold=10 '.label.'°}' at graph 0.05,0.95 font ',8'\n";

			gp<<"plot '"<<filename<<"-'.j.'.eff' title 'OPT front' ,  "
				"for[i=0:105] '"<<filename<<"-'.j.'_VARIABLE_'.i.'_'.step.'.expl' using 1:2 "
						"title 'front '.i.'  (size '.(system('wc -l < "<<filename<<"-'.j.'_VARIABLE_'.i.'_'.step.'.expl ')).')' with points ls (i+1) ,"
				" \""<<opt_points_filename<<"\" with points ls 1000 title 'DMs preference' \n";
		gp<<"set grid\n";

		gp<<"}\n";

	}

//	else {
//		gp<<"set terminal pngcairo size 2100,1400\n";
//		gp<<"set output \"INFO_"<<type_inst<<"_"<<size_inst<<"_T\".j.\".png\"\n";
//		gp<<"set multiplot layout 3,4 columnsfirst rowsfirst title \" {/:Bold=15 Evolution of the local search using "<<size_inst<<" items ( "<<type_inst<<" - T\".j.\" ) }\"\n";
//
//		gp<<"size = "<<size_string<<"\n";
//		gp<<"while(size <= "<<to_string(opt_size)<<"){\n";
////			gp<<"if(size == 10 ){\n unset key}\n";
////			gp<<"else { set key }\n";
//			gp<<"unset key\n";
//			gp<<"set label 1 '{/:Bold=10 Size='.size.'}' at graph 0.05,0.95 font ',8'\n";
//
//			gp<<"plot '"<<filename<<"-'.j.'.eff' title 'OPT front' ,  "
//					"for[i=1:150] '"<<filename<<"-'.j.'_'.size.'_'.i.'.expl' using 1:2 "
//					"title 'front '.i.'  (size '.(system('wc -l < "<<filename<<"-'.j.'_'.size.'_'.i.'.expl ')).')' with points ls (i+1)"
//					", \""<<opt_points_filename<<"\" with points ls 1000 title \"DMs preference\"\n";
//
//			gp<<"size = size + "<<to_string(step)<<"\n";
//
//		gp<<"}\n";
//
//
//		gp<<"set label 1 '{/:Bold=10 Variable size}' at graph 0.05,0.95 font ',8'\n";
//
//		gp<<"plot '"<<filename<<"-'.j.'.eff' title 'OPT front' ,  "
//				"for[i=1:150] '"<<filename<<"-'.j.'_VARIABLE_'.i.'.expl' using 1:2 "
//						"title 'front '.i.'  (size '.(system('wc -l < "<<filename<<"-'.j.'_VARIABLE_'.i.'.expl ')).')' with points ls (i+1) ,"
//				" \""<<opt_points_filename<<"\" with points ls 1000 title 'DMs preference' \n";
//
//		gp<<"set grid\n";
//
//
//
//	}


	//	#replot "Instances_Knapsack/Type_A/100_items/2KP100-TA-0_10XXXX.sol" title "final front" with points ls 14



//		gp<<"set terminal pngcairo size 2000,1400\n";
//		gp<<"set output \" PLOT.png\"\n";//"<<algo<<"_"<<type_inst<<"_"<<size_inst<<"_"<<size_string<<".png \"\n";
//		gp<<"unset output\n";
//	gp<<"}\n";

		gp<<"unset multiplot\n";
		gp<<"unset output\n";

	gp<<"}\n";


}



void Gnuplotter::Plot_SEARCH_EVOLUTION_WITH_INFO_PSize(string filename, string type_inst, string size_inst,string algo, int size, int step, int opt_size, string opt_points_filename){

	string size_string = to_string(size);

	if( size == -1)
		size_string = "VARIABLE";

	Gnuplot gp;
	gp<<"set grid\n";
	gp<<"set colorsequence default\n";
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
	gp<<"set style line 12 lt 12 lw 2 pt 12 ps 0.8 dt 12 lc rgb \"#99cc00\"   \n";
	gp<<"set style line 13 lt 13 lw 2 pt 13 ps 0.8 dt 13 lc rgb \"#996633\"   \n";
	gp<<"set style line 14 lt 14 lw 2 pt 14 ps 0.8 dt 14 lc rgb \"#ccccff\"   \n";
	gp<<"set style line 15 lt 15 lw 2 pt 15 ps 0.8 dt 15 lc rgb \"#ff9999\"   \n";
	gp<<"set style line 16 lt 16 lw 2 pt 16 ps 0.8 dt 16 lc rgb \"#cc6666\"   \n";
	gp<<"set style line 17 lt 17 lw 2 pt 17 ps 0.8 dt 17   \n";
	gp<<"set style line 18 lt 18 lw 2 pt 18 ps 0.8 dt 18    \n";
	gp<<"set style line 19 lt 19 lw 2 pt 19 ps 0.8 dt 19    \n";
	gp<<"set style line 20 lt 20 lw 2 pt 20 ps 0.8 dt 20   \n";

	gp<<"set style line 1000 lc rgb '#cc1300' pt 3 ps 5 \n";

	gp<<"set xlabel 'x_1'\n";
	gp<<"set ylabel 'x_2'\n";
	gp<<"unset xtics \n";
	gp<<"unset ytics\n";
	gp<<"set key left bottom\n";


	gp<<"set terminal pngcairo size 1500,900\n";


	gp<<"do for[j=0:0]{\n";

	gp<<"ub = "<<to_string(size)<<"\n";



	if(size != -1 ){
		gp<<"set output \"INFO_"<<type_inst<<"_"<<size_inst<<"_T\".j.\"_"<<algo<<"_\".ub.\".png\"\n";
		gp<<"set multiplot layout 2,4 columnsfirst rowsfirst  title 'Evolution of the search space with different information rate - "<<size_inst<<" items (Instances "<<type_inst<<" - T'.j.' ) - Variable population size'\n";

		size_string = "VARIABLE";
		gp<<"unset key\n";
		gp<<"do for[step=0:7]{\n";
			gp<<"label = 0\n";
			gp<<"if (step==0){ label = 90 }\n if (step == 1){ label = 41}\n if (step == 2 ) { label = 28 }\n if (step == 3) { label = 12}"
					"\n if ( step == 4 ) { label = 8}\n if (step == 5) { label = 5 }\n if (step == 6) { label=4 }\n";
			gp<<"set label 1 '{/:Bold=10 '.label.'°}' at graph 0.05,0.95 font ',8'\n";

			gp<<"plot '"<<filename<<"-'.j.'.eff' title 'OPT front' ,  "
				"for[i=1:80] '"<<filename<<"-'.j.'_'.ub.'_"<<algo<<"_'.i.'_INFO_'.step.'.expl' using 1:2 "
						"title 'front '.i.'  (size '.(system('wc -l < "<<filename<<"-'.j.'_'.ub.'_"<<algo<<"_'.i.'_INFO_'.step.'.expl' )).')' with points ls (i+1) ,"
				" \""<<opt_points_filename<<"\" with points ls 1000 title 'DMs preference' \n";
		gp<<"set grid\n";

		gp<<"}\n";

	}



		gp<<"unset multiplot\n";
		gp<<"unset output\n";

	gp<<"}\n";


}



