#include"qfunction.h"
Qfunction::Qfunction(int nActions,int nStateVars){
	this->nActions=nActions;
	this->nStateVars=nStateVars;
	net=new SingleHiddenLinear(nActions+nStateVars,HIDDENUNITS,1,GAMMA);
}
Qfunction::~Qfunction(){}
double Qfunction::getQ(Array<double> *actionStateArray){
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
	int newReward=getQ(actionStateArray);
	printf("Q reward=%f\n",newReward);
	getchar();
#endif
}
void Qfunction::modifyAction(Array<double> *actionStateArray,Action action){
	for(int i=0;i<4;i++){
		if(i==action){
			actionStateArray->item[i]=1;
		}else{
			actionStateArray->item[i]=-1;
		}
	}
}
int Qfunction::getBestAction(Array<double> *actionStateArray){
	int best=0;
	double bestVal=getQ(actionStateArray);
	double tmpVal;
	modifyAction(actionStateArray,0);
actionStateArray->print(3);
//getchar();
	for(int i=1;i<nActions;i++){
		modifyAction(actionStateArray,i);
//actionStateArray->print(3);
//getchar();
		tmpVal=getQ(actionStateArray);
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
