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

#include "TimeDateSetup.h"
#include "timedate.h"
#include "callbacks.h"
#include "guivars.h"
#include "string.h"
#include "stdio.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "TimeSetup.h"
#include <stdbool.h>
extern RTC_DateTypeDef sDate;
extern RTC_HandleTypeDef hrtc;
extern MasterClock masterClock;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontArial18;
/*********************************************************************
*
*       Defines
*
**********************************************************************
*/



// USER START (Optionally insert additional defines)
RTC_DateTypeDef sDateTemp;

// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "Window", ID_WINDOW_DATETIMESETUP, 1, -3, 320, 240, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "", ID_BUTTON_DTS_Dplus, 5, 85, 70, 70, 0, 0x0, 0 },
  { HEADER_CreateIndirect, "Header", ID_HEADER_DTS_DMY, 0, 20, 240, 30, 0, 0x0, 0 },
  { HEADER_CreateIndirect, "Header", ID_HEADER_DTS_VALS, 0, 50, 240, 30, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "", ID_BUTTON_DTS_Mplus, 85, 85, 70, 70, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "", ID_BUTTON_DTS_Yplus, 165, 85, 70, 70, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "����", ID_BUTTON_DTS_ENTER, 245, 85, 70, 70, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "", ID_BUTTON_DTS_Dminus, 5, 165, 70, 70, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "", ID_BUTTON_DTS_Mminus, 85, 165, 70, 70, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "", ID_BUTTON_DTS_Yminus, 165, 165, 70, 70, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "�����", ID_BUTTON_DTS_BACK, 245, 165, 70, 70, 0, 0x0, 0 },
  { HEADER_CreateIndirect, "Header", ID_HEADER_DTS, 0, 0, 240, 20, 0, 0x0, 0 },
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

//void correctDate(char* outString)
//{
//
//	if (sDateTemp.Month == 1 || sDateTemp.Month == 3 || sDateTemp.Month == 5 || sDateTemp.Month == 7 || sDateTemp.Month == 8 || sDateTemp.Month == 10 || sDateTemp.Month == 12)
//	{
//		if (sDateTemp.Date > 31)
//		{
//			sDateTemp.Date = 31;
//			sprintf(outString, "%02d", sDateTemp.Date);
//			HEADER_SetItemText(masterClock.handles->hHeaderTimeDateSetupVals, 0, outString);
//		}
//	}
//	else if (sDateTemp.Month == 4 || sDateTemp.Month == 6 || sDateTemp.Month == 9 || sDateTemp.Month == 11)
//	{
//		if (sDateTemp.Date > 30)
//		{
//			sDateTemp.Date = 30;
//			sprintf(outString, "%02d", sDateTemp.Date);
//			HEADER_SetItemText(masterClock.handles->hHeaderTimeDateSetupVals, 0, outString);
//		}
//	}
//	else if (sDateTemp.Month == 2) //���� �������
//	{
//		if ((sDateTemp.Year % 400 == 0 || (sDateTemp.Year % 4 == 0 && sDateTemp.Year % 100 != 0))) //���� ���������� ���
//		{
//			if (sDateTemp.Date > 29)
//			{
//				sDateTemp.Date = 29;
//				sprintf(outString, "%02d", sDateTemp.Date);
//				HEADER_SetItemText(masterClock.handles->hHeaderTimeDateSetupVals, 0, outString);
//			}
//		}
//		else
//
//		{
//			if (sDateTemp.Date > 28)
//			{
//				sDateTemp.Date = 28;
//				sprintf(outString, "%02d", sDateTemp.Date);
//				HEADER_SetItemText(masterClock.handles->hHeaderTimeDateSetupVals, 0, outString);
//			}
//		}
//	}
//}
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
	WM_HWIN hItem;
	int     NCode;
	int     Id;
	char date[3];
	uint8_t valsChangedOld = false;

	// USER START (Optionally insert additional variables)
	// USER END

	switch (pMsg->MsgId) {
	case WM_INIT_DIALOG:
		//
		// Initialization of 'Main Window'
		//
		sDateTemp = sDate;
		hItem = pMsg->hWin;
		WINDOW_SetBkColor(hItem, 0x191615);
		//
	// Initialization of 'Header'
	//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_HEADER_DTS_DMY);
		HEADER_AddItem(hItem, 80, "����", 14);
		HEADER_AddItem(hItem, 80, "�����", 14);
		HEADER_AddItem(hItem, 80, "���", 14);
		HEADER_SetTextColor(hItem, GUI_WHITE);
		//
		// Initialization of 'Header'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_HEADER_DTS_VALS);
		HEADER_AddItem(hItem, 80, "18", 14);
		HEADER_AddItem(hItem, 80, "43", 14);
		HEADER_AddItem(hItem, 80, "54", 14);
		HEADER_SetTextColor(hItem, GUI_WHITE);
		masterClock.handles->hHeaderTimeDateSetupVals = hItem;
		sprintf(date, "%02d", sDateTemp.Date);
		HEADER_SetItemText(masterClock.handles->hHeaderTimeDateSetupVals, 0, date);
		sprintf(date, "%02d", sDateTemp.Month);
		HEADER_SetItemText(masterClock.handles->hHeaderTimeDateSetupVals, 1, date);
		sprintf(date, "%02d", sDateTemp.Year);
		HEADER_SetItemText(masterClock.handles->hHeaderTimeDateSetupVals, 2, date);
		HEADER_SetTextColor(masterClock.handles->hHeaderTimeDateSetupVals, GUI_WHITE);
		//
		// Initialization of 'Header'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_HEADER_DTS);
		HEADER_AddItem(hItem, 240, "��������� ������� ����", 14);
		HEADER_SetTextColor(hItem, GUI_WHITE);
		// USER START (Optionally insert additional code for further widget initialization)


		// USER END
		break;
	case MENU_STATE_TIMEDATESETUP:
		sDateTemp = sDate;
		break;

	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (Id) {
		case ID_BUTTON_DTS_Dplus: // Notifications sent by 'd+'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)
				masterClock.guiVars->timeFrozen = 1;
				if (sDateTemp.Date != getLastDayOfMonth(&sDateTemp))
				{
					pollButton(ID_BUTTON_DTS_Dplus, WM_NOTIFICATION_CLICKED, (int8_t*)&sDateTemp.Date);
				}
				else
				{
					masterClock.longPressCNT->value = getLastDayOfMonth(&sDateTemp);
				}
				if (valsChangedOld != masterClock.guiVars->valsChanged)
				{
					WM_Invalidate(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_DTS_ENTER));
				}
				// USER END
				break;
			case WM_NOTIFICATION_RELEASED:
				// USER START (Optionally insert code for reacting on notification message)	
				pollButton(ID_BUTTON_DTS_Dplus, WM_NOTIFICATION_RELEASED, (int8_t*)&sDateTemp.Date);
				// USER END
				break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
			}
			break;

		case ID_BUTTON_DTS_Mplus: // Notifications sent by 'm+'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)
				masterClock.guiVars->timeFrozen = 1;
				if (sDateTemp.Date != 12)
				{
					pollButton(ID_BUTTON_DTS_Mplus, WM_NOTIFICATION_CLICKED, (int8_t*)&sDateTemp.Month);
				}
				else
				{
					masterClock.longPressCNT->value = 12;
				}
				if (valsChangedOld != masterClock.guiVars->valsChanged)
				{
					WM_Invalidate(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_DTS_ENTER));
				}
				// USER END
				break;
			case WM_NOTIFICATION_RELEASED:
				// USER START (Optionally insert code for reacting on notification message)
				pollButton(ID_BUTTON_DTS_Mplus, WM_NOTIFICATION_RELEASED, (int8_t*)&sDateTemp.Month);
				correctDate(&sDateTemp);
				sprintf(date, "%02d", sDateTemp.Date);
				HEADER_SetItemText(masterClock.handles->hHeaderTimeDateSetupVals, 0, date);
				HEADER_SetTextColor(masterClock.handles->hHeaderTimeDateSetupVals, GUI_WHITE);
				// USER END
				break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
			}
			break;
		case ID_BUTTON_DTS_Yplus: // Notifications sent by 'y+'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)
				masterClock.guiVars->timeFrozen = 1;
				if (sDateTemp.Date != 99)
				{
					pollButton(ID_BUTTON_DTS_Yplus, WM_NOTIFICATION_CLICKED, (int8_t*)&sDateTemp.Year);
				}
				else
				{
					masterClock.longPressCNT->value = 99;
				}
				if (valsChangedOld != masterClock.guiVars->valsChanged)
				{
					WM_Invalidate(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_DTS_ENTER));
				}
				// USER END
				break;
			case WM_NOTIFICATION_RELEASED:
				// USER START (Optionally insert code for reacting on notification message)
				pollButton(ID_BUTTON_DTS_Yplus, WM_NOTIFICATION_RELEASED, (int8_t*)&sDateTemp.Year);
				correctDate(&sDateTemp);
				sprintf(date, "%02d", sDateTemp.Date);
				HEADER_SetItemText(masterClock.handles->hHeaderTimeDateSetupVals, 0, date);
				HEADER_SetTextColor(masterClock.handles->hHeaderTimeDateSetupVals, GUI_WHITE);
				// USER END
				break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
			}
			break;
		case ID_BUTTON_DTS_ENTER: // Notifications sent by 'Enter'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)
				// USER END
				break;
			case WM_NOTIFICATION_RELEASED:
				// USER START (Optionally insert code for reacting on notification message)

				sDate = sDateTemp;
				sDateTemp.WeekDay = (sDateTemp.Date += sDateTemp.Month < 3 ? sDateTemp.Year-- : sDateTemp.Year - 2, 23 * sDateTemp.Month / 9 + sDateTemp.Date + 4 + sDateTemp.Year / 4 - sDateTemp.Year / 100 + sDateTemp.Year / 400) % 7;
				if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
				{
					while (1) {};
				}
				sendMsg(masterClock.handles->hTimeDateSetupMenu, WM_DATE_UPDATE);
				masterClock.guiVars->valsChanged = false;
				masterClock.guiVars->timeFrozen = false;
				sDateTemp = sDate;
				saveDateToBKP();
				// USER END
				break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
			}
			break;
		case ID_BUTTON_DTS_Dminus: // Notifications sent by 'd-'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)
				masterClock.guiVars->timeFrozen = 1;
				if (sDateTemp.Date != 0)
				{
					pollButton(ID_BUTTON_DTS_Dminus, WM_NOTIFICATION_CLICKED, (int8_t*)&sDateTemp.Date);
				}

				if (valsChangedOld != masterClock.guiVars->valsChanged)
				{
					WM_Invalidate(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_DTS_ENTER));
				}
				// USER END
				break;
			case WM_NOTIFICATION_RELEASED:
				// USER START (Optionally insert code for reacting on notification message)
				pollButton(ID_BUTTON_DTS_Dminus, WM_NOTIFICATION_RELEASED, (int8_t*)&sDateTemp.Date);
				// USER END
				break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
			}
			break;
		case ID_BUTTON_DTS_Mminus: // Notifications sent by 'm-'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)
				masterClock.guiVars->timeFrozen = 1;
				if (sDateTemp.Date != 0)
				{
					pollButton(ID_BUTTON_DTS_Mminus, WM_NOTIFICATION_CLICKED, (int8_t*)&sDateTemp.Month);
				}
				if (valsChangedOld != masterClock.guiVars->valsChanged)
				{
					WM_Invalidate(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_DTS_ENTER));
				}
				// USER END
				break;
			case WM_NOTIFICATION_RELEASED:
				// USER START (Optionally insert code for reacting on notification message)
				pollButton(ID_BUTTON_DTS_Mminus, WM_NOTIFICATION_RELEASED, (int8_t*)&sDateTemp.Month);
				correctDate(&sDateTemp);
				sprintf(date, "%02d", sDateTemp.Date);
				HEADER_SetItemText(masterClock.handles->hHeaderTimeDateSetupVals, 0, date);
				HEADER_SetTextColor(masterClock.handles->hHeaderTimeDateSetupVals, GUI_WHITE);
				// USER END
				break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
			}
			break;
		case ID_BUTTON_DTS_Yminus: // Notifications sent by 'y-'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)
				masterClock.guiVars->timeFrozen = 1;
				if (sDateTemp.Date != 0)
				{
					pollButton(ID_BUTTON_DTS_Yminus, WM_NOTIFICATION_CLICKED, (int8_t*)&sDateTemp.Year);
				}
				if (valsChangedOld != masterClock.guiVars->valsChanged)
				{
					WM_Invalidate(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_DTS_ENTER));
				}
				// USER END
				break;
			case WM_NOTIFICATION_RELEASED:
				// USER START (Optionally insert code for reacting on notification message)
				pollButton(ID_BUTTON_DTS_Yminus, WM_NOTIFICATION_RELEASED, (int8_t*)&sDateTemp.Year);
				correctDate(&sDateTemp);
				sprintf(date, "%02d", sDateTemp.Date);
				HEADER_SetItemText(masterClock.handles->hHeaderTimeDateSetupVals, 0, date);
				HEADER_SetTextColor(masterClock.handles->hHeaderTimeDateSetupVals, GUI_WHITE);
				// USER END
				break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
			}
			break;
		case ID_BUTTON_DTS_BACK: // Notifications sent by 'Back'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)
				// USER END
				break;
			case WM_NOTIFICATION_RELEASED:
				// USER START (Optionally insert code for reacting on notification message)
				masterClock.guiVars->menuState = MENU_STATE_TIMESETUP;
				masterClock.guiVars->valsChanged = false;
				CreateTimeSetupWindow();
				WM_DeleteWindow(pMsg->hWin);

				// USER END
				break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
			}
			break;

			// USER START (Optionally insert additional code for further Ids)
			// USER END
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
WM_HWIN CreateTimeDateWindow(void) {
	WM_HWIN hWin;

	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
	masterClock.handles->hTimeDateSetupMenu = hWin;
	BUTTON_SetDefaultFont(&GUI_FontArial18);
	WM_SetCallback(WM_GetDialogItem(hWin, ID_BUTTON_DTS_Dplus), _cbArrowUpButton);
	WM_SetCallback(WM_GetDialogItem(hWin, ID_BUTTON_DTS_Mplus), _cbArrowUpButton);
	WM_SetCallback(WM_GetDialogItem(hWin, ID_BUTTON_DTS_Yplus), _cbArrowUpButton);
	WM_SetCallback(WM_GetDialogItem(hWin, ID_BUTTON_DTS_Dminus), _cbArrowDownButton);
	WM_SetCallback(WM_GetDialogItem(hWin, ID_BUTTON_DTS_Mminus), _cbArrowDownButton);
	WM_SetCallback(WM_GetDialogItem(hWin, ID_BUTTON_DTS_Yminus), _cbArrowDownButton);
	masterClock.handles->hButtonDTSenter = WM_GetDialogItem(hWin, ID_BUTTON_DTS_ENTER);
	WM_SetCallback(masterClock.handles->hButtonDTSenter, _cbEnterButton);
	return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
