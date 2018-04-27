import os
import sys
import random

oop = 0

def output(res,f):
    for a in range(0,len(res)):
        print(res[a],' ',end='',file=f)

def test(res,f):
    f = open(f,"w")
    output(res,f)
    f.close()

    os.system("..\\simulator_easy.exe ..\\%d\\%d.in test.out" % (oop,oop))

    f = open("res.txt","r")

    v = int(f.readline()[:-1])

    f.close()

    return v

def read(inf):
    line = inf.readline()[:-1].split(" ")
    n = int(line[0])
    m = int(line[1])
    k = int(line[2])
    op = int(line[3])
    ed = []
    for a in range(0,m):
        line = inf.readline()[:-1].split(" ")
        ed.append((int(line[0]),int(line[1])))
    t = []
    r = []
    for a in range(0,n):
        t.append(inf.readline()[:-1].split(" "))
    for a in range(0,k):
        r.append(inf.readline()[:-1].split(" "))
    for a in range(0,n):
        for b in range(0,k):
            t[a][b]=int(t[a][b])
    for a in range(0,k):
        for b in range(0,k):
            r[a][b]=int(r[a][b])

    return n,m,k,op,ed,t,r

def work(inf,ouf):
    n,m,k,op,ed,t,r = read(inf)

    res = []
    resx = []
    for a in range(0,n):
        res.append(0)
        resx.append(0)

    ans = 10**20
    for a in range(0,1000):
        for b in range(0,n):
            res[b] = random.randint(1,k)

        v = test(res,"test.out")
        if v < ans:
            ans = v
            for b in range(0,n):
                resx[b] = res[b]

    output(resx,ouf)

    print("%d result value: %d" % (oop,ans))

for a in range(1,11):
    if os.path.exists("../%d"%a):
        oop = a
        inf = open("../%d/%d.in" % (a,a),"r")
        ouf = open("%d.out" % a,"w")

        work(inf,ouf)

        inf.close()
        ouf.close()
