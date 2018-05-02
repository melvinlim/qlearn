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
	printf(".\n");
}
State *Game::step(Action *action){
	printf("received: %c (%d)\n",*action,*action);
	return 0;
}
