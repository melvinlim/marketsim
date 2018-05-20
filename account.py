class Account():
	def __init__(self,idn,agent,name,funds):
		self.idn=idn
		self.agent=agent
		self.name=name
		self.funds=funds
		self.stocks=dict()
	def buy(self,amount,stock,price):
		if stock not in self.stocks:
			self.stocks[stock]=0
		self.stocks[stock]+=100
		self.funds-=amount*float(price)
	def sell(self,amount,stock,price):
		if stock not in self.stocks or self.stocks[stock]==0:
			return 0
		self.stocks[stock]-=100
		self.funds+=amount*float(price)
