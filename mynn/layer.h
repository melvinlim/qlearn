#ifndef _LAYER_H
#define _LAYER_H
#include<assert.h>
#include<math.h>
#include"defs.h"
#include"matrix.h"
#include"array.h"
class Layer{
public:
	double gamma;
	int nRows;
	int nCols;
	Matrix<double> mat;
	Matrix<double> dw;
	Array<double> out;
	Array<double> deriv;
	Array<double> delta;
	Layer(int,int,double);
	Layer(Matrix<double> &,double);
	~Layer();
	Array<double> &forward(const Array<double> &);
	void outputDelta(const Array<double> &);
	void hiddenDelta(const Matrix<double> &,const Array<double> &);
	void saveErrors(const Array<double> &);
	void updateWeights();
	void directUpdateWeights(const Array<double> &);
	void randomize();
};
#endif
