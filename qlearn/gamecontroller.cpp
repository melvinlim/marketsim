#include"gamecontroller.h"
GameController::GameController():
records(MEMORYSIZE)
{
	t=0;
	displayOutput=false;
}
GameController::~GameController(){}
void GameController::start(){
	running=true;
}
void GameController::reset(){
	world.reset();
}
void GameController::end(){
	t=0;
	if(displayOutput)
		printf("game over\n");
}
void GameController::display(){
	world.display();
}
double GameController::step(const Action &action){
	int i=world.playerObject.i;
	int j=world.playerObject.j;
	int result=0;
	double reward=0;
	switch(action){
		case NORTH:
			result=world.movePlayer(i-1,j);
		break;
		case EAST:
			result=world.movePlayer(i,j+1);
		break;
		case SOUTH:
			result=world.movePlayer(i+1,j);
		break;
		case WEST:
			result=world.movePlayer(i,j-1);
		break;
		default:
			printf("error\n");
			printf("received: %c (%d)\n",action,action);
			reward=0;
			#ifndef HUMAN
				assert(0);
			#endif
			return reward;
		break;
	}
	if(result<0){
		reward=-1;
		running=false;
	}else if(result>0){
		if(displayOutput)
			printf("win\n");
		reward=1;
		running=false;
	}
	if((++t>TIMELIMIT)&&(reward==0)){
		if(displayOutput)
			printf("out of time\n");
		reward=-0.5;
		running=false;
		t=0;
	}
	return reward;
}
void GameController::getState(double *state){
	memcpy(state,world.state,sizeof(double)*STATEVARS);
}
void GameController::updateState(){
	world.updateState();
}
