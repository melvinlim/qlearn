#include"world.h"
void World::updateState(){
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
	int iRel=stairs.i-i;
	if(abs(iRel)<=1){
		int jRel=stairs.j-j;
		if(abs(jRel)<=1){
			int iSt=iRel+1;
			int jSt=jRel+1;
			if(vision(iSt,jSt)!=' '){
				vision(iSt,jSt)='<';
			}
		}
	}
#ifdef DEBUG
	displayMat(vision);
#endif
	double *p=state;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(vision(i,j)=='.'){
				*p++=0;
			}else if(vision(i,j)=='@'){
				*p++=0;
			}else if(vision(i,j)=='<'){
				*p++=1.;
			}else{
				*p++=-1.;
			}
		}
	}
#ifdef DEBUG
//	debugState();
#endif
}
void World::debugState(){
	for(int i=0;i<STATEVARS;i++){
		if(i%3==0){
			printf("\n");
		}
		printf("%2.2f ",state[i]);
	}
	printf("\n");
}
void World::displayMat(const Matrix<char> &m){
	for(int i=0;i<m.nRows;i++){
		for(int j=0;j<m.nCols;j++){
			printf("%c",m(i,j));
		}
		printf("\n");
	}
}
World::World():
	world(10,10),
	vision(3,3)
{
	nRows=nCols=10;
	reset();
}
void World::reset(){
	generateWorld();
	srand(time(0));
	int i=1+random()%(nRows-2);
	int j=1+random()%(nCols-2);
	placeObject(playerObject,i,j);
	int t=0;
	do{
		t=random()%nRows;
	}while(t==i);
	i=t;
	j=1+random()%(nCols-2);
	placeObject(stairs,i,j);
	updateState();
}
int World::movePlayer(int i,int j){
	int i0=playerObject.i;
	int j0=playerObject.j;
	if(world(i,j)==' ')	return -1;
	int result=0;
	if(i==stairs.i&&j==stairs.j)	result=1;
	world(i0,j0)='.';
	placeObject(playerObject,i,j);
	return result;
}
void World::generateWorld(){
	//for(int i=0;i<world.nRows;i++){
	//	for(int j=0;j<world.nCols;j++){
	for(int j=0;j<world.nCols;j++){
		world(0,j)=' ';
	}
	for(int i=1;i<world.nRows-1;i++){
		world(i,0)=' ';
		for(int j=1;j<world.nCols-1;j++){
			world(i,j)='.';
		}
		world(i,world.nCols-1)=' ';
	}
	for(int j=0;j<world.nCols;j++){
		world(world.nRows-1,j)=' ';
	}
}
World::~World(){}
void World::placeObject(Object &obj,int i,int j){
	world(i,j)=obj.self;
	obj.i=i;
	obj.j=j;
}
void World::display(){
	for(int i=0;i<nRows;i++){
		for(int j=0;j<nCols;j++){
			printf("%c",world(i,j));
		}
		printf("\n");
	}
}
