#include "callbacks.h"

#include "cmsis_os.h"
#include "stm32f1xx_hal.h"
#include "guivars.h"
#include "lcdcmd.h"
#include "TimeSetup.h"
#include "TimeDateSetup.h"
#include "TimeCalibrate.h"
#include "TimeSumWinSetup.h"
#include "LineSetupPulse.h"
#include "LineSetup.h"
#include "timedate.h"

#define HEADER_ITEM0 0
#define HEADER_ITEM1 1
#define HEADER_ITEM2 2
#define HEADER_ITEM3 3
#define DESCENDING -1
#define ASCENDING 1
extern RTC_TimeTypeDef sTime;

extern osMessageQId queueLCDLinesTimeHandle;
extern GUI_CONST_STORAGE GUI_CHARINFO GUI_FontArial18_CharInfo[192];
extern GUI_CONST_STORAGE GUI_FONT_PROP GUI_FontArial18_Prop2;
extern GUI_CONST_STORAGE GUI_FONT_PROP GUI_FontArial18_Prop1;

extern TIM_HandleTypeDef htim7;


//void saveDateToBKP(void)
//{
//	uint16_t write = 0;
//	RTC_DateTypeDef Date;
//
//	HAL_RTC_GetDate(&hrtc, &Date, RTC_FORMAT_BIN);
//	write = Date.Date;
//	write |= (Date.Month << 5);
//	write |= (Date.Year << 9);
//	rtc_write_backup_reg(BKP_DATE_OFFSET, write);
//}
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
		if (masterClock.guiVars->valsChanged)
		{
			GUI_SetColor(0x282171);
			GUI_FillRect(5, 60, 65, 65);
		}
	default:
		BUTTON_Callback(pMsg);
		if (masterClock.guiVars->valsChanged)
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
		sprintf(str, "%02d:%02d:%02d", hoursToUTC(sTime.Hours, masterClock.daylightSaving->timeZone), sTime.Minutes, sTime.Seconds);
		TFT_LineSetupShowString(173, 17, str, 18, 0xFFFF);
		break;
	default:
		HEADER_Callback(pMsg);
		sprintf(str, "%02d:%02d:%02d", hoursToUTC(sTime.Hours, masterClock.daylightSaving->timeZone), sTime.Minutes, sTime.Seconds);
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
void prepareLPCNT(int8_t direction, int16_t lowerLimit, int16_t upperLimit, int16_t value, uint16_t valueMult, HEADER_Handle valuesHeaderHandle, uint8_t valuesHeaderItem, BUTTON_Handle actionButtonHandle)
{
	char str[5] = { 0,0,0,0,0 };

	masterClock.longPressCNT->itCNT = 0;
	masterClock.guiVars->valsChanged = true;
	masterClock.longPressCNT->direction = direction;
	masterClock.longPressCNT->value = value + direction;
	masterClock.longPressCNT->lowerLimit = lowerLimit;
	masterClock.longPressCNT->upperLimit = upperLimit;
	masterClock.longPressCNT->header = valuesHeaderHandle;
	masterClock.longPressCNT->headerItem = valuesHeaderItem;
	masterClock.longPressCNT->button = actionButtonHandle;

	if (masterClock.longPressCNT->value > 0)
	{
		sprintf(str, (lowerLimit < 0) ? "+%d" : "%02d", masterClock.longPressCNT->value*valueMult);
	}
	else if (masterClock.longPressCNT->value <= 0)
	{
		sprintf(str, "%d", masterClock.longPressCNT->value*valueMult);
	}
	HEADER_SetItemText(masterClock.longPressCNT->header, masterClock.longPressCNT->headerItem, str);
	HEADER_SetTextColor(masterClock.longPressCNT->header, GUI_WHITE);
	HAL_TIM_Base_Start_IT(&htim7);

}
void pollButton(uint16_t id, uint8_t action, int8_t* val)
{
	char str[5];
	if (action == WM_NOTIFICATION_CLICKED)
	{
		masterClock.longPressCNT->lowerLimit = 0;
		masterClock.longPressCNT->itCNT = 0;
		masterClock.guiVars->valsChanged = true;
		//HAL_TIM_Base_Start_IT(&htim7);
		switch (id)
		{
		case ID_BUTTON_LINESETUP_Hminus:
			/*masterClock.longPressCNT->direction = -1;
			masterClock.longPressCNT->value = *val - 1;
			masterClock.longPressCNT->header = WM_GetDialogItem(masterClock.handles->hLineSetupMenu, ID_HEADER_LINESETUP_VALS);
			masterClock.longPressCNT->headerItem = 0;
			masterClock.longPressCNT->button = WM_GetDialogItem(masterClock.handles->hLineSetupMenu, ID_BUTTON_LINESETUP_Hminus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", masterClock.longPressCNT->value);
			HEADER_SetItemText(masterClock.longPressCNT->header, masterClock.longPressCNT->headerItem, str);
			HEADER_SetTextColor(masterClock.longPressCNT->header, GUI_WHITE);
			masterClock.guiVars->valsChanged = true;*/
			prepareLPCNT(DESCENDING, 0, 24, *val, 1, WM_GetDialogItem(masterClock.handles->hLineSetupMenu, ID_HEADER_LINESETUP_VALS), HEADER_ITEM0, WM_GetDialogItem(masterClock.handles->hLineSetupMenu, ID_BUTTON_LINESETUP_Hminus));
			break;
		case ID_BUTTON_LINESETUP_Mminus:
			/*masterClock.longPressCNT->direction = -1;

			masterClock.longPressCNT->value = *val - 1;
			masterClock.longPressCNT->header = WM_GetDialogItem(masterClock.handles->hLineSetupMenu, ID_HEADER_LINESETUP_VALS);
			masterClock.longPressCNT->headerItem = 1;
			masterClock.longPressCNT->button = WM_GetDialogItem(masterClock.handles->hLineSetupMenu, ID_BUTTON_LINESETUP_Mminus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", masterClock.longPressCNT->value);
			HEADER_SetItemText(masterClock.longPressCNT->header, masterClock.longPressCNT->headerItem, str);
			HEADER_SetTextColor(masterClock.longPressCNT->header, GUI_WHITE);
			masterClock.guiVars->valsChanged = true;*/
			prepareLPCNT(DESCENDING, 0, 60, *val, 1, WM_GetDialogItem(masterClock.handles->hLineSetupMenu, ID_HEADER_LINESETUP_VALS), HEADER_ITEM1, WM_GetDialogItem(masterClock.handles->hLineSetupMenu, ID_BUTTON_LINESETUP_Mminus));

			break;
		case ID_BUTTON_LINESETUP_Hplus:
			masterClock.longPressCNT->direction = 1;
			masterClock.longPressCNT->upperLimit = 23;

			masterClock.longPressCNT->value = *val + 1;
			masterClock.longPressCNT->header = WM_GetDialogItem(masterClock.handles->hLineSetupMenu, ID_HEADER_LINESETUP_VALS);
			masterClock.longPressCNT->headerItem = 0;
			masterClock.longPressCNT->button = WM_GetDialogItem(masterClock.handles->hLineSetupMenu, ID_BUTTON_LINESETUP_Hplus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", masterClock.longPressCNT->value);
			HEADER_SetItemText(masterClock.longPressCNT->header, masterClock.longPressCNT->headerItem, str);
			HEADER_SetTextColor(masterClock.longPressCNT->header, GUI_WHITE);
			masterClock.guiVars->valsChanged = true;
			break;
		case ID_BUTTON_LINESETUP_Mplus:
			masterClock.longPressCNT->direction = 1;
			masterClock.longPressCNT->upperLimit = 59;

			masterClock.longPressCNT->value = *val + 1;
			masterClock.longPressCNT->header = WM_GetDialogItem(masterClock.handles->hLineSetupMenu, ID_HEADER_LINESETUP_VALS);
			masterClock.longPressCNT->headerItem = 1;
			masterClock.longPressCNT->button = WM_GetDialogItem(masterClock.handles->hLineSetupMenu, ID_BUTTON_LINESETUP_Mplus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", masterClock.longPressCNT->value);
			HEADER_SetItemText(masterClock.longPressCNT->header, masterClock.longPressCNT->headerItem, str);
			HEADER_SetTextColor(masterClock.longPressCNT->header, GUI_WHITE);
			masterClock.guiVars->valsChanged = true;
			break;
			//vv TIMESETUP vv
		case ID_BUTTON_HOURplus:
			masterClock.longPressCNT->direction = 1;
			masterClock.longPressCNT->upperLimit = 23;

			masterClock.longPressCNT->value = *val + 1;
			masterClock.longPressCNT->header = WM_GetDialogItem(masterClock.handles->hTimeSetupMenu, ID_HEADER_HMS_VALUE);
			masterClock.longPressCNT->headerItem = 0;
			masterClock.longPressCNT->button = WM_GetDialogItem(masterClock.handles->hTimeSetupMenu, ID_BUTTON_HOURplus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", masterClock.longPressCNT->value);
			HEADER_SetItemText(masterClock.longPressCNT->header, masterClock.longPressCNT->headerItem, str);
			HEADER_SetTextColor(masterClock.longPressCNT->header, GUI_WHITE);
			masterClock.guiVars->valsChanged = true;
			break;
			break;
		case ID_BUTTON_MINplus:
			masterClock.longPressCNT->direction = 1;
			masterClock.longPressCNT->upperLimit = 59;

			masterClock.longPressCNT->value = *val + 1;
			masterClock.longPressCNT->header = WM_GetDialogItem(masterClock.handles->hTimeSetupMenu, ID_HEADER_HMS_VALUE);
			masterClock.longPressCNT->headerItem = 1;
			masterClock.longPressCNT->button = WM_GetDialogItem(masterClock.handles->hTimeSetupMenu, ID_BUTTON_MINplus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", masterClock.longPressCNT->value);
			HEADER_SetItemText(masterClock.longPressCNT->header, masterClock.longPressCNT->headerItem, str);
			HEADER_SetTextColor(masterClock.longPressCNT->header, GUI_WHITE);
			masterClock.guiVars->valsChanged = true;
			break;
		case ID_BUTTON_SECplus:
			masterClock.longPressCNT->direction = 1;
			masterClock.longPressCNT->upperLimit = 59;

			masterClock.longPressCNT->value = *val + 1;
			masterClock.longPressCNT->header = WM_GetDialogItem(masterClock.handles->hTimeSetupMenu, ID_HEADER_HMS_VALUE);
			masterClock.longPressCNT->headerItem = 2;
			masterClock.longPressCNT->button = WM_GetDialogItem(masterClock.handles->hTimeSetupMenu, ID_BUTTON_SECplus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", masterClock.longPressCNT->value);
			HEADER_SetItemText(masterClock.longPressCNT->header, masterClock.longPressCNT->headerItem, str);
			HEADER_SetTextColor(masterClock.longPressCNT->header, GUI_WHITE);
			masterClock.guiVars->valsChanged = true;
			break;
		case ID_BUTTON_HOURminus:
			masterClock.longPressCNT->direction = -1;

			masterClock.longPressCNT->value = *val - 1;
			masterClock.longPressCNT->header = WM_GetDialogItem(masterClock.handles->hTimeSetupMenu, ID_HEADER_HMS_VALUE);
			masterClock.longPressCNT->headerItem = 0;
			masterClock.longPressCNT->button = WM_GetDialogItem(masterClock.handles->hTimeSetupMenu, ID_BUTTON_HOURminus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", masterClock.longPressCNT->value);
			HEADER_SetItemText(masterClock.longPressCNT->header, masterClock.longPressCNT->headerItem, str);
			HEADER_SetTextColor(masterClock.longPressCNT->header, GUI_WHITE);
			masterClock.guiVars->valsChanged = true;
			break;
		case ID_BUTTON_MINminus:
			masterClock.longPressCNT->direction = -1;

			masterClock.longPressCNT->value = *val - 1;
			masterClock.longPressCNT->header = WM_GetDialogItem(masterClock.handles->hTimeSetupMenu, ID_HEADER_HMS_VALUE);
			masterClock.longPressCNT->headerItem = 1;
			masterClock.longPressCNT->button = WM_GetDialogItem(masterClock.handles->hTimeSetupMenu, ID_BUTTON_MINminus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", masterClock.longPressCNT->value);
			HEADER_SetItemText(masterClock.longPressCNT->header, masterClock.longPressCNT->headerItem, str);
			HEADER_SetTextColor(masterClock.longPressCNT->header, GUI_WHITE);
			masterClock.guiVars->valsChanged = true;
			break;
		case ID_BUTTON_SECminus:
			masterClock.longPressCNT->direction = -1;

			masterClock.longPressCNT->value = *val - 1;
			masterClock.longPressCNT->header = WM_GetDialogItem(masterClock.handles->hTimeSetupMenu, ID_HEADER_HMS_VALUE);
			masterClock.longPressCNT->headerItem = 2;
			masterClock.longPressCNT->button = WM_GetDialogItem(masterClock.handles->hTimeSetupMenu, ID_BUTTON_SECminus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", masterClock.longPressCNT->value);
			HEADER_SetItemText(masterClock.longPressCNT->header, masterClock.longPressCNT->headerItem, str);
			HEADER_SetTextColor(masterClock.longPressCNT->header, GUI_WHITE);
			masterClock.guiVars->valsChanged = true;
			break;
		case ID_BUTTON_LINESETUP_PULSE_MSECplus:
			masterClock.longPressCNT->direction = 1;
			masterClock.longPressCNT->upperLimit = 15;

			masterClock.longPressCNT->value = *val + 1;
			masterClock.longPressCNT->header = WM_GetDialogItem(masterClock.handles->hLineSetupPulseMenu, ID_HEADER_LINESETUP_PULSE_VALS);
			masterClock.longPressCNT->headerItem = 0;
			masterClock.longPressCNT->button = WM_GetDialogItem(masterClock.handles->hLineSetupPulseMenu, ID_BUTTON_LINESETUP_PULSE_MSECplus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%4d", masterClock.longPressCNT->value * LINE_WIDTH_MULT);
			HEADER_SetItemText(masterClock.longPressCNT->header, masterClock.longPressCNT->headerItem, str);
			HEADER_SetTextColor(masterClock.longPressCNT->header, GUI_WHITE);
			masterClock.guiVars->valsChanged = true;
			break;
		case ID_BUTTON_LINESETUP_PULSE_MSECminus:
			masterClock.longPressCNT->direction = -1;

			masterClock.longPressCNT->value = *val - 1;
			masterClock.longPressCNT->header = WM_GetDialogItem(masterClock.handles->hLineSetupPulseMenu, ID_HEADER_LINESETUP_PULSE_VALS);
			masterClock.longPressCNT->headerItem = 0;
			masterClock.longPressCNT->button = WM_GetDialogItem(masterClock.handles->hLineSetupPulseMenu, ID_BUTTON_LINESETUP_PULSE_MSECminus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%4d", masterClock.longPressCNT->value * LINE_WIDTH_MULT);
			HEADER_SetItemText(masterClock.longPressCNT->header, masterClock.longPressCNT->headerItem, str);
			HEADER_SetTextColor(masterClock.longPressCNT->header, GUI_WHITE);
			masterClock.guiVars->valsChanged = true;
			break;
		case ID_BUTTON_SUMWINSETUP_Zplus:
			masterClock.longPressCNT->direction = 1;
			masterClock.longPressCNT->upperLimit = 12;
			masterClock.longPressCNT->lowerLimit = -12;

			masterClock.longPressCNT->value = *val + 1;
			masterClock.longPressCNT->header = WM_GetDialogItem(masterClock.handles->hTimeSumWinSetupMenu, ID_HEADER_SUMWINSETUP_VALS);
			masterClock.longPressCNT->headerItem = 0;
			masterClock.longPressCNT->button = WM_GetDialogItem(masterClock.handles->hTimeSumWinSetupMenu, ID_BUTTON_SUMWINSETUP_Zplus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			if (masterClock.longPressCNT->value > 0)
			{
				sprintf(str, "+%d", masterClock.longPressCNT->value);
			}
			else if (masterClock.longPressCNT->value <= 0)
			{
				sprintf(str, "%d", masterClock.longPressCNT->value);
			}
			HEADER_SetItemText(masterClock.longPressCNT->header, masterClock.longPressCNT->headerItem, str);
			HEADER_SetTextColor(masterClock.longPressCNT->header, GUI_WHITE);
			masterClock.guiVars->valsChanged = true;
			break;
		case ID_BUTTON_SUMWINSETUP_Zminus:
			masterClock.longPressCNT->direction = -1;
			masterClock.longPressCNT->lowerLimit = -12;

			masterClock.longPressCNT->value = *val - 1;
			masterClock.longPressCNT->header = WM_GetDialogItem(masterClock.handles->hTimeSumWinSetupMenu, ID_HEADER_SUMWINSETUP_VALS);
			masterClock.longPressCNT->headerItem = 0;
			masterClock.longPressCNT->button = WM_GetDialogItem(masterClock.handles->hTimeSumWinSetupMenu, ID_BUTTON_SUMWINSETUP_Zminus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			if (masterClock.longPressCNT->value > 0)
			{
				sprintf(str, "+%d", masterClock.longPressCNT->value);
			}
			else if (masterClock.longPressCNT->value <= 0)
			{
				sprintf(str, "%d", masterClock.longPressCNT->value);
			}
			HEADER_SetItemText(masterClock.longPressCNT->header, masterClock.longPressCNT->headerItem, str);
			HEADER_SetTextColor(masterClock.longPressCNT->header, GUI_WHITE);
			masterClock.guiVars->valsChanged = true;
			break;
		case ID_BUTTON_DTS_Dplus:
			masterClock.longPressCNT->direction = 1;
			masterClock.longPressCNT->upperLimit = getLastDayOfMonth((RTC_DateTypeDef*)(val - 2));

			masterClock.longPressCNT->value = *val + 1;
			masterClock.longPressCNT->header = masterClock.handles->hHeaderTimeDateSetupVals;
			masterClock.longPressCNT->headerItem = 0;
			masterClock.longPressCNT->button = WM_GetDialogItem(masterClock.handles->hTimeDateSetupMenu, ID_BUTTON_DTS_Dplus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", masterClock.longPressCNT->value);
			HEADER_SetItemText(masterClock.longPressCNT->header, masterClock.longPressCNT->headerItem, str);
			HEADER_SetTextColor(masterClock.longPressCNT->header, GUI_WHITE);
			masterClock.guiVars->valsChanged = true;
			break;
		case ID_BUTTON_DTS_Dminus:
			masterClock.longPressCNT->direction = -1;

			masterClock.longPressCNT->value = *val - 1;
			masterClock.longPressCNT->header = masterClock.handles->hHeaderTimeDateSetupVals;
			masterClock.longPressCNT->headerItem = 0;
			masterClock.longPressCNT->button = WM_GetDialogItem(masterClock.handles->hTimeDateSetupMenu, ID_BUTTON_DTS_Dminus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", masterClock.longPressCNT->value);
			HEADER_SetItemText(masterClock.longPressCNT->header, masterClock.longPressCNT->headerItem, str);
			HEADER_SetTextColor(masterClock.longPressCNT->header, GUI_WHITE);
			masterClock.guiVars->valsChanged = true;
			break;
		case ID_BUTTON_DTS_Mplus:
			masterClock.longPressCNT->direction = 1;
			masterClock.longPressCNT->upperLimit = 12;

			masterClock.longPressCNT->value = *val + 1;
			masterClock.longPressCNT->header = masterClock.handles->hHeaderTimeDateSetupVals;
			masterClock.longPressCNT->headerItem = 1;
			masterClock.longPressCNT->button = WM_GetDialogItem(masterClock.handles->hTimeDateSetupMenu, ID_BUTTON_DTS_Mplus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", masterClock.longPressCNT->value);
			HEADER_SetItemText(masterClock.longPressCNT->header, masterClock.longPressCNT->headerItem, str);
			HEADER_SetTextColor(masterClock.longPressCNT->header, GUI_WHITE);
			masterClock.guiVars->valsChanged = true;
			break;

		case ID_BUTTON_DTS_Mminus:
			masterClock.longPressCNT->direction = -1;
			masterClock.longPressCNT->upperLimit = 0;

			masterClock.longPressCNT->value = *val - 1;
			masterClock.longPressCNT->header = masterClock.handles->hHeaderTimeDateSetupVals;
			masterClock.longPressCNT->headerItem = 1;
			masterClock.longPressCNT->button = WM_GetDialogItem(masterClock.handles->hTimeDateSetupMenu, ID_BUTTON_DTS_Mminus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", masterClock.longPressCNT->value);
			HEADER_SetItemText(masterClock.longPressCNT->header, masterClock.longPressCNT->headerItem, str);
			HEADER_SetTextColor(masterClock.longPressCNT->header, GUI_WHITE);
			masterClock.guiVars->valsChanged = true;
			break;
		case ID_BUTTON_DTS_Yplus:
			masterClock.longPressCNT->direction = 1;
			masterClock.longPressCNT->upperLimit = 99;

			masterClock.longPressCNT->value = *val + 1;
			masterClock.longPressCNT->header = masterClock.handles->hHeaderTimeDateSetupVals;
			masterClock.longPressCNT->headerItem = 2;
			masterClock.longPressCNT->button = WM_GetDialogItem(masterClock.handles->hTimeDateSetupMenu, ID_BUTTON_DTS_Yplus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", masterClock.longPressCNT->value);
			HEADER_SetItemText(masterClock.longPressCNT->header, masterClock.longPressCNT->headerItem, str);
			HEADER_SetTextColor(masterClock.longPressCNT->header, GUI_WHITE);
			masterClock.guiVars->valsChanged = true;
			break;
		case ID_BUTTON_DTS_Yminus:
			masterClock.longPressCNT->direction = -1;

			masterClock.longPressCNT->value = *val - 1;
			masterClock.longPressCNT->header = masterClock.handles->hHeaderTimeDateSetupVals;
			masterClock.longPressCNT->headerItem = 2;
			masterClock.longPressCNT->button = WM_GetDialogItem(masterClock.handles->hTimeDateSetupMenu, ID_BUTTON_DTS_Yminus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", masterClock.longPressCNT->value);
			HEADER_SetItemText(masterClock.longPressCNT->header, masterClock.longPressCNT->headerItem, str);
			HEADER_SetTextColor(masterClock.longPressCNT->header, GUI_WHITE);
			masterClock.guiVars->valsChanged = true;
			break;
		case ID_BUTTON_TIMECALIBRATE_SECplus:
			masterClock.longPressCNT->direction = 1;
			masterClock.longPressCNT->upperLimit = 29;
			masterClock.longPressCNT->lowerLimit = -30;

			masterClock.longPressCNT->value = *val + 1;
			masterClock.longPressCNT->header = masterClock.handles->hHeaderTimeCalibrVals;
			masterClock.longPressCNT->headerItem = 0;
			masterClock.longPressCNT->button = WM_GetDialogItem(masterClock.handles->hTimeCalibrateMenu, ID_BUTTON_TIMECALIBRATE_SECplus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			if (masterClock.longPressCNT->value > 0)
			{
				sprintf(str, "+%d", masterClock.longPressCNT->value);
			}
			else if (masterClock.longPressCNT->value <= 0)
			{
				sprintf(str, "%d", masterClock.longPressCNT->value);
			}
			HEADER_SetItemText(masterClock.longPressCNT->header, masterClock.longPressCNT->headerItem, str);
			HEADER_SetTextColor(masterClock.longPressCNT->header, GUI_WHITE);
			masterClock.guiVars->valsChanged = true;
			break;
		case ID_BUTTON_TIMECALIBRATE_SECminus:
			masterClock.longPressCNT->direction = -1;
			masterClock.longPressCNT->lowerLimit = -30;

			masterClock.longPressCNT->value = *val - 1;
			masterClock.longPressCNT->header = masterClock.handles->hHeaderTimeCalibrVals;
			masterClock.longPressCNT->headerItem = 0;
			masterClock.longPressCNT->button = WM_GetDialogItem(masterClock.handles->hTimeCalibrateMenu, ID_BUTTON_TIMECALIBRATE_SECminus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			if (masterClock.longPressCNT->value > 0)
			{
				sprintf(str, "+%d", masterClock.longPressCNT->value);
			}
			else if (masterClock.longPressCNT->value <= 0)
			{
				sprintf(str, "%d", masterClock.longPressCNT->value);
			}
			HEADER_SetItemText(masterClock.longPressCNT->header, masterClock.longPressCNT->headerItem, str);
			HEADER_SetTextColor(masterClock.longPressCNT->header, GUI_WHITE);
			masterClock.guiVars->valsChanged = true;
			break;
		case ID_BUTTON_TIMECALIBRATE_DAYplus:
			masterClock.longPressCNT->direction = 1;
			masterClock.longPressCNT->upperLimit = 0xFF;

			masterClock.longPressCNT->value = *val + 1;
			masterClock.longPressCNT->header = masterClock.handles->hHeaderTimeCalibrVals;
			masterClock.longPressCNT->headerItem = 1;
			masterClock.longPressCNT->button = WM_GetDialogItem(masterClock.handles->hTimeCalibrateMenu, ID_BUTTON_TIMECALIBRATE_DAYplus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", masterClock.longPressCNT->value);
			HEADER_SetItemText(masterClock.longPressCNT->header, masterClock.longPressCNT->headerItem, str);
			HEADER_SetTextColor(masterClock.longPressCNT->header, GUI_WHITE);
			masterClock.guiVars->valsChanged = true;
			break;
		case ID_BUTTON_TIMECALIBRATE_DAYminus:
			masterClock.longPressCNT->direction = -1;

			masterClock.longPressCNT->value = *val - 1;
			masterClock.longPressCNT->header = masterClock.handles->hHeaderTimeCalibrVals;
			masterClock.longPressCNT->headerItem = 1;
			masterClock.longPressCNT->button = WM_GetDialogItem(masterClock.handles->hTimeCalibrateMenu, ID_BUTTON_TIMECALIBRATE_DAYminus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			sprintf(str, "%02d", masterClock.longPressCNT->value);
			HEADER_SetItemText(masterClock.longPressCNT->header, masterClock.longPressCNT->headerItem, str);
			HEADER_SetTextColor(masterClock.longPressCNT->header, GUI_WHITE);
			masterClock.guiVars->valsChanged = true;
			break;
		case ID_BUTTON_LINESETUP_Zplus:
			masterClock.longPressCNT->direction = 1;
			masterClock.longPressCNT->upperLimit = 12;
			masterClock.longPressCNT->lowerLimit = -12;

			masterClock.longPressCNT->value = *val + 1;
			masterClock.longPressCNT->header = masterClock.handles->hLineSetupVals;
			masterClock.longPressCNT->headerItem = 2;
			masterClock.longPressCNT->button = WM_GetDialogItem(masterClock.handles->hLineSetupMenu, ID_BUTTON_LINESETUP_Zplus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			if (masterClock.longPressCNT->value > 0)
			{
				sprintf(str, "+%d", masterClock.longPressCNT->value);
			}
			else if (masterClock.longPressCNT->value <= 0)
			{
				sprintf(str, "%d", masterClock.longPressCNT->value);
			}
			HEADER_SetItemText(masterClock.longPressCNT->header, masterClock.longPressCNT->headerItem, str);
			HEADER_SetTextColor(masterClock.longPressCNT->header, GUI_WHITE);
			masterClock.guiVars->valsChanged = true;
			break;
		case ID_BUTTON_LINESETUP_Zminus:
			masterClock.longPressCNT->direction = -1;
			masterClock.longPressCNT->upperLimit = 12;
			masterClock.longPressCNT->lowerLimit = -12;

			masterClock.longPressCNT->value = *val - 1;
			masterClock.longPressCNT->header = masterClock.handles->hLineSetupVals;
			masterClock.longPressCNT->headerItem = 2;
			masterClock.longPressCNT->button = WM_GetDialogItem(masterClock.handles->hLineSetupMenu, ID_BUTTON_LINESETUP_Zminus);
			TIM7->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim7);
			if (masterClock.longPressCNT->value > 0)
			{
				sprintf(str, "+%d", masterClock.longPressCNT->value);
			}
			else if (masterClock.longPressCNT->value <= 0)
			{
				sprintf(str, "%d", masterClock.longPressCNT->value);
			}
			HEADER_SetItemText(masterClock.longPressCNT->header, masterClock.longPressCNT->headerItem, str);
			HEADER_SetTextColor(masterClock.longPressCNT->header, GUI_WHITE);
			masterClock.guiVars->valsChanged = true;
			break;



		}
		return;
	}
	if (action == WM_NOTIFICATION_RELEASED)
	{

		masterClock.longPressCNT->direction = 0;
		masterClock.longPressCNT->itCNT = 0;
		*val = masterClock.longPressCNT->value;
		TIM7->CNT = 0;
		HAL_TIM_Base_Stop_IT(&htim7);


	}

}
