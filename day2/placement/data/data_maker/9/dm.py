from random import randint

n, m, k, v1, v2 = 100, 3000, 64, 1000, 30

print('%d %d %d 2' % (n, m + (n - 2) * 2, k))
for i in range(2, n):
    print('%d %d' % (1, i))
    print('%d %d' % (i, n))
edges = []
for i in range(m):
    while True:
        u, v = randint(2, n - 1), randint(2, n - 1)
        if u < v and not (u, v) in edges:
            break
    edges.append((u, v))
    print('%d %d' % (u, v))
for i in range(n):
    print(' '.join([ str(randint(1, v1)) for j in range(k) ]))
for i in range(k):
    print(' '.join([ '0' if i == j else str(randint(1, v2)) for j in range(k) ]))

