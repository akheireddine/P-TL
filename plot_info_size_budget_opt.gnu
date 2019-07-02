
set colorsequence podo
set terminal pngcairo size 1200,800

set output "opt_size_budget.png"
set datafile separator " "

p = 2
type ="A"
taille ="100"


plot for[i=0:5] x0 = y0 = NaN, "./Data/Evaluation".p."/".type."/".taille."/K_30_A100.algo" u ($2==i?(y0=$4,x0=$1) : x0):(y0) w lp linetype (i+1)  pt i lw 1.5 title "T".i
unset output




set output "opt_info_budget.png"
set datafile separator " "
plot for[i=0:5] x0 = y0 = NaN, "./Data/Evaluation".p."/".type."/".taille."/K_30_A100.algo" u ($2==i?(y0=$5,x0=$1) : x0):(y0) w lp linetype (i+1)  pt i lw 1.5 title "T".i
unset output







