#include"gamecontroller.h"
GameController::GameController():
records(MEMORYSIZE)
{
}
GameController::~GameController(){}
void GameController::start(){
	running=true;
}
void GameController::reset(){
	map.reset();
}
void GameController::end(){
#ifdef DEBUG
	printf("game over\n");
#endif
}
void GameController::display(){
	map.display();
}
void GameController::step(Action action,Info &info){
	int i=map.playerObject.i;
	int j=map.playerObject.j;
	bool result=false;
	int reward=0;
	switch(action){
		case'n':
			if(i>0)
				result=map.movePlayer(i-1,j);
			else{
				reward=-1;
				running=false;
			}
		break;
		case's':
			if(i<9)
				result=map.movePlayer(i+1,j);
			else{
				reward=-1;
				running=false;
			}
		break;
		case'e':
			if(j<9)
				result=map.movePlayer(i,j+1);
			else{
				reward=-1;
				running=false;
			}
		break;
		case'w':
			if(j>0)
				result=map.movePlayer(i,j-1);
			else{
				reward=-1;
				running=false;
			}
		break;
		default:
			printf("error\n");
			printf("received: %c (%d)\n",action,action);
			info.reward=0;
			assert(0);
			return;
		break;
	}
	if(result){
#ifdef DEBUG
		printf("win\n");
#endif
		reward=10;
		running=false;
	}
	info.action=action;
	getState(info);
	updateState();
	info.reward=reward;
	records.push_back(info);
	return;
}
void GameController::getState(Info &info){
	memcpy(info.state,map.state,sizeof(double)*STATEVARS);
}
void GameController::updateState(){
	map.updateState();
}
