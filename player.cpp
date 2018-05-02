#include"player.h"
Player::Player(){}
Player::~Player(){}
Human::Human(){}
Human::~Human(){}
Action *Human::decide(){
	Action tmp=0;
	while(tmp!='\n'){
		action=tmp;
		tmp=getchar();
	}
	return &action;
}
