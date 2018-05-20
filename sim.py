from marketdata import *
from dayofweek import *
md=MarketData('allData.pkl')
data=md['all']
dates=data.keys()
dates.sort()
today=data[dates[0]]
i=0
while len(today)!=8:
	today=data[dates[i]]
	i+=1
dates=dates[i:]
for date in dates:
	today=data[date]
	for stock in today:
		d=today[stock].pop('timestamp',None)
		assert d==date
		for irrelevant in ['split_coefficient','dividend_amount']:
			today[stock].pop(irrelevant,None)
	dow=getDayOfWeek(strDate(date))
	print dow,strDate(date)
	for stock in today.keys():
		print stock,today[stock]
	raw_input()
