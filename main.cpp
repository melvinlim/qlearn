#include"gamecontroller.h"
#include"player.h"
#include"defs.h"
#include<string.h>
int main(){
	GameController gameController;
//	Human player;
	Agent player;
	Info info;
	info.reward=0;
	memset(info.state,0,sizeof(double)*STATEVARS);
	Action action;
	int t=0;
	int i=0;
	for(;;){
		gameController.reset();
		gameController.start();
		while(gameController.running){
			t++;
			i++;
			if(t>TRAININGTIME)
				gameController.display();
			player.decide(action,info);
			gameController.step(action,info);
			if(i>=MEMORYSIZE){
				player.train(gameController.records);
				i=0;
			}
		}
		gameController.end();
	}
	return 0;
}
