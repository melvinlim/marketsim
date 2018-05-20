from marketdata import *
def isLeap(year):
	if year%4!=0:
		return False
	if year%100!=0:
		return True
	if year%400==0:
		return True
	return False
mkey=[0,1,4,4,0,2,5,0,3,6,1,4,6]
#day of week as number from 0-6.  0=Sunday, 1=Monday.
def getDayOfWeek(date):
	year,month,day=date
	print year,month,day
	l2d=year%100
	tmp=l2d/4
	tmp=tmp+day
	tmp=tmp+mkey[month]
	if month==1 or month==2:
		if isLeap(year):
			tmp=tmp-1
	tmp=tmp+6	#this is for any year in the 2000's.
	tmp=tmp+l2d
	res=tmp%7
	res=res+6
	res=res%7
	return res
def strDate(d):
	res=map(int,d.split('-'))
	return res
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
	dow=getDayOfWeek(strDate(date))
	for stock in today.keys():
		print dow,date,strDate(date),stock,today[stock]
	raw_input()
