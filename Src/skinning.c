#include "skinning.h"
extern Lines line[4];
extern GUI_CONST_STORAGE GUI_FONT GUI_FontArial18;

int _DrawSkin_BUTTON(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) {
    char str[6]="";
    GUI_RECT pRect;
		char button_number[4]="0000";
//    const GUI_FONT * pFont;
    GUI_COLOR TextColor_Disabled, TextColor_Pressed, TextColor_Unpressed;
    int TextAlign;
    switch (pDrawItemInfo->Cmd) {
    case WIDGET_ITEM_DRAW_TEXT:
        // Get the coords of the button rect and decrease the rect width 
        // to avoid covering the button frame with the text 
        
        // Get the text of the button
        BUTTON_GetText(pDrawItemInfo->hWin, button_number, 4);
        // Get text align
        TextAlign = BUTTON_GetTextAlign(pDrawItemInfo->hWin);
        // Get font
        //pFont = BUTTON_GetFont(pDrawItemInfo->hWin);
        // Get colors 
        TextColor_Disabled = BUTTON_GetTextColor(pDrawItemInfo->hWin, BUTTON_CI_DISABLED);
        TextColor_Pressed = BUTTON_GetTextColor(pDrawItemInfo->hWin, BUTTON_CI_PRESSED);
        TextColor_Unpressed = BUTTON_GetTextColor(pDrawItemInfo->hWin, BUTTON_CI_UNPRESSED);
        // Set font 
        GUI_SetFont(&GUI_FontArial18);
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
        //GUI_DispStringInRectWrap(str, &pRect, TextAlign, GUI_WRAPMODE_WORD);
				pRect.x0 = pDrawItemInfo->x0;
        //pRect.y0 = pDrawItemInfo->y0;
				pRect.y0 = BUTTON_TEXT_LINENAME_Y0;
        pRect.x1 = pDrawItemInfo->x1;
				pRect.y1 = BUTTON_TEXT_LINENAME_Y1;
        //pRect.y1 = pDrawItemInfo->y1;
				switch (button_number[0])
				{
					case '1':
						GUI_DispStringInRect("ÀËÌËˇ 1", &pRect, TextAlign);
						break;
					case '2':
						GUI_DispStringInRect("ÀËÌËˇ 2", &pRect, TextAlign);
						break;
					case '3':
						GUI_DispStringInRect("ÀËÌËˇ 3", &pRect, TextAlign);
						break;
					case '4':
						GUI_DispStringInRect("ÀËÌËˇ 4", &pRect, TextAlign);
						break;
				}
				
				
				pRect.x0 = pDrawItemInfo->x0;
				pRect.y0 = BUTTON_TEXT_LINETIME_Y0;
        pRect.x1 = pDrawItemInfo->x1;
				pRect.y1 = BUTTON_TEXT_LINETIME_Y1;
				switch (button_number[0])
				{
					case '1':
						switch (line[0].Status){
							case LINE_STATUS_OFF:
								strncpy(str,"¬€ À",4);
								break;
							case LINE_STATUS_RUN:
								sprintf(str,"%02d:%02d",line[0].Hours,line[0].Minutes);
								break;
							case LINE_STATUS_STOP:
								strncpy(str,"—“Œœ",4);
								break;
						}
					break;
						case '2':
						switch (line[1].Status){
							case LINE_STATUS_OFF:
								strncpy(str,"¬€ À",4);
								
								break;
							case LINE_STATUS_RUN:
								sprintf(str,"%02d:%02d",line[1].Hours,line[1].Minutes);
								break;
							case LINE_STATUS_STOP:
								strncpy(str,"—“Œœ",4);
								break;
						}
					break;
						case '3':
						switch (line[2].Status){
							case LINE_STATUS_OFF:
								strncpy(str,"¬€ À",4);
								break;
							case LINE_STATUS_RUN:
								sprintf(str,"%02d:%02d",line[2].Hours,line[2].Minutes);
								break;
							case LINE_STATUS_STOP:
								strncpy(str,"—“Œœ",4);
								break;
						}
					break;
						case '4':
						switch (line[3].Status){
							case LINE_STATUS_OFF:
								strncpy(str,"¬€ À",4);
								break;
							case LINE_STATUS_RUN:
								sprintf(str,"%02d:%02d",line[3].Hours,line[3].Minutes);
								break;
							case LINE_STATUS_STOP:
								strncpy(str,"—“Œœ",4);
								break;
						}
					break;
					}
				GUI_DispStringInRect(str, &pRect, TextAlign);
				
        break;
    default:				
         BUTTON_DrawSkinFlex(pDrawItemInfo);
				 
		break;
        
    }
		
    return 0;
}

