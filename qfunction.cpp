#include"qfunction.h"
Qfunction::Qfunction(int nActions){
	double gamma=0.1;
	int hiddenUnits=50;
	this->nActions=nActions;
	net=new SingleHidden(STATEVARS,hiddenUnits,1,gamma);
}
Qfunction::~Qfunction(){}
double aStates[4][4]={{+1,-1,-1,-1},{-1,+1,-1,-1},{-1,-1,+1,-1},{-1,-1,-1,+1}};
//this will need to be dynamically created to vary with different action space sizes;
double Qfunction::getReward(int action,double *state){
	double resp;
	//should convert fully to Arrays to speed things up.
	for(int i=0;i<4;i++){
		printf("%f\n", aStates[action][i]);
	}
	stateArray=new Array<double>(aStates[action],state,4,STATEVARS);
	net->forward(stateArray);
	delete stateArray;
	resp=net->response->item[0];
	printf("resp: %f\n",resp);
	return resp;
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
