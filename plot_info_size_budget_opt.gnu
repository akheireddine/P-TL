
set colorsequence podo
set terminal pngcairo size 1200,800

set output "opt_size_budget.png"
set datafile separator " "

p = 2
type ="A"
taille ="100"

#Type, Size, Budget, Instance, Diversification, PopSize, Info, AVG_dist, MaxMin, PR



plot for[i=0:4] x0 = y0 = NaN, "./Data/Evaluation".p."/".type."/".taille."/K_30.algo" u ($4==i?(y0=$6,x0=$3) : x0):(y0) w lp linetype (i+1) pt i lw 1.5 title "T".i
unset output




set output "opt_info_budget.png"
set datafile separator " "
plot for[i=0:4] x0 = y0 = NaN, "./Data/Evaluation".p."/".type."/".taille."/K_30.algo" u ($4==i?(y0=$7,x0=$3) : x0):(y0) w lp linetype (i+1)  pt i lw 1.5 title "T".i
unset output







