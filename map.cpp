#include"map.h"
Map::Map():mat(10,10){
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
	if(mat.item[i*10+j]=='<')	result=true;
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
			switch(mat.atIndex(i,j)){
				case 0:
					printf(".");
				break;
				case 1:
					printf("@");
				break;
				case 2:
					printf("<");
				break;
				default:
					printf("?");
			}
		}
		printf("\n");
	}
}
