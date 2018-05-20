from marketparser import *
from stock import *
import os.path
import pickle
class MarketData(dict):
	def __init__(self,filename=''):
		self.stocks=[]
		if filename!='':
			fp=open(filename,'r')
			self['all']=pickle.load(fp)
	def saveCombined(self):
		if 'all' not in self:
			print 'combined data not present.'
			return False
		filename='allData.pkl'
		if os.path.isfile(filename):
			print 'file exists.  not saving.'
			return False
		fp=open(filename,'w')
		pickle.dump(self['all'],fp)
	def saveCSV(self,stocks):
		for stock in stocks:
			filename=stock+'-'+self.parser.name+'.csv'
			if os.path.isfile(filename):
				print 'file exists.  not saving.'
				return False
			else:
				fp=open(filename,'w')
				fp.write(self[stock]['csv'])
				fp.close()
	def openCSV(self,files,apikey='demo'):
		for f in files:
			filename=f
			if not os.path.isfile(filename):
				print 'file: '+filename+' does not exist.'
				return False
			fp=open(filename,'r')
			fn=filename.strip('\n')
			fn=fn.strip('\r')
			fn=fn.strip('.csv')
			stock,parser=fn.split('-')
			print parser
			if parser=='alphavantage':
				self.parser=AlphaVantageParser(apikey)
			elif parser=='quandl':
				self.parser=QuandlParser(apikey)
			self[stock]=Stock()
			csv=fp.read()
			self[stock]['csv']=csv
			data=self.parser.getData(csv)
			self[stock]['data']=data
	def getFromInternet(self,stocks,parser='AlphaVantage',apikey='demo'):
		if parser=='AlphaVantage':
			self.parser=AlphaVantageParser(apikey)
		elif parser=='Quandl':
			self.parser=QuandlParser(apikey)
		function='TIME_SERIES_DAILY_ADJUSTED'
		for stock in stocks:
			newStock=Stock()
			csv=self.parser.getCSV(function,stock)
			newStock['csv']=csv
			data=self.parser.getData(csv)
			newStock['data']=data
			self[stock]=newStock
		self.stocks=self.keys()
	def display(self,target):
		if target=='csv':
			for stock in self.keys():
				data=self[stock]['csv']
				print data
		if target=='data':
			for stock in self.keys():
				data=self[stock]['data']
				for line in data:
					print line
		if target=='all':
			data=self['all']
			for date in data.keys():
				for stock in data[date].keys():
					print date,stock,data[date][stock]
	def getCombined(self):
		res=dict()
		for stock in self.keys():
			data=self[stock]['data']
			for line in data:
				ts=line['timestamp']
				if ts not in res:
					res[ts]=dict()
				res[ts][stock]=line
		self['all']=res
		return res
