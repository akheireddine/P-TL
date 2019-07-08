
set colorsequence podo
set terminal pngcairo size 1200,800



p = 2
type ="A"
taille ="100"
div = "FALSE"


#Type,  Size,  Instance,  Budget,  PopSize,  Info,  nb_evaluation,  AVG_dist,  MaxMin,  PR,  Diversification

set output "OPT_size_budget_div0.png"
plot for[i=0:0] x0 = y0 = NaN, "./Data/Evaluation".p."/".type."/".taille."/K_30.algo" u ($3==i && stringcolumn(11) eq div?(y0=$5,x0=$4) : x0):(y0) w lp linetype (i+1) pt i lw 1.5 title "T".i
unset output



set output "OPT_info_budget_div0.png"
set datafile separator " "
plot for[i=0:9] x0 = y0 = NaN, "./Data/Evaluation".p."/".type."/".taille."/K_30.algo" u ($3==i && stringcolumn(11) eq div? (y0=$76,x0=$4) : x0):(y0) w lp linetype (i+1)  pt i lw 1.5 title "T".i
unset output







