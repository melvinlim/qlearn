#ifndef _PLAYER_H
#define _PLAYER_H
#include"defs.h"
#include<stdio.h>
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
	Agent();
	~Agent();
	void decide(Action &,Info &);
};
#endif
