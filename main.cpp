#include"game.h"
#include"player.h"
#include"defs.h"
int main(){
	Game game;
	Human player;
	Info info;
	for(;;){
		game.reset();
		game.start();
		while(game.running){
			game.display();
			game.step(*player.decide(),info);
		}
		game.end();
	}
	return 0;
}
