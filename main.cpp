#include"game.h"
#include"player.h"
#include"defs.h"
int main(){
	Game game;
	Human player;
	Info info;
	Action action;
	for(;;){
		game.reset();
		game.start();
		while(game.running){
			game.display();
			player.decide(action);
			game.step(action,info);
		}
		game.end();
	}
	return 0;
}
