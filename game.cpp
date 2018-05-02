#include"game.h"
Game::Game(){
}
Game::~Game(){}
void Game::start(){
	running=true;
	map=Map();
}
void Game::reset(){
}
void Game::display(){
	map.display();
	printf(":");
}
State *Game::step(Action *action){
	printf("received: %c (%d)\n",*action,*action);
	return 0;
}
