set grid
set colorsequence default



set style line 1000 lc rgb '#cc1300' pt 3 ps 5

set xlabel 'x_1'
set ylabel 'x_2'
set zlabel 'x_3'
unset xtics
unset ytics
unset ztics
set terminal pngcairo size 1300,1000


filename_OPT="Instances_Knapsack3/Type_A/100_items/2KP100-TA-0.eff"

filename_plot="Data/Population3/A/100/T3/MOLS_PSize/100"


#set cbrange [1:15]

#set palette defined ( 1 "red", 2 "orange", 3 "yellow", 4 "blue", 5 "red", 6 "blue", 7 "violet", 8 "#1a75ff", 9 "#c27982", 10 "#993366", 11 "#86b300", 12 "#99cc00" , 13 "#996633" , 14 "#ff9999" , 15 "#cc6666" )


info = "0 1 2 4 6 7"

set cbrange [1:42]

# line styles
set style line 1 lt 1 lc rgb '#D53E4F' # red
set style line 2 lt 1 lc rgb '#F46D43' # orange
set style line 3 lt 1 lc rgb '#FDAE61' # pale orange
set style line 4 lt 1 lc rgb '#FEE08B' # pale yellow-orange
set style line 5 lt 1 lc rgb '#E6F598' # pale yellow-green
set style line 6 lt 1 lc rgb '#ABDDA4' # pale green
set style line 7 lt 1 lc rgb '#66C2A5' # green
set style line 8 lt 1 lc rgb '#3288BD' # blue

# palette
set palette defined ( 1 '#D53E4F',\
    	    	      10 '#F46D43',\
		      15 '#FDAE61',\
		      20 '#FEE08B',\
		      25 '#E6F598',\
		      30 '#ABDDA4',\
		      35 '#66C2A5',\
		      42 '#3288BD' )


j=3

set output "INFO_A_100_T".j.".png";
set multiplot layout 2,2 columnsfirst rowsfirst  title 'Evolution of the search space with different information rate - 100 items (Instances A - T3 )
unset key
do for[step in info]{
splot filename_OPT title 'OPT front' , filename_plot."/".step."/Pop_0.pop" using 1:2:3:5 with points lc palette z 
}
unset multiplot
unset output



























