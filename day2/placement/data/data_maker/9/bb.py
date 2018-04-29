with open('9.in', 'r') as f:
    n, m, k, op = [ int(x) for x in f.readline().split(' ') ]
    e = []
    for i in range(m):
        e.append(f.readline().split(' '))
    t = [ None ] * n
    for i in range(n):
        t[i] = [ int(x) for x in f.readline().split(' ') ]
    r = [ None ] * k
    for i in range(k):
        r[i] = [ int(x) for x in f.readline().split(' ') ]

res = [ 0 ] * n
for i in range(n):
    s = 0
    for j in range(k):
        if t[i][j] < t[i][s]:
            s = j
    res[i] = s + 1

print(' '.join([ str(x) for x in res ]))

