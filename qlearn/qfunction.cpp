#include"qfunction.h"
Qfunction::Qfunction(int nStateVars,int nActions):
net(nActions+nStateVars,HIDDENUNITS,1,GAMMA,LAMBDA_DECAY,SCALE_FACTOR)
{
	this->nActions=nActions;
	this->nStateVars=nStateVars;
	actionStateArray=new Array<double>(nActions+nStateVars);
	targetArray=new Array<double>(1);
	iter=0;
}
Qfunction::~Qfunction(){}
double Qfunction::getQMax(const double *state,const Action &action){
	updateActionStateArray(state,action);
	double bestVal;
	double tmpVal;
	bestVal=getQ(state,0);
//actionStateArray->print(3);
//getchar();
	for(int i=1;i<nActions;i++){
//actionStateArray->print(3);
//getchar();
		tmpVal=getQ(state,i);
		if(tmpVal>bestVal){
			bestVal=tmpVal;
		}
	}
	return bestVal;
}
double Qfunction::getQ(const double *state,const Action &action){
	updateActionStateArray(state,action);
	double resp;
	net.forward(actionStateArray);
	resp=net.response->item[0];
#ifdef DEBUG
	printf("resp: %f\n",resp);
#endif
	return resp;
}
double Qfunction::getSqErr(const double *state,const Action &action,const double &target){
	getQ(state,action);
	targetArray->item[0]=target;
	net.updateError(targetArray);
	double error=net.error.item[0];
	return (error*error);
}
void Qfunction::updateQ(const double *state,const Action &action,const double &target){
	targetArray->item[0]=target;
	updateActionStateArray(state,action);
#ifdef DEBUG
	actionStateArray->print();
	targetArray->print();
	printf("target Q:%f\n",targetArray->item[0]);
#endif
	net.trainBatch(actionStateArray,targetArray);
#ifdef DEBUG
	double response=getQ(state,action);
	printf("Q response after training:%f\n",response);
	getchar();
#endif
}
void Qfunction::getQArray(Array<double> *QArray,const double *state){
	for(int i=0;i<nActions;i++){
		QArray->item[i]=getQ(state,i);
	}
}
int Qfunction::getBestAction(const double *state){
	int best=0;
	double bestVal;
	double tmpVal;
	bestVal=getQ(state,0);
actionStateArray->print(3);
//getchar();
	for(int i=1;i<nActions;i++){
//actionStateArray->print(3);
//getchar();
		tmpVal=getQ(state,i);
		if(tmpVal>bestVal){
			bestVal=tmpVal;
			best=i;
		}
	}
	return best;
}
int Qfunction::getRandomAction(){
	int best=0;
	best=random()%nActions;
	return best;
}
void Qfunction::updateActionStateArray(const double *state,const Action &action){
	assert(action<nActions);
	int p=0;
	for(int i=0;i<nActions;i++){
		actionStateArray->item[p++]=aStates[action][i];
	}
	for(int i=0;i<nStateVars;i++){
		actionStateArray->item[p++]=state[i];
	}
}
void Qfunction::saveQf(const char *filename){
	IDX::saveNetwork(&net,filename);
}
void Qfunction::loadQf(const char *filename){
	IDX::loadNetwork(&net,filename,GAMMA,LAMBDA_DECAY);
}
