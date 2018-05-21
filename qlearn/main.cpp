#include<Python.h>
#include"gamecontroller.h"
#include"player.h"
#include"defs.h"
#include<string.h>
#include<time.h>
int game(){
	time_t startTime,endTime;
	GameController gameController;
	#ifdef HUMAN
		Human player;
	#else
		Agent player;
	#endif
	Info info;
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
#include<stdarg.h>
static PyObject *
qlearn_listToState(PyObject *self, PyObject *args){
	float x;
	PyObject *tmp;
	Py_ssize_t sz=PyTuple_Size(args);
	printf("C++ received: ");
	for(Py_ssize_t i=0;i<sz;i++){
		tmp=PyTuple_GetItem(args,i);
		tmp=PyNumber_Float(tmp);
		x=PyFloat_AsDouble(tmp);
		printf("%f,",x);
	}
	printf("\n");
	return PyLong_FromLong(0);
}
static PyObject *
qlearn_getArray(PyObject *self,PyObject *args){
	float x,y,z;
	if (!PyArg_ParseTuple(args,"(fff)",&x,&y,&z))
		return NULL;
	printf("C++ received: %f %f %f\n",x,y,z);
	return PyLong_FromLong(0);
}
static PyObject *QLearnError;
static PyObject *
qlearn_game(PyObject *self, PyObject *args){
	game();
	return PyLong_FromLong(0);
}
static PyObject *
qlearn_system(PyObject *self, PyObject *args)
{
    const char *command;
    int sts;
    if (!PyArg_ParseTuple(args, "s", &command))
        return NULL;
    sts = system(command);
    if (sts < 0) {
        PyErr_SetString(QLearnError, "System command failed");
        return NULL;
    }
    return PyLong_FromLong(sts);
}
static PyMethodDef QLearnMethods[] = {
    {"system",  qlearn_system, METH_VARARGS,
     "Execute a shell command."},
    {"game",  qlearn_game, METH_VARARGS,
     "run game."},
    {"listToState",  qlearn_listToState, METH_VARARGS,
     "."},
    {"getArray",  qlearn_getArray, METH_VARARGS,
     "pass an array."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};
PyMODINIT_FUNC
initqlearn(void)
{
    PyObject *m;

    m = Py_InitModule("qlearn", QLearnMethods);
    if (m == NULL)
        return;

    QLearnError = PyErr_NewException("qlearn.error", NULL, NULL);
    Py_INCREF(QLearnError);
    PyModule_AddObject(m, "error", QLearnError);
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
