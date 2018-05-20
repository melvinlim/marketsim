from dayofweek import *
class Agent():
	def __init__(self,funds):
		self.funds=funds
class Human(Agent):
	def __init__(self,name,funds):
		self.name=name
		self.funds=funds
	def decide(self,state):
		(date,funds,info)=state
		dow=getDayOfWeek(strDate(date))
		print dow,date,funds
		for stock in info:
			print stock,info[stock]
		return raw_input()
