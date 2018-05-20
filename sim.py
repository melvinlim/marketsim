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
		for irrelevant in ['split_coefficient','dividend_amount']:
			today[stock].pop(irrelevant,None)
	for stock in today.keys():
		print stock,today[stock]
	raw_input()
