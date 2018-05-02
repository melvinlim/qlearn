#include"game.h"
#include"player.h"
#include"defs.h"
#include<string.h>
int main(){
	Game game;
//	Human player;
	Agent player;
	Info info;
	memset(info.state,0,sizeof(double)*STATEVARS);
	Action action;
	for(;;){
		game.reset();
		game.start();
		while(game.running){
			game.display();
			player.decide(action,info);
			game.step(action,info);
		}
		game.end();
	}
	return 0;
}
