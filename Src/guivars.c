#include "guivars.h"
#include "adc.h"
GUI_Vars gui_Vars;
Handles handles;
TimeCalibration timeCalibr;
LongPressCNT longPressCNT;
DaylightSaving daylightSaving;
MasterClock masterClock;
CurrentSense currentSense;
void initStructures(void)
{
	masterClock.daylightSaving = &daylightSaving;
	masterClock.guiVars = &gui_Vars;
	masterClock.handles = &handles;
	masterClock.longPressCNT = &longPressCNT;
	masterClock.timeCalibration = &timeCalibr;
	masterClock.currentSense = &currentSense;
	masterClock.currentSense->startCurrentSense = _startCurrentSense;
	masterClock.currentSense->stopCurrentSense = _stopCurrentSense;
}
void sendMsg(WM_HWIN handle, uint16_t message)
{
	WM_MESSAGE msgStruct;
	if (masterClock.handles->hMainMenu != 0)
	{
		msgStruct.MsgId = message;
		msgStruct.Data.v = 0xFF;
		WM_SendMessage(handle, &msgStruct);
	}
}