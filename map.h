#ifndef _MAP_H
#define _MAP_H
#include"matrix.h"
#include"object.h"
#include"defs.h"
#include<vector>
using namespace std;
class Map{
	Matrix<int> mat;
	Matrix<char> vision;
public:
	State state[STATEVARS];
	PlayerObject playerObject;
	Stairs stairs;
	int nRows;
	int nCols;
	Map();
	~Map();
	void reset();
	void display();
	void generateMap();
	void updateState();
	void placeObject(Object &,int,int);
	bool movePlayer(int,int);
};
#endif
