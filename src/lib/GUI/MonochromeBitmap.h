#ifndef _MONOCHROME_BITMAP_H_
#define _MONOCHROME_BITMAP_H_
// #############################################################################
// =============================================================================
#include "global.h"
#include <iostream>
// =============================================================================
#pragma pack(push, 1) // super important to pack the bytes together!
// https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapfileheader
typedef struct tagBITMAPFILEHEADER {
  WORD  bfType;
  DWORD bfSize;
  WORD  bfReserved1;
  WORD  bfReserved2;
  DWORD bfOffBits;
} BITMAPFILEHEADER;
// =============================================================================
// https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader
typedef struct tagBITMAPINFOHEADER {
  DWORD biSize;
  LONG  biWidth;
  LONG  biHeight;
  WORD  biPlanes;
  WORD  biBitCount;
  DWORD biCompression;
  DWORD biSizeImage;
  LONG  biXPelsPerMeter;
  LONG  biYPelsPerMeter;
  DWORD biClrUsed;
  DWORD biClrImportant;
} BITMAPINFOHEADER;
// =============================================================================
// https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-rgbquad
typedef struct tagRGBQUAD {
  BYTE rgbBlue;
  BYTE rgbGreen;
  BYTE rgbRed;
  BYTE rgbReserved;
} RGBQUAD;
#pragma pack(pop)
// =============================================================================
class MonochromeBitmap
{
// - private static ------------------------------------------------------------
	private:
		static const WORD  MAGIC_NUMBER   = 0x4D42; // "BM" Little Endian
		static const DWORD BITMAP_PADDING = 4;      // Byte
// - private member ------------------------------------------------------------
	private:
		std::string      _path;
		BITMAPFILEHEADER _fileHeader;
		BITMAPINFOHEADER _infoHeader;
		RGBQUAD          _rgbQuad[2];
		BYTE*            _pxData;
		DWORD            _pxDataSize;
		BYTE             _idxWhite;
		BYTE             _idxBlack;
		DWORD            _stride; // bytes (needed) per row
		DWORD            _height; // height (num of _rows_)
// - public member -------------------------------------------------------------
	public:
		MonochromeBitmap(const std::string path);
		~MonochromeBitmap();
		void         print() const;
// - inline --------------------------------------------------------------------
		inline DWORD getStride() const { return _stride; }
		inline const BYTE* getPxData() const { return _pxData; }
		inline DWORD getHeight() const { return _height; }
};
// #############################################################################
#endif // _MONOCHROME_BITMAP_H_
