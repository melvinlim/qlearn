#include"qfunction.h"
Qfunction::Qfunction(int nActions,int nStateVars):
net(nActions+nStateVars,HIDDENUNITS,1,GAMMA,LAMBDA_DECAY)
{
	this->nActions=nActions;
	this->nStateVars=nStateVars;
	actionStateArray=new Array<double>(nActions+nStateVars);
	targetArray=new Array<double>(1);
	iter=0;
}
Qfunction::~Qfunction(){}
//double Qfunction::getQMax(Array<double> *actionStateArray){
double Qfunction::getQMax(const Action &action,const double *state){
	updateActionStateArray(action,state);
	double bestVal;
	double tmpVal;
	modifyAction(actionStateArray,0);
	//bestVal=getQ(actionStateArray);
	bestVal=getQ(0,state);
//actionStateArray->print(3);
//getchar();
	for(int i=1;i<nActions;i++){
		modifyAction(actionStateArray,i);
//actionStateArray->print(3);
//getchar();
		//tmpVal=getQ(actionStateArray);
		tmpVal=getQ(i,state);
		if(tmpVal>bestVal){
			bestVal=tmpVal;
		}
	}
	return bestVal;
}
//double Qfunction::getQ(Array<double> *actionStateArray){
double Qfunction::getQ(const Action &action,const double *state){
	updateActionStateArray(action,state);
	double resp;
	net.forward(actionStateArray);
	resp=net.response->item[0];
#ifdef DEBUG
	printf("resp: %f\n",resp);
#endif
	return resp;
}
void Qfunction::updateQ(Array<double> *actionStateArray,Array<double> *targetArray){
#ifdef DEBUG
	actionStateArray->print();
	targetArray->print();
	printf("target Q:%f\n",targetArray->item[0]);
#endif
	net.trainBatch(actionStateArray,targetArray);
#ifdef DEBUG
	double response=getQ(actionStateArray);
	printf("Q response after training:%f\n",response);
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
//void Qfunction::getQArray(Array<double> *QArray,Array<double> *actionStateArray){
void Qfunction::getQArray(Array<double> *QArray,const double *state){
	updateActionStateArray(0,state);
	for(int i=0;i<nActions;i++){
		modifyAction(actionStateArray,i);
		//QArray->item[i]=getQ(actionStateArray);
		QArray->item[i]=getQ(i,state);
	}
}
//int Qfunction::getBestAction(Array<double> *actionStateArray){
int Qfunction::getBestAction(const double *state){
	updateActionStateArray(0,state);
	int best=0;
	double bestVal;
	double tmpVal;
	modifyAction(actionStateArray,0);
	//bestVal=getQ(actionStateArray);
	bestVal=getQ(0,state);
actionStateArray->print(3);
//getchar();
	for(int i=1;i<nActions;i++){
		modifyAction(actionStateArray,i);
//actionStateArray->print(3);
//getchar();
		//tmpVal=getQ(actionStateArray);
		tmpVal=getQ(i,state);
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
void Qfunction::updateActionStateArray(const Action &action,const double *state){
	assert(action<nActions);
	int p=0;
	for(int i=0;i<nActions;i++){
		actionStateArray->item[p++]=aStates[action][i];
	}
	for(int i=0;i<nStateVars;i++){
		actionStateArray->item[p++]=state[i];
	}
}
