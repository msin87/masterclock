#ifndef TIMECALIBRATE_H
#define TIMECALIBRATE_H	
#define ID_WINDOW_TIMECALIBRATE   (GUI_ID_USER + 0x30)
#define ID_BUTTON_TIMECALIBRATE_SECplus   (GUI_ID_USER + 0x31)
#define ID_HEADER_TIMECALIBRATE_2ND_LINE   (GUI_ID_USER + 0x32)
#define ID_HEADER_TIMECALIBRATE_VALS   (GUI_ID_USER + 0x33)
#define ID_BUTTON_TIMECALIBRATE_DAYplus   (GUI_ID_USER + 0x35)
#define ID_BUTTON_TIMECALIBRATE_ENTER   (GUI_ID_USER + 0x36)
#define ID_BUTTON_TIMECALIBRATE_SECminus   (GUI_ID_USER + 0x37)
#define ID_BUTTON_TIMECALIBRATE_DAYminus   (GUI_ID_USER + 0x39)
#define ID_BUTTON_TIMECALIBRATE_BACK   (GUI_ID_USER + 0x3A)
#define ID_HEADER_TIMECALIBRATE   (GUI_ID_USER + 0x3B)
#define ID_BUTTON_TIMECALIBRATE_SUMWIN (GUI_ID_USER + 0x3C)
#include "DIALOG.h"
#include "guivars.h"
#include "string.h"
#include "stdio.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "callbacks.h"
#include "TimeSetup.h"
#include "sram.h"
#include "TimeSumWinSetup.h"
WM_HWIN CreateTimeCalibrateWindow(void);
extern GUI_Vars gui_Vars;
extern Handles handles;
extern TimeCalibration timeCalibr;
#endif
