#include"matrix.h"

Matrix::Matrix(int m,int n){
	int i;
	nRows=m;
	nCols=n;
	item=new double[m*n];
	for(i=0;i<m*n;i++){
		item[i]=0;
	}
}
Matrix::~Matrix(){
	delete[] item;
}
double Matrix::atIndex(int i,int j) const{
	return item[i*nCols+j];
}
double Matrix::atIndex(int i,int j){
	return item[i*nCols+j];
}
void Matrix::randomize(int max){
	int i,j;
	double *p=item;
	for(i=0;i<nRows;i++){
		for(j=0;j<nCols;j++){
			*p++=random()%max;
			//*p++=(random()-(RAND_MAX/2))*2.0/((double)RAND_MAX)/((double)RANDSCALING);
		}
	}
}
void Matrix::print(){
	int i,j;
	for(i=0;i<nRows;i++){
		for(j=0;j<nCols;j++){
			printf("[%3i,%3i] %+.09f ",i,j,atIndex(i,j));
		}
		printf("\n");
	}
	printf("\n");
}
