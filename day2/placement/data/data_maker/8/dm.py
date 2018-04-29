from random import randint
import numpy as np

n = [ 1 ] + [ 50 ] * 10 + [ 1 ]
m = [ n[i] * n[i + 1] for i in range(len(n) - 1) ]
k, v1, v2 = 600, 10, 1000

print('%d %d %d 2' % (np.sum(n), np.sum(m), k))
b = 1
for i in range(len(n) - 1):
    for j in range(0, n[i]):
        for l in range(0, n[i + 1]):
            print('%d %d' % (b + j, b + n[i] + l))
    b += n[i]
for i in n:
    vx = randint(v1, v1 + v2)
    for j in range(i):
        print(' '.join([ str(randint(vx, vx * 2 - 1)) for i in range(k) ]))
for i in range(k):
    print(' '.join([ '0' if i == j else '1' for j in range(k) ]))

