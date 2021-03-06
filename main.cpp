#include"gamecontroller.h"
#include"player.h"
#include"defs.h"
#include<string.h>
#include<time.h>
int main(){
	Stack<Info> records(MEMORYSIZE);
	time_t startTime,endTime;
	GameController gameController;
	#ifdef HUMAN
		Human player;
	#else
		Agent player;
	#endif
	Info info;
	info.reward=0;
	memset(info.state,0,sizeof(double)*STATEVARS);
	unsigned long t=0;
	int i=0;
	#ifdef LOADQ
		printf("loading player\n");
		player.load();
//		t=TRAININGTIME;
//		player.currentTime=t;
	#endif
	time(&startTime);
	for(;;){
		gameController.reset();
		gameController.start();
		gameController.updateState();
		while(gameController.running){
			t++;
			i++;
			if(t>TRAININGTIME){
				time(&endTime);
				gameController.displayOutput=true;
				printf("training time: %d\n",(int)difftime(endTime,startTime));
				printf("t: %d\n",gameController.t);
				gameController.display();
			}
			gameController.getState(info.state);
			player.decide(info.state,info.action);
			info.reward=gameController.step(info.action);
			gameController.updateState();
			if(info.reward!=0){	//if the game is over.
				memset(info.nextState,0,sizeof(double)*STATEVARS);
			}else{
				gameController.getState(info.nextState);
			}
			records.push_back(info);
			if(i>=MEMORYSIZE){
				player.train(records);
#ifdef PRINTSSE
//				player.getSumSqErr(records);
#endif
				records.clear();
				i=0;
			}
			if(t==TRAININGTIME){
				printf("saving player\n");
				player.save();
			}
		}
		gameController.end();
	}
	return 0;
}
