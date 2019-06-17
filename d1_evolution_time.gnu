sizer = "100 60 20 8 2"

set xlabel "time CPU (second)"
set ylabel "Average minimum distance "
set xrange [0:50]
unset ytics


set terminal pngcairo size 1200,800

set key at screen 0.9,screen 0.9
unset key
set colorsequence default
set grid


type = "A"
info = "0"

do for[i=0:0]{ 
set output "EVOL_A_100_D1_Time_T".i.".png"

set multiplot layout 2,2 columnsfirst rowsfirst title " {/:Bold=15 Evolution of the average minimum indicator with time execution  (instance T".i."-".type." }"
do for[s in sizer]{
set label 1 "{/:Bold=10Size".s."}" at graph 0.05,0.95 font ",8"
plot for[k=0:4] "./Instances_Knapsack/Type_A/100_items/2KP100-TA-".i."_".info."_".s.".ev" u ($4==k?($3,$1):1/0) w lines lw 2 
}
unset multiplot
unset output
}



sizer = "2 8 20 60 100"
array uncertainty[8]
uncertainty[1] = 90
uncertainty[2] = 41 
uncertainty[3] = 28
uncertainty[8] = 0
set xlabel "time CPU (second)"
set grid
unset key
unset ylabel
set terminal pngcairo size 1400,1000

do for[i=0:9]{

do for[s in sizer]{
set output "test_evol_D1_TIME_T".i."_s".s.".png"
set multiplot layout 2,2 columnsfirst rowsfirst title " {/:Bold=15 Evolution of the Average minimum distance from optimal front with time (second) - T".i." - Population size ".s." }"

do for[j in "0 1 2 7"]{
set label 1 "{/:Bold=10 ".uncertainty[j+1]." ° }" at graph 0.85,0.95 font ",8"
plot for[k=0:9] "./Data/Evaluation/A/100/T0/MOLS_PSize/".s."/".j."/K_".k.".iter" w linespoints title "Replication_".k
}
unset multiplot
unset output
}
}




