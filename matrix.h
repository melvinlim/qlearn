#ifndef _MATRIX_H
#define _MATRIX_H
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"defs.h"
#include<algorithm>
template<typename T>
class Matrix{
public:
	int nRows;
	int nCols;
	int nElements;
	T *item;
	Matrix(int m,int n){
		int i;
		nRows=m;
		nCols=n;
		nElements=nRows*nCols;
		item=new T[m*n];
		for(i=0;i<m*n;i++){
			item[i]=0;
		}
	}
	~Matrix(){
		delete[] item;
	}
	const T atIndex(int i,int j) const{
		return item[i*nCols+j];
	}
	T &atIndex(int i,int j){
		return item[i*nCols+j];
	}
	void clear(){
		T *p=item;
		for(int i=0;i<nElements;i++){
			*p++=0;
		}
	}
	void randomize(int scalefactor){
		int i,j;
		T *p=item;
		for(i=0;i<nRows;i++){
			for(j=0;j<nCols;j++){
				*p++=(random()-(RAND_MAX/2))*2.0/((T)RAND_MAX)/((T)scalefactor);
			}
		}
	}
	void randomizeInt(int max){
		int i,j;
		T *p=item;
		for(i=0;i<nRows;i++){
			for(j=0;j<nCols;j++){
				*p++=random()%max;
			}
		}
	}
	//modified from cppreference.com/w/cpp/language/operators
	T& operator=(const T& other) // copy assignment
	{
			if (this != &other) { // self-assignment check expected
					if (other.nElements != nElements) {         // storage cannot be reused
							delete[] item;              // destroy storage in this
							nElements = 0;
							item = nullptr;             // preserve invariants in case next line throws
							item = new T[other.size]; // create storage in this
							nElements = other.size;
					} 
					std::copy(other.item, other.item + other.nElements, item);
			}
			return *this;
	}
	T& operator[](std::size_t idx)       { return item[idx]; }
	const T& operator[](std::size_t idx) const { return item[idx]; }
	T &operator()(int i,int j){
		return atIndex(i,j);
	}
	const T &operator()(int i,int j) const{
		return atIndex(i,j);
	}
	void print(){
		int i,j;
		for(i=0;i<nRows;i++){
			for(j=0;j<nCols;j++){
				printf("[%3i,%3i] %+.09f ",i,j,atIndex(i,j));
			}
			printf("\n");
		}
		printf("\n");
	}
	friend bool operator==(const Matrix &lhs,const Matrix &rhs){
		int mn=lhs.nRows*lhs.nCols;
		T tol=0.0001;
		for(int i=0;i<mn;i++){
			if(fabs(lhs.item[i]-rhs.item[i])>tol){
				return false;
			}
		}
		return true;
	}
};
#endif
