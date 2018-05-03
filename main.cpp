#include"game.h"
#include"player.h"
#include"defs.h"
#include<string.h>
int main(){
	Game game;
//	Human player;
	Agent player;
	Info info;
	info.reward=0;
	memset(info.state,0,sizeof(double)*STATEVARS);
	Action action;
	int t=0;
	int i=0;
	for(;;){
		game.reset();
		game.start();
		while(game.running){
			t++;
			i++;
			if(t>TRAININGTIME)
				game.display();
			player.decide(action,info);
			game.step(action,info);
			if(i>=MEMORYSIZE){
				player.train(game.records);
				i=0;
			}
		}
		game.end();
	}
	return 0;
}
