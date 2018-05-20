from account import *
from agent import *
class Broker():
	def __init__(self,agents,data):
		self.accounts=dict()
		self.idn=0
		for agent in agents:
			name=agent.name
			funds=agent.funds
			self.accounts[self.idn]=Account(self.idn,agent,name,funds)
			self.idn+=1
		self.data=data
		self.dates=data.keys()
		self.dates.sort()
		self.skip()
		self.removeIrrelevant()
	def skip(self):	#skip days prior to XUS.TO's existence.
		data=self.data
		dates=self.dates
		today=data[dates[0]]
		i=0
		while len(today)!=8:
			today=data[dates[i]]
			i+=1
		self.dates=dates[i:]
	def printStats(self,account,today):
		value=account.funds
		for stock in account.stocks:
			amount=float(account.stocks[stock])
			if stock in today:
				price=float(today[stock]['adjusted_close'])
				value+=price*amount
			else:
				print 'holdings: '+str(amount)+' shares of '+stock
		print 'value at end: '+str(value)
	def removeIrrelevant(self):
		data=self.data
		dates=self.dates
		for date in dates:
			today=data[date]
			for stock in today:
				d=today[stock].pop('timestamp',None)
				assert d==date
				for irrelevant in ['split_coefficient','dividend_amount','close']:
					today[stock].pop(irrelevant,None)
	def loop(self):
		data=self.data
		dates=self.dates
		for date in dates:
			today=data[date]
			for account in self.accounts:
				agent=self.accounts[account].agent
				state=(date,self.accounts[account],today)
				action=agent.decide(state)
				action.strip('\n')
				action.strip('\r')
				stock='XUS.TO'
				if action=='b':
					if stock in today:
						price=today[stock]['adjusted_close']
						self.accounts[account].buy(100,stock,price)
					else:
						print 'market data unavailable today'
#should sell at next available price.
				elif action=='s':
#should use tomorrow's opening price
					if stock in today:
						price=today[stock]['adjusted_close']
						self.accounts[account].sell(100,stock,price)
					else:
						print 'market data unavailable today'
#should sell at next available price.
		for account in self.accounts:
			finalDay=data[dates[-1]]
			self.printStats(self.accounts[account],finalDay)
