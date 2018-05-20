from dayofweek import *
from account import *
from agent import *
class Broker():
	def __init__(self,agents,data):
		self.agents=dict()
		self.idn=0
		for agent in agents:
			name=agent.name
			funds=agent.funds
			self.agents[self.idn]=Account(self.idn,name,funds)
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
	def removeIrrelevant(self):
		data=self.data
		dates=self.dates
		for date in dates:
			today=data[date]
			for stock in today:
				d=today[stock].pop('timestamp',None)
				assert d==date
				for irrelevant in ['split_coefficient','dividend_amount']:
					today[stock].pop(irrelevant,None)
	def loop(self):
		data=self.data
		dates=self.dates
		for date in dates:
			today=data[date]
			dow=getDayOfWeek(strDate(date))
			print dow,strDate(date)
			for stock in today.keys():
				print stock,today[stock]
			raw_input()
