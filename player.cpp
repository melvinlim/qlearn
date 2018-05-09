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
	qfA.nextQ=&qfB;
	qfB.nextQ=&qfA;
	QArrayA=new Array<double>(4+STATEVARS);
	QArrayB=new Array<double>(4+STATEVARS);
}
Agent::~Agent(){}
void Agent::decide(Action &action,Info &info){
	currentTime++;
	if(currentTime<TRAININGTIME){
		action=qfA.getRandomAction();
	}else{
//passing ASArray with action of 0 and expecting getQArray to modify array to try all other possibilities.
		//qfA.updateActionStateArray(0,info.state);
		//qfA.getQArray(QArrayA,qfA.actionStateArray);
		//qfB.getQArray(QArrayB,qfA.actionStateArray);
		qfA.getQArray(QArrayA,info.state);
		qfB.getQArray(QArrayB,info.state);
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
	qfA.updateActionStateArray(info.action,info.state);
	double Q;
	double targetQ;
	double reward;
	double QMax;
	records.pop_back();
	double currentError;
	double sse=0;
	int t;
	Qfunction *qptr=&qfA;
	for(int i=0;i<records.size;i++){
//		t=random()%records.size;
		t=i;
		info=records.atIndex(t);
		reward=info.reward;
//		t=random()%2;
//		if(t==0)
			qptr=qptr->nextQ;
		if(reward!=0){
			targetQ=reward;
			//targetQ=Q+ALPHA*(reward-Q);
		}else{
//			qfA.updateActionStateArray(info.action,info.state);
//			Q=qptr->getQ(qfA.actionStateArray);
			Q=qptr->getQ(info.action,info.state);
			//qfA.updateActionStateArray(info.action,info.nextState);
			//QMax=qptr->nextQ->getQMax(qfA.actionStateArray);
			QMax=qptr->nextQ->getQMax(info.action,info.nextState);
			targetQ=Q+ALPHA*(reward+DISCOUNT*QMax-Q);
//			qfA.updateActionStateArray(info.action,info.state);
		}
//		qfA.targetArray->item[0]=targetQ;
//		qptr->updateQ(qfA.actionStateArray,qfA.targetArray);
		qptr->updateQ(info.action,info.state,targetQ);
		currentError=qptr->net.error.item[0];
		if(qptr->iter++ >= BATCHSIZE){
			qptr->net.updateWeights();
			sse+=currentError*currentError;
			qptr->iter=0;
//			printf("%x sse:%f\n",qptr,sse/(double)BATCHSIZE);
			sse=0;
		}
	}
	records.clear();
}
