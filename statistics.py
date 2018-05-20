import math
MEMORYSIZE=60
WINDOWSZ=30
def mean(a):
	n=len(a)
	res=0
	for x in a:
		res+=x
	res/=float(n)
	return res
def stdev(a):
	n=len(a)
	res=0
	m=mean(a)
	for x in a:
		res+=(x-m)**2
	res/=(n-1)
	return math.sqrt(res)
