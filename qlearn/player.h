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
//	virtual void decide(Action &,Info &);
	void verifyRecords(Stack<Info> &);
};
class Human:public Player{
public:
	Human();
	~Human();
	void decide(const double *,Action &);
	void train(Stack<Info> &){}
};
class Agent:public Player{
public:
	Array<double> *QArrayA;
	Array<double> *QArrayB;
	int currentTime;
	Qfunction qfA;
	Qfunction qfB;
	Stack<Info> trainSet;
	Agent();
	~Agent();
	void decide(const double *,Action &);
	void train(Stack<Info> &);
	void getSumSqErr(Stack<Info> &);
};
#endif
