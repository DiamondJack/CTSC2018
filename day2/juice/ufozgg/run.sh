
for((i=1;i<=3;++i))
do
cp ../down/$i.in ./x$i.in
time ./force <x$i.in >x$i.ans
diff ../down/$i.ans x$i.ans
rm x$i.in x$i.ans
echo sample$i checked
done


for((i=1;i<=20;i+=2))
do
cp ../data/$i.in .
time ./force <$i.in >$i.ans
diff ../data/$i.ans $i.ans
rm $i.in $i.ans
echo data$i checked
done
