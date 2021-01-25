// ----------------------------------------------
#include "MonochromeDisplay.h"
#include "DisplayCommand.h"
#include "DEV_Config.h"
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
	this->init();
}
// ----------------------------------------------
MonochromeDisplay::~MonochromeDisplay()
{
}
// ----------------------------------------------


/******************************************************************************
function :	Software reset
parameter:
******************************************************************************/
void MonochromeDisplay::reset()
{
    _spi.write(_spi.RstPin, 1);
    _spi.delayMs(200);
    _spi.write(_spi.RstPin, 0);
    _spi.delayMs(2);
    _spi.write(_spi.RstPin, 1);
    _spi.delayMs(200);
}

/******************************************************************************
function :	send command
parameter:
     Reg : Command register
******************************************************************************/
void MonochromeDisplay::sendCommand(DisplayCommand Reg)
{
    _spi.write(_spi.DcPin, 0);
    _spi.transfer(static_cast<BYTE>(Reg));
}

/******************************************************************************
function :	send data
parameter:
    Data : Write data
******************************************************************************/
void MonochromeDisplay::sendData(BYTE Data)
{
    _spi.write(_spi.DcPin, 1);
    _spi.transfer(Data);
}

void MonochromeDisplay::sendData(const BYTE* pData, DWORD Len)
{
    _spi.write(_spi.DcPin, 1);
    _spi.transfer(pData, Len);
}


/******************************************************************************
function :	Wait until the busy_pin goes LOW
parameter:
******************************************************************************/
void MonochromeDisplay::readBusy()
{
    cout << "e-Paper busy" << endl;
    while(_spi.read(_spi.BusyPin) == 0) {      //LOW: idle, HIGH: busy
        _spi.delayMs(100);
    }
    cout << "e-Paper busy release" << endl;
}

/******************************************************************************
function :	Turn On Display
parameter:
******************************************************************************/
void MonochromeDisplay::turnOnDisplay()
{
    sendCommand(DisplayCommand::DisplayRefresh); // DISPLAY_REFRESH
    _spi.delayMs(100);
    readBusy();
}

/******************************************************************************
function :	Initialize the e-Paper register
parameter:
******************************************************************************/
void MonochromeDisplay::init()
{
    reset();

    sendCommand(DisplayCommand::PowerSetting);              // POWER_SETTING
    sendData(0x37);
    sendData(0x00);

    sendCommand(DisplayCommand::PanelSetting);              // PANEL_SETTING
    sendData(0xCF);
    sendData(0x08);

    sendCommand(DisplayCommand::BoosterSoftStart);          // BOOSTER_SOFT_START
    sendData(0xc7);
    sendData(0xcc);
    sendData(0x28);

    sendCommand(DisplayCommand::PowerOn);                   // POWER_ON
    readBusy();

    sendCommand(DisplayCommand::PllControl);                // PLL_CONTROL
    sendData(0x3c);

    sendCommand(DisplayCommand::TemperatureSensorSelection); // TEMPERATURE_SENSOR_SELECTION
    sendData(0x00);

    sendCommand(DisplayCommand::VcomAndDataIntervalSetting); // VCOM_AND_DATA_INTERVAL_SETTING
    sendData(0x77);

    sendCommand(DisplayCommand::TconSetting);               // TCON_SETTING
    sendData(0x22);

    sendCommand(DisplayCommand::ResolutionSetting);            // TCON_RESOLUTION
    sendData(Width >> 8); // source 600
    sendData(Width & 0xff);
    sendData(Height >> 8); // gate 448
    sendData(Height & 0xff);

    sendCommand(DisplayCommand::VcmDcSetting);              // VCM_DC_SETTING
    sendData(0x1E); // decide by LUT file

    sendCommand(DisplayCommand::FlashMode);                 // FLASH MODE
    sendData(0x03);
}

/******************************************************************************
function :	Clear screen
parameter:
******************************************************************************/
void MonochromeDisplay::clear()
{
	const BYTE white[4]{0x33, 0x33, 0x33, 0x33};
	DWORD width = (Width % 8 == 0)? (Width / 8 ): (Width / 8 + 1);

	sendCommand(DisplayCommand::DataStartTransmission1);
	for (DWORD j = 0; j < Height; j++) {
		for (DWORD i = 0; i < width; i++) {
			sendData(white, 4);
		}
	}
	turnOnDisplay();
}


/******************************************************************************
function :	Sends the image buffer in RAM to e-Paper and displays
parameter:
******************************************************************************/
void MonochromeDisplay::display(const MonochromeScreen& screen)
{
	BYTE data;
	DWORD width = (Width % 8 == 0)? (Width / 8 ): (Width / 8 + 1);
	const BYTE* buffer = screen.getScreenBuffer();

	sendCommand(DisplayCommand::DataStartTransmission1);
	for (DWORD j = 0; j < Height; j++) {
		for (DWORD i = 0; i < width; i++) {
			data = buffer[i + j * width];
			sendData(BYTE_SEND_TABLE[data], 4);
		}
	}
	turnOnDisplay();
}

/******************************************************************************
function :	Enter sleep mode
parameter:
******************************************************************************/
void MonochromeDisplay::sleep()
{
	sendCommand(DisplayCommand::PowerOff); // POWER_OFF
	readBusy();
	sendCommand(DisplayCommand::DeepSleep); // DEEP_SLEEP
	sendData(0xA5);
}
