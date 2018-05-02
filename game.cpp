#include"game.h"
Game::Game(){
}
Game::~Game(){}
void Game::start(){
	running=true;
}
void Game::reset(){
	map.reset();
}
void Game::end(){
	printf("game over\n");
}
void Game::display(){
	map.display();
	printf(":");
}
void Game::step(Action action,Info &info){
	int i=map.playerObject.i;
	int j=map.playerObject.j;
	bool result=false;
	int reward;
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
			return;
		break;
	}
	if(result){
		printf("win\n");
		running=false;
	}
	return;
}
