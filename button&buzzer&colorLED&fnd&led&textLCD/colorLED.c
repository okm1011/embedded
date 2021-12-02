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
#include "colorLED.h"



void pwmActivate(int bActivate, int pwmIndex)
{
	char	strshellcmd[150];
	if ( bActivate)
	{
		sprintf(strshellcmd,"echo '0' > %s%d/export\n",PWM_BASE_SYS_PATH,pwmIndex);
		
		system(strshellcmd);
	}
	else
	{
		sprintf(strshellcmd,"echo '0' > %s%d/unexport\n",PWM_BASE_SYS_PATH,pwmIndex);
		
		system(strshellcmd);
	}
}

void pwmEnable(int bEnable , int pwmIndex)
{
	char	strshellcmd[150];	
	if ( bEnable)
	{
		sprintf(strshellcmd,"echo '1' > %s%d/pwm0/%s\n",PWM_BASE_SYS_PATH,pwmIndex,PWM_ENABLE_NAME);
		
		system(strshellcmd);
	}
	else
	{
		sprintf(strshellcmd,"echo '0' > %s%d/pwm0/%s\n",PWM_BASE_SYS_PATH,pwmIndex,PWM_ENABLE_NAME);

		system(strshellcmd);
	}
}

// 65537 ~ 1000000000  Hz
void writePWMPeriod(int frequency, int pwmIndex) 
{
	char	strshellcmd[150];	
	sprintf(strshellcmd,"echo '%d' > %s%d/pwm0/%s\n",frequency,PWM_BASE_SYS_PATH, pwmIndex,PWM_FREQUENCY_NAME);

	system(strshellcmd);	
}

void writePWMDuty(int  DutyCycle , int pwmIndex)
{
	char	strshellcmd[150];	
	sprintf(strshellcmd,"echo '%d' > %s%d/pwm0/%s\n",DutyCycle,PWM_BASE_SYS_PATH,pwmIndex,PWM_DUTYCYCLE_NAME);

	system(strshellcmd);	
}

int colorLED(int red , int green, int blue)
{
	
	int redduty,greenduty,blueduty;
	
	

	
	if ( (red > MAX_INPUT_VALUE) || (red < 0))
	{
		perror("red over range.\n");

		return 1;
	}

	if ( (green > MAX_INPUT_VALUE) || (green < 0))
	{
		perror("green over range.\n");

		return 1;
	}

	if ( (blue > MAX_INPUT_VALUE) || (blue < 0))
	{
		perror("blue over range.\n");

		return 1;
	}
	
	// inverse
	red = MAX_INPUT_VALUE - red;
	green = MAX_INPUT_VALUE - green;
	blue = MAX_INPUT_VALUE - blue;
	
	// percentage
	redduty = PWM_FREQUENCY * red / MAX_INPUT_VALUE;
	greenduty = PWM_FREQUENCY * green / MAX_INPUT_VALUE;
	blueduty = PWM_FREQUENCY * blue / MAX_INPUT_VALUE;
	
	pwmActivate(TRUE,RED_INDEX );
	writePWMPeriod(PWM_FREQUENCY, RED_INDEX);
	writePWMDuty(redduty, RED_INDEX);
	pwmEnable(TRUE, RED_INDEX);
	
	pwmActivate(TRUE,GREEN_INDEX );
	writePWMPeriod(PWM_FREQUENCY, GREEN_INDEX);
	writePWMDuty(greenduty, GREEN_INDEX);
	pwmEnable(TRUE, GREEN_INDEX);
	
	pwmActivate(TRUE,BLUE_INDEX );
	writePWMPeriod(PWM_FREQUENCY, BLUE_INDEX);
	writePWMDuty(blueduty, BLUE_INDEX);
	pwmEnable(TRUE, BLUE_INDEX);
	
	return 0;
	
}
