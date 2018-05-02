#include"map.h"
void Map::updateState(){
	int i=playerObject.i;
	int j=playerObject.j;
//	vision.atIndex(1,1)='@';
	vision(1,1)='@';
	if(i<=0){
		vision(0,0)=' ';
		vision(1,0)=' ';
		vision(2,0)=' ';
	}
	if(i>=9){
		vision(0,2)=' ';
		vision(1,2)=' ';
		vision(2,2)=' ';
	}
	if(i<=0){
		vision(0,0)=' ';
		vision(0,1)=' ';
		vision(0,2)=' ';
	}
	if(j>=9){
		vision(2,0)=' ';
		vision(2,1)=' ';
		vision(2,2)=' ';
	}
}
Map::Map():
	mat(10,10),
	vision(3,3)
{
	nRows=nCols=10;
	generateMap();
	placeObject(playerObject,4,4);
	placeObject(stairs,9,9);
}
void Map::reset(){
	mat.item[playerObject.i*10+playerObject.j]=0;
	placeObject(playerObject,4,4);
	placeObject(stairs,9,9);
}
bool Map::movePlayer(int i,int j){
	int i0=playerObject.i;
	int j0=playerObject.j;
	bool result=false;
	if(i==stairs.i&&j==stairs.j)	result=true;
	mat.item[i0*10+j0]=0;
	placeObject(playerObject,i,j);
	return result;
}
void Map::generateMap(){
	for(int i=0;i<mat.nRows;i++){
		for(int j=0;j<mat.nCols;j++){
			mat.item[i*10+j]=0;
		}
	}
}
Map::~Map(){}
void Map::placeObject(Object &obj,int i,int j){
	mat.item[i*10+j]=obj.id;
	obj.i=i;
	obj.j=j;
}
void Map::display(){
	for(int i=0;i<nRows;i++){
		for(int j=0;j<nCols;j++){
			switch(mat(i,j)){
				case 0:
					printf(".");
				break;
				case 1:
					printf("@");
				break;
				case 2:
					printf("<");
				break;
				case 3:
					printf(" ");
				break;
				default:
					printf("?");
			}
		}
		printf("\n");
	}
}
