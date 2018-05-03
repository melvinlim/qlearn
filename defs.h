#ifndef _DEFS_H
#define _DEFS_H
#define STATEVARS 18
#define RANDSCALING 10
#define MEMORYSIZE 500
typedef char Action;
struct Info{
	double reward;
	double state[STATEVARS];
};
#endif
