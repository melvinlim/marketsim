from dayofweek import *
MEMORYSIZE=4
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
		self.buffer.append(processed)
		if len(self.buffer)>=MEMORYSIZE:
			self.buffer.pop(0)
			for i in self.buffer:
				printEvery(i,5)
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
