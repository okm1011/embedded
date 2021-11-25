#include "led.h"
#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
//#include "led.h"
int main(void)
{
 ledLibInit();
 sleep(1);
 ledOnOff(2,1);
 sleep(1);
 ledStatus();
 ledOnOff(2,0);
 sleep(1);
 ledStatus();
 ledOnOff(3,1);
 sleep(1);
 ledStatus();
 ledOnOff(3,0);
 sleep(1);
 ledStatus();
 sleep(2);
 ledLibExit();

 return 0;
}
/*
void doHelp(void)
{
    printf("ledtest <hex byte> :data bit0 operation 1=> on 0 =>off\r\n");

}

int main(int argc, char **argv)
{
    unsigned int data = 0;
    int fd;
    if(argc < 2)
    {
        perror("Args number is less than 2\r\n");
        doHelp();
        return 1;
    }
    data = strtol(argv[1],NULL,16);
    printf("write data: 0x%X\r\n",data);

    fd = open(LED_DRIVER_NAME,O_RDWR);
    if(fd < 0)
    {
        perror("driver (//dev//cnled) open error.\r\n");
        return 1;
    }

    write(fd, &data, 4);

    close(fd);
    return 0;
}*/