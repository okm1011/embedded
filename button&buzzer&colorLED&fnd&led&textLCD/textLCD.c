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
#include "textLCD.h"


#define TEXTLCD_DRIVER_NAME		"/dev/peritextlcd"

int lcdtextwrite(const char *str1 , int lineFlag)
{
	unsigned int linenum = 0;

	stTextLCD  stlcd; 
	int fd;
	int len; 
	
	memset(&stlcd,0,sizeof(stTextLCD));
	

	linenum = lineFlag;
	printf("linenum :%d\n", linenum);
	
	if ( linenum == 1) // firsst line
	{
		stlcd.cmdData = CMD_DATA_WRITE_LINE_1;
	}
	else if ( linenum == 2) // second line
	{
		stlcd.cmdData = CMD_DATA_WRITE_LINE_2;
	}
	else 
	{
		printf("linenum : %d  wrong .  range (1 ~ 2)\n", linenum);
		return 1; 
	}
	printf("string:%s\n",str1);
	len = strlen(str1);
	if ( len > COLUMN_NUM)
	{
		memcpy(stlcd.TextData[stlcd.cmdData - 1],str1,COLUMN_NUM);
	}
	else
	{
		memcpy(stlcd.TextData[stlcd.cmdData - 1],str1,len);
	}
	stlcd.cmd = CMD_WRITE_STRING;
	// open  driver 
	fd = open(TEXTLCD_DRIVER_NAME,O_RDWR);
	if ( fd < 0 )
	{
		perror("driver (//dev//peritextlcd) open error.\n");
		return 1;
	}
	write(fd,&stlcd,sizeof(stTextLCD));

	
	close(fd);
	
	return 0;
}

