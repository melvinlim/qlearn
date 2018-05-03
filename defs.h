#ifndef _DEFS_H
#define _DEFS_H
#define STATEVARS 18
#define RANDSCALING 10
#define MEMORYSIZE 500
#define BATCHSIZE 20
typedef char Action;
struct Info{
	double reward;
	Action action;
	double state[STATEVARS];
};
#endif
