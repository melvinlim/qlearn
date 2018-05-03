#include"qfunction.h"
Qfunction::Qfunction(int nActions,int nStateVars){
	this->nActions=nActions;
	this->nStateVars=nStateVars;
	net=new SingleHiddenLinear(nActions+nStateVars,HIDDENUNITS,1,GAMMA);
}
Qfunction::~Qfunction(){}
double Qfunction::getReward(Array<double> *actionStateArray){
	double resp;
	net->forward(actionStateArray);
	resp=net->response->item[0];
#ifdef DEBUG
	printf("resp: %f\n",resp);
#endif
	return resp;
}
void Qfunction::updateQ(Array<double> *actionStateArray,Array<double> *rewardArray){
#ifdef DEBUG
	actionStateArray->print();
	rewardArray->print();
	printf("training w. reward=%f -> ",rewardArray->item[0]);
#endif
	net->trainBatch(actionStateArray,rewardArray);
#ifdef DEBUG
	int newReward=getReward(actionStateArray);
	printf("Q reward=%f\n",newReward);
	getchar();
#endif
}
int Qfunction::getBestAction(Array<double> *actionStateArray){
	int best=0;
	double bestVal=getReward(actionStateArray);
	double tmpVal;
	for(int i=1;i<nActions;i++){
		tmpVal=getReward(actionStateArray);
		if(tmpVal>bestVal){
			bestVal=tmpVal;
			best=i;
		}
	}
	return best;
}
int Qfunction::getRandomAction(){
	int best=0;
	best=random()%nActions;
	return best;
}
