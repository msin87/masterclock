#include "lines.h"
#include "backup.h"
#include "timedate.h"
#include "main.h"
#define POLARITY_POSITIVE 1
#define POLARITY_NEGATIVE 0
extern RTC_TimeTypeDef sTime;
extern RTC_DateTypeDef sDate;
void lineSetupMenuUpdateVals(void)
{
	char str[3];
	sprintf(str, "%02d", masterClock.line[masterClock.guiVars->menuState - 4].Hours);
	HEADER_SetItemText(masterClock.handles->hLineSetupVals, 0, str);
	sprintf(str, "%02d", masterClock.line[masterClock.guiVars->menuState - 4].Minutes);
	HEADER_SetItemText(masterClock.handles->hLineSetupVals, 1, str);
	HEADER_SetTextColor(masterClock.handles->hLineSetupVals, GUI_WHITE);

}
void pollLinesOutput(uint8_t waitMinutes)
{
	uint16_t i = 0;
	uint8_t lineNum = 0;
	masterClock.guiVars->diffSystemLine = get_sTimeLinesDiff(&masterClock.line[0], waitMinutes);
	if (masterClock.guiVars->diffSystemLine > 0)
	{
		for (i = 0; i < masterClock.guiVars->diffSystemLine; i++)
		{
			for (lineNum = 0; lineNum < LINES_AMOUNT; ++lineNum)
			{
				if (masterClock.line[lineNum].Status == LINE_STATUS_RUN) xSemaphoreGive(masterClock.line[lineNum].xSemaphore);
			}
		}
	}
}
void pollGPIO(uint8_t lineNumber, uint8_t polarity)
{
	
	if (polarity == POLARITY_POSITIVE)
	{
		masterClock.currentSense->startCurrentSense();
		masterClock.line[lineNumber].LineGPIOpos->BSRR = masterClock.line[lineNumber].LinePinPos;            		//set
		osDelay(masterClock.line[lineNumber].Width * LINE_WIDTH_MULT);
		masterClock.line[lineNumber].LineGPIOpos->BSRR = masterClock.line[lineNumber].LinePinPos << 16;           //reset
		masterClock.currentSense->stopCurrentSense();
		osDelay(LINES_DEAD_TIME);
		return;
	}
	if (polarity == POLARITY_NEGATIVE)
	{
		masterClock.currentSense->startCurrentSense();
		masterClock.line[lineNumber].LineGPIOneg->BSRR = masterClock.line[lineNumber].LinePinNeg;         		//set
		osDelay(masterClock.line[lineNumber].Width * LINE_WIDTH_MULT);
		masterClock.line[lineNumber].LineGPIOneg->BSRR = masterClock.line[lineNumber].LinePinNeg << 16;           //reset
		masterClock.currentSense->stopCurrentSense();
		osDelay(LINES_DEAD_TIME);
	}
	
}
void lineSendSignal(uint8_t lineNumber)
{

	uint8_t outputMask = 1 << lineNumber;
	Lines *lTemp;
	uint16_t count = uxSemaphoreGetCount(masterClock.line[lineNumber].xSemaphore);

	if (masterClock.line[lineNumber].Status == LINE_STATUS_RUN)
	{
		masterClock.guiVars->linesPolarity ^= outputMask;
		linesIncreaseMinute(lineNumber);

		if (count == 0 && masterClock.line[lineNumber].pTemp)
		{
			lTemp = (Lines*)masterClock.line[lineNumber].pTemp;
			lTemp->Hours = masterClock.line[lineNumber].Hours;
			lTemp->Minutes = masterClock.line[lineNumber].Minutes;
		}
		if (masterClock.guiVars->menuState == lineNumber + 4)
			lineSetupMenuUpdateVals();
		WM_Invalidate(masterClock.handles->hButtonLine[lineNumber]);
		if (masterClock.guiVars->linesPolarity & outputMask)
		{
			pollGPIO(lineNumber, POLARITY_POSITIVE);
		}
		else
		{
			pollGPIO(lineNumber, POLARITY_NEGATIVE);
		}
		saveLinesPolarityToBKP();

	}
}
uint16_t get_sTimeLinesDiff(Lines* lineToCheck, uint8_t waitMinutes)
{
	int16_t diff_Min12 = 0;
	uint8_t sHour12 = 0, lHour12 = 0;
	int16_t sMinutes = 0, lMinutes = 0;
	sHour12 = hoursToUTC(sTime.Hours, masterClock.daylightSaving->timeZone) % 12;
	if (sHour12 == 0)
	{
		sHour12 = 12;
	}
	lHour12 = hoursToUTC(lineToCheck->Hours, lineToCheck->TimeZone) % 12;
	if (lHour12 == 0)
	{
		lHour12 = 12;
	}
	diff_Min12 = sHour12 * 60 + sTime.Minutes - (lHour12 * 60 + lineToCheck->Minutes);

	if (diff_Min12 < -waitMinutes)
	{

		diff_Min12 = 720 + diff_Min12;
	}
	sMinutes = hoursToUTC(sTime.Hours, masterClock.daylightSaving->timeZone) * 60 + sTime.Minutes;
	lMinutes = hoursToUTC(lineToCheck->Hours, lineToCheck->TimeZone) * 60 + lineToCheck->Minutes;
	if ((sMinutes - lMinutes >= 720))
	{
		lineToCheck->Hours += 12;
	}
	else
		if ((sMinutes - lMinutes) >= -720 && (sMinutes - lMinutes) < -waitMinutes)
	{
		lineToCheck->Hours -= 12;
		if (lineToCheck->Hours < 0) lineToCheck->Hours = -lineToCheck->Hours;
	}
	lineToCheck->Hours %= 24;
	return diff_Min12;
}
void linesIncreaseMinute(uint8_t lineNumber)
{
	uint8_t i = 0;

	if (lineNumber < LINES_AMOUNT)
	{
		i = lineNumber;
	}
	else
	{
		lineNumber--;
	}

	if (masterClock.line[i].Status == LINE_STATUS_RUN)	//если линия запущена, то делаем необходимые инкременты с проверками
		{

			masterClock.line[i].Minutes++;
			if (masterClock.line[i].Minutes == 60)
			{
				masterClock.line[i].Minutes = 0;
				masterClock.line[i].Hours++;

				if (masterClock.line[i].Hours == 24)
				{
					masterClock.line[i].Hours = 0;
				}
			}
		}
}
void LinesInit(void)
{
	uint8_t i = 0;
	uint16_t dataInBKP;
	uint16_t buff;
	//2 байта * 4 = 8 байт
	// 15    14    13    12   11   10    9    8    7    6    5    4    3    2    1    0
	// \status/		\---width--/	\--------------------hours*minutes-----------------/	
	//    |				  |										|
	//	  0 = STOP		  |										|
	//	  1 = RUN		  |										|
	//				 (0..7)*375	= 0,375...3000 sec. 			|
	//					0 sec = line status OFF					|
	//													1440 minutes (1 day)	
	masterClock.line[0].xSemaphore = xSemaphoreCreateCounting(720, 0);
	masterClock.line[1].xSemaphore = xSemaphoreCreateCounting(720, 0);
	masterClock.line[2].xSemaphore = xSemaphoreCreateCounting(720, 0);
	masterClock.line[3].xSemaphore = xSemaphoreCreateCounting(720, 0);

	masterClock.line[0].LineGPIOpos = LINE0_POS_OUTPUT_GPIO_Port;
	masterClock.line[0].LineGPIOneg = LINE0_NEG_OUTPUT_GPIO_Port;
	masterClock.line[0].LinePinPos = LINE0_POS_OUTPUT_Pin;
	masterClock.line[0].LinePinNeg = LINE0_NEG_OUTPUT_Pin;

	masterClock.line[1].LineGPIOpos = LINE1_POS_OUTPUT_GPIO_Port;
	masterClock.line[1].LineGPIOneg = LINE1_NEG_OUTPUT_GPIO_Port;
	masterClock.line[1].LinePinPos = LINE1_POS_OUTPUT_Pin;
	masterClock.line[1].LinePinNeg = LINE1_NEG_OUTPUT_Pin;

	masterClock.line[2].LineGPIOpos = LINE2_POS_OUTPUT_GPIO_Port;
	masterClock.line[2].LineGPIOneg = LINE2_NEG_OUTPUT_GPIO_Port;
	masterClock.line[2].LinePinPos = LINE2_POS_OUTPUT_Pin;
	masterClock.line[2].LinePinNeg = LINE2_NEG_OUTPUT_Pin;

	masterClock.line[3].LineGPIOpos = LINE3_POS_OUTPUT_GPIO_Port;
	masterClock.line[3].LineGPIOneg = LINE3_NEG_OUTPUT_GPIO_Port;
	masterClock.line[3].LinePinPos = LINE3_POS_OUTPUT_Pin;
	masterClock.line[3].LinePinNeg = LINE3_NEG_OUTPUT_Pin;

	for (i = 0; i < LINES_AMOUNT; ++i)
	{
		dataInBKP = rtc_read_backup_reg(i + BKP_LINE1_OFFSET);
		masterClock.line[i].Hours = (dataInBKP & 0b11111111111) / 60;
		masterClock.line[i].Minutes = (dataInBKP & 0b11111111111) % 60;
		masterClock.line[i].Width = (dataInBKP >> 11) & 0b111;
		masterClock.line[i].Status = (dataInBKP >> 14) & 0b11;
		//Проверка на ошибки, и если что, то все по нулям, и выкл линию. 
		if((masterClock.line[i].Hours > 23) || (masterClock.line[i].Minutes > 59) || (masterClock.line[i].Width > 15) || (masterClock.line[i].Status > 2))
		{
			masterClock.line[i].Minutes = 0;
			masterClock.line[i].Hours = 0;
			masterClock.line[i].Width = 0;
			masterClock.line[i].Status = LINE_STATUS_OFF;
		}

	}

	dataInBKP = rtc_read_backup_reg(BKP_LINES_TIMEZONE_OFFSET);
	for (i = 1; i < LINES_AMOUNT; ++i)
	{
		buff = (dataInBKP >> ((i - 1) * 5));
		if (buff & 0b10000)
		{
			masterClock.line[i].TimeZone = (char)(~(buff & 0b1111));
		}
		else
		{
			masterClock.line[i].TimeZone = (char)(buff & 0b1111);
		}
	}

	readDaylightSavingFromBKP();


	if (sTime.Hours == 1 && sTime.Minutes == 2 && sTime.Seconds == 30 && isDaylightSavingTimeEU(sDate.Date, sDate.Month, sDate.WeekDay))
	{
		doTimeCorrection = true;               //если время 01:02:00 и текущая дата - дата перехода на зимнее/летнее время
	}
	else
	{
		doTimeCorrection = false;
	}
	//Проверка отставания времени на Линии1 по отношению к системному времени, взятому из BKP


}
