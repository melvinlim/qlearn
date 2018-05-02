#ifndef PLAYER_H
#define PLAYER_H
#include"defs.h"
#include<stdio.h>
class Player{
public:
	Player();
	~Player();
};
class Human{
public:
	Human();
	~Human();
	void decide(Action &);
};
#endif
