#ifndef _WORLD_H
#define _WORLD_H
#include"matrix.h"
#include"object.h"
#include"defs.h"
#include<vector>
using namespace std;
class World{
	Matrix<char> mat;
	Matrix<char> vision;
public:
	double state[STATEVARS];
	PlayerObject playerObject;
	Stairs stairs;
	int nRows;
	int nCols;
	World();
	~World();
	void reset();
	void display();
	void displayMat(const Matrix<char> &);
	void generateWorld();
	void updateState();
	void placeObject(Object &,int,int);
	bool movePlayer(int,int);
	void debugState();
};
#endif