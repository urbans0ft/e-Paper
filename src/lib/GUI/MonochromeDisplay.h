#ifndef _MONOCHROME_DISPLAY_H_
#define _MONOCHROME_DISPLAY_H_
// #############################################################################
// =============================================================================
#include "global.h"
#include "MonochromeScreen.h"
#include "DisplayCommand.h"
#include "Spi.h"
// =============================================================================
class MonochromeDisplay
{
	private:
		const DWORD Width;
		const DWORD Height;
		Spi&        _spi = Spi::Instance();
	public:
		MonochromeDisplay(DWORD width, DWORD height);
		~MonochromeDisplay();
		void display(const MonochromeScreen& screen);
		void clear();
		void readBusy();
		void sendCommand(DisplayCommand Reg);
		void sendData(BYTE Data);
		void sendData(BYTE* pData, DWORD Len);
		void sleep();
		void turnOnDisplay();
	private:
		void init();
		void reset();

	public:
		static constexpr const uint8_t BYTE_SEND_TABLE[256][4]{
			{ 0x00, 0x00, 0x00, 0x00, }, // 00000000: 00000000 00000000 00000000 00000000
			{ 0x00, 0x00, 0x00, 0x03, }, // 00000001: 00000000 00000000 00000000 00000011
			{ 0x00, 0x00, 0x00, 0x30, }, // 00000010: 00000000 00000000 00000000 00110000
			{ 0x00, 0x00, 0x00, 0x33, }, // 00000011: 00000000 00000000 00000000 00110011
			{ 0x00, 0x00, 0x03, 0x00, }, // 00000100: 00000000 00000000 00000011 00000000
			{ 0x00, 0x00, 0x03, 0x03, }, // 00000101: 00000000 00000000 00000011 00000011
			{ 0x00, 0x00, 0x03, 0x30, }, // 00000110: 00000000 00000000 00000011 00110000
			{ 0x00, 0x00, 0x03, 0x33, }, // 00000111: 00000000 00000000 00000011 00110011
			{ 0x00, 0x00, 0x30, 0x00, }, // 00001000: 00000000 00000000 00110000 00000000
			{ 0x00, 0x00, 0x30, 0x03, }, // 00001001: 00000000 00000000 00110000 00000011
			{ 0x00, 0x00, 0x30, 0x30, }, // 00001010: 00000000 00000000 00110000 00110000
			{ 0x00, 0x00, 0x30, 0x33, }, // 00001011: 00000000 00000000 00110000 00110011
			{ 0x00, 0x00, 0x33, 0x00, }, // 00001100: 00000000 00000000 00110011 00000000
			{ 0x00, 0x00, 0x33, 0x03, }, // 00001101: 00000000 00000000 00110011 00000011
			{ 0x00, 0x00, 0x33, 0x30, }, // 00001110: 00000000 00000000 00110011 00110000
			{ 0x00, 0x00, 0x33, 0x33, }, // 00001111: 00000000 00000000 00110011 00110011
			{ 0x00, 0x03, 0x00, 0x00, }, // 00010000: 00000000 00000011 00000000 00000000
			{ 0x00, 0x03, 0x00, 0x03, }, // 00010001: 00000000 00000011 00000000 00000011
			{ 0x00, 0x03, 0x00, 0x30, }, // 00010010: 00000000 00000011 00000000 00110000
			{ 0x00, 0x03, 0x00, 0x33, }, // 00010011: 00000000 00000011 00000000 00110011
			{ 0x00, 0x03, 0x03, 0x00, }, // 00010100: 00000000 00000011 00000011 00000000
			{ 0x00, 0x03, 0x03, 0x03, }, // 00010101: 00000000 00000011 00000011 00000011
			{ 0x00, 0x03, 0x03, 0x30, }, // 00010110: 00000000 00000011 00000011 00110000
			{ 0x00, 0x03, 0x03, 0x33, }, // 00010111: 00000000 00000011 00000011 00110011
			{ 0x00, 0x03, 0x30, 0x00, }, // 00011000: 00000000 00000011 00110000 00000000
			{ 0x00, 0x03, 0x30, 0x03, }, // 00011001: 00000000 00000011 00110000 00000011
			{ 0x00, 0x03, 0x30, 0x30, }, // 00011010: 00000000 00000011 00110000 00110000
			{ 0x00, 0x03, 0x30, 0x33, }, // 00011011: 00000000 00000011 00110000 00110011
			{ 0x00, 0x03, 0x33, 0x00, }, // 00011100: 00000000 00000011 00110011 00000000
			{ 0x00, 0x03, 0x33, 0x03, }, // 00011101: 00000000 00000011 00110011 00000011
			{ 0x00, 0x03, 0x33, 0x30, }, // 00011110: 00000000 00000011 00110011 00110000
			{ 0x00, 0x03, 0x33, 0x33, }, // 00011111: 00000000 00000011 00110011 00110011
			{ 0x00, 0x30, 0x00, 0x00, }, // 00100000: 00000000 00110000 00000000 00000000
			{ 0x00, 0x30, 0x00, 0x03, }, // 00100001: 00000000 00110000 00000000 00000011
			{ 0x00, 0x30, 0x00, 0x30, }, // 00100010: 00000000 00110000 00000000 00110000
			{ 0x00, 0x30, 0x00, 0x33, }, // 00100011: 00000000 00110000 00000000 00110011
			{ 0x00, 0x30, 0x03, 0x00, }, // 00100100: 00000000 00110000 00000011 00000000
			{ 0x00, 0x30, 0x03, 0x03, }, // 00100101: 00000000 00110000 00000011 00000011
			{ 0x00, 0x30, 0x03, 0x30, }, // 00100110: 00000000 00110000 00000011 00110000
			{ 0x00, 0x30, 0x03, 0x33, }, // 00100111: 00000000 00110000 00000011 00110011
			{ 0x00, 0x30, 0x30, 0x00, }, // 00101000: 00000000 00110000 00110000 00000000
			{ 0x00, 0x30, 0x30, 0x03, }, // 00101001: 00000000 00110000 00110000 00000011
			{ 0x00, 0x30, 0x30, 0x30, }, // 00101010: 00000000 00110000 00110000 00110000
			{ 0x00, 0x30, 0x30, 0x33, }, // 00101011: 00000000 00110000 00110000 00110011
			{ 0x00, 0x30, 0x33, 0x00, }, // 00101100: 00000000 00110000 00110011 00000000
			{ 0x00, 0x30, 0x33, 0x03, }, // 00101101: 00000000 00110000 00110011 00000011
			{ 0x00, 0x30, 0x33, 0x30, }, // 00101110: 00000000 00110000 00110011 00110000
			{ 0x00, 0x30, 0x33, 0x33, }, // 00101111: 00000000 00110000 00110011 00110011
			{ 0x00, 0x33, 0x00, 0x00, }, // 00110000: 00000000 00110011 00000000 00000000
			{ 0x00, 0x33, 0x00, 0x03, }, // 00110001: 00000000 00110011 00000000 00000011
			{ 0x00, 0x33, 0x00, 0x30, }, // 00110010: 00000000 00110011 00000000 00110000
			{ 0x00, 0x33, 0x00, 0x33, }, // 00110011: 00000000 00110011 00000000 00110011
			{ 0x00, 0x33, 0x03, 0x00, }, // 00110100: 00000000 00110011 00000011 00000000
			{ 0x00, 0x33, 0x03, 0x03, }, // 00110101: 00000000 00110011 00000011 00000011
			{ 0x00, 0x33, 0x03, 0x30, }, // 00110110: 00000000 00110011 00000011 00110000
			{ 0x00, 0x33, 0x03, 0x33, }, // 00110111: 00000000 00110011 00000011 00110011
			{ 0x00, 0x33, 0x30, 0x00, }, // 00111000: 00000000 00110011 00110000 00000000
			{ 0x00, 0x33, 0x30, 0x03, }, // 00111001: 00000000 00110011 00110000 00000011
			{ 0x00, 0x33, 0x30, 0x30, }, // 00111010: 00000000 00110011 00110000 00110000
			{ 0x00, 0x33, 0x30, 0x33, }, // 00111011: 00000000 00110011 00110000 00110011
			{ 0x00, 0x33, 0x33, 0x00, }, // 00111100: 00000000 00110011 00110011 00000000
			{ 0x00, 0x33, 0x33, 0x03, }, // 00111101: 00000000 00110011 00110011 00000011
			{ 0x00, 0x33, 0x33, 0x30, }, // 00111110: 00000000 00110011 00110011 00110000
			{ 0x00, 0x33, 0x33, 0x33, }, // 00111111: 00000000 00110011 00110011 00110011
			{ 0x03, 0x00, 0x00, 0x00, }, // 01000000: 00000011 00000000 00000000 00000000
			{ 0x03, 0x00, 0x00, 0x03, }, // 01000001: 00000011 00000000 00000000 00000011
			{ 0x03, 0x00, 0x00, 0x30, }, // 01000010: 00000011 00000000 00000000 00110000
			{ 0x03, 0x00, 0x00, 0x33, }, // 01000011: 00000011 00000000 00000000 00110011
			{ 0x03, 0x00, 0x03, 0x00, }, // 01000100: 00000011 00000000 00000011 00000000
			{ 0x03, 0x00, 0x03, 0x03, }, // 01000101: 00000011 00000000 00000011 00000011
			{ 0x03, 0x00, 0x03, 0x30, }, // 01000110: 00000011 00000000 00000011 00110000
			{ 0x03, 0x00, 0x03, 0x33, }, // 01000111: 00000011 00000000 00000011 00110011
			{ 0x03, 0x00, 0x30, 0x00, }, // 01001000: 00000011 00000000 00110000 00000000
			{ 0x03, 0x00, 0x30, 0x03, }, // 01001001: 00000011 00000000 00110000 00000011
			{ 0x03, 0x00, 0x30, 0x30, }, // 01001010: 00000011 00000000 00110000 00110000
			{ 0x03, 0x00, 0x30, 0x33, }, // 01001011: 00000011 00000000 00110000 00110011
			{ 0x03, 0x00, 0x33, 0x00, }, // 01001100: 00000011 00000000 00110011 00000000
			{ 0x03, 0x00, 0x33, 0x03, }, // 01001101: 00000011 00000000 00110011 00000011
			{ 0x03, 0x00, 0x33, 0x30, }, // 01001110: 00000011 00000000 00110011 00110000
			{ 0x03, 0x00, 0x33, 0x33, }, // 01001111: 00000011 00000000 00110011 00110011
			{ 0x03, 0x03, 0x00, 0x00, }, // 01010000: 00000011 00000011 00000000 00000000
			{ 0x03, 0x03, 0x00, 0x03, }, // 01010001: 00000011 00000011 00000000 00000011
			{ 0x03, 0x03, 0x00, 0x30, }, // 01010010: 00000011 00000011 00000000 00110000
			{ 0x03, 0x03, 0x00, 0x33, }, // 01010011: 00000011 00000011 00000000 00110011
			{ 0x03, 0x03, 0x03, 0x00, }, // 01010100: 00000011 00000011 00000011 00000000
			{ 0x03, 0x03, 0x03, 0x03, }, // 01010101: 00000011 00000011 00000011 00000011
			{ 0x03, 0x03, 0x03, 0x30, }, // 01010110: 00000011 00000011 00000011 00110000
			{ 0x03, 0x03, 0x03, 0x33, }, // 01010111: 00000011 00000011 00000011 00110011
			{ 0x03, 0x03, 0x30, 0x00, }, // 01011000: 00000011 00000011 00110000 00000000
			{ 0x03, 0x03, 0x30, 0x03, }, // 01011001: 00000011 00000011 00110000 00000011
			{ 0x03, 0x03, 0x30, 0x30, }, // 01011010: 00000011 00000011 00110000 00110000
			{ 0x03, 0x03, 0x30, 0x33, }, // 01011011: 00000011 00000011 00110000 00110011
			{ 0x03, 0x03, 0x33, 0x00, }, // 01011100: 00000011 00000011 00110011 00000000
			{ 0x03, 0x03, 0x33, 0x03, }, // 01011101: 00000011 00000011 00110011 00000011
			{ 0x03, 0x03, 0x33, 0x30, }, // 01011110: 00000011 00000011 00110011 00110000
			{ 0x03, 0x03, 0x33, 0x33, }, // 01011111: 00000011 00000011 00110011 00110011
			{ 0x03, 0x30, 0x00, 0x00, }, // 01100000: 00000011 00110000 00000000 00000000
			{ 0x03, 0x30, 0x00, 0x03, }, // 01100001: 00000011 00110000 00000000 00000011
			{ 0x03, 0x30, 0x00, 0x30, }, // 01100010: 00000011 00110000 00000000 00110000
			{ 0x03, 0x30, 0x00, 0x33, }, // 01100011: 00000011 00110000 00000000 00110011
			{ 0x03, 0x30, 0x03, 0x00, }, // 01100100: 00000011 00110000 00000011 00000000
			{ 0x03, 0x30, 0x03, 0x03, }, // 01100101: 00000011 00110000 00000011 00000011
			{ 0x03, 0x30, 0x03, 0x30, }, // 01100110: 00000011 00110000 00000011 00110000
			{ 0x03, 0x30, 0x03, 0x33, }, // 01100111: 00000011 00110000 00000011 00110011
			{ 0x03, 0x30, 0x30, 0x00, }, // 01101000: 00000011 00110000 00110000 00000000
			{ 0x03, 0x30, 0x30, 0x03, }, // 01101001: 00000011 00110000 00110000 00000011
			{ 0x03, 0x30, 0x30, 0x30, }, // 01101010: 00000011 00110000 00110000 00110000
			{ 0x03, 0x30, 0x30, 0x33, }, // 01101011: 00000011 00110000 00110000 00110011
			{ 0x03, 0x30, 0x33, 0x00, }, // 01101100: 00000011 00110000 00110011 00000000
			{ 0x03, 0x30, 0x33, 0x03, }, // 01101101: 00000011 00110000 00110011 00000011
			{ 0x03, 0x30, 0x33, 0x30, }, // 01101110: 00000011 00110000 00110011 00110000
			{ 0x03, 0x30, 0x33, 0x33, }, // 01101111: 00000011 00110000 00110011 00110011
			{ 0x03, 0x33, 0x00, 0x00, }, // 01110000: 00000011 00110011 00000000 00000000
			{ 0x03, 0x33, 0x00, 0x03, }, // 01110001: 00000011 00110011 00000000 00000011
			{ 0x03, 0x33, 0x00, 0x30, }, // 01110010: 00000011 00110011 00000000 00110000
			{ 0x03, 0x33, 0x00, 0x33, }, // 01110011: 00000011 00110011 00000000 00110011
			{ 0x03, 0x33, 0x03, 0x00, }, // 01110100: 00000011 00110011 00000011 00000000
			{ 0x03, 0x33, 0x03, 0x03, }, // 01110101: 00000011 00110011 00000011 00000011
			{ 0x03, 0x33, 0x03, 0x30, }, // 01110110: 00000011 00110011 00000011 00110000
			{ 0x03, 0x33, 0x03, 0x33, }, // 01110111: 00000011 00110011 00000011 00110011
			{ 0x03, 0x33, 0x30, 0x00, }, // 01111000: 00000011 00110011 00110000 00000000
			{ 0x03, 0x33, 0x30, 0x03, }, // 01111001: 00000011 00110011 00110000 00000011
			{ 0x03, 0x33, 0x30, 0x30, }, // 01111010: 00000011 00110011 00110000 00110000
			{ 0x03, 0x33, 0x30, 0x33, }, // 01111011: 00000011 00110011 00110000 00110011
			{ 0x03, 0x33, 0x33, 0x00, }, // 01111100: 00000011 00110011 00110011 00000000
			{ 0x03, 0x33, 0x33, 0x03, }, // 01111101: 00000011 00110011 00110011 00000011
			{ 0x03, 0x33, 0x33, 0x30, }, // 01111110: 00000011 00110011 00110011 00110000
			{ 0x03, 0x33, 0x33, 0x33, }, // 01111111: 00000011 00110011 00110011 00110011
			{ 0x30, 0x00, 0x00, 0x00, }, // 10000000: 00110000 00000000 00000000 00000000
			{ 0x30, 0x00, 0x00, 0x03, }, // 10000001: 00110000 00000000 00000000 00000011
			{ 0x30, 0x00, 0x00, 0x30, }, // 10000010: 00110000 00000000 00000000 00110000
			{ 0x30, 0x00, 0x00, 0x33, }, // 10000011: 00110000 00000000 00000000 00110011
			{ 0x30, 0x00, 0x03, 0x00, }, // 10000100: 00110000 00000000 00000011 00000000
			{ 0x30, 0x00, 0x03, 0x03, }, // 10000101: 00110000 00000000 00000011 00000011
			{ 0x30, 0x00, 0x03, 0x30, }, // 10000110: 00110000 00000000 00000011 00110000
			{ 0x30, 0x00, 0x03, 0x33, }, // 10000111: 00110000 00000000 00000011 00110011
			{ 0x30, 0x00, 0x30, 0x00, }, // 10001000: 00110000 00000000 00110000 00000000
			{ 0x30, 0x00, 0x30, 0x03, }, // 10001001: 00110000 00000000 00110000 00000011
			{ 0x30, 0x00, 0x30, 0x30, }, // 10001010: 00110000 00000000 00110000 00110000
			{ 0x30, 0x00, 0x30, 0x33, }, // 10001011: 00110000 00000000 00110000 00110011
			{ 0x30, 0x00, 0x33, 0x00, }, // 10001100: 00110000 00000000 00110011 00000000
			{ 0x30, 0x00, 0x33, 0x03, }, // 10001101: 00110000 00000000 00110011 00000011
			{ 0x30, 0x00, 0x33, 0x30, }, // 10001110: 00110000 00000000 00110011 00110000
			{ 0x30, 0x00, 0x33, 0x33, }, // 10001111: 00110000 00000000 00110011 00110011
			{ 0x30, 0x03, 0x00, 0x00, }, // 10010000: 00110000 00000011 00000000 00000000
			{ 0x30, 0x03, 0x00, 0x03, }, // 10010001: 00110000 00000011 00000000 00000011
			{ 0x30, 0x03, 0x00, 0x30, }, // 10010010: 00110000 00000011 00000000 00110000
			{ 0x30, 0x03, 0x00, 0x33, }, // 10010011: 00110000 00000011 00000000 00110011
			{ 0x30, 0x03, 0x03, 0x00, }, // 10010100: 00110000 00000011 00000011 00000000
			{ 0x30, 0x03, 0x03, 0x03, }, // 10010101: 00110000 00000011 00000011 00000011
			{ 0x30, 0x03, 0x03, 0x30, }, // 10010110: 00110000 00000011 00000011 00110000
			{ 0x30, 0x03, 0x03, 0x33, }, // 10010111: 00110000 00000011 00000011 00110011
			{ 0x30, 0x03, 0x30, 0x00, }, // 10011000: 00110000 00000011 00110000 00000000
			{ 0x30, 0x03, 0x30, 0x03, }, // 10011001: 00110000 00000011 00110000 00000011
			{ 0x30, 0x03, 0x30, 0x30, }, // 10011010: 00110000 00000011 00110000 00110000
			{ 0x30, 0x03, 0x30, 0x33, }, // 10011011: 00110000 00000011 00110000 00110011
			{ 0x30, 0x03, 0x33, 0x00, }, // 10011100: 00110000 00000011 00110011 00000000
			{ 0x30, 0x03, 0x33, 0x03, }, // 10011101: 00110000 00000011 00110011 00000011
			{ 0x30, 0x03, 0x33, 0x30, }, // 10011110: 00110000 00000011 00110011 00110000
			{ 0x30, 0x03, 0x33, 0x33, }, // 10011111: 00110000 00000011 00110011 00110011
			{ 0x30, 0x30, 0x00, 0x00, }, // 10100000: 00110000 00110000 00000000 00000000
			{ 0x30, 0x30, 0x00, 0x03, }, // 10100001: 00110000 00110000 00000000 00000011
			{ 0x30, 0x30, 0x00, 0x30, }, // 10100010: 00110000 00110000 00000000 00110000
			{ 0x30, 0x30, 0x00, 0x33, }, // 10100011: 00110000 00110000 00000000 00110011
			{ 0x30, 0x30, 0x03, 0x00, }, // 10100100: 00110000 00110000 00000011 00000000
			{ 0x30, 0x30, 0x03, 0x03, }, // 10100101: 00110000 00110000 00000011 00000011
			{ 0x30, 0x30, 0x03, 0x30, }, // 10100110: 00110000 00110000 00000011 00110000
			{ 0x30, 0x30, 0x03, 0x33, }, // 10100111: 00110000 00110000 00000011 00110011
			{ 0x30, 0x30, 0x30, 0x00, }, // 10101000: 00110000 00110000 00110000 00000000
			{ 0x30, 0x30, 0x30, 0x03, }, // 10101001: 00110000 00110000 00110000 00000011
			{ 0x30, 0x30, 0x30, 0x30, }, // 10101010: 00110000 00110000 00110000 00110000
			{ 0x30, 0x30, 0x30, 0x33, }, // 10101011: 00110000 00110000 00110000 00110011
			{ 0x30, 0x30, 0x33, 0x00, }, // 10101100: 00110000 00110000 00110011 00000000
			{ 0x30, 0x30, 0x33, 0x03, }, // 10101101: 00110000 00110000 00110011 00000011
			{ 0x30, 0x30, 0x33, 0x30, }, // 10101110: 00110000 00110000 00110011 00110000
			{ 0x30, 0x30, 0x33, 0x33, }, // 10101111: 00110000 00110000 00110011 00110011
			{ 0x30, 0x33, 0x00, 0x00, }, // 10110000: 00110000 00110011 00000000 00000000
			{ 0x30, 0x33, 0x00, 0x03, }, // 10110001: 00110000 00110011 00000000 00000011
			{ 0x30, 0x33, 0x00, 0x30, }, // 10110010: 00110000 00110011 00000000 00110000
			{ 0x30, 0x33, 0x00, 0x33, }, // 10110011: 00110000 00110011 00000000 00110011
			{ 0x30, 0x33, 0x03, 0x00, }, // 10110100: 00110000 00110011 00000011 00000000
			{ 0x30, 0x33, 0x03, 0x03, }, // 10110101: 00110000 00110011 00000011 00000011
			{ 0x30, 0x33, 0x03, 0x30, }, // 10110110: 00110000 00110011 00000011 00110000
			{ 0x30, 0x33, 0x03, 0x33, }, // 10110111: 00110000 00110011 00000011 00110011
			{ 0x30, 0x33, 0x30, 0x00, }, // 10111000: 00110000 00110011 00110000 00000000
			{ 0x30, 0x33, 0x30, 0x03, }, // 10111001: 00110000 00110011 00110000 00000011
			{ 0x30, 0x33, 0x30, 0x30, }, // 10111010: 00110000 00110011 00110000 00110000
			{ 0x30, 0x33, 0x30, 0x33, }, // 10111011: 00110000 00110011 00110000 00110011
			{ 0x30, 0x33, 0x33, 0x00, }, // 10111100: 00110000 00110011 00110011 00000000
			{ 0x30, 0x33, 0x33, 0x03, }, // 10111101: 00110000 00110011 00110011 00000011
			{ 0x30, 0x33, 0x33, 0x30, }, // 10111110: 00110000 00110011 00110011 00110000
			{ 0x30, 0x33, 0x33, 0x33, }, // 10111111: 00110000 00110011 00110011 00110011
			{ 0x33, 0x00, 0x00, 0x00, }, // 11000000: 00110011 00000000 00000000 00000000
			{ 0x33, 0x00, 0x00, 0x03, }, // 11000001: 00110011 00000000 00000000 00000011
			{ 0x33, 0x00, 0x00, 0x30, }, // 11000010: 00110011 00000000 00000000 00110000
			{ 0x33, 0x00, 0x00, 0x33, }, // 11000011: 00110011 00000000 00000000 00110011
			{ 0x33, 0x00, 0x03, 0x00, }, // 11000100: 00110011 00000000 00000011 00000000
			{ 0x33, 0x00, 0x03, 0x03, }, // 11000101: 00110011 00000000 00000011 00000011
			{ 0x33, 0x00, 0x03, 0x30, }, // 11000110: 00110011 00000000 00000011 00110000
			{ 0x33, 0x00, 0x03, 0x33, }, // 11000111: 00110011 00000000 00000011 00110011
			{ 0x33, 0x00, 0x30, 0x00, }, // 11001000: 00110011 00000000 00110000 00000000
			{ 0x33, 0x00, 0x30, 0x03, }, // 11001001: 00110011 00000000 00110000 00000011
			{ 0x33, 0x00, 0x30, 0x30, }, // 11001010: 00110011 00000000 00110000 00110000
			{ 0x33, 0x00, 0x30, 0x33, }, // 11001011: 00110011 00000000 00110000 00110011
			{ 0x33, 0x00, 0x33, 0x00, }, // 11001100: 00110011 00000000 00110011 00000000
			{ 0x33, 0x00, 0x33, 0x03, }, // 11001101: 00110011 00000000 00110011 00000011
			{ 0x33, 0x00, 0x33, 0x30, }, // 11001110: 00110011 00000000 00110011 00110000
			{ 0x33, 0x00, 0x33, 0x33, }, // 11001111: 00110011 00000000 00110011 00110011
			{ 0x33, 0x03, 0x00, 0x00, }, // 11010000: 00110011 00000011 00000000 00000000
			{ 0x33, 0x03, 0x00, 0x03, }, // 11010001: 00110011 00000011 00000000 00000011
			{ 0x33, 0x03, 0x00, 0x30, }, // 11010010: 00110011 00000011 00000000 00110000
			{ 0x33, 0x03, 0x00, 0x33, }, // 11010011: 00110011 00000011 00000000 00110011
			{ 0x33, 0x03, 0x03, 0x00, }, // 11010100: 00110011 00000011 00000011 00000000
			{ 0x33, 0x03, 0x03, 0x03, }, // 11010101: 00110011 00000011 00000011 00000011
			{ 0x33, 0x03, 0x03, 0x30, }, // 11010110: 00110011 00000011 00000011 00110000
			{ 0x33, 0x03, 0x03, 0x33, }, // 11010111: 00110011 00000011 00000011 00110011
			{ 0x33, 0x03, 0x30, 0x00, }, // 11011000: 00110011 00000011 00110000 00000000
			{ 0x33, 0x03, 0x30, 0x03, }, // 11011001: 00110011 00000011 00110000 00000011
			{ 0x33, 0x03, 0x30, 0x30, }, // 11011010: 00110011 00000011 00110000 00110000
			{ 0x33, 0x03, 0x30, 0x33, }, // 11011011: 00110011 00000011 00110000 00110011
			{ 0x33, 0x03, 0x33, 0x00, }, // 11011100: 00110011 00000011 00110011 00000000
			{ 0x33, 0x03, 0x33, 0x03, }, // 11011101: 00110011 00000011 00110011 00000011
			{ 0x33, 0x03, 0x33, 0x30, }, // 11011110: 00110011 00000011 00110011 00110000
			{ 0x33, 0x03, 0x33, 0x33, }, // 11011111: 00110011 00000011 00110011 00110011
			{ 0x33, 0x30, 0x00, 0x00, }, // 11100000: 00110011 00110000 00000000 00000000
			{ 0x33, 0x30, 0x00, 0x03, }, // 11100001: 00110011 00110000 00000000 00000011
			{ 0x33, 0x30, 0x00, 0x30, }, // 11100010: 00110011 00110000 00000000 00110000
			{ 0x33, 0x30, 0x00, 0x33, }, // 11100011: 00110011 00110000 00000000 00110011
			{ 0x33, 0x30, 0x03, 0x00, }, // 11100100: 00110011 00110000 00000011 00000000
			{ 0x33, 0x30, 0x03, 0x03, }, // 11100101: 00110011 00110000 00000011 00000011
			{ 0x33, 0x30, 0x03, 0x30, }, // 11100110: 00110011 00110000 00000011 00110000
			{ 0x33, 0x30, 0x03, 0x33, }, // 11100111: 00110011 00110000 00000011 00110011
			{ 0x33, 0x30, 0x30, 0x00, }, // 11101000: 00110011 00110000 00110000 00000000
			{ 0x33, 0x30, 0x30, 0x03, }, // 11101001: 00110011 00110000 00110000 00000011
			{ 0x33, 0x30, 0x30, 0x30, }, // 11101010: 00110011 00110000 00110000 00110000
			{ 0x33, 0x30, 0x30, 0x33, }, // 11101011: 00110011 00110000 00110000 00110011
			{ 0x33, 0x30, 0x33, 0x00, }, // 11101100: 00110011 00110000 00110011 00000000
			{ 0x33, 0x30, 0x33, 0x03, }, // 11101101: 00110011 00110000 00110011 00000011
			{ 0x33, 0x30, 0x33, 0x30, }, // 11101110: 00110011 00110000 00110011 00110000
			{ 0x33, 0x30, 0x33, 0x33, }, // 11101111: 00110011 00110000 00110011 00110011
			{ 0x33, 0x33, 0x00, 0x00, }, // 11110000: 00110011 00110011 00000000 00000000
			{ 0x33, 0x33, 0x00, 0x03, }, // 11110001: 00110011 00110011 00000000 00000011
			{ 0x33, 0x33, 0x00, 0x30, }, // 11110010: 00110011 00110011 00000000 00110000
			{ 0x33, 0x33, 0x00, 0x33, }, // 11110011: 00110011 00110011 00000000 00110011
			{ 0x33, 0x33, 0x03, 0x00, }, // 11110100: 00110011 00110011 00000011 00000000
			{ 0x33, 0x33, 0x03, 0x03, }, // 11110101: 00110011 00110011 00000011 00000011
			{ 0x33, 0x33, 0x03, 0x30, }, // 11110110: 00110011 00110011 00000011 00110000
			{ 0x33, 0x33, 0x03, 0x33, }, // 11110111: 00110011 00110011 00000011 00110011
			{ 0x33, 0x33, 0x30, 0x00, }, // 11111000: 00110011 00110011 00110000 00000000
			{ 0x33, 0x33, 0x30, 0x03, }, // 11111001: 00110011 00110011 00110000 00000011
			{ 0x33, 0x33, 0x30, 0x30, }, // 11111010: 00110011 00110011 00110000 00110000
			{ 0x33, 0x33, 0x30, 0x33, }, // 11111011: 00110011 00110011 00110000 00110011
			{ 0x33, 0x33, 0x33, 0x00, }, // 11111100: 00110011 00110011 00110011 00000000
			{ 0x33, 0x33, 0x33, 0x03, }, // 11111101: 00110011 00110011 00110011 00000011
			{ 0x33, 0x33, 0x33, 0x30, }, // 11111110: 00110011 00110011 00110011 00110000
			{ 0x33, 0x33, 0x33, 0x33, }, // 11111111: 00110011 00110011 00110011 00110011
		};
};
// #############################################################################
#endif // _MONOCHROME_DISPLAY_H_
