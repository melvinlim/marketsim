from dayofweek import *
class Agent():
	def __init__(self,funds):
		self.funds=funds
class Human(Agent):
	def __init__(self,name,funds):
		self.name=name
		self.funds=funds
	def decide(self,state):
		(date,account,info)=state
		funds=account.funds
		stocks=account.stocks
		dow=getDayOfWeek(strDate(date))
		print dow,date,funds
		for stock in stocks:
			print stock,stocks[stock]
		for stock in info:
			print stock,info[stock]
			si=info[stock]
			processed=map(float,[dow,si['open'],si['high'],si['low'],si['adjusted_close'],si['volume']])
			print processed
		return raw_input()
