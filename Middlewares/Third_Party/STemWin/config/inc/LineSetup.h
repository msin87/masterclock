#ifndef LINESETUP_H
#define LINESETUP_H	
#define ID_WINDOW_LINESETUP   (GUI_ID_USER + 0x50)
#define ID_BUTTON_LINESETUP_Hplus   (GUI_ID_USER + 0x51)
#define ID_HEADER_LINESETUP_VALSNAMES   (GUI_ID_USER + 0x52)
#define ID_HEADER_LINESETUP_VALS   (GUI_ID_USER + 0x53)
#define ID_BUTTON_LINESETUP_Mplus   (GUI_ID_USER + 0x54)
#define ID_BUTTON_LINESETUP_Splus   (GUI_ID_USER + 0x55)
#define ID_BUTTON_LINESETUP_ENTER   (GUI_ID_USER + 0x56)
#define ID_BUTTON_LINESETUP_RUNSTOP   (GUI_ID_USER + 0x57)
#define ID_BUTTON_LINESETUP_PULSE   (GUI_ID_USER + 0x58)
#define ID_BUTTON_LINESETUP_Hminus   (GUI_ID_USER + 0x59)
#define ID_BUTTON_LINESETUP_Mminus   (GUI_ID_USER + 0x5A)
#define ID_BUTTON_LINESETUP_Sminus   (GUI_ID_USER + 0x5B)
#define ID_BUTTON_LINESETUP_BACK   (GUI_ID_USER + 0x5C)
#define ID_HEADER_LINESETUP_STATVALS   (GUI_ID_USER + 0x5D)
#define ID_HEADER_LINESETUP_TOP   (GUI_ID_USER + 0x5E)
	#include "DIALOG.h"
	#include "guivars.h"
	#include "callbacks.h"
	#include "string.h"
	#include "stdio.h"
	#include "stm32f1xx_hal.h"
	#include "cmsis_os.h"
	#include "sram.h"
	#include "mainMenu.h"
	#include "LineSetupPulse.h"

	extern GUI_Vars gui_Vars;
	extern Lines line[4];
	extern RTC_TimeTypeDef sTime;
	extern LongPressCNT longPressCNT;
	extern TIM_HandleTypeDef htim7;
	WM_HWIN CreateLineSetupWindow(void);
#endif
