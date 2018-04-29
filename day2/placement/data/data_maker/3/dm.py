from random import randint

n, m, k, v1, v2 = 50, 0, 3, 1, 17

print('%d %d %d 2' % (n, 0, k))
for i in range(n):
    print(' '.join([ str(randint(v1, v1 + v2)) for j in range(k - 1) ] + [ str(randint(v1, v2 * 2)) ] ))
for i in range(k):
    print(' '.join([ '0' if i == j else str(randint(1, v2)) for j in range(k) ]))

