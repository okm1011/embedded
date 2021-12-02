#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include "fnd.h"


int main(void){
	fndDisp(1234,0);
	sleep(1);
	fndDisp(123,0);
	sleep(1);
	fndDisp(12,0);
	sleep(1);
	fndDisp(1,0);
	fndOff();
	return 0;
	
	
	}
