#ifndef _DISPLAY_COMMAND_H_
#define _DISPLAY_COMMAND_H_
// #############################################################################
// =============================================================================
#include "global.h"
// =============================================================================
enum class DisplayCommand : BYTE
{
	PanelSetting                 = 0x00,
	PowerSetting                 = 0x01,
	PowerOff                     = 0x02,
	PowerOffSequenceSetting      = 0x03,
	PowerOn                      = 0x04,
	PowerOnMeasure               = 0x05,
	BoosterSoftStart             = 0x06,
	DeepSleep                    = 0x07,
	DataStartTransmission1       = 0x10,
	DataStop                     = 0x11,
	DisplayRefresh               = 0x12,
	DataStartTransmission2       = 0x13,
	VcomLut                      = 0x20,
	W2wLut                       = 0x21,
	B2wLut                       = 0x22,
	W2bLut                       = 0x23,
	B2bLut                       = 0x24,
	PllControl                   = 0x30,
	TemperatureSensorCalibration = 0x40,
	TemperatureSensorSelection   = 0x41,
	TemperatureSensorWrite       = 0x42,
	TemperatureSensorRead        = 0x43,
	VcomAndDataIntervalSetting   = 0x50,
	LowPowerDetection            = 0x51,
	TconSetting                  = 0x60,
	ResolutionSetting            = 0x61,
	GetStatus                    = 0x71,
	AutoMeasureVcom              = 0x80,
	ReadVcomValue                = 0x81,
	VcmDcSetting                 = 0x82,
	PartialWindow                = 0x90,
	PartialIn                    = 0x91,
	PartialOut                   = 0x92,
	ProgramMode                  = 0xA0,
	ActiveProgram                = 0xA1,
	ReadOtpData                  = 0xA2,
	PowerSaving                  = 0xE3,
};
// =============================================================================
// #############################################################################
#endif // _DISPLAY_COMMAND_H_