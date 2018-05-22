#ifndef _IDX_H
#define _IDX_H
#include<stdio.h>
#include<cstdint>
#include<assert.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/mman.h>
#include"matrix.h"
#include"net.h"
#include"string.h"

#define bswap_16(value) ((((value)&0xff)<<8)|((value)>>8))
#define bswap_32(value)	((bswap_16((value)&0xffff)<<16)|bswap_16((value)>>16))

#pragma pack(push,1)
struct idx1{
	int32_t magic;
	int32_t number;
};
struct idx2{
	int32_t magic;
	int32_t nRows;
	int32_t nCols;
};
struct idx3{
	int32_t magic;
	int32_t nImages;
	int32_t nRows;
	int32_t nCols;
};
struct image{
	uint8_t pixel[28*28];
};
#pragma pack(pop)

namespace IDX{
	void displayImage(double *img);
	void printImage(struct image *img);
	void loadIDXEntry(Matrix<double> &,struct idx2 *);
	void saveIDX(Matrix<double> &,const char *);
	void saveIDXEntry(Matrix<double> &,int);
	Matrix<double> *loadIDX(const char *);
	void saveNetwork(Net *,const char *);
	void loadNetwork(Net *,const char *,const double &,const double &);
	bool verifiedHeader(struct idx2 *);
};
#endif
