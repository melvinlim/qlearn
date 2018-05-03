#ifndef _PLAYER_H
#define _PLAYER_H
#include"defs.h"
#include"qfunction.h"
#include<stdio.h>
#include<assert.h>
#include<vector>
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
	void train(vector<Info> &){}
};
class Agent:public Player{
public:
	int currentTime;
	Qfunction qfunction;
	vector<Info> trainSet;
	Agent();
	~Agent();
	void decide(Action &,Info &);
	void train(vector<Info> &);
	void verifyRecords(vector<Info> &);
};
#endif
