from marketdata import *
md=MarketData('allData.pkl')
data=md['all']
dates=data.keys()
dates.sort()
for date in dates:
	today=data[date]
	for stock in today:
		d=today[stock].pop('timestamp',None)
		assert d==date
	print today
	raw_input()
