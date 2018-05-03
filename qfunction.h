#ifndef _QFUNCTION_H
#define _QFUNCTION_H
#include"defs.h"
#include"mynn/net.h"
#include"array.h"
#include<stdio.h>
#include<stdlib.h>
class Qfunction{
public:
	Array<double> *rewardArray;
	Array<double> *stateArray;
	void updateStateArray(Array<double> *,int,double *);
	Net *net;
	int nActions;
	int nStateVars;
	Qfunction(int,int);
	~Qfunction();
	double getReward(int,double *);
	int getBestAction(double *);
	int getRandomAction(double *);
	void updateQ(Info &);
};
#endif
