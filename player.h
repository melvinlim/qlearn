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
	Action action;
public:
	Human();
	~Human();
	Action *decide();
};
#endif
