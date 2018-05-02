#ifndef _MAP_H
#define _MAP_H
#include"matrix.h"
#include"object.h"
#include<vector>
using namespace std;
class Map{
	Matrix<int> mat;
public:
	PlayerObject playerObject;
	Stairs stairs;
	int nRows;
	int nCols;
	Map();
	~Map();
	void reset();
	void display();
	void generateMap();
	void placeObject(Object &,int,int);
	bool movePlayer(int,int);
};
#endif
