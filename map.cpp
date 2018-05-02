#include"map.h"
Map::Map():mat(10,10){
	nRows=nCols=10;
}
Map::~Map(){}
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
			}
		}
		printf("\n");
	}
}
