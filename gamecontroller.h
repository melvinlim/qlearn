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
	//vector<struct Info> records;
	Stack<Info> records;
	World world;
	bool running;
	GameController();
	~GameController();
	void start();
	void reset();
	void end();
	void display();
	void step(Action,Info &);
	void getState(Info &);
	void updateState();
};
#endif