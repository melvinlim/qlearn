#include"player.h"
Player::Player(){}
Player::~Player(){}
Human::Human(){}
Human::~Human(){}
Action *Human::decide(){
	action=getchar();
	return &action;
}
