#include<Python.h>
#include"gamecontroller.h"
#include"player.h"
#include"defs.h"
#include<string.h>
#include<time.h>
GameController gameController;
Info info;
Agent player;
static PyObject *qlearn_getSumSqErr(PyObject *self,PyObject *args){
	double x;
	x=player.getSumSqErr(gameController.records);
	return PyFloat_FromDouble(x);
}
static PyObject *qlearn_decide(PyObject *self,PyObject *args){
	player.currentTime=TRAININGTIME;
	double x;
	double state[STATEVARS];
	Action action;
	PyObject *tmp;
	Py_ssize_t sz=PyTuple_Size(args);
	for(Py_ssize_t i=0;i<sz;i++){
		tmp=PyTuple_GetItem(args,i);
		if(tmp==0)	return 0;
		tmp=PyNumber_Float(tmp);
		if(tmp==0)	return 0;
		x=PyFloat_AsDouble(tmp);
		state[i]=x;
	}
	player.decide(state,action);
	long res=action;
//	printf("decision (in main.cpp): %ld\n",res);
//	player.decide(const double *state,Action action);
	return PyLong_FromLong(res);
}
static PyObject *qlearn_loadQ(PyObject *self,PyObject *args){
	player.load();
	return PyLong_FromLong(0);
}
static PyObject *qlearn_saveQ(PyObject *self,PyObject *args){
	player.save();
	return PyLong_FromLong(0);
}
static PyObject *qlearn_train(PyObject *self,PyObject *args){
	player.train(gameController.records);
	return PyLong_FromLong(0);
}
static PyObject *qlearn_printRecords(PyObject *self,PyObject *args){
	player.verifyRecords(gameController.records);
	return PyLong_FromLong(0);
}
static PyObject *qlearn_printInfo(PyObject *self,PyObject *args){
	printf("previous state: ");
	for(int i=0;i<STATEVARS;i++){
		printf("%f,",info.state[i]);
	}
	printf("\n");
	printf("previous action: %d\n",info.action);
	printf("reward: %f\n",info.reward);
	printf("state: ");
	for(int i=0;i<STATEVARS;i++){
		printf("%f,",info.nextState[i]);
	}
	printf("\n");
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
static PyObject *qlearn_storeNextState(PyObject *self,PyObject *args){
	double x;
	PyObject *tmp;
	Py_ssize_t sz=PyTuple_Size(args);
	for(Py_ssize_t i=0;i<sz;i++){
		tmp=PyTuple_GetItem(args,i);
		if(tmp==0)	return 0;
		tmp=PyNumber_Float(tmp);
		if(tmp==0)	return 0;
		x=PyFloat_AsDouble(tmp);
		info.nextState[i]=x;
	}
	return PyLong_FromLong(0);
}
static PyObject *qlearn_storeState(PyObject *self,PyObject *args){
	double x;
	PyObject *tmp;
	Py_ssize_t sz=PyTuple_Size(args);
	for(Py_ssize_t i=0;i<sz;i++){
		tmp=PyTuple_GetItem(args,i);
		if(tmp==0)	return 0;
		tmp=PyNumber_Float(tmp);
		if(tmp==0)	return 0;
		x=PyFloat_AsDouble(tmp);
		info.state[i]=x;
	}
	return PyLong_FromLong(0);
}
static PyObject *qlearn_storeInfo(PyObject *self,PyObject *args){
	gameController.records.push_back(info);
	long n=gameController.records.size;
	return PyLong_FromLong(n);
}
static PyMethodDef QLearnMethods[] = {
    {"decide",  qlearn_decide, METH_VARARGS,
     "."},
    {"train",  qlearn_train, METH_VARARGS,
     "."},
    {"saveQ",  qlearn_saveQ, METH_VARARGS,
     "."},
    {"loadQ",  qlearn_loadQ, METH_VARARGS,
     "."},
    {"getSumSqErr",  qlearn_getSumSqErr, METH_VARARGS,
     "."},
    {"printRecords",  qlearn_printRecords, METH_VARARGS,
     "."},
    {"printInfo",  qlearn_printInfo, METH_VARARGS,
     "."},
    {"storeNextState",  qlearn_storeNextState, METH_VARARGS,
     "."},
    {"storeState",  qlearn_storeState, METH_VARARGS,
     "."},
    {"storeAction",  qlearn_storeAction, METH_VARARGS,
     "."},
    {"storeReward",  qlearn_storeReward, METH_VARARGS,
     "."},
    {"storeInfo",  qlearn_storeInfo, METH_VARARGS,
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
