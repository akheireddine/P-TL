j=0
for i in *machine*
do
j=$((j-$i))
mv Pop_$i.pop Pop_$j.pop
done
