#include"map.h"
void Map::updateState(){
	int i=playerObject.i;
	int j=playerObject.j;
	for(int m=0;m<3;m++){
		for(int n=0;n<3;n++){
			vision(m,n)='.';
		}
	}
	vision(1,1)='@';
	if(i<=0){
		vision(0,0)=' ';
		vision(0,1)=' ';
		vision(0,2)=' ';
	}
	if(i>=9){
		vision(2,0)=' ';
		vision(2,1)=' ';
		vision(2,2)=' ';
	}
	if(j<=0){
		vision(0,0)=' ';
		vision(1,0)=' ';
		vision(2,0)=' ';
	}
	if(j>=9){
		vision(0,2)=' ';
		vision(1,2)=' ';
		vision(2,2)=' ';
	}
	for(int m=0;m<3;m++){
		for(int n=0;n<3;n++){
			if(vision(m,n)!=' '){
				if(mat(i+m-1,j+n-1)=='<'){
					vision(m,n)='<';
				}
			}
		}
	}
	displayMat(vision);
	double *p=state;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(vision(i,j)=='.'){
				*p++=1.;
			}else{
				*p++=-1.;
			}
		}
	}
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(vision(i,j)=='<'){
				*p++=1.;
			}else{
				*p++=-1.;
			}
		}
	}
	debugState();
}
void Map::debugState(){
	for(int i=0;i<STATEVARS;i++){
		if(i%3==0){
			printf("\n");
		}
		printf("%2.2f ",state[i]);
	}
	printf("\n");
}
void Map::displayMat(const Matrix<char> &m){
	for(int i=0;i<m.nRows;i++){
		for(int j=0;j<m.nCols;j++){
			printf("%c",m(i,j));
		}
		printf("\n");
	}
}
Map::Map():
	mat(10,10),
	vision(3,3)
{
	nRows=nCols=10;
	reset();
}
void Map::reset(){
	generateMap();
	srand(time(0));
	int i=random()%nRows;
	int j=random()%nCols;
	placeObject(playerObject,i,j);
	int t=0;
	do{
		t=random()%nRows;
	}while(t==i);
	i=t;
	j=random()%nCols;
	placeObject(stairs,i,j);
	updateState();
}
bool Map::movePlayer(int i,int j){
	int i0=playerObject.i;
	int j0=playerObject.j;
	bool result=false;
	if(i==stairs.i&&j==stairs.j)	result=true;
	mat(i0,j0)='.';
	placeObject(playerObject,i,j);
	return result;
}
void Map::generateMap(){
	for(int i=0;i<mat.nRows;i++){
		for(int j=0;j<mat.nCols;j++){
			mat(i,j)='.';
		}
	}
}
Map::~Map(){}
void Map::placeObject(Object &obj,int i,int j){
	mat(i,j)=obj.self;
	obj.i=i;
	obj.j=j;
}
void Map::display(){
	for(int i=0;i<nRows;i++){
		for(int j=0;j<nCols;j++){
			printf("%c",mat(i,j));
		}
		printf("\n");
	}
}
