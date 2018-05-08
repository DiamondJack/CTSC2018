from os import *
from sys import *
from random import *
system("g++ ../immortalCO/mkr.cpp -o mkr -O2 -std=c++11")

for i in xrange(1, 5):
	system("echo 10 > %d.in" % i)
	for j in xrange(10):
		system("echo n=80 m=8 | ./mkr >> %d.in" % i)

for i in xrange(5, 7):
	system("echo 10 > %d.in" % i)
	for j in xrange(10):
		if i == 6:
			system("echo n=80 m=-1 chain | ./mkr >> %d.in" % i)
		else:
			system("echo n=80 m=1000 chain | ./mkr >> %d.in" % i)
		system("echo n=80 m=200 chain | ./mkr >> %d.in" % i)
		
for i in xrange(7, 11):
	system("echo 100 > %d.in" % i)
	for j in xrange(100):
		C = ""
		if randint(0, 1) == 0:
			C = "keep"
		if i == 9:
			system("echo n=200 m=233 chain %s | ./mkr  >> %d.in" % (C, i))
		elif i == 10:
			system("echo n=200 m=10000 chain %s | ./mkr  >> %d.in" % (C, i))
		else:
			system("echo n=200 m=-1 chain %s | ./mkr  >> %d.in" % (C, i))

for i in xrange(11, 13):
	system("echo 100 > %d.in" % i)
	for j in xrange(100):
		C = ""
		if randint(0, 1) == 0:
			C += " keep"
		if randint(0, 1) == 0:
			C += " chain"
		if i == 11:
			system("echo n=80 m=10000 %s | ./mkr >> %d.in" % (C, i))
		else:
			system("echo n=80 m=-1 %s | ./mkr >> %d.in" % (C, i))

for i in xrange(13, 21):
	system("echo 100 > %d.in" % i)
	for j in xrange(100):
		C = "chain" if randint(0, 1) == 0 else ""
		if i == 14 or i == 16 or i == 18 or i == 20:
			C = "chain" if randint(1, 20) != 1 else ""
		if randint(0, 1) == 0 and i != 17 and i != 18:
			C += " keep"
		if i == 13 or i == 14:
			system("echo n=200 m=-1 %s | ./mkr >> %d.in" % (C, i))
		elif i == 15 or i == 16:
			system("echo n=200 m=500 %s | ./mkr >> %d.in" % (C, i))
		elif i == 17 or i == 18:
			system("echo n=200 m=100000 %s | ./mkr >> %d.in" % (C, i))
		else:
			system("echo n=200 m=%d %s | ./mkr >> %d.in" % (randint(1, 200), C, i))


system("g++ ../immortalCO/poly.cpp -o tmp -O2 -std=c++11")

for i in xrange(1, 21):
	system("/usr/bin/time ./tmp < %d.in > %d.ans" % (i, i))
