name='green'
def get_line(in_f,num=1):
	line = in_f.readline()
	obj = line.split(' ')
	if len(obj) != num and -1 != num:
		print('ERROR')
	for i in range(len(obj)):
		obj[i] = int(obj[i])
	return obj

def check_in_file(in_f):
	[T,n] = get_line(in_f,2)
	LJ = True
	LJ1 = True
	for i in range(T):
		L = get_line(in_f,n)
		for j in range(n):
			if L[j] != j+1:
				LJ = False
			if L[j] != 1 and j != n-1:
				LJ1 = False
			assert(1<=L[j] and L[j]<=j+1)
	assert(T*n<=1000000)
	print([T,n,LJ,LJ1])

for i in range(1,21):
	print("data%d:\n"%i)
	in_f=open('../data/%d.in'%(i),'r')
	check_in_file(in_f)
	in_f.close()
for i in range(1,3):
	in_f=open('../down/%d.in'%(i),'r')
	check_in_file(in_f)
	in_f.close()