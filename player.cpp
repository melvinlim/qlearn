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
	if(currentTime<TRAININGTIME)
		action=qfunction.getRandomAction(info.state);
	else
		action=qfunction.getBestAction(info.state);
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
//if(info.reward!=0)
		getchar();
	}
}
void Agent::train(Stack<Info> &records){
//	verifyRecords(records);
	Info info;
	double targetQ;
	targetQ=0;
	info.reward=0;
	int i=0;
	bool resetQ=false;
	for(i=records.size-1;i>=0;i--){
		info=records.atIndex(i);
		targetQ+=info.reward;
		assert(targetQ<100);
		records.item[i].reward=targetQ;
		targetQ*=DISCOUNT;
		if(info.reward!=0){
			if(resetQ){
				targetQ=0;
				resetQ=false;
			}else	resetQ=true;
		}
	}
	info.reward=0;
//	verifyRecords(records);
	double sse=1000;
	while(sse>1){
		sse=0;
		for(int i=0;i<BATCHSIZE;i++){
			//info=records.item[random()%MEMORYSIZE];
			info=records.item[i];
			qfunction.updateQ(info);
			sse+=data.sumSqError(&qfunction.net->error);
		}
		sse/=(float)BATCHSIZE;
		printf("sse:%f\n",sse);
		assert(sse<1000);
		qfunction.net->updateWeights();
	}
	records.clear();
}
