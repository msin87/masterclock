/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.32                          *
*        Compiled Oct  8 2015, 11:59:02                              *
*        (c) 2015 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include "TimeSumWinSetup.h"
#include "TimeCalibrate.h"
#include "callbacks.h"
#include "TimeDateSetup.h"
#include "guivars.h"
#include "string.h"
#include "stdio.h"
#include "LineSetup.h"
#include <stdbool.h>
#include "backup.h"

extern RTC_TimeTypeDef sTime;
extern RTC_DateTypeDef sDate;

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)

extern GUI_CONST_STORAGE GUI_CHARINFO GUI_FontArial18_CharInfo[192];
DaylightSaving daylightSavingTemp;

// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
	{ WINDOW_CreateIndirect, "Window", ID_WINDOW_SUMWINSETUP, 1, -3, 320, 240, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "", ID_BUTTON_SUMWINSETUP_Zplus, 5, 85, 70, 70, 0, 0x0, 0 },
	{ HEADER_CreateIndirect, "Header", ID_HEADER_SUMWINSETUP_VALSNAMES, 0, 20, 240, 30, 0, 0x0, 0 },
	{ HEADER_CreateIndirect, "Header", ID_HEADER_SUMWINSETUP_VALS, 0, 50, 240, 30, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "", ID_BUTTON_SUMWINSETUP_SUMWIN_ON, 85, 85, 70, 70, 0, 0x0, 0 },
	//{ BUTTON_CreateIndirect, "", ID_BUTTON_SUMWINSETUP_Splus, 165, 85, 70, 70, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "����", ID_BUTTON_SUMWINSETUP_ENTER, 245, 85, 70, 70, 0, 0x0, 0 },
	// { BUTTON_CreateIndirect, "����", ID_BUTTON_SUMWINSETUP_RUNSTOP, 245, 5, 70, 30, 0, 0x0, 0 },
	// { BUTTON_CreateIndirect, "", ID_BUTTON_SUMWINSETUP_PULSE, 245, 45, 70, 30, 0, 0x0, 0 },
	 { BUTTON_CreateIndirect, "", ID_BUTTON_SUMWINSETUP_Zminus, 5, 165, 70, 70, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "", ID_BUTTON_SUMWINSETUP_SUMWIN_OFF, 85, 165, 70, 70, 0, 0x0, 0 },
	//{ BUTTON_CreateIndirect, "", ID_BUTTON_SUMWINSETUP_Sminus, 165, 165, 70, 70, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "�����", ID_BUTTON_SUMWINSETUP_BACK, 245, 165, 70, 70, 0, 0x0, 0 },

	{ HEADER_CreateIndirect, "Header", ID_HEADER_SUMWINSETUP_TOP, 0, 0, 240, 20, 0, 0x0, 0 },
	// USER START (Optionally insert additional widgets)
	// USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)

// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
	WM_HWIN hItem;
	int     NCode;
	int     Id;
	char str[9];

	uint8_t valsChangedOld = false;

	// USER START (Optionally insert additional variables)
	// USER END

	switch (pMsg->MsgId) {
	case WM_INIT_DIALOG:

		daylightSavingTemp = *masterClock.daylightSaving;
		// Initialization of Main Window
		//
		hItem = pMsg->hWin;
		WINDOW_SetBkColor(hItem, 0x191615);
		//
		// ��������
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_HEADER_SUMWINSETUP_VALSNAMES);
		HEADER_AddItem(hItem, 80, "���.����", 14);
		HEADER_AddItem(hItem, 80, "���.�����", 14);
		HEADER_SetTextColor(hItem, GUI_WHITE);
		//
		// �������� ��������
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_HEADER_SUMWINSETUP_VALS);
		masterClock.handles->hHeaderSumWinSetupVals = hItem;
		if ((int8_t)daylightSavingTemp.timeZone > 0)
		{
			sprintf(str, "+%d", masterClock.daylightSaving->timeZone);
		}
		else if ((int8_t)daylightSavingTemp.timeZone <= 0)
		{
			sprintf(str, "%d", (int8_t)masterClock.daylightSaving->timeZone);
		}
		HEADER_AddItem(hItem, 80, str, 14);
		if (daylightSavingTemp.enableDLS == 0)
		{
			HEADER_AddItem(hItem, 80, "����", 14);
		}
		else
		{
			HEADER_AddItem(hItem, 80, "���", 14);
		}
		HEADER_SetTextColor(hItem, GUI_WHITE);
		//
		// Initialization of 'Header'
		//


		//
		// Initialization of 'Header'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_HEADER_SUMWINSETUP_TOP);
		HEADER_AddItem(hItem, 240, "��������� �������� �����", 14);
		HEADER_SetTextColor(hItem, GUI_WHITE);
		// USER START (Optionally insert additional code for further widget initialization)
		// USER END
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (Id) {
		case ID_BUTTON_SUMWINSETUP_Zplus: // Notifications sent by 'Time Zone +'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)

				if (daylightSavingTemp.timeZone != 12)
				{
					pollButton(ID_BUTTON_SUMWINSETUP_Zplus, WM_NOTIFICATION_CLICKED, (int8_t*)&daylightSavingTemp.timeZone);

				}
				else
				{
					masterClock.longPressCNT->value = 12;
				}
				if (valsChangedOld != masterClock.guiVars->valsChanged)
				{
					WM_Invalidate(WM_GetDialogItem(masterClock.handles->hTimeSumWinSetupMenu, ID_BUTTON_SUMWINSETUP_ENTER));
				}
				// USER END
				break;
			case WM_NOTIFICATION_RELEASED:
				// USER START (Optionally insert code for reacting on notification message)
				pollButton(ID_BUTTON_SUMWINSETUP_Zplus, WM_NOTIFICATION_RELEASED, (int8_t*)&daylightSavingTemp.timeZone);

				// USER END
				break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
			}
			break;

		case ID_BUTTON_SUMWINSETUP_SUMWIN_ON: // Notifications sent by "Enable Daylight Saving"
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)


				// USER END
				break;
			case WM_NOTIFICATION_RELEASED:
				// USER START (Optionally insert code for reacting on notification message)
				if (daylightSavingTemp.enableDLS == false)
				{
					daylightSavingTemp.enableDLS = true;

					masterClock.guiVars->valsChanged = true;
					HEADER_SetItemText(WM_GetDialogItem(pMsg->hWin, ID_HEADER_SUMWINSETUP_VALS), 1, "���");
					HEADER_SetTextColor(WM_GetDialogItem(pMsg->hWin, ID_HEADER_SUMWINSETUP_VALS), GUI_WHITE);
					WM_Invalidate(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_SUMWINSETUP_ENTER));
				}


				// USER END
				break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
			}
			break;

		case ID_BUTTON_SUMWINSETUP_ENTER: // Notifications sent by 'Enter'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)

				// USER END
				break;
			case WM_NOTIFICATION_RELEASED:
				// USER START (Optionally insert code for reacting on notification message)
				masterClock.daylightSaving = &daylightSavingTemp;
				masterClock.guiVars->valsChanged = false;
				saveDaylightSavingToBKP();
				// USER END
				break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
			}
			break;

		case ID_BUTTON_SUMWINSETUP_Zminus: // Notifications sent by 'h-'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)

				if (daylightSavingTemp.timeZone != -12)
				{
					pollButton(ID_BUTTON_SUMWINSETUP_Zminus, WM_NOTIFICATION_CLICKED, (int8_t*)&daylightSavingTemp.timeZone);
				}
				if (valsChangedOld != masterClock.guiVars->valsChanged)
				{
					WM_Invalidate(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_SUMWINSETUP_ENTER));
				}

				// USER END
				break;
			case WM_NOTIFICATION_RELEASED:
				// USER START (Optionally insert code for reacting on notification message)
				pollButton(ID_BUTTON_SUMWINSETUP_Zminus, WM_NOTIFICATION_RELEASED, (int8_t*)&daylightSavingTemp.timeZone);

				// USER END
				break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
			}
			break;
		case ID_BUTTON_SUMWINSETUP_SUMWIN_OFF:
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)


				// USER END
				break;
			case WM_NOTIFICATION_RELEASED:
				// USER START (Optionally insert code for reacting on notification message)
				if (daylightSavingTemp.enableDLS == true)
				{
					daylightSavingTemp.enableDLS = false;
					masterClock.guiVars->valsChanged = true;
					HEADER_SetItemText(WM_GetDialogItem(pMsg->hWin, ID_HEADER_SUMWINSETUP_VALS), 1, "����");
					HEADER_SetTextColor(WM_GetDialogItem(pMsg->hWin, ID_HEADER_SUMWINSETUP_VALS), GUI_WHITE);
					WM_Invalidate(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_LINESETUP_ENTER));
				}




				// USER END
				break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
			}
			break;

		case ID_BUTTON_SUMWINSETUP_BACK: // Notifications sent by 'Back'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)
				// USER END
				break;
			case WM_NOTIFICATION_RELEASED:
				// USER START (Optionally insert code for reacting on notification message)
				masterClock.guiVars->menuState = MENU_STATE_TIMECALIBRATION;
				masterClock.guiVars->valsChanged = false;
				WM_DeleteWindow(masterClock.handles->hTimeSumWinSetupMenu);
				WM_ShowWindow(masterClock.handles->hTimeCalibrateMenu);

				// USER END
				break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
			}
			break;
		}
		break;
		// USER START (Optionally insert additional message handling)
		// USER END
	default:
		WM_DefaultProc(pMsg);
		break;
	}
	valsChangedOld = masterClock.guiVars->valsChanged;
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateWindow
*/

WM_HWIN CreateTimeSumWinSetupWindow(void) {
	WM_HWIN hWin;

	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
	masterClock.handles->hTimeSumWinSetupMenu = hWin;
	WM_SetCallback(WM_GetDialogItem(hWin, ID_BUTTON_SUMWINSETUP_Zplus), _cbArrowUpButton);
	WM_SetCallback(WM_GetDialogItem(hWin, ID_BUTTON_SUMWINSETUP_SUMWIN_ON), _cbArrowUpButton);
	//WM_SetCallback(WM_GetDialogItem(hWin,ID_BUTTON_LINESETUP_Splus),_cbArrowUpButton);
	WM_SetCallback(WM_GetDialogItem(hWin, ID_BUTTON_SUMWINSETUP_Zminus), _cbArrowDownButton);
	WM_SetCallback(WM_GetDialogItem(hWin, ID_BUTTON_SUMWINSETUP_SUMWIN_OFF), _cbArrowDownButton);
	//WM_SetCallback(WM_GetDialogItem(hWin,ID_BUTTON_LINESETUP_Sminus),_cbArrowDownButton);
	WM_SetCallback(WM_GetDialogItem(hWin, ID_BUTTON_SUMWINSETUP_ENTER), _cbEnterButton);
	return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/