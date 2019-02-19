#include "callbacks.h"

void saveDateToBKP(void)
{
	uint16_t write = 0;
	RTC_DateTypeDef Date;

	HAL_RTC_GetDate(&hrtc, &Date, RTC_FORMAT_BIN);
	write = Date.Date;
	write |= (Date.Month << 5);
	write |= (Date.Year << 9);
	rtc_write_backup_reg(BKP_DATE_OFFSET, write);
}
void _cbArrowUpButton(WM_MESSAGE * pMsg)
{
	GUI_RECT Rect;
	WM_GetClientRect(&Rect);
	uint8_t i = 0;

	switch (pMsg->MsgId) {

	case WM_PAINT:
		BUTTON_Callback(pMsg);
		GUI_SetColor(GUI_WHITE);
		if (WM_IsEnabled(pMsg->hWin))
		{
			for (i = 0; i < 20; i++)
			{
				GUI_DrawHLine(i + 25, 34 - i, 34 + i);
			}
		}
		break;

	default:
		BUTTON_Callback(pMsg);
		if (WM_IsEnabled(pMsg->hWin))
		{
			for (i = 0; i < 20; i++)
			{
				GUI_DrawHLine(i + 25, 34 - i, 34 + i);
			}
		}

		break;
	}
}
void _cbPulseSetupButton(WM_MESSAGE * pMsg)
{
	GUI_RECT Rect;
	WM_GetClientRect(&Rect);
	uint8_t i = 0;

	switch (pMsg->MsgId) {

	case WM_PAINT:
		BUTTON_Callback(pMsg);
		GUI_SetColor(GUI_WHITE);
		GUI_DrawHLine(22, 19, 29);
		GUI_DrawVLine(29, 5, 22);
		GUI_DrawHLine(5, 29, 39);
		GUI_DrawVLine(39, 5, 22);
		GUI_DrawHLine(22, 39, 49);
	default:
		BUTTON_Callback(pMsg);
		GUI_SetColor(GUI_WHITE);
		GUI_DrawHLine(22, 19, 29);
		GUI_DrawVLine(29, 5, 22);
		GUI_DrawHLine(5, 29, 39);
		GUI_DrawVLine(39, 5, 22);
		GUI_DrawHLine(22, 39, 49);
		break;
	}

}
void _cbArrowDownButton(WM_MESSAGE * pMsg)
{
	GUI_RECT Rect;
	WM_GetClientRect(&Rect);
	uint8_t i = 0;

	switch (pMsg->MsgId) {

	case WM_PAINT:
		BUTTON_Callback(pMsg);
		if (WM_IsEnabled(pMsg->hWin))
		{
			GUI_SetColor(GUI_WHITE);
			for (i = 0; i < 20; i++)
			{
				GUI_DrawHLine(45 - i, 34 - i, 34 + i);

			}
		}
	default:
		BUTTON_Callback(pMsg);
		if (WM_IsEnabled(pMsg->hWin))
		{
			GUI_SetColor(GUI_WHITE);
			for (i = 0; i < 20; i++)
			{
				GUI_DrawHLine(45 - i, 34 - i, 34 + i);
			}
		}

		break;
	}
}
void _cbEnterButton(WM_MESSAGE * pMsg)
{
	GUI_RECT Rect;
	WM_GetClientRect(&Rect);
	uint8_t i = 0;
	switch (pMsg->MsgId) {

	case WM_PAINT:
		BUTTON_Callback(pMsg);
		if (gui_Vars.valsChanged)
		{
			GUI_SetColor(0x282171);
			GUI_FillRect(5, 60, 65, 65);
		}
	default:
		BUTTON_Callback(pMsg);
		if (gui_Vars.valsChanged)
		{
			GUI_SetColor(0x282171);
			GUI_FillRect(5, 60, 65, 65);
		}

		break;
	}
}
void _cbLineSetupSystemTime(WM_MESSAGE * pMsg)
{
	GUI_RECT Rect;
	WM_GetClientRect(&Rect);
	uint8_t i = 0;
	char str[9];
	switch (pMsg->MsgId) {

	case WM_PAINT:
		HEADER_Callback(pMsg);
		sprintf(str, "%02d:%02d:%02d", sTime.Hours, sTime.Minutes, sTime.Seconds);
		TFT_LineSetupShowString(173, 17, str, 18, 0xFFFF);
		break;
	default:
		HEADER_Callback(pMsg);
		sprintf(str, "%02d:%02d:%02d", sTime.Hours, sTime.Minutes, sTime.Seconds);
		TFT_LineSetupShowString(173, 17, str, 18, 0xFFFF);
		break;
	}
}
int _DrawSkin_BUTTON_WORDWRAP(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) {
	char str[30];
	GUI_RECT pRect;
	const GUI_FONT * pFont;
	GUI_COLOR TextColor_Disabled, TextColor_Pressed, TextColor_Unpressed;
	int TextAlign;
	switch (pDrawItemInfo->Cmd) {
	case WIDGET_ITEM_DRAW_TEXT:
		// Get the coords of the button rect and decrease the rect width 
		// to avoid covering the button frame with the text 
		pRect.x0 = pDrawItemInfo->x0 + 4;
		pRect.y0 = pDrawItemInfo->y0;
		pRect.x1 = pDrawItemInfo->x1 - 4;
		pRect.y1 = pDrawItemInfo->y1;
		// Get the text of the button
		BUTTON_GetText(pDrawItemInfo->hWin, str, 30);
		// Get text align
		TextAlign = BUTTON_GetTextAlign(pDrawItemInfo->hWin);
		// Get font
		pFont = BUTTON_GetFont(pDrawItemInfo->hWin);
		// Get colors 
		TextColor_Disabled = BUTTON_GetTextColor(pDrawItemInfo->hWin, BUTTON_CI_DISABLED);
		TextColor_Pressed = BUTTON_GetTextColor(pDrawItemInfo->hWin, BUTTON_CI_PRESSED);
		TextColor_Unpressed = BUTTON_GetTextColor(pDrawItemInfo->hWin, BUTTON_CI_UNPRESSED);
		// Set font 
		GUI_SetFont(pFont);
		// If the button is enabled 
		if (WM_IsEnabled(pDrawItemInfo->hWin))
		{
			// Set color for pressed / unpressed state
			if (BUTTON_IsPressed(pDrawItemInfo->hWin))
				GUI_SetColor(TextColor_Pressed);
			else
				GUI_SetColor(TextColor_Unpressed);
		}
		else // Set color for disabled state
			GUI_SetColor(TextColor_Disabled);
		// Transparent mode
		GUI_SetTextMode(GUI_TM_TRANS);
		// Display the text using wrap mode word wise
		GUI_DispStringInRectWrap(str, &pRect, TextAlign, GUI_WRAPMODE_WORD);
		break;
	default:
		return BUTTON_DrawSkinFlex(pDrawItemInfo);
		break;
	}
	return 0;
}
void TFT_LineSetupShowChar(u16 x, u16 y, u8 num, uint8_t fontsize, u16 color)
{

	GUI_CHARINFO charinfo;
	u8 mask;
	//	uint16_t test=0;
	u8 pos, t, backgrline = 0, xlimit, step = 0;
	unsigned char* p;

	//num=num-0x20;
	charinfo = GUI_FontArial18_CharInfo[num];
	//if(x>MAX_CHAR_POSX||y>MAX_CHAR_POSY)return;
	//??¶??»????·?????µ????? 
	//??±?????

  //writeLCDCommand(32, y);
  //writeLCDCommand(33, y+11);

	Set_Work_Area(y, x, y + (charinfo.XSize - 1), x + fontsize);
	//for lgdp4531 lgdp4532
	//writeLCDCommand(0x0050, x); // Horizontal GRAM Start Address
	//writeLCDCommand(0x0051, x+fontsize); // Horizontal GRAM End Address
	//writeLCDCommand(0x0052, y); // Vertical GRAM Start Address
	//writeLCDCommand(0x0053, y+(charinfo.XSize-1)); // Vertical GRAM Start Address	 
	//writeLCDCommand(32, x); //lgdp4532
	//writeLCDCommand(33, y);	// lgdp4532

	//Lcd_Write_Reg(0x004e,x);
	//Lcd_Write_Reg(0x004f,y);
	Lcd_Write_Index(0x22);

	p = (unsigned char*)GUI_FontArial18_CharInfo[num].pData;

	if (charinfo.XSize < 9)
	{
		xlimit = charinfo.XSize;
	}
	else
	{
		xlimit = 8;
	}
	//  LCD_SetPos(x,x+5,y,y+11);//320x240


	   //;//µ?µ??«????µ??µ
	for (pos = 0; pos < fontsize*charinfo.BytesPerLine; pos++)
	{
		mask = 0x80;
		for (t = 0; t < xlimit; t++)
		{
			if (step == charinfo.XSize && (charinfo.XSize > 8))
			{
				step = 0;
				break;
			}
			if (p[pos] & mask)
			{
				Lcd_Write_Data(color);
			}
			else
			{

				Lcd_Write_Data(0x49E7);                 //°??«  

			}
			mask >>= 1;
			step++;
		}
		if (!((pos + 1) % charinfo.BytesPerLine))
		{
			backgrline++;
		}
	}
	//for LGDP4532
	x = 0;
	x |= 239 << 8;
	Set_Work_Area(0, 0, 319, 239);


}
void TFT_LineSetupShowString(uint16_t x, uint16_t y, char *p, uint8_t fontsize, uint16_t color)
{
	GUI_CHARINFO chinfo;
	uint8_t first1, first2, last1;
	first1 = GUI_FontArial18_Prop1.First;
	last1 = GUI_FontArial18_Prop1.Last;

	first2 = GUI_FontArial18_Prop2.First;
	char ch = '\0';

	while (*p != '\0')
	{
		//if(x>MAX_CHAR_POSX){x=0;y+=12;}
		//if(y>MAX_CHAR_POSY){y=x=0;}
		ch = (*p);
		if (ch > last1)
		{
			ch = *p - (first2 - last1 + first1 - 1);
			TFT_LineSetupShowChar(y, x, ch, fontsize, color);
		}
		else
		{
			ch = *p - first1;
			TFT_LineSetupShowChar(y, x, ch, fontsize, color);

		}
		chinfo = GUI_FontArial18_CharInfo[ch];

		x += chinfo.XSize;
		p++;
	}
}
unsigned char isDaylightSavingTimeUS(unsigned char day, unsigned char month, unsigned char dow)
{
	//January, february, and december are out.
	if (month < 3 || month > 11)
	{
		return false;
	}
	//April to October are in
	if (month > 3 && month < 11)
	{
		return true;
	}
	int previousSunday = day - dow;
	//In march, we are DST if our previous sunday was on or after the 8th.
	if (month == 3) { return previousSunday >= 8; }
	//In november we must be before the first sunday to be dst.
	//That means the previous sunday must be before the 1st.
	return previousSunday <= 0;
}
unsigned char isDaylightSavingTimeEU(unsigned char day, unsigned char month, unsigned char dow)
{
	if (month < 3 || month > 10)  return false;
	if (month > 3 && month < 10)  return true;

	int previousSunday = day - dow;

	if (month == 3) return previousSunday >= 25;
	if (month == 10) return previousSunday < 25;

	return false; // this line never gonna happend
}
void rtc_write_backup_reg(uint16_t BackupRegister, uint16_t data)
{
	uint32_t bkpCRC = 0;
	RTC_HandleTypeDef RtcHandle;
	RtcHandle.Instance = RTC;
	HAL_PWR_EnableBkUpAccess();
	HAL_RTCEx_BKUPWrite(&RtcHandle, BackupRegister, data);
	bkpCRC = calcCRCofBKP();                 //рассчет новой CRC для регистров BKP
	HAL_RTCEx_BKUPWrite(&RtcHandle, BKP_CRC_OFFSET_HIGH, bkpCRC >> 16);                 //запись старших 16 бит CRC (Маска 0xFFFF0000)
	HAL_RTCEx_BKUPWrite(&RtcHandle, BKP_CRC_OFFSET_LOW, bkpCRC & 0xFFFF);                 //запись младших 16 бит CRC


}
uint16_t rtc_read_backup_reg(uint16_t BackupRegister)
{
	RTC_HandleTypeDef RtcHandle;
	RtcHandle.Instance = RTC;
	return HAL_RTCEx_BKUPRead(&RtcHandle, BackupRegister);
}
uint32_t calcCRCofBKP(void)
{
	uint32_t dataInBKP[4] = { 0, 0, 0, 0 };
	dataInBKP[0] = rtc_read_backup_reg(BKP_DATE_OFFSET);                  //date
	dataInBKP[0] |= rtc_read_backup_reg(BKP_LINE1_OFFSET);                 //line 1
	dataInBKP[1] = rtc_read_backup_reg(BKP_LINE2_OFFSET);                  //line 2 
	dataInBKP[1] |= rtc_read_backup_reg(BKP_LINE3_OFFSET);                 //line 3
	dataInBKP[2] = rtc_read_backup_reg(BKP_LINE4_OFFSET);                  //line 4
	dataInBKP[2] |= rtc_read_backup_reg(BKP_DAYLIGHTSAVING_OFFSET);        //daylightsaving 8 бит из 16.
	dataInBKP[3] = rtc_read_backup_reg(BKP_TIMECALIBR_OFFSET);                 //

	CRC->CR |= CRC_CR_RESET;
	CRC->DR = dataInBKP[0];
	CRC->DR = dataInBKP[1];
	CRC->DR = dataInBKP[2];
	CRC->DR = dataInBKP[3];
	return CRC->DR;
}
uint32_t calkCRCofFlash(void)
{
	uint32_t dataInFLASH[6] = { 0, 0, 0, 0, 0, 0 };
	dataInFLASH[0] = flash_read(FLASH_CALIA_OFFSET);
	dataInFLASH[1] = flash_read(FLASH_CALIB_OFFSET);
	dataInFLASH[2] = flash_read(FLASH_CALIC_OFFSET);
	dataInFLASH[3] = flash_read(FLASH_CALID_OFFSET);
	dataInFLASH[4] = flash_read(FLASH_CALIE_OFFSET);
	dataInFLASH[5] = flash_read(FLASH_CALIF_OFFSET);
	CRC->CR |= CRC_CR_RESET;
	CRC->DR = dataInFLASH[0];
	CRC->DR = dataInFLASH[1];
	CRC->DR = dataInFLASH[2];
	CRC->DR = dataInFLASH[3];
	CRC->DR = dataInFLASH[4];
	CRC->DR = dataInFLASH[5];
	return CRC->DR;


}
uint8_t isCRC_OK_Flash(void)
{
	uint32_t CRCinFLASH = 0;
	CRCinFLASH = flash_read(FLASH_CRC_OFFSET);
	if (CRCinFLASH == calkCRCofFlash())
	{
		return 1;
	}
	else
	{
		return 0;
	}
	return 0;
}
uint8_t isCRC_OK_BKP(void)
{
	uint32_t CRCinBKP = 0;
	CRCinBKP = rtc_read_backup_reg(BKP_CRC_OFFSET_LOW);
	CRCinBKP |= (rtc_read_backup_reg(BKP_CRC_OFFSET_HIGH) << 16);
	if (CRCinBKP == calcCRCofBKP())
	{
		return 1;
	}
	else
	{
		return 0;
	}
	return 0;
}
void saveTimeCalibrToBKP(void)
{
	uint16_t writeBuff = 0;
	writeBuff = timeCalibr.days;
	writeBuff |= (timeCalibr.seconds << 8);
	//	15	14	13	12	11	10	9	8	7	6	5	4	3	2	1	0
	//  \----------seconds----------/    \---------days-------------/
	rtc_write_backup_reg(BKP_TIMECALIBR_OFFSET, writeBuff);
}
void saveLinesPolarityToBKP(void)
{
	uint16_t writeBuff = 0;
	writeBuff = rtc_read_backup_reg(BKP_DAYLIGHTSAVING_OFFSET);
	writeBuff &= 0x00FF;
	writeBuff |= (gui_Vars.linesPolarity << 8);
	rtc_write_backup_reg(BKP_LINESPOLARITY_OFFSET, writeBuff);

}
void readLinesPolarityFromBKP(void)
{
	uint16_t readBuff = 0;
	readBuff = rtc_read_backup_reg(BKP_DAYLIGHTSAVING_OFFSET);
	gui_Vars.linesPolarity = readBuff >> 8;
}
void readTimeCalibrFromBKP(void)
{
	uint16_t readBuff = 0;
	readBuff = rtc_read_backup_reg(BKP_TIMECALIBR_OFFSET);
	timeCalibr.days = readBuff & 0xFF;
	timeCalibr.seconds = (int8_t)(readBuff >> 8);
}
void saveLineToBKP(uint8_t lineNumber)
{

	rtc_write_backup_reg(lineNumber + BKP_LINE1_OFFSET, ((line[lineNumber].Hours * 60) + line[lineNumber].Minutes) | (line[lineNumber].Width << 11) | line[lineNumber].Status << 14);
}

void saveDaylightSavingToBKP(void)
{
	//daylight
	// 		7	6	5	4	3	2	1	0
	//		|	\---/	\----timezone---/
	//		|	  |			01111 = +16
	//		|	  |			10000 = -16
	//		|	  |
	//		|	TimeShift 
	//		|	 00 disable
	//		|	 01 +1
	//		|	 10	-1	
	//		|
	//		EnableDLS
	uint16_t dataToBKP = 0;

	if ((int8_t)daylightSaving.timeZone >= 0)
	{
		dataToBKP = daylightSaving.timeZone;
	}
	else
	{
		dataToBKP = (~(daylightSaving.timeZone)) & 0xFF;                 //если отрицательное, то инверсия и флаг отрицательного.
		dataToBKP |= 0b10000;
	}
	if (daylightSaving.timeShift < 0)
	{
		dataToBKP |= (0b10 << 5);                 //отрицательный флаг для timeShift
	}
	else
	{
		dataToBKP |= 1 << 5;
	}
	if (daylightSaving.enableDLS == true)
	{
		dataToBKP |= 1 << 7;
	}
	rtc_write_backup_reg(BKP_DAYLIGHTSAVING_OFFSET, dataToBKP);
}
void readDaylightSavingFromBKP(void)
{
	uint16_t dataInBKP = rtc_read_backup_reg(BKP_DAYLIGHTSAVING_OFFSET);
	if (dataInBKP & 0b10000) //если флаг отрицательного числа
	{
		daylightSaving.timeZone = (char)(~(dataInBKP & 0b1111));
	}
	else
	{
		daylightSaving.timeZone = (char)(dataInBKP & 0b1111);
	}
	if (dataInBKP & 0b1000000) //если отрицательный флаг
	{
		daylightSaving.timeShift = -1;

	}
	else
	{
		daylightSaving.timeShift = (dataInBKP >> 5) & 0b11;
	}
	daylightSaving.enableDLS = (dataInBKP >> 7);
}
uint8_t increaseDay(RTC_DateTypeDef* Date)
{
	if (Date->Month == 1 || Date->Month == 3 || Date->Month == 5 || Date->Month == 7 || Date->Month == 8 || Date->Month == 10 || Date->Month == 12)
	{
		if (Date->Date != 31)
		{
			Date->Date++;
		}
	}
	else if (Date->Month == 4 || Date->Month == 6 || Date->Month == 9 || Date->Month == 11)
	{
		if (Date->Date != 30)
		{
			Date->Date++;
		}
	}
	else if (Date->Month == 2) //Если февраль
	{
		if ((Date->Year % 400 == 0 || (Date->Year % 4 == 0 && Date->Year % 100 != 0))) //Если високосный год
		{
			if (Date->Date != 29)
			{
				Date->Date++;
			}
		}
		else

		{
			if (Date->Date != 28)
			{
				Date->Date++;
			}
		}
	}
}
uint8_t getLastDayOfMonth(RTC_DateTypeDef* Date)
{
	if (Date->Month == 1 || Date->Month == 3 || Date->Month == 5 || Date->Month == 7 || Date->Month == 8 || Date->Month == 10 || Date->Month == 12)
	{
		return 31;
	}
	else if (Date->Month == 4 || Date->Month == 6 || Date->Month == 9 || Date->Month == 11)
	{
		return 30;
	}
	else if (Date->Month == 2) //Если февраль
	{
		if ((Date->Year % 400 == 0 || (Date->Year % 4 == 0 && Date->Year % 100 != 0))) //Если високосный год
		{
			return 29;
		}
		else

		{
			return 28;
		}
	}
}
void correctDate(RTC_DateTypeDef* Date)
{
	if (Date->Date > 28)
	{
		char outString[3];
		if (Date->Month == 1 || Date->Month == 3 || Date->Month == 5 || Date->Month == 7 || Date->Month == 8 || Date->Month == 10 || Date->Month == 12)
		{
			if (Date->Date > 31)
			{
				Date->Date = 31;
				sprintf(outString, "%02d", Date->Date);
				HEADER_SetItemText(handles.hHeaderTimeDateSetupVals, 0, outString);
				HEADER_SetTextColor(handles.hHeaderTimeDateSetupVals, GUI_WHITE);
			}
		}
		else if (Date->Month == 4 || Date->Month == 6 || Date->Month == 9 || Date->Month == 11)
		{
			if (Date->Date > 30)
			{
				Date->Date = 30;
				sprintf(outString, "%02d", Date->Date);
				HEADER_SetItemText(handles.hHeaderTimeDateSetupVals, 0, outString);
				HEADER_SetTextColor(handles.hHeaderTimeDateSetupVals, GUI_WHITE);
			}
		}
		else if (Date->Month == 2) //Если февраль
		{
			if ((Date->Year % 400 == 0 || (Date->Year % 4 == 0 && Date->Year % 100 != 0))) //Если високосный год
			{
				if (Date->Date > 29)
				{
					Date->Date = 29;
					sprintf(outString, "%02d", Date->Date);
					HEADER_SetItemText(handles.hHeaderTimeDateSetupVals, 0, outString);
					HEADER_SetTextColor(handles.hHeaderTimeDateSetupVals, GUI_WHITE);
				}
			}
			else

			{
				if (Date->Date > 28)
				{
					Date->Date = 28;
					sprintf(outString, "%02d", Date->Date);
					HEADER_SetItemText(handles.hHeaderTimeDateSetupVals, 0, outString);
					HEADER_SetTextColor(handles.hHeaderTimeDateSetupVals, GUI_WHITE);

				}
			}
		}
	}
}
void flash_unlock(void) {
	FLASH->KEYR = FLASH_KEY1;
	FLASH->KEYR = FLASH_KEY2;
}
void flash_lock() {
	FLASH->CR |= FLASH_CR_LOCK;
}
uint8_t flash_ready(void) {
	return !(FLASH->SR & FLASH_SR_BSY);
}

void flash_write(uint32_t address, uint32_t data) {
	FLASH->CR |= FLASH_CR_PG;                 //Разрешаем программирование флеша
	while (!flash_ready());                 //Ожидаем готовности флеша к записи
	*(__IO uint16_t*)address = (uint16_t)data;                 //Пишем младшие 2 бата
	while (!flash_ready());
	address += 2;
	data >>= 16;
	*(__IO uint16_t*)address = (uint16_t)data;                 //Пишем старшие 2 байта
	while (!flash_ready());
	FLASH->CR &= ~(FLASH_CR_PG);                 //Запрещаем программирование флеша
}

void flash_erase_page(uint32_t address) {
	FLASH->CR |= FLASH_CR_PER;                 //Устанавливаем бит стирания одной страницы
	FLASH->AR = address;                 // Задаем её адрес
	FLASH->CR |= FLASH_CR_STRT;                 // Запускаем стирание 
	while (!flash_ready())
		;                  //Ждем пока страница сотрется. 
	FLASH->CR &= ~FLASH_CR_PER;                 //Сбрасываем бит обратно
}
uint32_t flash_read(uint32_t address) {
	return (*(__IO uint32_t*) address);
}

uint16_t get_sTimeLinesDiff(Lines* lineToCheck, uint8_t waitMinutes)
{
	int16_t diff_Min12 = 0;
	uint8_t sHour12 = 0, lHour12 = 0;
	int16_t sMinutes = 0, lMinutes = 0;
	sHour12 = sTime.Hours % 12;
	if (sHour12 == 0)
	{
		sHour12 = 12;
	}
	lHour12 = lineToCheck->Hours % 12;
	if (lHour12 == 0)
	{
		lHour12 = 12;
	}
	diff_Min12 = sHour12 * 60 + sTime.Minutes - (lHour12 * 60 + lineToCheck->Minutes);

	if (diff_Min12 < -waitMinutes)
	{

		diff_Min12 = 720 + diff_Min12;
	}
	sMinutes = sTime.Hours * 60 + sTime.Minutes;
	lMinutes = lineToCheck->Hours * 60 + lineToCheck->Minutes;
	if ((sMinutes - lMinutes >= 720))
	{
		lineToCheck->Hours += 12;
	}
	else
		if ((sMinutes - lMinutes) >= -720 && (sMinutes - lMinutes) < -waitMinutes)
		{
			lineToCheck->Hours -= 12;
		}

	return diff_Min12;
}
void pollLinesOutput(uint8_t waitMinutes)
{
	uint16_t i = 0;
	uint8_t lineNum = 0;
	gui_Vars.diffSystemLine = get_sTimeLinesDiff(&line[0], waitMinutes);
	if (gui_Vars.diffSystemLine > 0)
	{
		for (i = 0; i < gui_Vars.diffSystemLine; i++)
		{
			for (lineNum = 0; lineNum < LINES_AMOUNT; ++lineNum)
			{
				if (line[lineNum].Status == LINE_STATUS_RUN) xSemaphoreGive(line[lineNum].xSemaphore);
			}
		}
	}
}

void lineSendSignal(uint8_t lineNumber)
{
	uint8_t outputMask = 1 << lineNumber;
	if (line[lineNumber].Status == LINE_STATUS_RUN)
	{
		gui_Vars.linesPolarity ^= outputMask;
		linesIncreaseMinute(lineNumber);
		WM_Invalidate(handles.hButtonLine[lineNumber]);
		if (gui_Vars.linesPolarity & outputMask)
		{
			line[lineNumber].LineGPIOpos->BSRR = line[lineNumber].LinePinPos;		//set
			osDelay(line[lineNumber].Width * LINE_WIDTH_MULT);
			line[lineNumber].LineGPIOpos->BSRR = line[lineNumber].LinePinPos << 16; //reset
			osDelay(LINES_DEAD_TIME);
		}
		else
		{
			line[lineNumber].LineGPIOneg->BSRR = line[lineNumber].LinePinNeg;		//set
			osDelay(line[lineNumber].Width * LINE_WIDTH_MULT);
			line[lineNumber].LineGPIOneg->BSRR = line[lineNumber].LinePinNeg << 16; //reset
			osDelay(LINES_DEAD_TIME);
		}
		saveLinesPolarityToBKP();

	}
}
void linesIncreaseMinute(uint8_t lineNumber)
{
	uint8_t i = 0;
	char str[3];
	if (lineNumber < LINES_AMOUNT)
	{
		i = lineNumber;
	}
	else
	{
		lineNumber--;
	}

	if (line[i].Status == LINE_STATUS_RUN)	//если линия запущена, то делаем необходимые инкременты с проверками
	{

		line[i].Minutes++;
		if (line[i].Minutes == 60)
		{
			line[i].Minutes = 0;
			line[i].Hours++;

			if (line[i].Hours == 24)
			{
				line[i].Hours = 0;
			}
		}

		saveLineToBKP(i);
	}
}
void pollButton(uint16_t id, uint8_t action, int8_t* val)
{
	char str[5];
	if (action == WM_NOTIFICATION_CLICKED)
	{
		switch (id)
		{
		case ID_BUTTON_LINESETUP_Hminus:
			longPressCNT.direction = -1;
			longPressCNT.lowerLimit = 0;
			longPressCNT.itCNT = 0;
			longPressCNT.value = *val - 1;
			longPressCNT.header = WM_GetDialogItem(handles.hLineSetupMenu, ID_HEADER_LINESETUP_VALS);
			longPressCNT.headerItem = 0;
			longPressCNT.button = WM_GetDialogItem(handles.hLineSetupMenu, ID_BUTTON_LINESETUP_Hminus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", longPressCNT.value);
			HEADER_SetItemText(longPressCNT.header, longPressCNT.headerItem, str);
			HEADER_SetTextColor(longPressCNT.header, GUI_WHITE);
			gui_Vars.valsChanged = true;
			break;
		case ID_BUTTON_LINESETUP_Mminus:
			longPressCNT.direction = -1;
			longPressCNT.lowerLimit = 0;
			longPressCNT.itCNT = 0;
			longPressCNT.value = *val - 1;
			longPressCNT.header = WM_GetDialogItem(handles.hLineSetupMenu, ID_HEADER_LINESETUP_VALS);
			longPressCNT.headerItem = 1;
			longPressCNT.button = WM_GetDialogItem(handles.hLineSetupMenu, ID_BUTTON_LINESETUP_Mminus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", longPressCNT.value);
			HEADER_SetItemText(longPressCNT.header, longPressCNT.headerItem, str);
			HEADER_SetTextColor(longPressCNT.header, GUI_WHITE);
			gui_Vars.valsChanged = true;
			break;
		case ID_BUTTON_LINESETUP_Hplus:
			longPressCNT.direction = 1;
			longPressCNT.upperLimit = 23;
			longPressCNT.itCNT = 0;
			longPressCNT.value = *val + 1;
			longPressCNT.header = WM_GetDialogItem(handles.hLineSetupMenu, ID_HEADER_LINESETUP_VALS);
			longPressCNT.headerItem = 0;
			longPressCNT.button = WM_GetDialogItem(handles.hLineSetupMenu, ID_BUTTON_LINESETUP_Hplus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", longPressCNT.value);
			HEADER_SetItemText(longPressCNT.header, longPressCNT.headerItem, str);
			HEADER_SetTextColor(longPressCNT.header, GUI_WHITE);
			gui_Vars.valsChanged = true;
			break;
		case ID_BUTTON_LINESETUP_Mplus:
			longPressCNT.direction = 1;
			longPressCNT.upperLimit = 59;
			longPressCNT.itCNT = 0;
			longPressCNT.value = *val + 1;
			longPressCNT.header = WM_GetDialogItem(handles.hLineSetupMenu, ID_HEADER_LINESETUP_VALS);
			longPressCNT.headerItem = 1;
			longPressCNT.button = WM_GetDialogItem(handles.hLineSetupMenu, ID_BUTTON_LINESETUP_Mplus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", longPressCNT.value);
			HEADER_SetItemText(longPressCNT.header, longPressCNT.headerItem, str);
			HEADER_SetTextColor(longPressCNT.header, GUI_WHITE);
			gui_Vars.valsChanged = true;
			break;
			//vv TIMESETUP vv
		case ID_BUTTON_HOURplus:
			longPressCNT.direction = 1;
			longPressCNT.upperLimit = 23;
			longPressCNT.itCNT = 0;
			longPressCNT.value = *val + 1;
			longPressCNT.header = WM_GetDialogItem(handles.hTimeSetupMenu, ID_HEADER_HMS_VALUE);
			longPressCNT.headerItem = 0;
			longPressCNT.button = WM_GetDialogItem(handles.hTimeSetupMenu, ID_BUTTON_HOURplus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", longPressCNT.value);
			HEADER_SetItemText(longPressCNT.header, longPressCNT.headerItem, str);
			HEADER_SetTextColor(longPressCNT.header, GUI_WHITE);
			gui_Vars.valsChanged = true;
			break;
			break;
		case ID_BUTTON_MINplus:
			longPressCNT.direction = 1;
			longPressCNT.upperLimit = 59;
			longPressCNT.itCNT = 0;
			longPressCNT.value = *val + 1;
			longPressCNT.header = WM_GetDialogItem(handles.hTimeSetupMenu, ID_HEADER_HMS_VALUE);
			longPressCNT.headerItem = 1;
			longPressCNT.button = WM_GetDialogItem(handles.hTimeSetupMenu, ID_BUTTON_MINplus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", longPressCNT.value);
			HEADER_SetItemText(longPressCNT.header, longPressCNT.headerItem, str);
			HEADER_SetTextColor(longPressCNT.header, GUI_WHITE);
			gui_Vars.valsChanged = true;
			break;
		case ID_BUTTON_SECplus:
			longPressCNT.direction = 1;
			longPressCNT.upperLimit = 59;
			longPressCNT.itCNT = 0;
			longPressCNT.value = *val + 1;
			longPressCNT.header = WM_GetDialogItem(handles.hTimeSetupMenu, ID_HEADER_HMS_VALUE);
			longPressCNT.headerItem = 2;
			longPressCNT.button = WM_GetDialogItem(handles.hTimeSetupMenu, ID_BUTTON_SECplus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", longPressCNT.value);
			HEADER_SetItemText(longPressCNT.header, longPressCNT.headerItem, str);
			HEADER_SetTextColor(longPressCNT.header, GUI_WHITE);
			gui_Vars.valsChanged = true;
			break;
		case ID_BUTTON_HOURminus:
			longPressCNT.direction = -1;
			longPressCNT.lowerLimit = 0;
			longPressCNT.itCNT = 0;
			longPressCNT.value = *val - 1;
			longPressCNT.header = WM_GetDialogItem(handles.hTimeSetupMenu, ID_HEADER_HMS_VALUE);
			longPressCNT.headerItem = 0;
			longPressCNT.button = WM_GetDialogItem(handles.hTimeSetupMenu, ID_BUTTON_HOURminus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", longPressCNT.value);
			HEADER_SetItemText(longPressCNT.header, longPressCNT.headerItem, str);
			HEADER_SetTextColor(longPressCNT.header, GUI_WHITE);
			gui_Vars.valsChanged = true;
			break;
		case ID_BUTTON_MINminus:
			longPressCNT.direction = -1;
			longPressCNT.lowerLimit = 0;
			longPressCNT.itCNT = 0;
			longPressCNT.value = *val - 1;
			longPressCNT.header = WM_GetDialogItem(handles.hTimeSetupMenu, ID_HEADER_HMS_VALUE);
			longPressCNT.headerItem = 1;
			longPressCNT.button = WM_GetDialogItem(handles.hTimeSetupMenu, ID_BUTTON_MINminus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", longPressCNT.value);
			HEADER_SetItemText(longPressCNT.header, longPressCNT.headerItem, str);
			HEADER_SetTextColor(longPressCNT.header, GUI_WHITE);
			gui_Vars.valsChanged = true;
			break;
		case ID_BUTTON_SECminus:
			longPressCNT.direction = -1;
			longPressCNT.lowerLimit = 0;
			longPressCNT.itCNT = 0;
			longPressCNT.value = *val - 1;
			longPressCNT.header = WM_GetDialogItem(handles.hTimeSetupMenu, ID_HEADER_HMS_VALUE);
			longPressCNT.headerItem = 2;
			longPressCNT.button = WM_GetDialogItem(handles.hTimeSetupMenu, ID_BUTTON_SECminus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", longPressCNT.value);
			HEADER_SetItemText(longPressCNT.header, longPressCNT.headerItem, str);
			HEADER_SetTextColor(longPressCNT.header, GUI_WHITE);
			gui_Vars.valsChanged = true;
			break;
		case ID_BUTTON_LINESETUP_PULSE_MSECplus:
			longPressCNT.direction = 1;
			longPressCNT.upperLimit = 15;
			longPressCNT.itCNT = 0;
			longPressCNT.value = *val + 1;
			longPressCNT.header = WM_GetDialogItem(handles.hLineSetupPulseMenu, ID_HEADER_LINESETUP_PULSE_VALS);
			longPressCNT.headerItem = 0;
			longPressCNT.button = WM_GetDialogItem(handles.hLineSetupPulseMenu, ID_BUTTON_LINESETUP_PULSE_MSECplus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%4d", longPressCNT.value * LINE_WIDTH_MULT);
			HEADER_SetItemText(longPressCNT.header, longPressCNT.headerItem, str);
			HEADER_SetTextColor(longPressCNT.header, GUI_WHITE);
			gui_Vars.valsChanged = true;
			break;
		case ID_BUTTON_LINESETUP_PULSE_MSECminus:
			longPressCNT.direction = -1;
			longPressCNT.lowerLimit = 0;
			longPressCNT.itCNT = 0;
			longPressCNT.value = *val - 1;
			longPressCNT.header = WM_GetDialogItem(handles.hLineSetupPulseMenu, ID_HEADER_LINESETUP_PULSE_VALS);
			longPressCNT.headerItem = 0;
			longPressCNT.button = WM_GetDialogItem(handles.hLineSetupPulseMenu, ID_BUTTON_LINESETUP_PULSE_MSECminus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%4d", longPressCNT.value * LINE_WIDTH_MULT);
			HEADER_SetItemText(longPressCNT.header, longPressCNT.headerItem, str);
			HEADER_SetTextColor(longPressCNT.header, GUI_WHITE);
			gui_Vars.valsChanged = true;
			break;
		case ID_BUTTON_SUMWINSETUP_Zplus:
			longPressCNT.direction = 1;
			longPressCNT.upperLimit = 12;
			longPressCNT.itCNT = 0;
			longPressCNT.value = *val + 1;
			longPressCNT.header = WM_GetDialogItem(handles.hTimeSumWinSetupMenu, ID_HEADER_SUMWINSETUP_VALS);
			longPressCNT.headerItem = 0;
			longPressCNT.button = WM_GetDialogItem(handles.hTimeSumWinSetupMenu, ID_BUTTON_SUMWINSETUP_Zplus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			if (longPressCNT.value > 0)
			{
				sprintf(str, "+%d", longPressCNT.value);
			}
			else if (longPressCNT.value <= 0)
			{
				sprintf(str, "%d", longPressCNT.value);
			}
			HEADER_SetItemText(longPressCNT.header, longPressCNT.headerItem, str);
			HEADER_SetTextColor(longPressCNT.header, GUI_WHITE);
			gui_Vars.valsChanged = true;
			break;
		case ID_BUTTON_SUMWINSETUP_Zminus:
			longPressCNT.direction = -1;
			longPressCNT.lowerLimit = -12;
			longPressCNT.itCNT = 0;
			longPressCNT.value = *val - 1;
			longPressCNT.header = WM_GetDialogItem(handles.hTimeSumWinSetupMenu, ID_HEADER_SUMWINSETUP_VALS);
			longPressCNT.headerItem = 0;
			longPressCNT.button = WM_GetDialogItem(handles.hTimeSumWinSetupMenu, ID_BUTTON_SUMWINSETUP_Zminus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			if (longPressCNT.value > 0)
			{
				sprintf(str, "+%d", longPressCNT.value);
			}
			else if (longPressCNT.value <= 0)
			{
				sprintf(str, "%d", longPressCNT.value);
			}
			HEADER_SetItemText(longPressCNT.header, longPressCNT.headerItem, str);
			HEADER_SetTextColor(longPressCNT.header, GUI_WHITE);
			gui_Vars.valsChanged = true;
			break;
		case ID_BUTTON_DTS_Dplus:
			longPressCNT.direction = 1;
			longPressCNT.upperLimit = getLastDayOfMonth((RTC_DateTypeDef*)(val - 2));
			longPressCNT.itCNT = 0;
			longPressCNT.value = *val + 1;
			longPressCNT.header = handles.hHeaderTimeDateSetupVals;
			longPressCNT.headerItem = 0;
			longPressCNT.button = WM_GetDialogItem(handles.hTimeDateSetupMenu, ID_BUTTON_DTS_Dplus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", longPressCNT.value);
			HEADER_SetItemText(longPressCNT.header, longPressCNT.headerItem, str);
			HEADER_SetTextColor(longPressCNT.header, GUI_WHITE);
			gui_Vars.valsChanged = true;
			break;
		case ID_BUTTON_DTS_Dminus:
			longPressCNT.direction = -1;
			longPressCNT.lowerLimit = 0;
			longPressCNT.itCNT = 0;
			longPressCNT.value = *val - 1;
			longPressCNT.header = handles.hHeaderTimeDateSetupVals;
			longPressCNT.headerItem = 0;
			longPressCNT.button = WM_GetDialogItem(handles.hTimeDateSetupMenu, ID_BUTTON_DTS_Dminus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", longPressCNT.value);
			HEADER_SetItemText(longPressCNT.header, longPressCNT.headerItem, str);
			HEADER_SetTextColor(longPressCNT.header, GUI_WHITE);
			gui_Vars.valsChanged = true;
			break;
		case ID_BUTTON_DTS_Mplus:
			longPressCNT.direction = 1;
			longPressCNT.upperLimit = 12;
			longPressCNT.itCNT = 0;
			longPressCNT.value = *val + 1;
			longPressCNT.header = handles.hHeaderTimeDateSetupVals;
			longPressCNT.headerItem = 1;
			longPressCNT.button = WM_GetDialogItem(handles.hTimeDateSetupMenu, ID_BUTTON_DTS_Mplus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", longPressCNT.value);
			HEADER_SetItemText(longPressCNT.header, longPressCNT.headerItem, str);
			HEADER_SetTextColor(longPressCNT.header, GUI_WHITE);
			gui_Vars.valsChanged = true;
			break;

		case ID_BUTTON_DTS_Mminus:
			longPressCNT.direction = -1;
			longPressCNT.upperLimit = 0;
			longPressCNT.itCNT = 0;
			longPressCNT.value = *val - 1;
			longPressCNT.header = handles.hHeaderTimeDateSetupVals;
			longPressCNT.headerItem = 1;
			longPressCNT.button = WM_GetDialogItem(handles.hTimeDateSetupMenu, ID_BUTTON_DTS_Mminus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", longPressCNT.value);
			HEADER_SetItemText(longPressCNT.header, longPressCNT.headerItem, str);
			HEADER_SetTextColor(longPressCNT.header, GUI_WHITE);
			gui_Vars.valsChanged = true;
			break;
		case ID_BUTTON_DTS_Yplus:
			longPressCNT.direction = 1;
			longPressCNT.upperLimit = 99;
			longPressCNT.itCNT = 0;
			longPressCNT.value = *val + 1;
			longPressCNT.header = handles.hHeaderTimeDateSetupVals;
			longPressCNT.headerItem = 2;
			longPressCNT.button = WM_GetDialogItem(handles.hTimeDateSetupMenu, ID_BUTTON_DTS_Yplus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", longPressCNT.value);
			HEADER_SetItemText(longPressCNT.header, longPressCNT.headerItem, str);
			HEADER_SetTextColor(longPressCNT.header, GUI_WHITE);
			gui_Vars.valsChanged = true;
			break;
		case ID_BUTTON_DTS_Yminus:
			longPressCNT.direction = -1;
			longPressCNT.lowerLimit = 0;
			longPressCNT.itCNT = 0;
			longPressCNT.value = *val - 1;
			longPressCNT.header = handles.hHeaderTimeDateSetupVals;
			longPressCNT.headerItem = 2;
			longPressCNT.button = WM_GetDialogItem(handles.hTimeDateSetupMenu, ID_BUTTON_DTS_Yminus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", longPressCNT.value);
			HEADER_SetItemText(longPressCNT.header, longPressCNT.headerItem, str);
			HEADER_SetTextColor(longPressCNT.header, GUI_WHITE);
			gui_Vars.valsChanged = true;
			break;
		case ID_BUTTON_TIMECALIBRATE_SECplus:
			longPressCNT.direction = 1;
			longPressCNT.upperLimit = 29;
			longPressCNT.itCNT = 0;
			longPressCNT.value = *val + 1;
			longPressCNT.header = handles.hHeaderTimeCalibrVals;
			longPressCNT.headerItem = 0;
			longPressCNT.button = WM_GetDialogItem(handles.hTimeCalibrateMenu, ID_BUTTON_TIMECALIBRATE_SECplus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			if (longPressCNT.value > 0)
			{
				sprintf(str, "+%d", longPressCNT.value);
			}
			else if (longPressCNT.value <= 0)
			{
				sprintf(str, "%d", longPressCNT.value);
			}
			HEADER_SetItemText(longPressCNT.header, longPressCNT.headerItem, str);
			HEADER_SetTextColor(longPressCNT.header, GUI_WHITE);
			gui_Vars.valsChanged = true;
			break;
		case ID_BUTTON_TIMECALIBRATE_SECminus:
			longPressCNT.direction = -1;
			longPressCNT.lowerLimit = -30;
			longPressCNT.itCNT = 0;
			longPressCNT.value = *val - 1;
			longPressCNT.header = handles.hHeaderTimeCalibrVals;
			longPressCNT.headerItem = 0;
			longPressCNT.button = WM_GetDialogItem(handles.hTimeCalibrateMenu, ID_BUTTON_TIMECALIBRATE_SECminus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			if (longPressCNT.value > 0)
			{
				sprintf(str, "+%d", longPressCNT.value);
			}
			else if (longPressCNT.value <= 0)
			{
				sprintf(str, "%d", longPressCNT.value);
			}
			HEADER_SetItemText(longPressCNT.header, longPressCNT.headerItem, str);
			HEADER_SetTextColor(longPressCNT.header, GUI_WHITE);
			gui_Vars.valsChanged = true;
			break;
		case ID_BUTTON_TIMECALIBRATE_DAYplus:
			longPressCNT.direction = 1;
			longPressCNT.upperLimit = 0xFF;
			longPressCNT.itCNT = 0;
			longPressCNT.value = *val + 1;
			longPressCNT.header = handles.hHeaderTimeCalibrVals;
			longPressCNT.headerItem = 1;
			longPressCNT.button = WM_GetDialogItem(handles.hTimeCalibrateMenu, ID_BUTTON_TIMECALIBRATE_DAYplus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", longPressCNT.value);
			HEADER_SetItemText(longPressCNT.header, longPressCNT.headerItem, str);
			HEADER_SetTextColor(longPressCNT.header, GUI_WHITE);
			gui_Vars.valsChanged = true;
			break;
		case ID_BUTTON_TIMECALIBRATE_DAYminus:
			longPressCNT.direction = -1;
			longPressCNT.lowerLimit = 0;
			longPressCNT.itCNT = 0;
			longPressCNT.value = *val - 1;
			longPressCNT.header = handles.hHeaderTimeCalibrVals;
			longPressCNT.headerItem = 1;
			longPressCNT.button = WM_GetDialogItem(handles.hTimeCalibrateMenu, ID_BUTTON_TIMECALIBRATE_DAYminus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", longPressCNT.value);
			HEADER_SetItemText(longPressCNT.header, longPressCNT.headerItem, str);
			HEADER_SetTextColor(longPressCNT.header, GUI_WHITE);
			gui_Vars.valsChanged = true;
			break;




		}
		return;
	}
	if (action == WM_NOTIFICATION_RELEASED)
	{

		longPressCNT.direction = 0;
		longPressCNT.itCNT = 0;
		*val = longPressCNT.value;
		TIM7->CNT = 0;
		HAL_TIM_Base_Stop_IT(&htim7);


	}

}
