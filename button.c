#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/msg.h>
#include <pthread.h>
#include "button.h"

#define INPUT_DEVICE_LIST "/dev/input/event"
#define PROBE_FILE "/proc/bus/input/devices"
#define HAVE_TO_FIND_1 "N: Name=\"ecube-button\"\n"
#define HAVE_TO_FIND_2 "H: Handlers=kbd event"

static int fp,code,value;
static int readSize;//,inputIndex;
static struct input_event stEvent;
static char buttonPath[200]={0,};
static int exit_pth = 0;
static pthread_t buttonTh_id;
static int msgID;
//static FLAG_MSG F_rcv;
//static FLAG_MSG F_snd;
int i,j;
BUTTON_MSG_T snd;

int probeButtonPath(char *newPath)
{
    int returnValue = 0; //button에 해당하는 event#을 찾았나?
    int number = 0; //찾았다면 여기에 집어넣자
    FILE *fp0 = fopen(PROBE_FILE,"rt"); //파일을 열고

    while(!feof(fp0)) //끝까지 읽어들인다.
    {
        char tmpStr[200]; 
        fgets(tmpStr,200,fp0); 
        if (strcmp(tmpStr,HAVE_TO_FIND_1) == 0)
        {
            printf("YES! I found!: %s\r\n", tmpStr);
            returnValue = 1; 
        }

        if ((returnValue == 1) && (strncasecmp(tmpStr, HAVE_TO_FIND_2,strlen(HAVE_TO_FIND_2)) == 0))
        {
            printf ("-->%s",tmpStr);
            printf("\t%c\r\n",tmpStr[strlen(tmpStr)-3]);
            number = tmpStr[strlen(tmpStr)-3] - '0';
            break;
        }
    }

    fclose(fp0);
    if (returnValue == 1)
    sprintf (newPath,"%s%d",INPUT_DEVICE_LIST,number);
    return returnValue;
}

void* buttonThFunc(void *arg)
{
    msgID = msgget(MESSAGE_ID,IPC_CREAT|0666);

    if(probeButtonPath(buttonPath) == 0)  
    {
        printf("ERROR! File Not Found!\r\n"); 
        return 0;
    }

    fp = open(buttonPath, O_RDONLY);

    while(1)
    {
        readSize = read(fp, &stEvent , sizeof(stEvent));
        if (readSize != sizeof(stEvent))
        { continue;}
        if(stEvent.type == EV_KEY)
        {
            snd.messageNum = 1;
            snd.keyInput=stEvent.code;
            snd.pressed=stEvent.value;
            msgsnd(msgID,&snd, sizeof(snd)-sizeof(long int),0);  
        }
    }
}

int buttonInit(void)//한번만 읽어들이기 가능 여러번 확인하고 싶으면 이  함수 메인에서 여러번 호출 이렇게 아니라 계속
{
    //msgID = msgget(MESSAGE_ID,IPC_CREAT|0666);

    pthread_create(&buttonTh_id, NULL, buttonThFunc, NULL);
    pthread_detach(buttonTh_id);

    return 1;
}

int buttonExit(void)
{
    close(fp);

    return 2;
}
