﻿#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
#include "EPD_Test.h"   //Examples

void  Handler(int signo)
{
    //System Exit
    printf("\r\nHandler:exit\r\n");
    DEV_Module_Exit();

    exit(0);
}


int main(void)
{
    // Exception handling:ctrl + c
    signal(SIGINT, Handler);

    if(DEV_Module_Init()!=0){
        return -1;
    }

    EPD_5in83_test();
    
    DEV_Module_Exit();

    return 0;
}
