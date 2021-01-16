#include "MonochromeBitmap.h"
// ==============================================
#include <fstream>
#include <stdexcept>
#include <iostream>
// ==============================================
using namespace std;
// ==============================================
// ----------------------------------------------
MonochromeBitmap::MonochromeBitmap(const std::string path) : _path(path)
{
	ifstream bmpStream(_path, ifstream::binary);
	bmpStream.read((char*)&_fileHeader, sizeof(BITMAPFILEHEADER));
	bmpStream.read((char*)&_infoHeader, sizeof(BITMAPINFOHEADER));
	bmpStream.read((char*)&_rgbQuad,    sizeof(_rgbQuad));
	
	// check if the file is a monochromatic bitmap
	if (_fileHeader.bfType != MonochromeBitmap::MAGIC_NUMBER)
	{
		throw invalid_argument(_path + " is not a bitmap");
	}
	if (_infoHeader.biBitCount != 1)
	{
		throw invalid_argument(_path + " is not a monochromatic bitmap");
	}
	bool flipBits; // 1 is supposed to represent white.
	if (_rgbQuad[0].rgbRed == 0xFF && _rgbQuad[0].rgbGreen == 0xFF && _rgbQuad[0].rgbBlue == 0xFF
	 && _rgbQuad[1].rgbRed == 0x00 && _rgbQuad[1].rgbGreen == 0x00 && _rgbQuad[1].rgbBlue == 0x00)
	{
		cout << "White is _rgbQuad[0]" << endl;
		cout << "Black is _rgbQuad[1]" << endl;
		_idxWhite = 0;
		_idxBlack = 1;
		flipBits = true;
	}
	else if (_rgbQuad[1].rgbRed == 0xFF && _rgbQuad[1].rgbGreen == 0xFF && _rgbQuad[1].rgbBlue == 0xFF
	      && _rgbQuad[0].rgbRed == 0x00 && _rgbQuad[0].rgbGreen == 0x00 && _rgbQuad[0].rgbBlue == 0x00)
	{
		cout << "White is _rgbQuad[1]" << endl;
		cout << "Black is _rgbQuad[0]" << endl;
		_idxWhite = 1;
		_idxBlack = 0;
		flipBits = false;
	}
	else
	{
		throw logic_error("Bitmap's color table is faulty.");
	}
	_height = _infoHeader.biHeight;
	_width  = _infoHeader.biWidth;
	_stride = (((_width + 31) & ~31) >> 3); // bytes (needed) per row
	// read px data
	_pxDataSize = _fileHeader.bfSize - _fileHeader.bfOffBits;
	_pxData = new BYTE[_pxDataSize];
	_pxGrid = new BYTE*[_height];
	for (DWORD i = 0; i < _height; i++)
		_pxGrid[i] = &_pxData[i * _stride];
	bmpStream.read((char*)_pxData, _pxDataSize);
	if (flipBits)
	{
		cout << "Flipping bits so 1 represents white and 0 black." << endl;
		for(DWORD i = 0; i < _pxDataSize; i += 4) // flip DWORDs because it's faster
		{
			DWORD& flipping = *(DWORD*)&_pxData[i];
			flipping = ~flipping;
		}
	}
	cout << bmpStream.gcount() << endl;
}
// ----------------------------------------------
MonochromeBitmap::~MonochromeBitmap()
{
}
// ----------------------------------------------
void MonochromeBitmap::print() const
{
	// bytes per row
	// adapted from https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader#calculating-surface-stride
	auto coloredBytesPerRow = _infoHeader.biWidth % 8 == 0 ? _infoHeader.biWidth / 8 : _infoHeader.biWidth / 8 + 1;
	auto skipping = _stride - coloredBytesPerRow;
	int currentCol = 0;
	for (DWORD i = 0; i < _pxDataSize; i++)
	{
		for (int rShift = 0; rShift < 8; rShift++) // every byte has 8 px informtion
		{
			BYTE bitSelect = 128 >> rShift; // shift 1000 0000 to the right
			bool isPxSet  = _pxData[i] & bitSelect;
			if (!isPxSet)
			{
				cout << "X";
			}
			else
			{
				cout << " ";
			}
			currentCol++;
			if (currentCol >= _infoHeader.biWidth)
			{
				i += skipping;
				currentCol = 0;
				cout << endl;
				break;
			}
		}
	}
}
// ----------------------------------------------

// ----------------------------------------------
// ==============================================
