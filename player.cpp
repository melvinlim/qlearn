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
		data.updateActionStateArray(info);
//passing ASA with action of 0 and expecting getBestAction to modify function and try other possibilities.
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
	data.updateActionStateArray(info);
	int nextQ=0;
	double Q;
	double targetQ;
	double QMax=qfA.getQMax(data.actionStateArray);
	int iA,iB;
	iA=iB=0;
	records.pop_back();
//	for(int r=0;r<2;r++)
	for(int i=records.size-1;i>=0;i--){
		info=records.atIndex(i);
		data.updateActionStateArray(info);
		nextQ=random()%2;
		if(nextQ==0){
			Q=qfB.getQ(data.actionStateArray);
			targetQ=Q+ALPHA*(info.reward+DISCOUNT*QMax-Q);
			data.targetArray->item[0]=targetQ;
			qfB.updateQ(data.actionStateArray,data.targetArray);
			QMax=qfB.getQMax(data.actionStateArray);
			if(iB++ >= BATCHSIZE){
				qfB.net->updateWeights();
				iB=0;
			}
		}else{
			Q=qfA.getQ(data.actionStateArray);
			targetQ=Q+ALPHA*(info.reward+DISCOUNT*QMax-Q);
			data.targetArray->item[0]=targetQ;
			qfA.updateQ(data.actionStateArray,data.targetArray);
			QMax=qfA.getQMax(data.actionStateArray);
			if(iA++ >= BATCHSIZE){
				qfA.net->updateWeights();
				iA=0;
			}
		}
	}
	records.clear();
/*
	double sse=1000;
	for(int t=0;t<MEMORYSIZE;t++){
		sse=0;
		for(int i=0;i<BATCHSIZE;i++){
			info=records.item[random()%MEMORYSIZE];
			//info=records.item[i];
			data.updateActionStateArray(info);
			data.targetArray->item[0]=info.targetQ;
			qfA.updateQ(data.actionStateArray,data.targetArray);
			sse+=data.sumSqError(&qfA.net->error);
		}
		sse/=(float)BATCHSIZE;
//		printf("sse:%f\n",sse);
		assert(sse<1000);
		qfA.net->updateWeights();
	}
	records.clear();
*/
}
void Agent::addFutureRewards(Stack<Info> &records){
	Info info;
	info=records.back();
/*
	data.updateActionStateArray(info);
	double Q;
	double QMax=qfA.getQMax(data.actionStateArray);
	records.pop_back();
	for(int i=records.size-1;i>=0;i--){
		info=records.atIndex(i);
		data.updateActionStateArray(info);
		records.item[i].QMax=QMax;
		Q=qfA.getQ(data.actionStateArray);
		records.item[i].targetQ=Q+ALPHA*(info.reward+DISCOUNT*QMax-Q);
		QMax=qfA.getQMax(data.actionStateArray);
	}
*/
}
