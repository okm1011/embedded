#include "led.h"
#include <fcntl.h>

static unsigned int ledValue = 0;
static int fd = 0;

int ledOnOff(int ledNum, int onOff)
{
    int i = 1;
    i = i << ledNum;
    ledValue = ledValue & (~i);
    if(onOff != 0) ledValue |= i;
    write (fd, &ledValue, 4);
}

int ledLibInit(void)
{
    fd = open(_LED_DRIVER_NAME,O_WRONLY);
    ledValue = 0;
}

int ledLibExit(void)
{
    ledValue = 0;
    ledOnOff(0,0);
    close(fd);
}

int ledStatus(void)
{
    printf("번째 led가 켜졌습니다.");
}