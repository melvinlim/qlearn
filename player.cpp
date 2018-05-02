#include"player.h"
Player::Player(){}
Player::~Player(){}
Human::Human(){}
Human::~Human(){}
Action *Human::decide(){
	do{
		action=getchar();
	}while(action=='\n');
	return &action;
}
