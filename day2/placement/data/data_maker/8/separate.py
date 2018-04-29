n = [ 1 ] + [ 50 ] * 10 + [ 1 ]

with open('8.in', 'r') as f:
    totn, m, k, op = [ int(x) for x in f.readline().split() ]
    for i in range(m):
        f.readline()
    for i, v in enumerate(n):
        with open('p%d.in' % i, 'w') as o:
            o.write('%d 0 %d 2\n' % (v, k))
            for j in range(v):
                o.write(f.readline() + '\n')

