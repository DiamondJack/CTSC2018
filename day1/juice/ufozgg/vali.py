name='juice'
def get_line(in_f,num=1):
	line = in_f.readline()
	obj = line.split(' ')
	if len(obj) != num and -1 != num:
		print('ERROR')
	for i in range(len(obj)):
		obj[i] = int(obj[i])
	return obj

def check_in_file(in_f):
	P1 = True
	L1 = True
	[n,m]=get_line(in_f,2)
	assert(1<=n and n<= 100000)
	assert(1<=m and m<= 100000)
	for i in range(n):
		[d,p,l]=get_line(in_f,3)
		assert(1<=d and d<= 1e5)
		assert(1<=p and p<= 1e5)
		assert(1<=l and l<= 1e5)
		if p != 1:
			P1 = False
		if l != 1:
			L1 = False
	for i in range(m):
		[g,l]=get_line(in_f,2)
		assert(1<=g and g<= 1e18)
		assert(1<=l and l<= 1e18)
	print([n,m,P1,L1])
	
for i in range(1,21):
	print("data%d:"%i)
	in_f=open('../data/%d.in'%(i),'r')
	check_in_file(in_f)
	in_f.close()
for i in range(1,4):
	in_f=open('../down/%d.in'%(i),'r')
	check_in_file(in_f)
	in_f.close()