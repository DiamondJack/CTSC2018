name='trie'
def get_line(in_f,num=1):
	line = in_f.readline()
	obj = line.split(' ')
	if len(obj) != num and -1 != num:
		print('ERROR')
	for i in range(len(obj)):
		obj[i] = int(obj[i])
	return obj

def check_in_file(in_f):
	line = in_f.readline().strip()
	n=len(line)
	Qc = 0
	Is = True
	Maxdep = 0
	assert(n<=300)
	dep = [0 for i in range(n+1)]
	for i in range(n):
		assert((line[i]==',')or(line[i]=='?')or('0'<=line[i] and line[i]<='9'))
		if line[i]=='?':
			Qc += 1
	fa = get_line(in_f,n)
	for i in range(n):
		assert(0<=fa[i] and fa[i]<=i)
		dep[i+1]=dep[fa[i]]+1
		if dep[i+1]>Maxdep:
			Maxdep = dep[i+1]
		if fa[i]!=i:
			Is = False
	print([n,Qc,Is,Maxdep])
	
for i in range(1,21):
	print("data%d:"%i)
	in_f=open('../data/%d.in'%(i),'r')
	check_in_file(in_f)
	in_f.close()
for i in range(1,5):
	in_f=open('../down/%d.in'%(i),'r')
	check_in_file(in_f)
	in_f.close()