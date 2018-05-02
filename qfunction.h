#ifndef _QFUNCTION_H
#define _QFUNCTION_H
#include"defs.h"
#include"mynn/net.h"
#include<stdio.h>
class Qfunction{
public:
	Net *net;
	int nActions;
	Qfunction(int);
	~Qfunction();
	double getReward(int,double *);
	int getBestAction(double *);
};
#endif
