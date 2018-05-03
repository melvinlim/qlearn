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
	if(currentTime>50000)
		getchar();
}
void Agent::verifyRecords(vector<Info> &records){
	Info info;
	int k;
	int r=0;
	while(!records.empty()){
		r++;
		info=records.back();
		records.pop_back();
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
void Agent::train(vector<Info> &records){
//	verifyRecords(records);
	Info info;
	int r=0;
	int size;
	int i=0;
	size=MEMORYSIZE;
	while(!records.empty()){
		r=random()%records.size();
		info=records[r];
		records.erase(records.begin()+r);
		qfunction.updateQ(info);
		if(i%BATCHSIZE==0)
			qfunction.net->updateWeights();
		i++;
	}
}
