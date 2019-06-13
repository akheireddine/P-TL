sizer =  "100 80 60 20 8 2"
array sizer[7]
sizer[1]=100
sizer[2]=80
sizer[3]=60
sizer[4]=20
sizer[5]=14
sizer[6]=8
sizer[7]=2

index_size = "0 2 3 5 6"

set xtics ('90' 0 ,'41' 1 ,'28' 2 ,'12' 3, '0' 4 )     
set xlabel "Information rate - angle degree (°)  of covered space"
set ylabel "Average minimum distance (%)"
unset ytics
set output "AVG_A_100_D1_Info.png"
set terminal pngcairo size 1200,800

set key at screen 0.81,screen 0.9

set colorsequence default
set grid
set multiplot layout 2,2 columnsfirst rowsfirst title " {/:Bold=15 Evolution of the average minimum indicator regarding the information rate }"


type = "A"

do for[i=0:3]{ 
set label 1 "{/:Bold=10T".i."}" at graph 0.05,0.95 font ",8"
plot for[j in index_size] "./Data/ParetoFront/".type."/I_100_AVG_PS".i.".front" every ::(5*j + 1*j)::((j+1)*5 + 1*j) using 1 w linespoints lw 2 title "size_{".sizer[j+1]."}
}
unset multiplot
unset output

