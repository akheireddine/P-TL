array sizer[6]
sizer[1] = 2
sizer[2] = 8
sizer[3] = 20
sizer[4] = 60
sizer[5] = 100
sizer[6] = 200

type = "A"
algo = "MOLS_PSize"
length = "200"
replic = "10"
i = 0

set key at screen 0.9,screen 0.3
#set key at screen 0.63,screen 0.4

set xtics ('41' 0 ,'28' 1 ,'12' 2 ,'10' 3,'8' 4,'4' 5, '0' 6 )     
set xlabel "Information rate (degree)"
set grid
set terminal pngcairo size 1400,1000
set colorsequence podo

do for[i=0:2]{


set output "evol_V1V2_".type."_".length."_D1_INFO_T".i.".png"
set multiplot layout 2,3 columnsfirst rowsfirst title " {/:Bold=15 Evolution of the Average minimum distance from optimal front with uncertainty  - T".i." }"

do for[j in "0 1 2 3 4"]{
set label 1 "{/:Bold=10 Size_{".sizer[j+1]."} }" at graph 0.85,0.95 font ",8"
plot "./Data/Evaluation/".type."/".length."/T".i."/".algo."/K_".replic.".v1" every ::(7*j + 1*j)::((j+1)*7 + 1*j) using 5 w linespoints title "w/o information + filtering",  "./Data/Evaluation/".type."/".length."/T".i."/".algo."/K_".replic.".v2" every ::(7*j + 1*j)::((j+1)*7 + 1*j) using 5 w linespoints title "w/o information", "./Data/Evaluation/".type."/".length."/T".i."/".algo."/K_".replic.".eval" every ::(7*j + 1*j  + 1)::((j+1)*7 + 1*j) using 5 w linespoints title "w information",
}
unset multiplot
unset output
}


#AVG


array sizer[6]
sizer[1] = 2
sizer[2] = 8
sizer[3] = 20
sizer[4] = 60
sizer[5] = 100
sizer[6] = 200


type = "A"
length = "200"
replic = "10"

set key at screen 0.9,screen 0.3
#set key at screen 0.63,screen 0.4

set xtics ('41' 0 ,'28' 1 ,'12' 2 ,'10' 3,'8' 4,'4' 5, '0' 6 )        
set xlabel "Information rate (degree)"
set grid
set terminal pngcairo size 1400,1000
set colorsequence podo


set output "evol_V1V2_".type."_".length."_D1_INFO.png"

set multiplot layout 2,3 columnsfirst rowsfirst title " {/:Bold=15 Evolution of the Average minimum distance from optimal front with uncertainty - AVG of 3 instances ".type."  }"

do for[j in "0 1 2 3 4"]{

set label 1 "{/:Bold=10 Size_{".sizer[j+1]."} }" at graph 0.85,0.95 font ",8"

plot "./Data/Evaluation/".type."/".length."/AVG_K_".replic.".v1" every ::(7*j + 1*j)::((j+1)*7 + 1*j) using 5 w linespoints title "w/o information + filtering",  "./Data/Evaluation/".type."/".length."/AVG_K_".replic.".v2" every ::(7*j + 1*j)::((j+1)*7 + 1*j) using 5 w linespoints title "w/o information", "./Data/Evaluation/".type."/".length."/AVG_K_".replic.".eval" every ::(7*j + 1*j  + 1)::((j+1)*7 + 1*j) using 5 w linespoints title "w information",
}
unset multiplot
unset output













########## OS


array sizer[5]
sizer[1] = 2
sizer[2] = 8
sizer[3] = 20
sizer[4] = 60
sizer[5] = 100


type = "A"
algo = "MOLS_PSize_DIV/OS"
length = "100"
replic = "30"
i = 0

set key at screen 0.9,screen 0.3

set xtics ('41' 0 ,'28' 1 ,'12' 2 ,'10' 3,'8' 4,'4' 5, '0' 6 )     
set xlabel "Information rate (degree)"
set grid
set terminal pngcairo size 1400,1000
set colorsequence podo

do for[i=0:4]{


set output "evol_V1V2_".type."_".length."_OS_D1_INFO_T".i.".png"
set multiplot layout 2,3 columnsfirst rowsfirst title " {/:Bold=15 Evolution of the Average minimum distance from optimal front with uncertainty  - T".i."  + Diversification (OS)  }"

do for[j in "0 1 2 3 4"]{
set label 1 "{/:Bold=10 Size_{".sizer[j+1]."} }" at graph 0.85,0.95 font ",8"
plot "./Data/Evaluation/".type."/".length."/T".i."/".algo."/K_".replic.".v1" every ::(7*j + 1*j)::((j+1)*7 + 1*j) using 5 w linespoints title "w/o information + filtering",  "./Data/Evaluation/".type."/".length."/T".i."/".algo."/K_".replic.".v2" every ::(7*j + 1*j)::((j+1)*7 + 1*j) using 5 w linespoints title "w/o information", "./Data/Evaluation/".type."/".length."/T".i."/".algo."/K_".replic.".eval" every ::(7*j + 1*j  + 1)::((j+1)*7 + 1*j) using 5 w linespoints title "w information",
}
unset multiplot
unset output
}


#AVG


array sizer[5]
sizer[1] = 2
sizer[2] = 8
sizer[3] = 20
sizer[4] = 60
sizer[5] = 100


type = "A"
length = "100"
replic = "30"

set key at screen 0.9,screen 0.3

set xtics ('41' 0 ,'28' 1 ,'12' 2 ,'10' 3,'8' 4,'4' 5, '0' 6 )        
set xlabel "Information rate (degree)"
set grid
set terminal pngcairo size 1400,1000
set colorsequence podo


set output "evol_V1V2_".type."_".length."_OS_D1_INFO.png"

set multiplot layout 2,3 columnsfirst rowsfirst title " {/:Bold=15 Evolution of the Average minimum distance from optimal front with uncertainty - AVG of 5 instances ".type." + Div. (OS) }"

do for[j in "0 1 2 3 4"]{

set label 1 "{/:Bold=10 Size_{".sizer[j+1]."} }" at graph 0.85,0.95 font ",8"

plot "./Data/Evaluation/".type."/".length."/AVG_OS_K_".replic.".v1" every ::(7*j + 1*j)::((j+1)*7 + 1*j) using 5 w linespoints title "w/o information + filtering",  "./Data/Evaluation/".type."/".length."/AVG_OS_K_".replic.".v2" every ::(7*j + 1*j)::((j+1)*7 + 1*j) using 5 w linespoints title "w/o information", "./Data/Evaluation/".type."/".length."/AVG_OS_K_".replic.".eval" every ::(7*j + 1*j  + 1)::((j+1)*7 + 1*j) using 5 w linespoints title "w information",
}
unset multiplot
unset output












