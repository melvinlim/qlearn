#include"gamedata.h"

GameData::~GameData(){}
GameData::GameData():Data(){
	sz=4;
	nOutputs=4;
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
