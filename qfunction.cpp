#include"qfunction.h"
Qfunction::Qfunction(int nActions){
	this->nActions=nActions;
}
Qfunction::~Qfunction(){}
double Qfunction::getReward(int action,double *state){
	return 0;
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
