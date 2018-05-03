#include"qfunction.h"
Qfunction::Qfunction(int nActions){
	this->nActions=nActions;
	net=new SingleHiddenLinear(4+STATEVARS,HIDDENUNITS,1,GAMMA);
	rewardArray=new Array<double>(1);
	stateArray=new Array<double>(4+STATEVARS);
}
Qfunction::~Qfunction(){}
double aStates[4][4]={{+1,-1,-1,-1},{-1,+1,-1,-1},{-1,-1,+1,-1},{-1,-1,-1,+1}};
void Qfunction::updateStateArray(Array<double> *array,int action,double *state){
	assert(action<4);
	int p=0;
	for(int i=0;i<4;i++){
		array->item[p++]=aStates[action][i];
	}
	for(int i=0;i<STATEVARS;i++){
		array->item[p++]=state[i];
	}
}
double Qfunction::getReward(int action,double *state){
	double resp;
	updateStateArray(stateArray,action,state);
	net->forward(stateArray);
	resp=net->response->item[0];
#ifdef DEBUG
	printf("resp: %f\n",resp);
#endif
	return resp;
}
void Qfunction::updateQ(Info &info){
	int iAction;
	switch(info.action){
		case 'n':
			iAction=0;
		break;
		case 'e':
			iAction=1;
		break;
		case 's':
			iAction=2;
		break;
		case 'w':
			iAction=3;
		break;
	}
	rewardArray->item[0]=info.reward;
	updateStateArray(stateArray,iAction,info.state);
#ifdef DEBUG
	stateArray->print();
	rewardArray->print();
	printf("training w. reward=%f -> ",info.reward);
#endif
	net->trainBatch(stateArray,rewardArray);
#ifdef DEBUG
	newReward=getReward(iAction,info.state);
	printf("Q reward=%f\n",newReward);
	getchar();
#endif
}
int Qfunction::getBestAction(double *state){
	int best=0;
	double bestVal=getReward(0,state);
	double tmpVal;
	for(int i=1;i<nActions;i++){
		tmpVal=getReward(i,state);
		if(tmpVal>bestVal){
			bestVal=tmpVal;
			best=i;
		}
	}
	return best;
}
int Qfunction::getRandomAction(double *state){
	int best=0;
	best=random()%4;
	updateStateArray(stateArray,best,state);
#ifdef DEBUG
	stateArray->print();
#endif
	return best;
}
