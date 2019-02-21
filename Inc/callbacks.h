#ifndef CALLBACKS_H
#define CALLBACKS_H

#define u8 uint8_t
#define u16 uint16_t
#include "DIALOG.h"
#include "cmsis_os.h"
#include "stm32f1xx_hal.h"
#include "guivars.h"
#include "lcdcmd.h"
#include "TimeSetup.h"
#include "TimeDateSetup.h"
#include "TimeCalibrate.h"
#include "LineSetupPulse.h"
#include "LineSetup.h"
void _cbArrowUpButton(WM_MESSAGE * pMsg);
void _cbArrowDownButton(WM_MESSAGE * pMsg);
void _cbEnterButton(WM_MESSAGE * pMsg);
void _cbLineSetupSystemTime(WM_MESSAGE * pMsg);
void _cbPulseSetupButton(WM_MESSAGE * pMsg);

int _DrawSkin_BUTTON_WORDWRAP(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);

void TFT_LineSetupShowString(uint16_t x, uint16_t y, char *p, uint8_t fontsize, uint16_t color);
void TFT_LineSetupShowChar(u16 x, u16 y, u8 num, uint8_t fontsize, u16 color);

extern RTC_TimeTypeDef sTime;


extern Lines line[4];
extern LineMessage lineMessage;
extern GUI_Vars gui_Vars;
extern DaylightSaving daylightSaving;
extern osMessageQId queueLCDLinesTimeHandle;
extern GUI_CONST_STORAGE GUI_CHARINFO GUI_FontArial18_CharInfo[192];
extern GUI_CONST_STORAGE GUI_FONT_PROP GUI_FontArial18_Prop2;
extern GUI_CONST_STORAGE GUI_FONT_PROP GUI_FontArial18_Prop1;

void pollButton(uint16_t id, uint8_t action, int8_t* val);

unsigned char isDaylightSavingTimeUS(unsigned char day, unsigned char month, unsigned char dow);
unsigned char isDaylightSavingTimeEU(unsigned char day, unsigned char month, unsigned char dow);

uint8_t increaseDay(RTC_DateTypeDef* Date);
void linesIncreaseMinute(uint8_t lineNumber);
uint8_t getLastDayOfMonth(RTC_DateTypeDef* Date);
void correctDate(RTC_DateTypeDef* Date);
uint8_t hoursToUTC(int8_t hours, int8_t timeZone);

void saveDateToBKP(void);
void saveLineToBKP(uint8_t lineNumber);
void saveDaylightSavingToBKP(void);
void readDaylightSavingFromBKP(void);
void saveTimeCalibrToBKP(void);
void readTimeCalibrFromBKP(void);
void saveLinesPolarityToBKP(void);
void readLinesPolarityFromBKP(void);

uint16_t get_sTimeLinesDiff(Lines* lineToCheck, uint8_t waitMinutes);

void pollLinesOutput(uint8_t waitMinutes);
void lineSendSignal(uint8_t lineNumber);

uint32_t calkCRCofFlash(void);
uint32_t calcCRCofBKP(void);
uint8_t isCRC_OK_BKP(void);
uint8_t isCRC_OK_Flash(void);



void flash_unlock(void);
void flash_lock(void);
uint8_t flash_ready(void);
void flash_erase_page(uint32_t address);
void flash_write(uint32_t address, uint32_t data);
uint32_t flash_read(uint32_t address);
void rtc_write_backup_reg(uint16_t BackupRegister, uint16_t data);
uint16_t rtc_read_backup_reg(uint16_t BackupRegister);
#endif
