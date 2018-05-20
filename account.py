commisions=5.0	#per trade commisions
class Account():
	def __init__(self,idn,agent,name,funds):
		self.idn=idn
		self.agent=agent
		self.name=name
		self.funds=funds
		self.stocks=dict()
		self.trades=0
		self.commisions=0
	def buy(self,amount,stock,price):
		fundsAfter=self.funds-amount*float(price)-commisions
		if fundsAfter<0:
			return False
		if stock not in self.stocks:
			self.stocks[stock]=0
		self.stocks[stock]+=amount
		self.funds=fundsAfter
		self.commisions+=commisions
		self.trades+=1
	def sell(self,amount,stock,price):
		if stock not in self.stocks or self.stocks[stock]==0:
			return False
		self.stocks[stock]-=amount
		self.funds+=amount*float(price)-commisions
		self.commisions+=commisions
		self.trades+=1
