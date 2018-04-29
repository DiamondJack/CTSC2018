s = [ 0 ] * 3
with open('3.in', 'r') as f:
    n, m, k, op = [ int(x) for x in f.readline().split(' ') ]
    for i in range(n):
        t = [ int(x) for x in f.readline().split(' ') ]
        for j in range(3):
            s[j] += t[j]
print(s)
