import sys
sys.path.append('qlearn')
import qlearn
l=[3.0,2.0,1.0,13,342,543,2.34]
qlearn.storeState(*l)
qlearn.storeAction(2)
qlearn.storeReward(1.5)
qlearn.printInfo()
qlearn.storeInfo()
#qlearn.game()
