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
	hl=[]
	vol=[]
	for i in range(WINDOWSZ):
		hl.append(buf[i][1]-buf[i][2])
		vol.append(buf[i][4])
	hlsd=stdev(hl)*0.318
	volsd=stdev(vol)*0.318
	hlm=mean(hl)
	volm=mean(vol)
	hl=buf[0][1]-buf[0][2]
	res.append(tof(hl>(hlm+hlsd)))
	res.append(tof(hl<(hlm-hlsd)))
	res.append(tof(buf[0][4]>(volm+volsd)))
	res.append(tof(buf[0][4]<(volm-volsd)))
	return res
class Agent():
	def __init__(self,funds):
		self.funds=funds
	def fillGaps(self,info,buf):
		if len(self.stockList)!=len(info.keys()):
			for stock in self.stockList:
				if stock not in info.keys():
					info[stock]=buf[0][stock]
	def updateProcessedBuffer(self,info):
		i=0
		for stock in info:
			print stock,info[stock]
			si=info[stock]
			processed=map(float,[si['open'],si['high'],si['low'],si['adjusted_close'],si['volume']])
			self.processedBuffer[i].insert(0,processed)
			i+=1
class Human(Agent):
	def __init__(self,name,funds):
		self.name=name
		self.startingFunds=funds
		self.funds=funds
		self.buffer=[]
		self.processedBuffer=[]
		self.stockList=[]
		self.obs=[]
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
		ownedStocks=account.stocks
		totalStocks=0
		for stock in ownedStocks:
			totalStocks+=ownedStocks[stock]
		dow=getDayOfWeek(strDate(date))
		self.display(state)
		if self.stockList==[]:
			for stock in info.keys():
				self.stockList.append(stock)
				self.processedBuffer.append([])
		self.fillGaps(info,self.buffer)
		self.buffer.insert(0,info)
		for entry in self.buffer:
			assert(len(entry)==8)
		assert len(self.stockList)==len(info.keys())
		self.updateProcessedBuffer(info)
		if len(self.buffer)>=MEMORYSIZE:
			self.obs=[]
			for i in range(len(self.stockList)):
				self.obs+=buildObs(self.processedBuffer[i])
				self.processedBuffer[i].pop()
			self.obs+=expand(float(dow)-1,5)
			self.obs+=[tof(totalStocks>0)]
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
