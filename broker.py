from account import *
from agent import *
class Broker():
	def __init__(self,agents,marketData):
		self.accounts=dict()
		self.idn=0
		for agent in agents:
			name=agent.name
			funds=agent.funds
			self.accounts[self.idn]=Account(self.idn,agent,name,funds)
			self.idn+=1
		self.marketData=marketData
		self.dates=marketData.keys()
		self.dates.sort()
		self.skip()
		self.removeIrrelevant()
	def skip(self):	#skip days prior to XUS.TO's existence.
		marketData=self.marketData
		dates=self.dates
		currentData=marketData[dates[0]]
		i=0
		while 'XUS.TO' not in currentData:
			currentData=marketData[dates[i]]
			i+=1
		self.dates=dates[i:]
	def printStats(self,account,currentData):
		print 'account: '+account.name
		value=account.funds
		for stock in account.stocks:
			amount=float(account.stocks[stock])
			if stock in currentData:
				price=float(currentData[stock]['adjusted_close'])
				value+=price*amount
			else:
				print 'holdings: '+str(amount)+' shares of '+stock
		print 'value at start: '+str(account.agent.startingFunds)
		print 'value at end: '+str(value)
		print 'trades: '+str(account.trades)
		print 'commisions: '+str(account.commisions)
	def removeIrrelevant(self):
		marketData=self.marketData
		dates=self.dates
		for date in dates:
			currentData=marketData[date]
			for stock in currentData:
				d=currentData[stock].pop('timestamp',None)
				assert d==date
				for irrelevant in ['split_coefficient','dividend_amount','close']:
					currentData[stock].pop(irrelevant,None)
	def loop(self):
		marketData=self.marketData
		dates=self.dates
		for date in dates:
			currentData=marketData[date]
			for account in self.accounts:
				agent=self.accounts[account].agent
				state=(date,self.accounts[account],currentData)
				action=agent.decide(state)
				stock='XUS.TO'
				if action==0:
					if stock in currentData:
						price=currentData[stock]['adjusted_close']
						self.accounts[account].buy(100,stock,price)
					else:
						print 'market data unavailable today'
#should sell at next available price.
				elif action==1:
#should use tomorrow's opening price
					if stock in currentData:
						price=currentData[stock]['adjusted_close']
#should sell at next available price.
						self.accounts[account].sell(100,stock,price)
					else:
						print 'market data unavailable today'
				elif action==2:
					pass
				elif action==-1:
					return
	def summary(self):
		for account in self.accounts:
			finalDay=self.marketData[self.dates[-1]]
			self.printStats(self.accounts[account],finalDay)
