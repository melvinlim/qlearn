#include"game.h"
#include"player.h"
#include"defs.h"
int main(){
	Game game;
	Human player;
	State *state;
	for(;;){
		game.reset();
		game.start();
		while(game.running){
			game.display();
			state=game.step(*player.decide());
		}
		game.end();
	}
	return 0;
}
