#ifndef _QFUNCTION_H
#define _QFUNCTION_H
#include"defs.h"
#include"mynn/net.h"
#include"array.h"
#include<stdio.h>
#include<stdlib.h>
const double aStates[4][4]={{+1,-1,-1,-1},{-1,+1,-1,-1},{-1,-1,+1,-1},{-1,-1,-1,+1}};
class Qfunction{
public:
	SingleHiddenLinear net;
	int iter;
	int nActions;
	int nStateVars;
	Qfunction *nextQ;
	Qfunction(int,int);
	~Qfunction();
	//double getQ(Array<double> *);
	double getQ(const Action &,const double *);
	//double getQMax(Array<double> *);
	double getQMax(const Action &,const double *);
	//int getBestAction(Array<double> *);
	int getBestAction(const double *);
	//void getQArray(Array<double> *,Array<double> *);
	void getQArray(Array<double> *,const double *);
	int getRandomAction();
	//void updateQ(Array<double> *,Array<double> *);
	void updateQ(const Action &,const double *,const double &);
	void modifyAction(Action);
	Array<double> *actionStateArray;
	Array<double> *targetArray;
	void updateActionStateArray(const Action &,const double *);
};
#endif
