#ifndef _SPI_H_
#define _SPI_H_
// #############################################################################
#include "global.h"
// =============================================================================
class Spi
{
	private:
		int EPD_RST_PIN;
		int EPD_DC_PIN;
		int EPD_CS_PIN;
		int EPD_BUSY_PIN;
	public:
		Spi();
		~Spi();
		BYTE read(WORD pin);
		BYTE initModule();
		int testing();
		void delayMs(unsigned int ms);
		void write(WORD pin, BYTE value);
		void initGpio();
		void setGpioMode(WORD pin, WORD mode);
		void exitModule();
		void transfer(BYTE value);
		void transfer(BYTE* data, WORD len);
};
// #############################################################################
#endif // _SPI_H_
