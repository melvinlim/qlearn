#ifndef _GAMECONTROLLER_H
#define _GAMECONTROLLER_H
#include"defs.h"
#include"map.h"
#include<stdio.h>
#include<vector>
#include"stack.h"
using namespace std;
class GameController{
public:
	//vector<struct Info> records;
	Stack<Info> records;
	Map map;
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
