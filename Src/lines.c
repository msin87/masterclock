#include "lines.h"
extern RTC_TimeTypeDef sTime;
extern MasterClock masterClock;
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
			masterClock.line[lineNumber].LineGPIOpos->BSRR = masterClock.line[lineNumber].LinePinPos;		//set
			osDelay(masterClock.line[lineNumber].Width * LINE_WIDTH_MULT);
			masterClock.line[lineNumber].LineGPIOpos->BSRR = masterClock.line[lineNumber].LinePinPos << 16; //reset
			osDelay(LINES_DEAD_TIME);
		}
		else
		{
			masterClock.line[lineNumber].LineGPIOneg->BSRR = masterClock.line[lineNumber].LinePinNeg;		//set
			osDelay(masterClock.line[lineNumber].Width * LINE_WIDTH_MULT);
			masterClock.line[lineNumber].LineGPIOneg->BSRR = masterClock.line[lineNumber].LinePinNeg << 16; //reset
			osDelay(LINES_DEAD_TIME);
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