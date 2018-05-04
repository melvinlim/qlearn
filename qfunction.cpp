#include"qfunction.h"
Qfunction::Qfunction(int nActions,int nStateVars){
	this->nActions=nActions;
	this->nStateVars=nStateVars;
	net=new SingleHiddenLinear(nActions+nStateVars,HIDDENUNITS,1,GAMMA);
}
Qfunction::~Qfunction(){}
double Qfunction::getQMax(Array<double> *actionStateArray){
	double bestVal;
	double tmpVal;
	modifyAction(actionStateArray,0);
	bestVal=getQ(actionStateArray);
//actionStateArray->print(3);
//getchar();
	for(int i=1;i<nActions;i++){
		modifyAction(actionStateArray,i);
//actionStateArray->print(3);
//getchar();
		tmpVal=getQ(actionStateArray);
		if(tmpVal>bestVal){
			bestVal=tmpVal;
		}
	}
	return bestVal;
}
double Qfunction::getQ(Array<double> *actionStateArray){
	double resp;
	net->forward(actionStateArray);
	resp=net->response->item[0];
#ifdef DEBUG
//	printf("resp: %f\n",resp);
#endif
	return resp;
}
void Qfunction::updateQ(Array<double> *actionStateArray,Array<double> *targetArray){
#ifdef DEBUG
	actionStateArray->print();
	targetArray->print();
	printf("target Q:%f",targetArray->item[0]);
#endif
	net->trainBatch(actionStateArray,targetArray);
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
int Qfunction::getBestAction(Array<double> *actionStateArray){
	int best=0;
	double bestVal;
	double tmpVal;
	modifyAction(actionStateArray,0);
	bestVal=getQ(actionStateArray);
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
