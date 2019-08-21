set grid
set colorsequence default
set style line 1 lt 1 lw 2 pt 1 ps 0.8 dt 1
set style line 2 lt 2 lw 2 pt 2 ps 0.8 dt 2
set style line 3 lt 3 lw 2 pt 3 ps 0.8 dt 3 lc rgb "#e62e00"   
set style line 4 lt 4 lw 2 pt 4 ps 0.8 dt 4
set style line 5 lt 5 lw 2 pt 5 ps 0.8 dt 5
set style line 6 lt 6 lw 2 pt 6 ps 0.8 dt 6
set style line 7 lt 7 lw 2 pt 7 ps 0.8 dt 7
set style line 8 lt 8 lw 2 pt 8 ps 0.8 dt 8 lc rgb "#1a75ff"   
set style line 9 lt 9 lw 2 pt 9 ps 0.8 dt 9 lc rgb "#c27982"   
set style line 10 lt 10 lw 2 pt 10 ps 0.8 dt 10 lc rgb "#993366"   
set style line 11 lt 11 lw 2 pt 11 ps 0.8 dt 11 lc rgb "#86b300"   
set style line 12 lt 12 lw 2 pt 12 ps 0.8 dt 12 lc rgb "#99cc00"   
set style line 13 lt 13 lw 2 pt 13 ps 0.8 dt 13 lc rgb "#996633"   
set style line 14 lt 14 lw 2 pt 14 ps 0.8 dt 14 lc rgb "#ccccff"   
set style line 15 lt 15 lw 2 pt 15 ps 0.8 dt 15 lc rgb "#ff9999"   
set style line 16 lt 16 lw 2 pt 16 ps 0.8 dt 16 lc rgb "#cc6666"   
set style line 17 lt 17 lw 2 pt 17 ps 0.8 dt 17   
set style line 18 lt 18 lw 2 pt 18 ps 0.8 dt 18   
set style line 19 lt 19 lw 2 pt 19 ps 0.8 dt 19   
set style line 20 lt 20 lw 2 pt 20 ps 0.8 dt 20   

set style line 1000 lc rgb '#cc1300' pt 3 ps 5 

set xlabel 'x_1'
set ylabel 'x_2'
unset xtics 
unset ytics
set key left bottom
set terminal pngcairo size 1900,1400

unset key
file_opt = "Instances_Knapsack2/Type_A/100_items/2KP100-TA-8.eff"
filename = "Data/Population2/A/100/T8/MOLS_PSize_DIV/OS"
opt_points_filename = "DM_preference_point"

set output "PLOTTER.png"
set multiplot layout 3,4 columnsfirst rowsfirst title " {/:Bold=15 Evolution of the local search A100 - T8 }"
do for[j=0:1]{

plot file_opt title "OPT front" , x=0,y=0,ind=0, filename."/100/".j."/Pop_0.pop" using ($4 > -1 ?(x=$1, y=$2, ind=$4): NaN) with points ls (ind) , opt_points_filename with points ls 1000 title "DMs preference"

unset multiplot
unset output
}

