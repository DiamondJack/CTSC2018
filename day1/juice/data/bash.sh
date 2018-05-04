for((i=1;i<=21;++i))
do
	./dmk.exe $i
	./juice
	mv juice.in $i.in
	mv juice.out $i.ans
done