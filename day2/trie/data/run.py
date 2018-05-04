from os import *
from sys import *
system("g++ ../immortalCO/mkr.cpp -o mkr -O2 -std=c++11")

system("echo n=50 m=5 | ./mkr > 1.in")
system("echo n=80 m=8 | ./mkr > 2.in")
system("echo n=80 m=8 | ./mkr > 3.in")
system("echo n=80 m=8 | ./mkr > 4.in")
system("echo n=80 m=-1 chain | ./mkr > 5.in")
system("echo n=80 m=80 chain | ./mkr > 6.in")
system("echo n=300 m=-1 chain | ./mkr > 7.in")
system("echo n=300 m=233 chain | ./mkr > 8.in")
system("echo n=300 m=10000 chain | ./mkr > 9.in")
system("echo n=80 m=-1 | ./mkr > 10.in")
system("echo n=80 m=30 | ./mkr > 11.in")
system("echo n=80 m=100 | ./mkr > 12.in")
system("echo n=300 m=-1 | ./mkr > 13.in")
system("echo n=300 m=30 | ./mkr > 14.in")
system("echo n=300 m=50 | ./mkr > 15.in")
system("echo n=300 m=100 | ./mkr > 16.in")
system("echo n=300 m=450 chain | ./mkr > 17.in")
system("echo n=300 m=200 | ./mkr > 18.in")
system("echo n=300 m=10000 chain | ./mkr > 19.in")
system("echo n=300 m=100000 | ./mkr > 20.in")

system("g++ ../immortalCO/poly.cpp -o tmp")

for i in xrange(1, 21):
	system("/usr/bin/time ./tmp < %d.in > %d.ans" % (i, i))
