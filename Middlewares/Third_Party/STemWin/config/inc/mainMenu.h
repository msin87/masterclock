#ifndef MAINMENU_H
#define MAINMENU_H	
#include "DIALOG.h"
#include "cmsis_os.h"
#include "stm32f1xx_hal.h"
#include "stdio.h"
#include "main.h"
#include "string.h"
#include "lcdcmd.h"
#include "arial18.h"
#include "LineSetup.h"
#include "LineSetupPulse.h"
#include "Password.h"
#include "TimeCalibrate.h"
#include "TimeDateSetup.h"
#include "TimeSetup.h"
#include "button76x76Skin.h"
#include "guivars.h"

	WM_HWIN CreateMainMenu(void);
	
	extern RTC_HandleTypeDef hrtc;
	extern RTC_TimeTypeDef sTime;
	extern RTC_DateTypeDef sDate;
	void TFT_ShowString(uint16_t x,uint16_t y,char *p,uint8_t fontsize, uint16_t color);
	void TFT_ReadBackground(uint16_t x, uint16_t y, uint8_t fontsize, uint16_t* backgroundBuffer);
	void TFT_MainMenu_ShowLineTime (void);
	void TFT_MainMenu_ShowLineTime_ex (uint8_t i);
	void TFT_MainMenu_ShowDate(void);
#endif
