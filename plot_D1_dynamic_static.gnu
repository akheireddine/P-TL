
set colorsequence podo
set terminal pngcairo size 1200,800



p = 2
type ="A"
taille ="100"

#Type,  Size,  Instance,  Budget,  PopSize,  Info,  nb_evaluation,  AVG_dist,  MaxMin,  PR,  Diversification




set xlabe "Budget"
set ylabel "AVG minimum distance"
info=90
pop_size=100
div="FALSE"

set output "D1_budget_dyn_stat_Div0.png"

set multiplot layout 2,2 columnsfirst rowsfirst title " {/:Bold=15 Compare Static & Dynamic algorithm varying the Population size }"


do for[i=0:2]{
plot x0 = y0 = NaN, "./Data/Evaluation".p."/".type."/".taille."/K_30.eval" u ($5==pop_size && $3==i && $6==info && stringcolumn(11) eq div?(y0=$8,x0=$4) : x0):(y0) w lp lc rgb "red" pt i lw 1.5 title "T".i." (static)",  x0 = y0 = NaN, "./Data/Evaluation".p."/".type."/".taille."/K_25.evalS" u ($3==i && $6==info && stringcolumn(11) eq div?(y0=$8,x0=$4) : x0):(y0) w lp lc rgb "blue" pt i lw 1.5 title "T".i." (dynamic)" 
}
unset multiplot
unset output




div = 0
popsize = 100
i = 5

set output "test3D.png"
set terminal pngcairo size 1200,800
set dgrid3d 410,410
set hidden3d
set xlabel "D1"
set ylabel "Info"
splot x0 = y0 = z0 = NaN, "K_20.eval" u ($5==popsize && $11==div && $3==i ?(x0=$8,y0=$6,z0=$4) : x0=x0,y0=y0,z0=z0) w lines
unset output
