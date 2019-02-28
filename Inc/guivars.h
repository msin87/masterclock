#ifndef GUIVARS_H
#define GUIVARS_H
#define GUI_BACKGROUND_COLOR 0x191615


#include "cmsis_os.h"
#include "DIALOG.h"
#include "stm32f1xx_hal.h"

#define MENU_STATE_MAIN 0
#define MENU_STATE_TIMESETUP 1
#define MENU_STATE_TIMEDATESETUP 2
#define MENU_STATE_TIMECALIBRATION 3
#define MENU_STATE_LINE1SETUP 4
#define MENU_STATE_LINE2SETUP 5
#define MENU_STATE_LINE3SETUP 6
#define MENU_STATE_LINE4SETUP 7
#define MENU_STATE_LINE1SETUP_PULSE 8
#define MENU_STATE_LINE2SETUP_PULSE 9
#define MENU_STATE_LINE3SETUP_PULSE 10
#define MENU_STATE_LINE4SETUP_PULSE 11
#define MENU_STATE_TIME_SUMWIN 12

#define LINES_AMOUNT 4
#define LINES_DEAD_TIME 50
#define LINE_WIDTH_MULT 375
#define LINE_STATUS_OFF  0
#define LINE_STATUS_RUN  1
#define LINE_STATUS_STOP 2
#define BKP_DATE_OFFSET 1
#define BKP_LINE1_OFFSET BKP_DATE_OFFSET+1
#define BKP_LINE2_OFFSET BKP_LINE1_OFFSET+1
#define BKP_LINE3_OFFSET BKP_LINE2_OFFSET+1
#define BKP_LINE4_OFFSET BKP_LINE3_OFFSET+1

#define BKP_DAYLIGHTSAVING_OFFSET BKP_LINE4_OFFSET+1

#define BKP_TIMECALIBR_OFFSET BKP_DAYLIGHTSAVING_OFFSET + 1
#define BKP_LINESPOLARITY_OFFSET BKP_DAYLIGHTSAVING_OFFSET

#define BKP_LINES_TIMEZONE_OFFSET BKP_TIMECALIBR_OFFSET+1


#define BKP_CRC_OFFSET_HIGH BKP_LINES_TIMEZONE_OFFSET+1
#define BKP_CRC_OFFSET_LOW BKP_CRC_OFFSET_HIGH+1


#define FLASH_CALIA_OFFSET 0x0807F800 + 0
#define FLASH_CALIB_OFFSET 0x0807F800 + 4
#define FLASH_CALIC_OFFSET 0x0807F800 + 8
#define FLASH_CALID_OFFSET 0x0807F800 + 12
#define FLASH_CALIE_OFFSET 0x0807F800 + 16
#define FLASH_CALIF_OFFSET 0x0807F800 + 20
#define FLASH_CRC_OFFSET 0x0807F800 + 24

typedef struct
{
	uint8_t menuLocked;
	uint8_t menuState;
	uint8_t prevSecond_L;
	uint8_t prevSecond_H;
	uint8_t prevHour;
	uint8_t timeFrozen;
	uint8_t valsChanged;
	uint8_t linesPolarity;
	uint8_t linesTimeChanged;
	int16_t	diffSystemLine;

} GUI_Vars;
typedef struct
{
	int16_t value;
	int16_t upperLimit;
	int16_t lowerLimit;
	int8_t direction;
	HEADER_Handle header;
	BUTTON_Handle button;
	uint8_t headerItem;
	uint8_t it;
	uint8_t itPrev;
	uint8_t itCNT;

} LongPressCNT;
typedef struct
{
	int8_t seconds;
	uint8_t days;
	uint8_t daysPassed;
	uint8_t isCalibrated;
} TimeCalibration;
typedef struct
{
	WM_HWIN hMainMenu;
	WM_HWIN hTimeSetupMenu;
	WM_HWIN hTimeDateSetupMenu;
	WM_HWIN hTimeCalibrateMenu;
	WM_HWIN hTimeSumWinSetupMenu;
	WM_HWIN hLineSetupMenu;
	WM_HWIN hLineSetupPulseMenu;
	WM_HWIN hBottomMenu;
	WM_HWIN hHourMinString;
	WM_HWIN hSecondsString_H;
	WM_HWIN hSecondsString_L;

	HEADER_Handle hHeaderTimeSetupVals;
	HEADER_Handle hHeaderTimeDateSetupVals;
	HEADER_Handle hHeaderTimeCalibrVals;
	HEADER_Handle hHeaderSumWinSetupVals;
	HEADER_Handle hLocalTimeNames;
	HEADER_Handle hLocalTimeHMS;

	BUTTON_Handle hButtonLine[4];
	BUTTON_Handle hButtonDTSenter;


	TEXT_Handle hLineSetupVals;


	FRAMEWIN_Handle hLocalTimeSeupWindow;



} Handles;
typedef struct
{

	int8_t Hours;
	int8_t Minutes;
	uint8_t Status;
	uint8_t Width;
	uint8_t Polarity;
	int16_t	Pulses;
	int8_t TimeZone;
	GPIO_TypeDef* LineGPIOpos;
	GPIO_TypeDef* LineGPIOneg;
	uint32_t LinePinPos;
	uint32_t LinePinNeg;
	SemaphoreHandle_t xSemaphore;
	uint32_t *pTemp;
	// 15    14    13    12   11   10    9    8    7    6    5    4    3    2    1    0
	// \status/		\---width--/	\--------------------hours*minutes-----------------/	
	//    |				  |										|
	//	  0 = STOP		  |										|
	//	  1 = RUN		  |										|
	//				 (0..7)*375	= 0,375...3000 sec. 			|
	//					0 sec = line status OFF					|
	//													1440 minutes (1 day)			
} Lines;

typedef struct
{
	char timeZone;
	char timeShift;
	char enableDLS;
	char needToShift;

} DaylightSaving;
typedef struct
{
	uint8_t DMAtransferComplete;
	uint16_t ADCdata[20];
	uint32_t currentLevel;
	void(*startCurrentSense)(void);
	void(*stopCurrentSense)(void);
	
}
CurrentSense;
typedef struct
{
	GUI_Vars* guiVars;
	LongPressCNT* longPressCNT;
	TimeCalibration* timeCalibration;
	Handles* handles;
	CurrentSense* currentSense;
	Lines line[4];
	DaylightSaving* daylightSaving;
} MasterClock;

MasterClock masterClock;
void sendMsg(WM_HWIN handle, uint16_t message);
void sendMsg_struct(WM_HWIN handle, WM_MESSAGE* msgStruct);

void initStructures(void);
#endif

