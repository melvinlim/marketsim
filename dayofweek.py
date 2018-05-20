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
