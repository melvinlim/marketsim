from marketdata import *
from broker import *
from agent import *
md=MarketData('allData.pkl')
data=md['all']
agents=[]
agents.append(Human('human',20000))
agents.append(BuyAndHold('B&H',20000))
agents.append(Random('Random',20000))
broker=Broker(agents,data)
broker.loop()
