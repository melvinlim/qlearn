#include"idx.h"
void IDX::displayImage(double *img){
	double *p=img;
	for(int i=0;i<28;i++){
		for(int j=0;j<28;j++){
			if(*p++>0){
				printf(".");
			}else{
				printf(" ");
			}
		}
		printf("\n");
	}
}
void IDX::printImage(struct image *img){
	uint8_t *p=img->pixel;
	for(int i=0;i<28;i++){
		for(int j=0;j<28;j++){
			if(*p++>=128){
				printf(".");
			}else{
				printf(" ");
			}
		}
		printf("\n");
	}
}
bool IDX::verifiedHeader(struct idx2 *hdr){
	//assert(bswap_32(idx1Header->magic)==0x801);
	if((hdr->magic)==0xe02){
		return true;
	}
	if(bswap_32(hdr->magic)==0xe02){
		hdr->nRows=bswap_32(hdr->nRows);
		hdr->nCols=bswap_32(hdr->nCols);
		return true;
	}
	return false;
}
void IDX::loadNetwork(Net *net,const char *filename,const double &gamma,const double &lambda_decay){
	void *mem;
	int offset;
	struct idx2 *idx2Header;
	int layers=0;
	int fd=open(filename,O_RDONLY);
	int8_t *ptr;
	int rows,cols;
	const int MAXLAYERS=10;
	int lRows[MAXLAYERS];
	int lCols[MAXLAYERS];
	int MMAPSIZE=1024*1024*1024;	//this must be >= file size.
	assert(fd>=0);
	mem=mmap(0,MMAPSIZE,PROT_READ,MAP_FILE|MAP_SHARED,fd,0);
	assert(mem!=MAP_FAILED);
	idx2Header=(struct idx2 *)mem;
	offset=0;
	//int ninputs=idx2Header->nRows;
	//int hidden=idx2Header->nCols;
	while(verifiedHeader(idx2Header)){
		rows=idx2Header->nRows;
		cols=idx2Header->nCols;
		lRows[layers]=rows;
		lCols[layers]=cols;
		offset+=sizeof(struct idx2)+(rows*cols*sizeof(double));
		assert(offset<MMAPSIZE);
		ptr=(int8_t *)mem+offset;
		idx2Header=(struct idx2 *)ptr;
		layers++;
	}
	//int noutputs=idx2Header->nCols;
	//net=new SingleHidden(ninputs,hidden,noutputs,gamma,lambda_decay,scale_factor);
	idx2Header=(struct idx2 *)mem;
	offset=0;
	for(int i=0;i<layers;i++){
		Matrix<double> mat(lRows[i],lCols[i]);
		loadIDXEntry(mat,idx2Header);
		delete net->L[i];
		net->insertLayer(i,mat,gamma,lambda_decay);
		rows=idx2Header->nRows;
		cols=idx2Header->nCols;
		offset+=sizeof(struct idx2)+(rows*cols*sizeof(double));
		ptr=(int8_t *)mem+offset;
		idx2Header=(struct idx2 *)ptr;
	}
	close(fd);
	assert(munmap(mem,MMAPSIZE)==0);
}
void IDX::loadIDXEntry(Matrix<double> &mat,idx2 *hdr){
	double *ptr;
	int rows,cols,matlen;
	rows=hdr->nRows;
	cols=hdr->nCols;
	matlen=rows*cols;
	ptr=(double *)++hdr;
	for(int i=0;i<matlen;i++){
		mat.item[i]=*ptr++;
	}
}
void IDX::saveIDXEntry(Matrix<double> &mat,int fd){
	struct idx2 hdr;
	hdr.magic=0xe02;
	hdr.nRows=mat.nRows;
	hdr.nCols=mat.nCols;
	double *ptr=mat.item;
	write(fd,&hdr,sizeof(hdr));
	for(int i=0;i<mat.nRows;i++){
		for(int j=0;j<mat.nCols;j++){
			write(fd,ptr++,sizeof(ptr));
		}
	}
}
void IDX::saveIDX(Matrix<double> &mat,const char *filename){
	int fd=open(filename,O_CREAT|O_TRUNC|O_WRONLY);
	assert(fd>=0);
	saveIDXEntry(mat,fd);
	close(fd);
}
void IDX::saveNetwork(Net *network,const char *filename){
	int fd=open(filename,O_CREAT|O_TRUNC|O_WRONLY);
	assert(fd>=0);
	int layers=network->n;
	for(int i=0;i<layers;i++){
		saveIDXEntry(network->L[i]->mat,fd);
	}
	close(fd);
}
