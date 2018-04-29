n=(-1 5 40 40 40 40 100 100 100 100 100)
Q=(-1 21 199992 199993 199994 199995 199996 199997 199998 199999 200000)
C=(-1 6 400 400 400 400 0 1000 1000 1000 1000)
Type=(-1 0 1 2 0 0 0 3 0 0 0)

seedList=$(cat seed.txt)

i=0
make gen

for seed in $seedList
do
	((++i))
	echo "./gen $seed ${n[i]} ${Q[i]} ${C[i]} ${Type[i]} >$i.in"
	./gen $seed ${n[i]} ${Q[i]} ${C[i]} ${Type[i]} >$i.in
done
