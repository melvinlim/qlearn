#include"qfunction.h"
Qfunction::Qfunction(int nActions){
	this->nActions=nActions;
	net=new SingleHiddenLinear(4+STATEVARS,HIDDENUNITS,1,GAMMA);
	rewardArray=new Array<double>(1);
	stateArray=new Array<double>(4+STATEVARS);
	previousStateArray=new Array<double>(4+STATEVARS);
	previousState=new double[STATEVARS];
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
	double newReward=0;
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
	updateStateArray(previousStateArray,iAction,info.state);
#ifdef DEBUG
	previousStateArray->print();
	rewardArray->print();
	printf("training w. reward=%f -> ",info.reward);
#endif
	net->trainBatch(previousStateArray,rewardArray);
#ifdef DEBUG
	newReward=getReward(iAction,info.state);
	printf("Q reward=%f\n",newReward);
	getchar();
#endif
}
void Qfunction::updateQ(double reward){
	double newReward=0;
	rewardArray->item[0]=reward;
	rewardArray->print();
	previousStateArray->print();
	printf("training w. reward=%f\n",reward);
	printf("before: %f\n",getReward(previousAction,previousState));
	net->trainBatch(previousStateArray,rewardArray);
	newReward=getReward(previousAction,previousState);
	printf("after %f\n",newReward);
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
	updateStateArray(previousStateArray,best,state);
	for(int i=0;i<STATEVARS;i++){
		previousState[i]=state[i];
	}
	previousStateArray->print();
	previousRewardEst=bestVal;
	previousAction=best;
	return best;
}
int Qfunction::getRandomAction(double *state){
	int best=0;
	best=random()%4;
	updateStateArray(previousStateArray,best,state);
	for(int i=0;i<STATEVARS;i++){
		previousState[i]=state[i];
	}
#ifdef DEBUG
	previousStateArray->print();
#endif
	previousRewardEst=-4;
	previousAction=best;
	return best;
}
