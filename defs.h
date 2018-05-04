#ifndef _DEFS_H
#define _DEFS_H
//#define HUMAN
#define STATEVARS 18
#define RANDSCALING 10
#define MEMORYSIZE 1000
#define BATCHSIZE 10
#define ALPHA 0.1
#define GAMMA 0.01
#define DISCOUNT 0.6
#define HIDDENUNITS 100
#ifdef HUMAN
	#define TRAININGTIME 0
#else
	#define TRAININGTIME 10000
#endif

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

typedef int Action;
struct Info{
	double targetQ;
	double reward;
	Action action;
	double state[STATEVARS];
	Info &operator=(const Info &x){
		targetQ=x.targetQ;
		reward=x.reward;
		action=x.action;
		for(int i=0;i<STATEVARS;i++){
			state[i]=x.state[i];
		}
		return *this;
	}
};
#endif
