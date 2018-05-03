#ifndef _DEFS_H
#define _DEFS_H
//#define HUMAN
#define STATEVARS 18
#define RANDSCALING 10
#define MEMORYSIZE 1000
#define BATCHSIZE 50
#define GAMMA 0.01
#define DISCOUNT 0.6
#define HIDDENUNITS 100
#define TRAININGTIME 60000
typedef char Action;
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
