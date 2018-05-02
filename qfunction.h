#ifndef _QFUNCTION_H
#define _QFUNCTION_H
#include"defs.h"
#include<stdio.h>
class Qfunction{
public:
	int nActions;
	Qfunction(int);
	~Qfunction();
	double getReward(int,double *);
	int getBestAction(double *);
};
#endif
