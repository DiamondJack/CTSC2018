from os import *
if True:
	system("pypy mkr.py N=36 BB=[0,0] PP=[[6],[6]] VL=1 VR=1 NoShuf=True > 1.in");
	system("pypy mkr.py N=366 BB=[0,0] PP=[[1,2,3,4],[1,2,3,4]] VL=1 VR=1 > 2.in");
	system("pypy mkr.py N=1388 BB=[0,0] PP=[[1,2,3,4],[1,2,3,4]] VL=0 VR=2017011328 > 3.in");
	system("pypy mkr.py N=1999 BB=[0,0] PP=[[1],[1,2,3,4]] VL=0 VR=2017011328 > 4.in");
	system("pypy mkr.py N=2666 BB=[0,0] PP=[[1],[1,2,3,4]] VL=0 VR=2017011328 > 5.in");
	system("pypy mkr.py N=5666 BB=[0,0] PP=[[1,2,3,4],[1,2,3,4]] VL=-2017011328 VR=2017011328 > 6.in");
	system("pypy mkr.py N=8666 BB=[0,0] PP=[[1],[1,2,3,4]] VL=-2017011328 VR=2017011328 > 7.in");
	system("pypy mkr.py N=11111 BB=[0,0] PP=[[6],[1,2,3,4]] VL=-2017011328 VR=2017011328 > 8.in");
	system("pypy mkr.py N=12345 BB=[0,0] PP=[[6],[1,2,3,4]] VL=-2017011328 VR=2017011328 > 9.in");
	system("pypy mkr.py N=188888 BB=[1,1] PP=[[6],[6]] VL=0 VR=2017011328 NoShuf=True > 10.in");
	system("pypy mkr.py N=366666 BB=[1,1] PP=[[6],[6]] VL=-2017011328 VR=2017011328 NoShuf=True > 11.in");
	system("pypy mkr.py N=188888 BB=[1,0] PP=[[6],[1,2,3,4]] VL=0 VR=2017011328 NoShuf=True > 12.in");
	system("pypy mkr.py N=366666 BB=[1,0] PP=[[6],[1,2,3,4]] VL=0 VR=2017011328 NoShuf=True > 13.in");
	system("pypy mkr.py N=366666 BB=[1,0] PP=[[6],[1,2,3,4]] VL=-2017011328 VR=2017011328 NoShuf=True > 14.in");
	system("pypy mkr.py N=188888 BB=[0,1] PP=[[1,2,3,4],[6]] VL=0 VR=2017011328 NoShuf=True > 15.in");
	system("pypy mkr.py N=366666 BB=[0,1] PP=[[1,2,3,4],[6]] VL=0 VR=2017011328 NoShuf=True > 16.in");
	system("pypy mkr.py N=366666 BB=[0,1] PP=[[1,2,3,4],[6]] VL=-2017011328 VR=2017011328 NoShuf=True > 17.in");
	system("pypy mkr.py N=366666 BB=[0,0] PP=[[1,2,3,3,3,4],[1,2,3,4]] VL=-2017011328 VR=2017011328 > 18.in")
	system("pypy mkr.py N=366666 BB=[0,0] PP=[[1],[1,2,3,4]] VL=-2017011328 VR=2017011328 > 19.in")
	system("pypy mkr.py N=366666 BB=[0,0] PP=[[1,2,3,4],[1,2,3,4]] VL=-2017011328 VR=2017011328 > 20.in")

system("g++ ../immortalCO/tmp.cpp -o tmp -O2 -std=c++11")
for i in xrange(1,21):
	print i
	system("/usr/bin/time ./tmp < %d.in > %d.ans" % (i,i))
