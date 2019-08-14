set colorsequence podo
set terminal pngcairo size 1200,800


path="./Data/Evaluation2"
file_plot = "'/A/100/AVG_K_30.evalRAPPORT' '/A/200/AVG_K_30.evalRAPPORT' '/C/100/AVG_K_20.evalRAPPORT' "

label = "A-100 A-200 C-100"


set grid
set xlabe "Degré d'information (°)"
set ylabel "D1"


set output "Info_D1_REPPORT.png"


plot for[f,l in file_plot,label] path.f using 6:8 w linespoints w title l


unset output
