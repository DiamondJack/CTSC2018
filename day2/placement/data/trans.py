import os

f = open("value.txt","r")
res = []
for line in f:
    res.append(line[:-1].split("\t"))

for a in range(0,10):
    for b in range(0,10):
        res[a][b] = int(res[a][b])

for a in range(1,11):
    os.system("copy data_maker\\%d\\%d.in %d.in" % (a,a,a))

    f = open("%d.ans"%a,"w")
    for b in range(0,10):
        print(res[b][a-1],file=f)
    f.close()
