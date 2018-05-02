#ifndef GAME_H
#define GAME_H
#include"defs.h"
#include"map.h"
#include<stdio.h>
class Game{
public:
	Map map;
	bool running;
	Game();
	~Game();
	void start();
	void reset();
	void end();
	void display();
	State *step(Action);
};
#endif
