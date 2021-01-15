/*!
 *  \file    MonochromeBitmap.h
 *  \author  urbanSoft <support@urbansoft.de>
 *  \version 1.0
 *  \brief   Contains mandatory declarations for a monochrome Bitmap (V3).
 *  
 *  Changelog
 *  =========
 *  - 1.0
 *      - Initial Version
 */
#ifndef _MONOCHROME_BITMAP_H_
#define _MONOCHROME_BITMAP_H_
// #############################################################################
// =============================================================================
#include "global.h"
#include <iostream>
// =============================================================================
#pragma pack(push, 1) // super important to pack the bytes together!
/*!
 *  The structure defining a Bitmap file header.
 *  
 *  For a detailed member description see the
 *  [Win API](https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapfileheader).
 */
typedef struct tagBITMAPFILEHEADER {
  WORD  bfType;
  DWORD bfSize;
  WORD  bfReserved1;
  WORD  bfReserved2;
  DWORD bfOffBits;
} BITMAPFILEHEADER;
// =============================================================================
/*!
 *  The structure defining a Bitmap info header.
 *  
 *  For a detailed member description see the
 *  [Win API](https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader).
 */
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
/*!
 *  The structure defining the color entry of the Bitmap color table.
 *  
 *  For a detailed member description see the
 *  [Win API](https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-rgbquad).
 */
typedef struct tagRGBQUAD {
  BYTE rgbBlue;
  BYTE rgbGreen;
  BYTE rgbRed;
  BYTE rgbReserved;
} RGBQUAD;
#pragma pack(pop)
// =============================================================================
/*!
 *  A class representing a **monochrome** Bitmap file.
 */
class MonochromeBitmap
{
// - private static ------------------------------------------------------------
	private:
		//! The magic number (aka BOM) of a valid Bitmap file.
		static const WORD  MAGIC_NUMBER   = 0x4D42; // "BM" Little Endian
// - private member ------------------------------------------------------------
	private:
		//! The path of the Bitmap file.
		std::string      _path;
		//! The Bitmap file header
		BITMAPFILEHEADER _fileHeader;
		//! The Bitmap info header
		BITMAPINFOHEADER _infoHeader;
		//! The Bitmap color table (with two entries: black / white)
		RGBQUAD          _rgbQuad[2];
		//! The plain image data a a byte array
		BYTE*            _pxData;
		//! The size of the plain image data
		DWORD            _pxDataSize;
		//! Two-Dim array of the _pxData
		BYTE**           _pxGrid;
		//! Index of white in _rqbQuad
		BYTE             _idxWhite;
		//! Index of black in _rqbQuad
		BYTE             _idxBlack;
		//! Number of bytes per row
		DWORD            _stride;
		//! Height of the image (pixel count)
		DWORD            _height;
		//! Width of the image (pixel count)
		DWORD            _width;
// - public member -------------------------------------------------------------
	public:
		/*!
		 *  \brief Create a new monochrome Bitmap object.
		 *  \param [in] path The *.bmp file to read.
		 */
		MonochromeBitmap(const std::string path);
		/*!
		 *  \brief Destruct the object.
		 */
		~MonochromeBitmap();
		inline const BYTE* operator[](DWORD idx) const { return _pxGrid[idx]; }
		/*!
		 *  \brief Print the image as ASCII art to stdout.
		 */
		void         print() const;
// - inline --------------------------------------------------------------------
		/*!
		 *  \brief Get the _stride member.
		 *  \return The _stride value.
		 */
		inline DWORD       getStride() const { return _stride; }
		/*!
		 *  \brief Get the _pxData member.
		 *  \return The _pxData pointer.
		 */
		inline const BYTE* getPxData() const { return _pxData; }
		/*!
		 *  \brief Get the _height member.
		 *  \return The _height value.
		 */
		inline DWORD       getHeight() const { return _height; }
		/*!
		 *  \brief Get the _width member.
		 *  \return The _width value.
		 */
		inline DWORD       getWidth()  const { return _width; }
};
// #############################################################################
#endif // _MONOCHROME_BITMAP_H_
