#ifndef _BUTTON_H_
#define _BUTTON_H_
#define MESSAGE_ID 1122
typedef struct
{
long int messageNum;
int keyInput;
int pressed;
} BUTTON_MSG_T;

typedef struct
{
    long int message;
    int flag;
} FLAG_MSG;

int buttonInit(void);
int buttonExit(void);
int probeButtonPath(char *newPath);
void* buttonThFunc(void *arg);
void* buttonThRcvFunc(void*arg);

#endif
