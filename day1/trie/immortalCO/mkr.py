from random import *
from sys import *

N = 300

def rndcho(S):	return S[randint(0, len(S) - 1)]

print "".join([rndcho("????????????????,1234567890"[:1]) for i in xrange(N)])

print " ".join(map(str, [randint(1, i) for i in xrange(1, N)]))
