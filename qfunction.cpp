#include"qfunction.h"
Qfunction::Qfunction(int nActions){
	this->nActions=nActions;
	net=new SingleHiddenLinear(STATEVARS,HIDDENUNITS,1,GAMMA);
	rewardArray=new Array<double>(1);
	stateArray=new Array<double>(4+STATEVARS);
	previousStateArray=new Array<double>(4+STATEVARS);
	previousState=new double[STATEVARS];
}
Qfunction::~Qfunction(){}
double aStates[4][4]={{+1,-1,-1,-1},{-1,+1,-1,-1},{-1,-1,+1,-1},{-1,-1,-1,+1}};
void Qfunction::updateStateArray(Array<double> *array,int action,double *state){
	int p=0;
	for(int i=0;i<4;i++){
		array->item[p++]=aStates[action][i];
	}
	for(int i=0;i<STATEVARS;i++){
		array->item[p++]=state[i];
	}
}
//this will need to be dynamically created to vary with different action space sizes;
double Qfunction::getReward(int action,double *state){
	double resp;
	//should convert fully to Arrays to speed things up.
	for(int i=0;i<4;i++){
//		printf("%f\n", aStates[action][i]);
	}
	updateStateArray(stateArray,action,state);
	net->forward(stateArray);
	resp=net->response->item[0];
	printf("resp: %f\n",resp);
	return resp;
}
void Qfunction::updateQ(Info &info){
	double newReward=0;
	rewardArray->item[0]=info.reward;
//	rewardArray->print();
	updateStateArray(previousStateArray,info.action,info.state);
//	previousStateArray->print();
	printf("training w. reward=%f -> ",info.reward);
	net->trainBatch(previousStateArray,rewardArray);
	newReward=getReward(info.action,info.state);
	printf("Q reward=%f\n",newReward);
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
	previousStateArray->print();
	previousRewardEst=-4;
	previousAction=best;
	return best;
}
