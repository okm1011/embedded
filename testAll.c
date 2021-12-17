
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
#include <sys/mman.h>
#include <linux/fb.h> 
#include "button.h"
#include "led.h"
#include "buzzer.h"
#include "textLCD.h"
#include "fnd.h"
#include "colorLED.h"
#include "temperature.h"
#include "accelMagGyro.h"
#include "bitmap.h"
#include "touch.h"
#include "libfbdev.h"
#include "jpeglib.h"
#include "jpgAnimation.h"
#include <time.h>


#define FBDEV_FILE  "/dev/fb0" // nodefile for using memory
#define FBDEV_FILE2  "/dev/fb1" // nodefile for using memory
#define BIT_VALUE_24BIT   24

void* touchThRcvFunc(void*arg);
void* buttonThRcvFunc(void*arg);
void* fnd_func(void*arg);
void* led_func(void*arg);
void* color_led_func(void*arg);
void* textlcd_func(void*arg);
void* buzzer_func(void*arg);
void* Gyro_Accel_func(void*arg);
void* tftlcd_Func(void*arg);
void* temp_func(void*arg);
void* read_jpg (void*arg);
//void* check_if_fail(void*arg);


static pthread_t fnd_th_ID;
static pthread_t led_th_ID;
static pthread_t color_led_th_ID;
static pthread_t textlcd_th_ID;
static pthread_t buzzer_th_ID;
static pthread_t Gyro_Accel_th_ID;
static pthread_t tftlcd_th_ID;
static pthread_t temp_th_ID; 
static pthread_t button_rcv_ID;
static pthread_t touch_th_id;
static pthread_t follow_ball_th_id;
static pthread_t read_jpg_th_id;
//static pthread_t check_if_fail_th_id;




static int clear_time = 0;
static int msgID,msgID2; //msgID:button thread, msgID2:touchscreen thread
static int state = 0;// main screen state main:0 start:1, help:2, setup:3, exit:4
static int un_pressed = 0;
static int b_value;
// state 1 == start , 2 == finish 
BUTTON_MSG_T rcv;
int failed = 0;


void* touchThRcvFunc(void*arg)
{
	touchInit();

	msgID2 = msgget( MESSAGE_ID2, IPC_CREAT|0666);
	BUTTON_MSG_T2 recvMsg;
	while (1)
	{
		msgrcv(msgID2, &recvMsg, sizeof (recvMsg)-sizeof (long int), 0, 0);
		//이떄는 터치가 일어나거나 아니면 터리가 끝날때만 여기에 들어옴!
		switch (recvMsg.keyInput)
		{
			case 999:
				if (recvMsg.pressed == 1)
				{		
                     
                  if (state == 0 && recvMsg.x <900 && recvMsg.y < 200 && recvMsg.x > 100 && recvMsg.y > 20)
					{
						printf ("START: %d %d\r\n",recvMsg.x, recvMsg.y);
                     state=1;
                         pthread_create(&read_jpg_th_id, NULL, read_jpg, NULL);
                         pthread_detach (read_jpg_th_id);
                    
					}
					
				}
			break;
		}
	
	}
}
void* follow_ball_th(void*arg){
	while(rcv.pressed == 1){
		printGyro();
		b_value = printGyro();
		sleep(1);
		send_value(b_value);
		
		}
	unpress();
	}
int follow_ball(void){
	
	pthread_create(&follow_ball_th_id, NULL, follow_ball_th, NULL);
    pthread_detach (follow_ball_th_id);
	return 0;
	}

//static char* name; if have time
void* buttonThRcvFunc(void*arg){

	 msgID = msgget(MESSAGE_ID,IPC_CREAT|0666);
    buttonInit();
    
    while (1)
    {
        msgrcv(msgID, &rcv, sizeof(rcv)-sizeof(long int),0,0);
        switch (rcv.keyInput)
        {
            case KEY_HOME: printf("Home key):\r\n"); break;

                                                     
            case KEY_BACK: printf("Back key):\r\n"); break;
            case KEY_SEARCH: printf("Search key):\r\n"); break;
            case KEY_MENU: printf("Menu key):\r\n"); break;
            case KEY_VOLUMEUP: printf("Volume up key):\r\n"); break;
            case KEY_VOLUMEDOWN:follow_ball();   break;//printf("Volume down key):\r\n"); break;
        }
        if(rcv.pressed) printf("pressed\r\n");
        else printf("released\r\n");
    }
    
    buttonExit();
	
	}

void init(void)
{
	// init for all
    ledLibInit();
    buttonInit();
    buzzerInit();

    pthread_create(&button_rcv_ID, NULL, buttonThRcvFunc, NULL);
    pthread_detach (button_rcv_ID);

    pthread_create(&touch_th_id, NULL, touchThRcvFunc, NULL);
    pthread_detach (touch_th_id);

    pthread_create(&tftlcd_th_ID, NULL, tftlcd_Func, NULL);
    pthread_detach (tftlcd_th_ID);

    pthread_create(&fnd_th_ID, NULL, fnd_func, NULL);
    pthread_detach (fnd_th_ID);

    pthread_create(&led_th_ID, NULL, led_func, NULL);
    pthread_detach (led_th_ID);

    pthread_create(&color_led_th_ID, NULL, color_led_func, NULL);
    pthread_detach (color_led_th_ID);

    pthread_create(&textlcd_th_ID, NULL, textlcd_func, NULL);
    pthread_detach (textlcd_th_ID);

   // pthread_create(&buzzer_th_ID, NULL, buzzer_func, NULL);
   // pthread_detach (buzzer_th_ID);

    pthread_create(&Gyro_Accel_th_ID, NULL, Gyro_Accel_func, NULL);
    pthread_detach (Gyro_Accel_th_ID);

    pthread_create(&temp_th_ID, NULL, temp_func, NULL);
    pthread_detach (temp_th_ID);

	//pthread_create(&check_if_fail_th_id, NULL, check_if_fail, NULL);
   // pthread_detach (check_if_fail_th_id);
	
	
	 
}

void* fnd_func(void*arg)
{
	while(1)
    {
	    if(state == 1)//게임 초 계산 && finish == 0
        {	
          /*  clear_time++;
            fndDisp(clear_time,0);
            sleep(1); */
          	 
         }
        else
            clear_time=0;
    }
}

void* led_func(void*arg)
{
    while(1)
    {
        if(state==1)//부가 조건 있어야 할 것
         {
            ledOnOff(0,1);
            ledOnOff(1,1);
            ledOnOff(2,1);
            ledOnOff(3,1);
            ledOnOff(4,1);
            ledOnOff(5,1);
            ledOnOff(6,1);
            ledOnOff(7,1);
          }

      
    }
}
void* color_led_func(void*arg)
{
    while(1)
    {
	    if( state == 1)
        {
		    colorLED(20,0,0);
		    sleep(1);
		    colorLED(0,20,0);
		    sleep(1);
		    colorLED(0,0,20);
		    sleep(1);	
     	
		 		
		 }
       //else
      // botton_state_flag=0;	
    }
}

void* textlcd_func(void*arg)
{
	int i=0;
    while(1)
    {
        if(state == 1 && i < 4 )
         {
             lcdtextwrite("3" , 1);
             i++;
             sleep(1);
             i++;
             lcdtextwrite("2" , 1);
             sleep(1);
             i++;
             lcdtextwrite("1" , 1);
             sleep(1);
             i++;             
             lcdtextwrite("start" , 1);
             state = 0 ;
			 
             
         }
		
        
    }

		// have to change form of clear time before put into lcd text
//    lcdtextwrite("name" , 1);
 //   lcdtextwrite("cleartime" , 1);

}

void* buzzer_func(void*arg)
{
	int i =0;

}	

	// song



void* Gyro_Accel_func(void*arg)
{
//gyro
}

void* tftlcd_Func(void*arg)
{
	while(1){
		if(state == 1){
			char filename[200]={0,} ;
	        //snprintf(filename,200,"1.bmp");
	        
	         
			}
		
		
		}
	
}

void* temp_func(void*arg)
{
	//temp
	
}
void main_dis(void){
	    char filename[200]={0,} ;
	snprintf(filename,200,"./image/game_main.bmp");
	 bmp_read(filename);
	 }			
int main(void)
{	
	

	init();
	main_dis();
	/*
	lcdtextwrite("\0" , 1);
	//buzzerInit();
	//buzzerPlaySong(3);
	printf("FREQUENCY 3 playing \r\n");
	sleep(3);
	//buzzerPlaySong(6);
	
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
	printAccel();
	printMag();
	printGyro();
	sleep(3);
	printAccel();
	printMag();
	printGyro();	
	
	sleep(100);
	
	*/
	sleep(1000);
	return 0;
}
