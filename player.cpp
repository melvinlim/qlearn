#include"player.h"
Player::Player(){}
Player::~Player(){}
Human::Human(){}
Human::~Human(){}
void Human::decide(Action &action){
	Action tmp=0;
	while(tmp!='\n'){
		action=tmp;
		tmp=getchar();
	}
}
