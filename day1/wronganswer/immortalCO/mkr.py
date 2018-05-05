from random import *
N = 366
V = 2017011328

print N
for k in xrange(2):
	for i in xrange(1, N):
		print randint(1, i), i + 1, randint(-int(V**0.5), V)
	print