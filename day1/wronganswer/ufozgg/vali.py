import sys   
sys.setrecursionlimit(500000)
name='wronganswer'
def get_line(in_f,num=1):
	line = in_f.readline()
	obj = line.split(' ')
	if len(obj) != num and -1 != num:
		print('ERROR')
	for i in range(len(obj)):
		obj[i] = int(obj[i])
	return obj

fa = [i for i in range(366670)]	

def get_fa(d):
	global fa
	g = [d]
	while fa[g[len(g)-1]]!=g[len(g)-1]:
		g.append(fa[g[len(g)-1]])
	ret = g[len(g)-1]
	for i in range(len(g)):
		fa[g[i]]=ret
	return ret

def check_in_file(in_f):
	global fa
	[n]=get_line(in_f)
	V_NonNegtive = True
	V1 = True
	T_Line = True
	T0_Line = True
	assert(n<=366666)
	fa = [i for i in range(366670)]	
	for i in range(n-1):
		[x,y,v]=get_line(in_f,3)
		if v<0:
			V_NonNegtive = False
		if v!=1:
			V1 = False
		if abs(x-y)!=1:
			T_Line = False
		assert(abs(v)<=2017011328)
		assert(get_fa(x) != get_fa(y))
		fa[get_fa(x)]=get_fa(y)

	fa = [i for i in range(366670)]	
	for i in range(n-1):
		[x,y,v]=get_line(in_f,3)
		if v<0:
			V_NonNegtive = False
		if v!=1:
			V1 = False
		if abs(x-y)!=1:
			T0_Line = False
		assert(abs(v)<=2017011328)
		assert(get_fa(x) != get_fa(y))
		fa[get_fa(x)]=get_fa(y)
	print([n,V_NonNegtive,V1,T_Line,T0_Line])

for i in range(1,21):
	print("data%d:"%i)
	in_f=open('../data/%d.in'%(i),'r')
	check_in_file(in_f)
	in_f.close()
for i in range(1,3):
	in_f=open('../down/%d.in'%(i),'r')
	check_in_file(in_f)
	in_f.close()