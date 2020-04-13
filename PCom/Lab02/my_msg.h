#ifndef MY_MESSAGE
#define MY_MESSAGE

#define MAX_VALUE 1396

typedef struct
{
    int type;
    char payload[MAX_VALUE];
} my_msg;

#endif