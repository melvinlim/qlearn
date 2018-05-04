#include"gamecontroller.h"
#include"player.h"
#include"defs.h"
#include<string.h>
int main(){
	GameController gameController;
	#ifdef HUMAN
		Human player;
	#else
		Agent player;
	#endif
	Info info;
	info.reward=0;
	memset(info.state,0,sizeof(double)*STATEVARS);
	Action action;
	unsigned long t=0;
	int i=0;
	for(;;){
		gameController.reset();
		gameController.start();
		while(gameController.running){
			t++;
			i++;
			if(t>TRAININGTIME){
				gameController.display();
				gameController.getState(info);
			}
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
