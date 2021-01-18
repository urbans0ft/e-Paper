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
void MonochromeDisplay::reset(void)
{
    DEV_Digital_Write(EPD_RST_PIN, 1);
    DEV_Delay_ms(200);
    DEV_Digital_Write(EPD_RST_PIN, 0);
    DEV_Delay_ms(2);
    DEV_Digital_Write(EPD_RST_PIN, 1);
    DEV_Delay_ms(200);
}

/******************************************************************************
function :	send command
parameter:
     Reg : Command register
******************************************************************************/
void MonochromeDisplay::sendCommand(UBYTE Reg)
{
    DEV_Digital_Write(EPD_DC_PIN, 0);
    DEV_Digital_Write(EPD_CS_PIN, 0);
    DEV_SPI_WriteByte(Reg);
    DEV_Digital_Write(EPD_CS_PIN, 1);
}

/******************************************************************************
function :	send data
parameter:
    Data : Write data
******************************************************************************/
void MonochromeDisplay::sendData(UBYTE Data)
{
    DEV_Digital_Write(EPD_DC_PIN, 1);
    DEV_Digital_Write(EPD_CS_PIN, 0);
    DEV_SPI_WriteByte(Data);
    DEV_Digital_Write(EPD_CS_PIN, 1);
}

void MonochromeDisplay::sendData(UBYTE* pData, uint32_t Len)
{
    DEV_Digital_Write(EPD_DC_PIN, 1);
    DEV_Digital_Write(EPD_CS_PIN, 0);
    DEV_SPI_Write_nByte(pData, Len);
    DEV_Digital_Write(EPD_CS_PIN, 1);
}


/******************************************************************************
function :	Wait until the busy_pin goes LOW
parameter:
******************************************************************************/
void MonochromeDisplay::readBusy(void)
{
    cout << "e-Paper busy" << endl;
    while(DEV_Digital_Read(EPD_BUSY_PIN) == 0) {      //LOW: idle, HIGH: busy
        DEV_Delay_ms(100);
    }
    cout << "e-Paper busy release" << endl;
}

/******************************************************************************
function :	Turn On Display
parameter:
******************************************************************************/
void MonochromeDisplay::turnOnDisplay(void)
{
    sendCommand(DisplayCommand::DisplayRefresh); // DISPLAY_REFRESH
    DEV_Delay_ms(100);
    readBusy();
}

/******************************************************************************
function :	Initialize the e-Paper register
parameter:
******************************************************************************/
void MonochromeDisplay::init(void)
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

    sendCommand(DisplayCommand::TemperatureCalibration);    // TEMPERATURE_CALIBRATION
    sendData(0x00);

    sendCommand(DisplayCommand::VomAndDataIntervalSetting); // VCOM_AND_DATA_INTERVAL_SETTING
    sendData(0x77);

    sendCommand(DisplayCommand::TconSetting);               // TCON_SETTING
    sendData(0x22);

    sendCommand(DisplayCommand::TconResolution);            // TCON_RESOLUTION
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
void MonochromeDisplay::clear(void)
{
	DWORD width = (Width % 8 == 0)? (Width / 8 ): (Width / 8 + 1);

	sendCommand(DisplayCommand::DataStartTransmission1);
	for (UWORD j = 0; j < Height; j++) {
		for (UWORD i = 0; i < width; i++) {
			for(UBYTE k = 0; k < 4; k++) {
				//! \todo send more thant one byte at a time.
				sendData(0x33);
			}
		}
	}
	turnOnDisplay();
}


/******************************************************************************
function :	Sends the image buffer in RAM to e-Paper and displays
parameter:
******************************************************************************/
void MonochromeDisplay::display(UBYTE *Image)
{
	BYTE data;
	DWORD width = (Width % 8 == 0)? (Width / 8 ): (Width / 8 + 1);

	sendCommand(DisplayCommand::DataStartTransmission1);
	for (UWORD j = 0; j < Height; j++) {
		for (int i = 0; i < width; i++) {
			data = Image[i + j * width];
			sendData(BYTE_SEND_TABLE[data], 4);
		}
	}
	turnOnDisplay();
}

/******************************************************************************
function :	Enter sleep mode
parameter:
******************************************************************************/
void MonochromeDisplay::sleep(void)
{
	sendCommand(DisplayCommand::PowerOff); // POWER_OFF
	readBusy();
	sendCommand(DisplayCommand::DeepSleep); // DEEP_SLEEP
	sendData(0xA5);
}
