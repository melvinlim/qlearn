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
qfunction(4),
trainSet(BATCHSIZE)
{
	currentTime=0;
}
Agent::~Agent(){}
void Agent::decide(Action &action,Info &info){
	int y;
	currentTime++;
	if(currentTime<TRAININGTIME)
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
	if(currentTime>TRAININGTIME)
		getchar();
}
void Agent::verifyRecords(Stack<Info> &records){
	Info info;
	int k;
	int r=0;
	while(!records.empty()){
		r++;
/*
		info=records.back();
		records.pop_back();
*/
		info=records.pop_back();
		printf("%d: %c\n",r,info.action);
		printf("reward: %f\n",info.reward);
		k=0;
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				printf("%+f,",info.state[k++]);
			}
			printf("\n");
		}
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				printf("%+f,",info.state[k++]);
			}
			printf("\n");
		}
//if(info.reward>0)
		getchar();
	}
}
void Agent::train(Stack<Info> &records){
	verifyRecords(records);
/*
	Info info;
	double targetQ;
	targetQ=0;
	info.reward=0;
	int i=0;
	for(vector<Info>::reverse_iterator i=records.rbegin();i!=records.rend();i++){
		if(info.reward!=0){
			targetQ=0;
		}
		info=records.back();
		targetQ+=info.reward;
		info.reward=targetQ;
		targetQ*=DISCOUNT;
	}
	info.reward=0;
	while(!records.empty()){
		info=records.back();
		qfunction.updateQ(info);
		records.pop_back();
		if(i++%BATCHSIZE==0)
			qfunction.net->updateWeights();
	}
*/
}
