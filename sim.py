from marketdata import *
from broker import *
from agent import *
md=MarketData('allData.pkl')
data=md['all']
agent=Human('human',20000)
broker=Broker([agent],data)
broker.loop()
