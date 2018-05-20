from dayofweek import *
from statistics import *
import random
MEMORYSIZE=60
WINDOWSZ=30
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
	for stk in range(len(buf[0])):
		res.append(tof(buf[0][stk][4]>buf[1][stk][4]))
		res.append(tof(buf[0][stk][4]<buf[1][stk][4]))
		res.append(tof(buf[0][stk][0]>buf[1][stk][1]))
		res.append(tof(buf[0][stk][0]<buf[1][stk][2]))
		res.append(tof(buf[0][stk][0]>buf[1][stk][3]))
		res.append(tof(buf[0][stk][0]<buf[1][stk][3]))
		intervals=[5,10,15,30,60]
		for interval in intervals:
			ind=interval-1
			if (ind)<n:
				res.append(tof(buf[0][stk][3]>buf[ind][stk][3]))
				res.append(tof(buf[0][stk][3]<buf[ind][stk][3]))
		hl=[]
		vol=[]
		for i in range(WINDOWSZ):
			hl.append(buf[i][stk][1]-buf[i][stk][2])
			vol.append(buf[i][stk][4])
		hlsd=stdev(hl)*0.318
		volsd=stdev(vol)*0.318
		hlm=mean(hl)
		volm=mean(vol)
		hl=buf[0][stk][1]-buf[0][stk][2]
		res.append(tof(hl>(hlm+hlsd)))
		res.append(tof(hl<(hlm-hlsd)))
		res.append(tof(buf[0][stk][4]>(volm+volsd)))
		res.append(tof(buf[0][stk][4]<(volm-volsd)))
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
		self.processedBuffer=[]
		self.stockList=[]
	def display(self,state):
		(date,account,info)=state
		dow=getDayOfWeek(strDate(date))
		funds=account.funds
		ownedStocks=account.stocks
		print dow,date,funds
		for stock in ownedStocks:
			print stock,ownedStocks[stock]
	def decide(self,state):
		(date,account,info)=state
		dow=getDayOfWeek(strDate(date))
		self.display(state)
		if self.stockList==[]:
			for stock in info.keys():
				self.stockList.append(stock)
		if len(self.stockList)!=len(info.keys()):
			for stock in self.stockList:
				if stock not in info.keys():
					info[stock]=self.buffer[0][stock]
		assert len(self.stockList)==len(info.keys())
		processed=[]
		for stock in info:
			print stock,info[stock]
			si=info[stock]
			processed.append(map(float,[si['open'],si['high'],si['low'],si['adjusted_close'],si['volume']]))
		self.processedBuffer.insert(0,processed)
		self.buffer.insert(0,info)
		for entry in self.buffer:
			assert(len(entry)==8)
		if len(self.buffer)>=MEMORYSIZE:
#			for i in self.buffer:
#				printEvery(i,5)
			self.obs=buildObs(self.processedBuffer)
			self.obs+=expand(float(dow)-1,5)
			print self.obs
			self.buffer.pop()
		return raw_input()
class Random(Agent):
	def __init__(self,name,funds):
		self.name=name
		self.startingFunds=funds
		self.funds=funds
		self.buffer=[]
	def decide(self,state):
		(date,account,info)=state
		ownedStocks=account.stocks
		r=random.randint(0,2)
		if r==0:
			return 'b'
		elif r==1:
			return 's'
		else:
			return '\n'
class BuyAndHold(Agent):
	def __init__(self,name,funds):
		self.name=name
		self.startingFunds=funds
		self.funds=funds
		self.buffer=[]
	def decide(self,state):
		totalStocks=0
		(date,account,info)=state
		ownedStocks=account.stocks
		for stock in ownedStocks:
			totalStocks+=ownedStocks[stock]
		if totalStocks<1000:
			return 'b'
		return '\n'
