#ifndef GAME_H
#define GAME_H
#include"defs.h"
#include<stdio.h>
class Game{
public:
	bool running;
	Game();
	~Game();
	void start();
	void reset();
	void display();
	State *step(Action *);
};
#endif
