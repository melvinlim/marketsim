#ifndef _QFUNCTION_H
#define _QFUNCTION_H
#include"defs.h"
#include"mynn/net.h"
#include"mynn/idx.h"
#include"array.h"
#include<stdio.h>
#include<stdlib.h>
const double aStates[4][4]={{+1,-1,-1,-1},{-1,+1,-1,-1},{-1,-1,+1,-1},{-1,-1,-1,+1}};
class Qfunction{
private:
public:
	SingleHiddenLinear net;
	int iter;
	int nActions;
	int nStateVars;
	Qfunction *nextQ;
	Qfunction(int,int);
	~Qfunction();
	double getQ(const double *,const Action &);
	double getQMax(const double *,const Action &);
	int getBestAction(const double *);
	void getQArray(Array<double> *,const double *);
	int getRandomAction();
	void updateQ(const double *,const Action &,const double &);
	double getSqErr(const double *,const Action &,const double &);
	Array<double> *actionStateArray;
	Array<double> *targetArray;
	void updateActionStateArray(const double *,const Action &);
	void saveQf(const char *filename);
	void loadQf(const char *filename);
};
#endif
