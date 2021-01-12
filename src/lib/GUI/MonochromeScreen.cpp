// ----------------------------------------------
#include "MonochromeScreen.h"
#include <algorithm>
#include <iostream>

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
	for (DWORD row = 0; row < bmp.getHeight(); row++) {
		std::copy_n(bmp.getPxData() + bmp.getStride() * row, bmp.getStride(), _screenBuffer + Width * row);
	}
}
// ----------------------------------------------
BYTE MonochromeScreen::reverse(BYTE b)
{
	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
	return b;
}
// ----------------------------------------------
