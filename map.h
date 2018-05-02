#ifndef _MAP_H
#define _MAP_H
#include"matrix.h"
class Map{
	Matrix<int> mat;
public:
	int nRows;
	int nCols;
	Map();
	~Map();
	void display();
};
#endif
