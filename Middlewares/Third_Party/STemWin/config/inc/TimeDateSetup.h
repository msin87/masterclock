#ifndef TIMEDATE_H
#define TIMEDATE_H	
#define ID_WINDOW_DATETIMESETUP   (GUI_ID_USER + 0x40)
#define ID_BUTTON_DTS_Dplus   (GUI_ID_USER + 0x41)
#define ID_HEADER_DTS_DMY   (GUI_ID_USER + 0x42)
#define ID_HEADER_DTS_VALS   (GUI_ID_USER + 0x43)
#define ID_BUTTON_DTS_Mplus   (GUI_ID_USER + 0x44)
#define ID_BUTTON_DTS_Yplus   (GUI_ID_USER + 0x45)
#define ID_BUTTON_DTS_Mminus     (GUI_ID_USER + 0x46)
#define ID_BUTTON_DTS_Yminus   (GUI_ID_USER + 0x47)
#define ID_BUTTON_DTS_ENTER   (GUI_ID_USER + 0x48)
#define ID_BUTTON_DTS_Dminus   (GUI_ID_USER + 0x49)
#define ID_BUTTON_DTS_BACK    (GUI_ID_USER + 0x4A)
#define ID_HEADER_DTS   (GUI_ID_USER + 0x4B)
#include "DIALOG.h"
#include "callbacks.h"
#include "guivars.h"
#include "string.h"
#include "stdio.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "TimeSetup.h"
#include "sram.h"
WM_HWIN CreateTimeDateWindow(void);
extern GUI_Vars gui_Vars;
extern Handles handles;
extern RTC_DateTypeDef sDate;
#endif
