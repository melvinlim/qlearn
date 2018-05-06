#ifndef _GAMEDATA_H
#define _GAMEDATA_H
#include"array.h"
#include"mynn/data.h"
#include"stack.h"
#include"defs.h"
#include<time.h>
#define LINEARINPUTS 2
#define LINEAROUTPUTS 2

const double aStates[4][4]={{+1,-1,-1,-1},{-1,+1,-1,-1},{-1,-1,+1,-1},{-1,-1,-1,+1}};
const double exlinear1[LINEARINPUTS]={-1,-1};
const double exlinear2[LINEARINPUTS]={-1,+1};
const double exlinear3[LINEARINPUTS]={+1,-1};
const double exlinear4[LINEARINPUTS]={+1,+1};
const double anslinear1[LINEAROUTPUTS]={-50,23};
const double anslinear2[LINEAROUTPUTS]={+50,-4};
const double anslinear3[LINEAROUTPUTS]={+0.05,-10};
const double anslinear4[LINEAROUTPUTS]={-0.05,40};

class GameData:public Data{
public:
	Array<double> *actionStateArray;
	Array<double> *targetArray;
	int nActions;
	int nStateVars;
	GameData();
	~GameData();
	void status(Array<double> **,const Array<double> *,const Array<double> *);
//	void addFutureRewards(Stack<Info> &);
	void verifyRecords(Stack<Info> &);
	void updateActionStateArray(const Action &,const double *);
};
#endif
