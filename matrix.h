#ifndef _MATRIX_H
#define _MATRIX_H
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"defs.h"

class Matrix{
public:
	int nRows;
	int nCols;
	double *item;
	Matrix(int,int);
	~Matrix();
	double atIndex(int,int) const;
	double atIndex(int,int);
	void randomize(int);
	void print();
	friend bool operator==(const Matrix &lhs,const Matrix &rhs){
		int mn=lhs.nRows*lhs.nCols;
		double tol=0.0001;
		for(int i=0;i<mn;i++){
			if(fabs(lhs.item[i]-rhs.item[i])>tol){
				return false;
			}
		}
		return true;
	}
};
#endif
