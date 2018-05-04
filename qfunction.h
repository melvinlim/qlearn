#ifndef _QFUNCTION_H
#define _QFUNCTION_H
#include"defs.h"
#include"mynn/net.h"
#include"array.h"
#include<stdio.h>
#include<stdlib.h>
class Qfunction{
public:
	Net *net;
	int nActions;
	int nStateVars;
	Qfunction(int,int);
	~Qfunction();
	double getQ(Array<double> *);
	double getQMax(Array<double> *);
	int getBestAction(Array<double> *);
	int getRandomAction();
	void updateQ(Array<double> *,Array<double> *);
	void modifyAction(Array<double> *,Action);
};
#endif
