#ifndef _OBJECT_H
#define _OBJECT_H
class Object{
public:
	int stateId;
	Object();
	~Object();
	int i;
	int j;
	char self;
};
class Floor:public Object{
public:
	Floor();
	~Floor();
};
class Stairs:public Object{
public:
	Stairs();
	~Stairs();
};
class PlayerObject:public Object{
public:
	PlayerObject();
	~PlayerObject();
};
#endif
