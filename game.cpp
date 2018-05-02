#include"game.h"
Game::Game(){
}
Game::~Game(){}
void Game::start(){
	running=true;
}
void Game::reset(){
}
void Game::display(){
	map.display();
	printf(":");
}
State *Game::step(Action action){
	int i=map.playerObject.i;
	int j=map.playerObject.j;
	int reward;
	switch(action){
		case'n':
			if(i>0)
				map.movePlayer(i-1,j);
			else{
				reward=-1;
				running=false;
			}
		break;
		case's':
			if(i<9)
				map.movePlayer(i+1,j);
			else{
				reward=-1;
				running=false;
			}
		break;
		case'e':
			if(j<9)
				map.movePlayer(i,j+1);
			else{
				reward=-1;
				running=false;
			}
		break;
		case'w':
			if(j>0)
				map.movePlayer(i,j-1);
			else{
				reward=-1;
				running=false;
			}
		break;
		default:
			printf("error\n");
			printf("received: %c (%d)\n",action,action);
			return 0;
		break;
	}
	return 0;
}
