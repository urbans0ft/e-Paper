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

// Let Destructors still do their job (Spi singleton)
void Handler(int signo)
{
    cout << "Ctrl + c received" << endl;

    exit(0);
}


int main(int argc, char* argv[])
{
    // Exception handling:ctrl + c
    signal(SIGINT, Handler);

	if (argc != 2)
	{
		cout << "Usage: epd image.bmp" << endl;
		cout << "       image.bmp must be a 600x448 V3 monochrome bitmap." << endl;
		return 0;
	}

	cout << "Reading MonochromBitmap" << endl;
	MonochromeBitmap bmp(argv[1]);
	cout << "Creating MonochromeScreen" << endl;
	MonochromeScreen screen(600, 448);
	cout << "Draw Bitmap to Screen" << endl;
	screen.draw(bmp);
	cout << "Create Display" << endl;
	MonochromeDisplay display(600, 448);
	cout << "Clear Display" << endl;
	display.clear();
	cout << "Display Screen" << endl;
	display.display(screen);

	cout << "Wait for 2 seconds" << endl;
	Spi::Instance().delayMs(2000);    

    return 0;
}
