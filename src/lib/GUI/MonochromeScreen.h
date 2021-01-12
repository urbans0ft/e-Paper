#ifndef _MONOCHROME_SCREEN_H_
#define _MONOCHROME_SCREEN_H_
// #############################################################################
// =============================================================================
#include "global.h"
#include "MonochromeBitmap.h"
// =============================================================================
class MonochromeScreen
{
	private:
		const DWORD Width;
		const DWORD Height;
		const DWORD ScreenBufferSize;
		BYTE* _screenBuffer;
	public:
		MonochromeScreen(DWORD width, DWORD height);
		~MonochromeScreen();
		void draw(const MonochromeBitmap& bmp);
		inline const BYTE* getScreenBuffer() const { return _screenBuffer; }
	private:
		BYTE reverse(BYTE b);
};
// #############################################################################
#endif // _MONOCHROME_SCREEN_H_
