#include "Spi.h"
#include <iostream>
#include <bcm2835.h>
#include <unistd.h> // open / read

using std::cout;
using std::endl;

/*****************************************************************************
* | File      	:   DEV_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*----------------
* |	This version:   V3.0
* | Date        :   2019-07-31
* | Info        :   
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of theex Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include <fcntl.h>

/**
 * GPIO
**/
int EPD_RST_PIN;
int EPD_DC_PIN;
int EPD_CS_PIN;
int EPD_BUSY_PIN;

/**
 * GPIO read and write
**/
void Spi::write(WORD pin, BYTE value)
{
	bcm2835_gpio_write(pin, value);
}

BYTE Spi::read(WORD pin)
{
	BYTE Read_value = 0;
	Read_value = bcm2835_gpio_lev(pin);
	return Read_value;
}

/**
 * SPI
**/
void Spi::transfer(BYTE value)
{
	bcm2835_spi_transfer(value);
}

void Spi::transfer(BYTE* data, WORD len)
{
	char rData[len];
	//! \todo make cast unnecessary
	bcm2835_spi_transfernb((char*)data,rData,len);
}

/**
 * GPIO Mode
**/
void Spi::setGpioMode(WORD Pin, WORD Mode)
{
	if(Mode == 0 || Mode == BCM2835_GPIO_FSEL_INPT) {
		bcm2835_gpio_fsel(Pin, BCM2835_GPIO_FSEL_INPT);
	} else {
		bcm2835_gpio_fsel(Pin, BCM2835_GPIO_FSEL_OUTP);
	}
}

/**
 * delay x ms
**/
void Spi::delayMs(unsigned int ms)
{
	bcm2835_delay(ms);
}

int Spi::testing(void)
{
	int i;
	int fd;
	char value_str[20];
	fd = open("/etc/issue", O_RDONLY);
    printf("Current environment: ");
	while(1) {
		if (fd < 0) {
			cout << "Read failed Pin" << endl;;
			return -1;
		}
		for(i=0;; i++) {
			if (::read(fd, &value_str[i], 1) < 0) {
				cout << "failed to read value!" << endl;
				return -1;
			}
			if(value_str[i] ==32) {
				printf("\r\n");
				break;
			}
			printf("%c",value_str[i]);
		}
		break;
	}
#ifdef RPI
	if(i<5) {
		printf("Unrecognizable\r\n");
	} else {
		char RPI_System[10]   = {"Raspbian"};
		for(i=0; i<6; i++) {
			if(RPI_System[i]!= value_str[i]) {
				printf("Please make JETSON !!!!!!!!!!\r\n");
				return -1;
			}
		}
	}
#endif
	return 0;
}



void Spi::initGpio(void)
{
	EPD_RST_PIN     = 17;
	EPD_DC_PIN      = 25;
	EPD_CS_PIN      = 8;
	EPD_BUSY_PIN    = 24;

	setGpioMode(EPD_RST_PIN, 1);
	setGpioMode(EPD_DC_PIN, 1);
	setGpioMode(EPD_CS_PIN, 1);
	setGpioMode(EPD_BUSY_PIN, 0);

	write(EPD_CS_PIN, 1);
}
/******************************************************************************
function:	Module Initialize, the library and initialize the pins, SPI protocol
parameter:
Info:
******************************************************************************/
BYTE Spi::initModule(void)
{
    printf("/***********************************/ \r\n");
	if(testing() < 0) {
		return 1;
	}
	if(!bcm2835_init()) {
		printf("bcm2835 init failed  !!! \r\n");
		return 1;
	} else {
		printf("bcm2835 init success !!! \r\n");
	}

	// GPIO Config
	initGpio();

	bcm2835_spi_begin();                                         //Start spi interface, set spi pin for the reuse function
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);     //High first transmission
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                  //spi mode 0
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_128);  //Frequency
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                     //set CE0
	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);     //enable cs0

    printf("/***********************************/ \r\n");
	return 0;
}

/******************************************************************************
function:	Module exits, closes SPI and BCM2835 library
parameter:
Info:
******************************************************************************/
void Spi::exitModule(void)
{
	write(EPD_CS_PIN, LOW);
	write(EPD_DC_PIN, LOW);
	write(EPD_RST_PIN, LOW);

	bcm2835_spi_end();
	bcm2835_close();
}

