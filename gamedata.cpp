#include"gamedata.h"

GameData::~GameData(){}
GameData::GameData():Data(){
	nActions=4;
	nStateVars=STATEVARS;
	sz=4;
	nOutputs=4;
/*
	pInputs=new Array<double> *[sz];
	pOutputs=new Array<double> *[sz];
	pInputs[0]=new Array<double>(exlinear1,LINEARINPUTS);
	pInputs[1]=new Array<double>(exlinear2,LINEARINPUTS);
	pInputs[2]=new Array<double>(exlinear3,LINEARINPUTS);
	pInputs[3]=new Array<double>(exlinear4,LINEARINPUTS);
	pOutputs[0]=new Array<double>(anslinear1,LINEAROUTPUTS);
	pOutputs[1]=new Array<double>(anslinear2,LINEAROUTPUTS);
	pOutputs[2]=new Array<double>(anslinear3,LINEAROUTPUTS);
	pOutputs[3]=new Array<double>(anslinear4,LINEAROUTPUTS);
*/
	actionStateArray=new Array<double>(nActions+nStateVars);
	targetArray=new Array<double>(1);
}
void GameData::status(Array<double> **ioArrays,const Array<double> *response,const Array<double> *error){
	Array<double> *pIn=ioArrays[0];
	Array<double> *pOut=ioArrays[1];
	printf("in:[%+.0f,%+.0f] resp:[%+.2f,%+.2f] targ:[%+.2f,%+.2f] err:[%+.2f,%+.2f]\n",
	pIn->item[0],pIn->item[1],
	response->item[0],response->item[1],
	pOut->item[0],pOut->item[1],
	error->item[0],error->item[1]
	);
}
void GameData::verifyRecords(Stack<Info> &records){
	Info info;
	int k;
	int r=0;
	while(!records.empty()){
		r++;
		info=records.pop_back();
		printf("%d: %d\n",r,info.action);
		printf("reward: %f\n",info.reward);
		printf("targetQ: %f\n",info.targetQ);
		printf("Q: %f\n",info.Q);
		printf("Q0: %f\n",info.Q0);
		k=0;
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				printf("%+f,",info.state[k++]);
			}
			printf("\n");
		}
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				printf("%+f,",info.state[k++]);
			}
			printf("\n");
		}
if(info.reward>0)
		getchar();
	}
}
void GameData::updateActionStateArray(Info &info){
	Action action=info.action;
	double *state=info.state;
	assert(action<nActions);
	int p=0;
	for(int i=0;i<nActions;i++){
		actionStateArray->item[p++]=aStates[action][i];
	}
	for(int i=0;i<nStateVars;i++){
		actionStateArray->item[p++]=state[i];
	}
}
