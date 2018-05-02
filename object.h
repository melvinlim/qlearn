#ifndef _OBJECT_H
#define _OBJECT_H
class Object{
public:
	Object();
	~Object();
	int xLoc;
	int yLoc;
	char self;
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
