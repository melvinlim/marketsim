from marketdata import *
from broker import *
md=MarketData('allData.pkl')
data=md['all']
broker=Broker(data)
broker.loop()
