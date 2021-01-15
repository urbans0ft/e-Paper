// ----------------------------------------------
#include "MonochromeDisplay.h"
#include <iostream>
#include <bitset>
#include <iomanip>
// ----------------------------------------------
using std::cout;
using std::endl;
// ----------------------------------------------
constexpr BYTE MonochromeDisplay::BYTE_SEND_TABLE[256][4];
// ----------------------------------------------
MonochromeDisplay::MonochromeDisplay(DWORD width, DWORD height)
	: Width(width), Height(height)
{
}
// ----------------------------------------------
MonochromeDisplay::~MonochromeDisplay()
{
}
// ----------------------------------------------
void MonochromeDisplay::display(const MonochromeScreen& screen)
{
	uint8_t Data_Black, Data;
	uint8_t byte = 0b0000'0000;
	do {
		std::bitset<8> bits(byte);
		cout << bits << ": ";
		Data_Black = ~byte;
		for(uint8_t k = 0; k < 8; k++) {
			if(Data_Black & 0x80)
				Data = 0x00;
			else
				Data = 0x03;
			Data <<= 4;
			Data_Black <<= 1;
			k++;
			if(Data_Black & 0x80)
				Data |= 0x00;
			else
				Data |= 0x03;
			Data_Black <<= 1;
			//EPD_5IN83_SendData(Data);
			std::bitset<8> sentBits(Data);
			cout << sentBits << " ";
		}
		cout << "}," << endl;
	} while (byte++ < 0b1111'1111);
}
// ----------------------------------------------
