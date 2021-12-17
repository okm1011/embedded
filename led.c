#include "led.h"
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

static unsigned int ledValue = 0;
static int fd = 0;
int ledOnOff(int ledNum, int onOff)
{

	int i=1;
	i = i<<ledNum;
	ledValue = ledValue& (~i);
	if (onOff != 0) ledValue |= i;
	write(fd, &ledValue, 4);


}
int ledLibInit(void){
	fd = open("/dev/periled", O_RDWR);
	printf("%d",fd);
	ledValue = 0;
	}
int ledLibExit(void){
	
	ledValue = 0;
	ledOnOff (0, 0);
	close(fd);
	
	}
	
int ledStatus(void){
	
	printf("%d\r\n",ledValue);
	
	}
