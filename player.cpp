#include"player.h"
Player::Player(){}
Player::~Player(){}
//void Player::decide(Action &action,Info &info){}
Human::Human(){}
Human::~Human(){}
void Human::decide(Action &action,Info &info){
	printf(":");
	char tmp;
	char prev;
	tmp=' ';
	while(tmp!='\n'){
		prev=tmp;
		tmp=getchar();
	}
	switch(prev){
		case 'n':
			action=NORTH;
		break;
		case 'e':
			action=EAST;
		break;
		case 's':
			action=SOUTH;
		break;
		case 'w':
			action=WEST;
		break;
		default:
			action=4;
		break;
	}
}
Agent::Agent():
qfunction(4,STATEVARS),
trainSet(BATCHSIZE)
{
	currentTime=0;
}
Agent::~Agent(){}
void Agent::decide(Action &action,Info &info){
	currentTime++;
	if(currentTime<TRAININGTIME){
		action=qfunction.getRandomAction();
	}else{
		data.updateActionStateArray(info);
//passing ASA with action of 0 and expecting getBestAction to modify function and try other possibilities.
		action=qfunction.getBestAction(data.actionStateArray);
	}
	if(currentTime>TRAININGTIME)
		getchar();
}
void Agent::train(Stack<Info> &records){
//	data.verifyRecords(records);
	data.addFutureRewards(records);
//	data.verifyRecords(records);
//train
	Info info;
	double sse=1000;
	while(sse>1){
		sse=0;
		for(int i=0;i<BATCHSIZE;i++){
			info=records.item[random()%MEMORYSIZE];
			//info=records.item[i];
			data.updateActionStateArray(info);
			qfunction.updateQ(data.actionStateArray,data.rewardArray);
			sse+=data.sumSqError(&qfunction.net->error);
		}
		sse/=(float)BATCHSIZE;
//		printf("sse:%f\n",sse);
		assert(sse<1000);
		qfunction.net->updateWeights();
	}
	records.clear();
}
