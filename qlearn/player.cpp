#include"player.h"
Player::Player(){}
Player::~Player(){}
//void Player::decide(Action &action,Info &info){}
Agent::Agent():
qfA(STATEVARS,ACTIONVARS),
qfB(STATEVARS,ACTIONVARS)
{
	currentTime=0;
	qfA.nextQ=&qfB;
	qfB.nextQ=&qfA;
	QArrayA=new Array<double>(ACTIONVARS);
	QArrayB=new Array<double>(ACTIONVARS);
}
Agent::~Agent(){}
void Agent::decide(const double *state,Action &action){
	currentTime++;
	if(currentTime<TRAININGTIME){
		action=qfA.getRandomAction();
	}else{
		qfA.getQArray(QArrayA,state);
		qfB.getQArray(QArrayB,state);
		double bestQ,tmpQ;
		action=0;
		bestQ=QArrayA->item[0]+QArrayB->item[0];
		for(int i=1;i<ACTIONVARS;i++){
			tmpQ=QArrayA->item[i]+QArrayB->item[i];
			if(tmpQ>bestQ){
				action=i;
				bestQ=tmpQ;
			}
		}
	}
//	if(currentTime>TRAININGTIME)
//		getchar();
}
double Agent::getSumSqErr(Stack<Info> &records){
	Info info;
	info=records.back();
	double Q;
	double targetQ;
	double reward;
	double QMax;
	records.pop_back();
	double currentError;
	double sse=0;
	int t;
	Qfunction *qptr=&qfA;
	for(int i=0;i<records.size;i++){
		t=i;
		info=records.atIndex(t);
		reward=info.reward;
		qptr=qptr->nextQ;
		if(reward!=0){
			targetQ=reward;
		}else{
			Q=qptr->getQ(info.state,info.action);
			QMax=qptr->nextQ->getQMax(info.nextState,info.action);
			targetQ=Q+ALPHA*(reward+DISCOUNT*QMax-Q);
		}
		currentError=qptr->getSqErr(info.state,info.action,targetQ);
		sse+=currentError;
	}
	sse/=(double)records.size;
	printf("sse:%f\n",sse);
	return sse;
}
void Agent::train(Stack<Info> &records){
	//verifyRecords(records);
	Info info;
	info=records.back();
	double Q;
	double targetQ;
	double reward;
	double QMax;
	records.pop_back();
	int t;
	Qfunction *qptr=&qfA;
	for(int i=0;i<records.size;i++){
//		t=random()%records.size;
		t=i;
		info=records.atIndex(t);
		reward=info.reward;
//		t=random()%2;
//		if(t==0)
			qptr=qptr->nextQ;
		if(reward!=0){
			targetQ=reward;
			//targetQ=Q+ALPHA*(reward-Q);
		}else{
			Q=qptr->getQ(info.state,info.action);
			QMax=qptr->nextQ->getQMax(info.nextState,info.action);
			targetQ=Q+ALPHA*(reward+DISCOUNT*QMax-Q);
		}
		qptr->updateQ(info.state,info.action,targetQ);
		if(qptr->iter++ >= BATCHSIZE){
			qptr->net.updateWeights();
			qptr->iter=0;
		}
	}
}
void Player::verifyRecords(Stack<Info> &records){
	Info info;
	int r=0;
	for(int i=0;i<records.size;i++){
		r++;
		info=records.atIndex(i);
		printf("record: %d\n",r);
		for(int i=0;i<STATEVARS;i++){
			printf("%+f,",info.state[i]);
		}
		printf("action: %d\n",info.action);
		printf("reward: %f\n",info.reward);
		for(int i=0;i<STATEVARS;i++){
			printf("%+f,",info.nextState[i]);
		}
		if(info.reward>0)
			getchar();
	}
}
void Agent::save(){
	qfA.saveQf("qfA.qf");
	qfB.saveQf("qfB.qf");
}
void Agent::load(){
	qfA.loadQf("qfA.qf");
	qfB.loadQf("qfB.qf");
}
