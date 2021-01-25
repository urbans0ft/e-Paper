// ----------------------------------------------
#include "MonochromeScreen.h"
#include <algorithm>
#include <iostream>
// ----------------------------------------------
using std::cout;
using std::endl;
// ----------------------------------------------
MonochromeScreen::MonochromeScreen(DWORD width, DWORD height)
	: Width{width % 8 == 0 ? width / 8 : width / 8 + 1}, Height{height}, ScreenBufferSize{Width * Height}
{
	_screenBuffer = new BYTE[ScreenBufferSize];
	std::fill(_screenBuffer, _screenBuffer + ScreenBufferSize, 0xFF);
}
// ----------------------------------------------
MonochromeScreen::~MonochromeScreen()
{
	delete[] _screenBuffer;
}
// ----------------------------------------------
void MonochromeScreen::draw(const MonochromeBitmap& bmp)
{
	const DWORD& bmpHeight = bmp.getHeight();
	const DWORD& bmpWidth  = bmp.getWidth();
	const DWORD& bmpStride = bmp.getStride();

	// calculate endianness
	const WORD endianTest = 0x0100; // LE => 00 10 / BE => 01 00
	// calculate padding **BITS** not bytes!
	auto  paddingBits       = bmpStride * 8 - bmpWidth;        // num of bits used for padding
	DWORD whiteningBitMask  = *(BYTE*)&endianTest              // either 0x01 xor 0x00
		? 0xFFFFFFFF >> (32 - paddingBits)                     // big-endian
		: __builtin_bswap32(0xFFFFFFFF >> (32 - paddingBits)); // little-endian

	cout << "Drawing to screen" << endl;
	// draw bmp onto the screen row by row
	for (DWORD row = 0; row < bmpHeight; row++) {
		std::copy_n(bmp[bmpHeight - row - 1], bmpStride, _screenBuffer + Width * row);
		// whiten padding bits (setting to 1) by grabbing padding **BYTE**
		DWORD& paddingByte = *(DWORD*)&_screenBuffer[Width * row + bmpStride - 4];
		paddingByte |= whiteningBitMask;
	}
}
// ----------------------------------------------
void MonochromeScreen::print() const
{
	for (DWORD y = 0; y < Height; y++)
	{
		for (DWORD x = 0; x < Width; x++)
		{
			for (int px = 0; px < 8; px++)
			{
				if(_screenBuffer[Width * y + x] & (0x80 >> px)) // set means WHITE
				{
					cout << " ";
				}
				else
				{
					cout << "X";
				}
			}
		}
		cout << endl;
	}
}
// ----------------------------------------------
