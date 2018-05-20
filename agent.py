from dayofweek import *
MEMORYSIZE=5
def expand(x,n):
	res=[]
	for i in range(n):
		if i==x:
			res.append(1.0)
		else:
			res.append(-1.0)
	return res
def printEvery(l,x):
	n=len(l)
	t=0
	while t+x<n:
		print l[t:t+x]
		t+=x
	print l[t:]
def tof(x):
	if x==True:
		return 1.0
	else:
		return -1.0
def buildObs(buf):
	n=len(buf)
	res=[]
	res.append(tof(buf[0][4]>buf[1][4]))
	res.append(tof(buf[0][4]<buf[1][4]))
	res.append(tof(buf[0][0]>buf[1][1]))
	res.append(tof(buf[0][0]<buf[1][2]))
	res.append(tof(buf[0][0]>buf[1][3]))
	res.append(tof(buf[0][0]<buf[1][3]))
	intervals=[5,10,15,30,60]
	for interval in intervals:
		ind=interval-1
		if (ind)<n:
			res.append(tof(buf[0][3]>buf[ind][3]))
			res.append(tof(buf[0][3]<buf[ind][3]))
	return res
class Agent():
	def __init__(self,funds):
		self.funds=funds
class Human(Agent):
	def __init__(self,name,funds):
		self.name=name
		self.startingFunds=funds
		self.funds=funds
		self.buffer=[]
	def decide(self,state):
		(date,account,info)=state
		funds=account.funds
		stocks=account.stocks
		dow=getDayOfWeek(strDate(date))
		print dow,date,funds
		totalStocks=0
		for stock in stocks:
			print stock,stocks[stock]
			totalStocks+=stocks[stock]
		processed=[]
		for stock in info:
			print stock,info[stock]
			si=info[stock]
			processed+=map(float,[si['open'],si['high'],si['low'],si['adjusted_close'],si['volume']])
#		processed+=[float(dow)]
		processed+=expand(float(dow)-1,5)
		#self.buffer.append(processed)
		self.buffer.insert(0,processed)
		if len(self.buffer)>MEMORYSIZE:
			self.buffer.pop()
			for i in self.buffer:
				printEvery(i,5)
			self.obs=buildObs(self.buffer)
			print self.obs
		return raw_input()
class BuyAndHold(Agent):
	def __init__(self,name,funds):
		self.name=name
		self.startingFunds=funds
		self.funds=funds
		self.buffer=[]
	def decide(self,state):
		totalStocks=0
		(date,account,info)=state
		stocks=account.stocks
		for stock in stocks:
			totalStocks+=stocks[stock]
		if totalStocks==0:
			return 'b'
		return '\n'
