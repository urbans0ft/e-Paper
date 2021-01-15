#include <iostream>
#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
#include "EPD_Test.h"   //Examples
#include "EPD_5in83.h"
#include "MonochromeBitmap.h"
#include "MonochromeScreen.h"

using std::cout;
using std::endl;

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

	cout << "Reading MonochromBitmap" << endl;
	MonochromeBitmap bmp("./pic/5in83.bmp");
	cout << "Creating MonochromeScreen" << endl;
	MonochromeScreen screen(600, 448);
	cout << "Draw Bitmap to Screen" << endl;
	screen.draw(bmp);
	cout << "Get the ScreenBuffer" << endl;
	const BYTE* image = screen.getScreenBuffer();
    EPD_5IN83_Init();
    EPD_5IN83_Clear();
	EPD_5IN83_Display(image);
	DEV_Delay_ms(2000);
	
	
    
    DEV_Module_Exit();

    return 0;
}
