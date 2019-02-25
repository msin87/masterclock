#include "guivars.h"
GUI_Vars gui_Vars;
Handles handles;
Lines line[4];
TimeCalibration timeCalibr;
LongPressCNT longPressCNT;
DaylightSaving daylightSaving;
MasterClock masterClock;
void initStructures(void)
{
	masterClock.daylightSaving = &daylightSaving;
	masterClock.guiVars = &gui_Vars;
	masterClock.handles = &handles;
	masterClock.longPressCNT = &longPressCNT;
	masterClock.timeCalibration = &timeCalibr;

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