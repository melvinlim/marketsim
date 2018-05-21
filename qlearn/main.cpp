#include<Python.h>
#include"gamecontroller.h"
#include"player.h"
#include"defs.h"
#include<string.h>
#include<time.h>
GameController gameController;
Info info;
int game(){
	time_t startTime,endTime;
	#ifdef HUMAN
		Human player;
	#else
		Agent player;
	#endif
	info.reward=0;
	memset(info.state,0,sizeof(double)*STATEVARS);
	unsigned long t=0;
	int i=0;
	time(&startTime);
	for(;;){
		gameController.reset();
		gameController.start();
		gameController.updateState();
		while(gameController.running){
			t++;
			i++;
			if(t>TRAININGTIME){
				time(&endTime);
				gameController.displayOutput=true;
				printf("training time: %d\n",(int)difftime(endTime,startTime));
				printf("t: %d\n",gameController.t);
				gameController.display();
			}
			gameController.getState(info.state);
			player.decide(info.state,info.action);
			info.reward=gameController.step(info.action);
			gameController.updateState();
			if(info.reward!=0){	//if the game is over.
				memset(info.nextState,0,sizeof(double)*STATEVARS);
			}else{
				gameController.getState(info.nextState);
			}
			gameController.records.push_back(info);
			if(i>=MEMORYSIZE){
				player.train(gameController.records);
				player.getSumSqErr(gameController.records);
				gameController.records.clear();
				i=0;
			}
		}
		gameController.end();
	}
	return 0;
}
static PyObject *qlearn_printInfo(PyObject *self,PyObject *args){
	printf("\naction: %d\n",info.action);
	printf("state: ");
	for(int i=0;i<STATEVARS;i++){
		printf("%f,",info.state[i]);
	}
	printf("\nreward: %d\n",info.reward);
	return PyLong_FromLong(0);
}
static PyObject *qlearn_storeReward(PyObject *self,PyObject *args){
	double x;
	PyArg_ParseTuple(args,"f",&x);
	info.reward=x;
	return PyLong_FromLong(0);
}
static PyObject *qlearn_storeAction(PyObject *self,PyObject *args){
	int x;
	PyArg_ParseTuple(args,"i",&x);
	info.action=x;
	return PyLong_FromLong(0);
}
static PyObject *qlearn_storeState(PyObject *self,PyObject *args){
	float x;
	PyObject *tmp;
	Py_ssize_t sz=PyTuple_Size(args);
	printf("C++ received: ");
	for(Py_ssize_t i=0;i<sz;i++){
		tmp=PyTuple_GetItem(args,i);
		if(tmp==0)	return 0;
		tmp=PyNumber_Float(tmp);
		if(tmp==0)	return 0;
		x=PyFloat_AsDouble(tmp);
		info.state[i]=x;
		printf("%f,",x);
	}
	printf("\n");
	return PyLong_FromLong(0);
}
static PyObject *qlearn_game(PyObject *self,PyObject *args){
	game();
	return PyLong_FromLong(0);
}
static PyMethodDef QLearnMethods[] = {
    {"game",  qlearn_game, METH_VARARGS,
     "run game."},
    {"printInfo",  qlearn_printInfo, METH_VARARGS,
     "."},
    {"storeState",  qlearn_storeState, METH_VARARGS,
     "."},
    {"storeAction",  qlearn_storeAction, METH_VARARGS,
     "."},
    {"storeReward",  qlearn_storeReward, METH_VARARGS,
     "."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};
PyMODINIT_FUNC
initqlearn(void)
{
    PyObject *m;

    m = Py_InitModule("qlearn", QLearnMethods);
    if (m == NULL)
        return;
}
int main(int argc,char *argv[]){
	/* Pass argv[0] to the Python interpreter */
	Py_SetProgramName(argv[0]);
	/* Initialize the Python interpreter.  Required. */
	Py_Initialize();
	/* Add a static module */
	initqlearn();
	return 0;
}
