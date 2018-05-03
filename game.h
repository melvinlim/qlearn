#ifndef _GAME_H
#define _GAME_H
#include"defs.h"
#include"map.h"
#include<stdio.h>
#include<vector>
#include"stack.h"
using namespace std;
class Game{
public:
	//vector<struct Info> records;
	Stack<Info> records;
	Map map;
	bool running;
	Game();
	~Game();
	void start();
	void reset();
	void end();
	void display();
	void step(Action,Info &);
	void getState(Info &);
	void updateState();
};
#endif
