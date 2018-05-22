from marketdata import *
from broker import *
from agent import *
md=MarketData('allData.pkl')
data=md['all']
qagent=QAgent('QAgent',20000)
if os.path.isfile('qfA.qf'):
	qagent.load()
agents=[]
#agents.append(Human('human',20000))
agents.append(qagent)
agents.append(BuyAndHold('B&H',20000))
agents.append(Random('Random',20000))
broker=Broker(agents,data)
broker.loop()
broker.summary()
qagent.save()
