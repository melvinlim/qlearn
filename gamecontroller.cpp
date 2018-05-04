#include"gamecontroller.h"
GameController::GameController():
records(MEMORYSIZE)
{
	t=0;
}
GameController::~GameController(){}
void GameController::start(){
	running=true;
}
void GameController::reset(){
	world.reset();
}
void GameController::end(){
#ifdef DEBUG
	printf("game over\n");
#endif
}
void GameController::display(){
	world.display();
}
void GameController::step(Action action,Info &info){
	int i=world.playerObject.i;
	int j=world.playerObject.j;
	bool result=false;
	double reward=0;
	switch(action){
		case NORTH:
			if(i>0)
				result=world.movePlayer(i-1,j);
			else{
				reward=-1;
				running=false;
			}
		break;
		case EAST:
			if(j<9)
				result=world.movePlayer(i,j+1);
			else{
				reward=-1;
				running=false;
			}
		break;
		case SOUTH:
			if(i<9)
				result=world.movePlayer(i+1,j);
			else{
				reward=-1;
				running=false;
			}
		break;
		case WEST:
			if(j>0)
				result=world.movePlayer(i,j-1);
			else{
				reward=-1;
				running=false;
			}
		break;
		default:
			printf("error\n");
			printf("received: %c (%d)\n",action,action);
			info.reward=0;
			#ifndef HUMAN
				assert(0);
			#endif
			return;
		break;
	}
	if(result){
#ifdef DEBUG
		printf("win\n");
#endif
		reward=1;
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
	memcpy(info.state,world.state,sizeof(double)*STATEVARS);
}
void GameController::updateState(){
	world.updateState();
}
