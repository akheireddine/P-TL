sizer = "2 8 20 60 100"

array uncertainty[8]
uncertainty[1] = 90
uncertainty[2] = 41
uncertainty[3] = 28
uncertainty[4] = 12
uncertainty[5] = 10
uncertainty[6] = 8
uncertainty[7] = 4
uncertainty[8] = 0


unset ytics
unset xtics
set terminal pngcairo size 1600,1200

#set key at screen 0.9,screen 0.9
unset key
set colorsequence default
set grid


type = "A"
info = "0"
length = "100"
algo = "MOLS_PSize"


# line styles
set style line 1 lt 1 lc rgb '#A6CEE3' # light blue
set style line 2 lt 1 lc rgb '#1F78B4' # dark blue
set style line 3 lt 1 lc rgb '#B2DF8A' # light green
set style line 4 lt 1 lc rgb '#33A02C' # dark green
set style line 5 lt 1 lc rgb '#FB9A99' # light red
set style line 6 lt 1 lc rgb '#E31A1C' # dark red
set style line 7 lt 1 lc rgb '#FDBF6F' # light orange
set style line 8 lt 1 lc rgb '#FF7F00' # dark orange

# palette
set palette maxcolors 8
set palette defined ( 0 '#A6CEE3',\
    	    	      1 '#1F78B4',\
		      2 '#B2DF8A',\
		      3 '#33A02C',\
		      4 '#FB9A99',\
		      5 '#E31A1C',\
		      6 '#FDBF6F',\
		      7 '#FF7F00' )


set colorbox user vertical origin 0.8,0.03 size 0.03,0.25 front
set cbtics ('236 Hz' 236,'1296 Hz' 1296) offset 0,0.5 scale 0

#set palette rgb 33,13,10; set title "rainbow (blue-green-yellow-red)"; splot g(x)



do for[i=0:0]{ 

do for[s in sizer]{
set output "EVOL_POP_".type."_".length."_T".i."_S".s.".png"

set multiplot layout 3,3 columnsfirst rowsfirst title " {/:Bold=15 Evolution of the Population with szie ".s." (instance T".i."-".type.") }"

do for[j=0:7]{

set label 1 "{/:Bold=10 ".uncertainty[j+1]." ° }" at graph 0.05,0.95 font ",8"

filename = "./Data/Population/".type."/".length."/T".i."/".algo."/".s."/".j."/Pop_0.pop"

stats filename using 4 nooutput
set style data points

plot for [k=STATS_min+1:STATS_max] filename using 1:($4==k?$2:1/0):4 with points lt 1 pt k palette 
} 
unset multiplot
unset output
}
}


