
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h> 
#include <sys/msg.h>
#include <pthread.h>
#include "button.h"
#include "led.h"
#include "buzzer.h"
int main(void){
	buzzerInit();
	buzzerPlaySong(3);
	printf("FREQUENCY 3 playing \r\n");
	sleep(3);
	buzzerPlaySong(6);
	
	printf("FREQUENCY 6 playing \r\n");
	sleep(2);
	buzzerStopSong();
	
	printf("stop the buzzer \r\n");
	ledLibInit();
	ledOnOff(0,1);
	sleep(1);
	ledOnOff(1,1);
	sleep(1);
	ledOnOff(2,1);
	sleep(1);
	ledOnOff(3,1);
	ledStatus();
	ledLibExit();		
	BUTTON_MSG_T rcv;
	int msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);
	
	buttonInit();
	while(1){
		msgrcv(msgID,&rcv.keyInput,sizeof(rcv.keyInput),0,0);
		switch(rcv.keyInput){
			case(1): printf("VOLUMEUP\r\n"); break;
		    case(2): printf("HOME\r\n"); break;
		    case(3): printf("SEARCH\r\n"); break;
		    case(4): printf("BACK\r\n"); break;
		    case(5): printf("MENU\r\n"); break;
		    case(6): printf("VOLUMEDOWN\r\n"); break;
		}
		msgrcv(msgID,&rcv.pressed,sizeof(rcv.pressed),0,0);
		switch(rcv.pressed){
			case(1): printf("on\r\n"); break;
			case(3): printf("off\r\n"); break;
			}
		}
				
	buttonExit();
	
	}
