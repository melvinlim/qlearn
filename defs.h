#ifndef _DEFS_H
#define _DEFS_H
#define STATEVARS 50
typedef char Action;
typedef char *State;
struct Info{
	double reward;
	double state[STATEVARS];
};
#endif
