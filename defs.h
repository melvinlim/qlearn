#ifndef _DEFS_H
#define _DEFS_H
//#define HUMAN
#define DEBUG
#define STATEVARS 18
#define RANDSCALING 10
#define MEMORYSIZE 1000
#define BATCHSIZE 40
#define ALPHA 0.1
#define GAMMA (0.01/(double)BATCHSIZE)
#define DISCOUNT 0.8
#define HIDDENUNITS 500
#ifdef HUMAN
	#define TRAININGTIME 0
#else
	#define TRAININGTIME 20000
//	#define TRAININGTIME 0
#endif

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

typedef int Action;
struct Info{
	double targetQ;
	double Q;
	double Q0;
	double reward;
	Action action;
	double state[STATEVARS];
	Info &operator=(const Info &x){
		targetQ=x.targetQ;
		Q=x.Q;
		Q0=x.Q0;
		reward=x.reward;
		action=x.action;
		for(int i=0;i<STATEVARS;i++){
			state[i]=x.state[i];
		}
		return *this;
	}
};
#endif
