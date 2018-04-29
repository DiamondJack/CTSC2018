import os
import sys
import random
import queue

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

    in_cnt = []
    edge = []
    res = []
    for a in range(0,n):
        res.append(0)
        in_cnt.append(0)
        edge.append([])
        for b in range(0,n):
            edge[a].append(False)

    for (s,e) in ed:
        s -= 1;
        e -= 1;
        edge[s][e] = True
        in_cnt[e] += 1

    q = queue.Queue()
    for a in range(0,n):
        if in_cnt[a] == 0:
            q.put(a)

    ans=0

    for a in range(0,n):
        p = q.get()

        nowres = 10**20
        nowp = 0
        for b in range(0,k):
            nowv = t[p][b]
            for c in range(0,n):
                if edge[c][p]:
                    nowv += r[res[c]][b]
            if nowv<nowres:
                nowres = nowv
                nowp=b
        res[p]=nowp
        ans += nowres

        for b in range(0,n):
            if edge[p][b]:
                in_cnt[b] -= 1
                if in_cnt[b] == 0:
                    q.put(b)

    for a in range(0,len(res)):
        res[a] += 1


    if test(res,"test.out") != ans:
        print(ans)
        print(test(res,"test.out"))

    output(res,ouf)

    print("%d result value: %d" % (oop,ans))

for a in range(1,11):
    if os.path.exists("../%d"%a):
        oop = a
        inf = open("../%d/%d.in" % (a,a),"r")
        ouf = open("%d.out" % a,"w")

        work(inf,ouf)

        inf.close()
        ouf.close()
