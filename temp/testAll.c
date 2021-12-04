
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
#include "textLCD.h"
#include "fnd.h"
#include "colorLED.h"
#include "temperature.h"





int main(void){
	
	lcdtextwrite("hsdello world\0" , 1);
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
	buttonInit();
	buttonrcv();
	fndDisp(1234,0);
	colorLED(0,10,20);
	printTemp();
	sleep(100);
	}
