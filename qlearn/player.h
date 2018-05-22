#ifndef _PLAYER_H
#define _PLAYER_H
#include"defs.h"
#include"qfunction.h"
#include<stdio.h>
#include<assert.h>
#include<vector>
#include"stack.h"
using namespace std;
class Player{
public:
	Player();
	~Player();
	virtual void save(){};
	virtual void load(){};
//	virtual void decide(Action &,Info &);
	void verifyRecords(Stack<Info> &);
};
class Agent:public Player{
public:
	Array<double> *QArrayA;
	Array<double> *QArrayB;
	int currentTime;
	Qfunction qfA;
	Qfunction qfB;
	Agent();
	~Agent();
	void decide(const double *,Action &);
	void train(Stack<Info> &);
	double getSumSqErr(Stack<Info> &);
	void save();
	void load();
};
#endif
