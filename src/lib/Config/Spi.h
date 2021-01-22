#ifndef _SPI_H_
#define _SPI_H_
// #############################################################################
#include "global.h"
// =============================================================================
class Spi
{
	public:
		static Spi& Instance()
		{
			static Spi _instance;
			return _instance;
		}
		//! \todo replace by getter and search an replace everywhere.
		/*const*/ int RstPin;
		/*const*/ int DcPin;
		/*const*/ int CsPin;
		/*const*/ int BusyPin;
	private:
		Spi();
	public:
		~Spi();
		Spi(const Spi&) = delete;
		Spi& operator=(const Spi&)  = delete;
		BYTE read(WORD pin);
		BYTE initModule();
		int testing();
		void delayMs(unsigned int ms);
		void write(WORD pin, BYTE value);
		void initGpio();
		void setGpioMode(WORD pin, WORD mode);
		void exitModule();
		void transfer(BYTE value);
		void transfer(const BYTE* data, WORD len);
};
// #############################################################################
#endif // _SPI_H_
