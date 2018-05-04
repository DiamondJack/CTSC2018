

for((i=2;i<=20;i+=2))
do
cp ../data/$i.in .
time ./force <$i.in >$i.ans
diff ../data/$i.ans $i.ans
rm $i.in $i.ans
echo data$i checked
done
