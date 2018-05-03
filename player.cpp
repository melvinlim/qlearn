#include"player.h"
Player::Player(){}
Player::~Player(){}
//void Player::decide(Action &action,Info &info){}
Human::Human(){}
Human::~Human(){}
void Human::decide(Action &action,Info &info){
	printf(":");
	Action tmp=0;
	while(tmp!='\n'){
		action=tmp;
		tmp=getchar();
	}
}
Agent::Agent():
qfunction(4)
{
	currentTime=0;
}
Agent::~Agent(){}
void Agent::decide(Action &action,Info &info){
	int y;
	currentTime++;
	if(currentTime<50000)
		y=qfunction.getRandomAction(info.state);
	else
		y=qfunction.getBestAction(info.state);
	switch(y){
		case 0:
			action='n';
		break;
		case 1:
			action='e';
		break;
		case 2:
			action='s';
		break;
		case 3:
			action='w';
		break;
		default:
			assert(false);
		break;
	}
	qfunction.updateQ(info.reward);
	if(currentTime%40)	qfunction.net->updateWeights();
	if(currentTime>50000)
		getchar();
}
