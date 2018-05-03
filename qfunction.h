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
	Array<double> *previousStateArray;
	void updateStateArray(Array<double> *,int,double *);
	double previousRewardEst;
	double *previousState;
	int previousAction;
	Net *net;
	int nActions;
	Qfunction(int);
	~Qfunction();
	double getReward(int,double *);
	int getBestAction(double *);
	int getRandomAction(double *);
	void updateQ(double);
};
#endif
