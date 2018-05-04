#include"gamecontroller.h"
GameController::GameController():
records(MEMORYSIZE)
{
	t=0;
	displayOutput=false;
}
GameController::~GameController(){}
void GameController::start(){
	running=true;
}
void GameController::reset(){
	world.reset();
}
void GameController::end(){
	t=0;
	if(displayOutput)
		printf("game over\n");
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
		if(displayOutput)
			printf("win\n");
		reward=1;
		running=false;
	}
	if((t++>TIMELIMIT)&&(reward==0)){
		if(displayOutput)
			printf("out of time\n");
		reward=-0.5;
		running=false;
		t=0;
	}
	info.action=action;
	getState(info.state);
	updateState();
	info.reward=reward;
	records.push_back(info);
	return;
}
void GameController::getState(double *state){
	memcpy(state,world.state,sizeof(double)*STATEVARS);
}
void GameController::updateState(){
	world.updateState();
}
