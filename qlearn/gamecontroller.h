#ifndef _GAMECONTROLLER_H
#define _GAMECONTROLLER_H
#include"defs.h"
#include"world.h"
#include<stdio.h>
#include<vector>
#include"stack.h"
using namespace std;
class GameController{
public:
	int t;
	Stack<Info> records;
	World world;
	bool running;
	bool displayOutput;
	GameController();
	~GameController();
	void start();
	void reset();
	void end();
	void display();
	double step(const Action &);
	void getState(double *);
	void updateState();
};
#endif
