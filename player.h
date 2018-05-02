#ifndef _PLAYER_H
#define _PLAYER_H
#include"defs.h"
#include"qfunction.h"
#include<stdio.h>
#include<assert.h>
class Player{
public:
	Player();
	~Player();
//	virtual void decide(Action &,Info &);
};
class Human:public Player{
public:
	Human();
	~Human();
	void decide(Action &,Info &);
};
class Agent:public Player{
public:
	Qfunction qfunction;
	Agent();
	~Agent();
	void decide(Action &,Info &);
};
#endif
