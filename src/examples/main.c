#include <iostream>
#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
#include "EPD_Test.h"   //Examples
#include "MonochromeBitmap.h"
#include "MonochromeScreen.h"
#include "MonochromeDisplay.h"
#include "Spi.h"

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

    /*
	if(DEV_Module_Init()!=0){
        return -1;
    }
	//*/
	cout << "Creating Spi driver object" << endl;
	//Spi spi;

	cout << "Reading MonochromBitmap" << endl;
	MonochromeBitmap bmp("./pic/out.bmp");
	cout << "Creating MonochromeScreen" << endl;
	MonochromeScreen screen(600, 448);
	cout << "Draw Bitmap to Screen" << endl;
	screen.draw(bmp);
    //EPD_5IN83_Init();
    //EPD_5IN83_Clear();
	//EPD_5IN83_Display(image);
	cout << "Create Display" << endl;
	MonochromeDisplay display(600, 448);
	display.clear();
	cout << "Display screen" << endl;
	display.display(screen);

	DEV_Delay_ms(2000);
	//spi.delayMs(2000);
	
	
    
    //DEV_Module_Exit(); // implicit bis ~Spi

    return 0;
}
