#include"layer.h"
Layer::Layer(Matrix<double> &mat,double gamma):
mat(mat),
dw(mat.nRows,mat.nCols),
out(mat.nCols),
deriv(mat.nCols),
delta(mat.nCols)
{
	int m=mat.nRows;
	int n=mat.nCols;
	nRows=m;
	nCols=n;
	this->gamma=gamma;
}
Layer::Layer(int m,int n,double gamma):
mat(m,n),
dw(m,n),
out(mat.nCols),
deriv(mat.nCols),
delta(mat.nCols)
{
	nRows=m;
	nCols=n;
	this->gamma=gamma;
}
Layer::~Layer(){
}
Array<double> &Layer::forward(const Array<double> &x){
	int i,j;
	double a,tmp;
	for(j=0;j<nCols;j++){
		a=0;
		for(i=0;i<x.nElements;i++){
			a+=(mat.atIndex(i,j))*x.item[i];
		}
		a+=(mat.atIndex(i,j));
		tmp=tanh(a);
		out.item[j]=tmp;
		deriv.item[j]=1.0-(tmp*tmp);
	}
	return(out);
}
void Layer::outputDelta(const Array<double> &error){
	int j;
	for(j=0;j<error.nElements;j++){
		delta.item[j]=deriv.item[j]*error.item[j];
	}
}
void Layer::hiddenDelta(const Matrix<double> &W,const Array<double> &delta2){
	int j,k;
	double sum;
	for(j=0;j<deriv.nElements;j++){
		sum=0;
		for(k=0;k<delta2.nElements;k++){
			sum+=(W.atIndex(j,k))*delta2.item[k];
		}
		delta.item[j]=deriv.item[j]*sum;
	}
}
void Layer::updateWeights(){
	int i,j;
	for(j=0;j<nCols;j++){
		for(i=0;i<nRows;i++){
			mat.item[i*nCols+j]+=dw.item[i*nCols+j];
			dw.item[i*nCols+j]=0;
		}
	}
}
void Layer::saveErrors(const Array<double> &input){
	int i,j;
	for(j=0;j<nCols;j++){
		for(i=0;i<input.nElements;i++){
			dw.item[i*nCols+j]+=gamma*input.item[i]*delta.item[j];
		}
		dw.item[i*nCols+j]+=gamma*delta.item[j];
	}
}
void Layer::directUpdateWeights(const Array<double> &input){
	int i,j;
	for(j=0;j<nCols;j++){
		for(i=0;i<input.nElements;i++){
			mat.item[i*nCols+j]+=gamma*input.item[i]*delta.item[j];
		}
		mat.item[i*nCols+j]+=gamma*delta.item[j];
	}
}
void Layer::randomize(){
	mat.randomize(RANDSCALING);
}