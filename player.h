#ifndef _PLAYER_H
#define _PLAYER_H
#include"defs.h"
#include"qfunction.h"
#include<stdio.h>
#include<assert.h>
#include<vector>
#include"stack.h"
#include"gamedata.h"
using namespace std;
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
	void train(Stack<Info> &){}
};
class Agent:public Player{
public:
	GameData data;
	int currentTime;
	Qfunction qfunction;
	Stack<Info> trainSet;
	Agent();
	~Agent();
	void decide(Action &,Info &);
	void train(Stack<Info> &);
	void verifyRecords(Stack<Info> &);
	void addFutureRewards(Stack<Info> &);
};
#endif
