#include"player.h"
Player::Player(){}
Player::~Player(){}
//void Player::decide(Action &action,Info &info){}
Human::Human(){}
Human::~Human(){}
void Human::decide(Action &action,Info &info){
	info.action=0;
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
qfA(4,STATEVARS),
qfB(4,STATEVARS),
trainSet(BATCHSIZE)
{
	currentTime=0;
	QArrayA=new Array<double>(4+STATEVARS);
	QArrayB=new Array<double>(4+STATEVARS);
}
Agent::~Agent(){}
void Agent::decide(Action &action,Info &info){
	currentTime++;
	if(currentTime<TRAININGTIME){
		action=qfA.getRandomAction();
	}else{
		data.updateActionStateArray(0,info.state);
//passing ASArray with action of 0 and expecting getQArray to modify array to try all other possibilities.
		qfA.getQArray(QArrayA,data.actionStateArray);
		qfB.getQArray(QArrayB,data.actionStateArray);
		double bestQ,tmpQ;
		action=0;
		bestQ=QArrayA->item[0]+QArrayB->item[0];
		for(int i=1;i<4;i++){
			tmpQ=QArrayA->item[i]+QArrayB->item[i];
			if(tmpQ>bestQ){
				action=i;
				bestQ=tmpQ;
			}
		}
	}
	if(currentTime>TRAININGTIME)
		getchar();
}
void Agent::train(Stack<Info> &records){
//	data.verifyRecords(records);
//	addFutureRewards(records);
//	data.verifyRecords(records);
//train
	Info info;
	info=records.back();
	data.updateActionStateArray(info.action,info.state);
	int nextQ=1;
	double Q;
	double targetQ;
	double reward;
	double QMax;
	int iA,iB;
	iA=iB=0;
	records.pop_back();
	double currentError;
	double sse=0;
//	for(int r=0;r<2;r++)
	for(int i=records.size-1;i>=0;i--){
		info=records.atIndex(i);
		data.updateActionStateArray(info.action,info.state);
		reward=info.reward;
//		nextQ=random()%2;
		nextQ=(nextQ+1)%2;
		if(nextQ==0){
			Q=qfB.getQ(data.actionStateArray);
			if(reward!=0){
				targetQ=Q+ALPHA*(reward-Q);
			}else{
				data.updateActionStateArray(info.action,info.nextState);
				QMax=qfB.getQMax(data.actionStateArray);
				targetQ=Q+ALPHA*(reward+DISCOUNT*QMax-Q);
			}
			data.targetArray->item[0]=targetQ;
			qfB.updateQ(data.actionStateArray,data.targetArray);
			currentError=qfB.net.error.item[0];
			if(iB++ >= BATCHSIZE){
				qfB.net.updateWeights();
				sse+=currentError*currentError;
				iB=0;
//				printf("qfB sse:%f\n",sse/(double)BATCHSIZE);
				sse=0;
			}
		}else{
			Q=qfA.getQ(data.actionStateArray);
			if(reward!=0){
				targetQ=Q+ALPHA*(reward-Q);
			}else{
				data.updateActionStateArray(info.action,info.nextState);
				QMax=qfA.getQMax(data.actionStateArray);
				targetQ=Q+ALPHA*(reward+DISCOUNT*QMax-Q);
			}
			data.targetArray->item[0]=targetQ;
			qfA.updateQ(data.actionStateArray,data.targetArray);
			currentError=qfA.net.error.item[0];
			if(iA++ >= BATCHSIZE){
				qfA.net.updateWeights();
				sse+=currentError*currentError;
				iA=0;
//				printf("qfA sse:%f\n",sse/(double)BATCHSIZE);
				sse=0;
			}
		}
	}
	records.clear();
}
