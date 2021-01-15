#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
#include "EPD_Test.h"   //Examples
#include "EPD_5in83.h"
#include "MonochromeBitmap.h"
#include "MonochromeScreen.h"

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

    //EPD_5in83_test();
	MonochromeBitmap bmp("./pic/hello_world.bmp");
	MonochromeScreen screen(600, 448);
	screen.draw(bmp);
	const BYTE* image = screen.getScreenBuffer();
    EPD_5IN83_Init();
    EPD_5IN83_Clear();
	EPD_5IN83_Display(image);
	DEV_Delay_ms(2000);
	
	
    
    DEV_Module_Exit();

    return 0;
}
