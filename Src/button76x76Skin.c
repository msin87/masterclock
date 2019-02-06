#include "button76x76Skin.h"
int _DarkGraySkin_BUTTON(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) {
	static int ToggleButtonSkin;
	GUI_COLOR  aColor[2] = { BUTTON76x76_BACKGROUND_COLOR, GUI_RED };
  static int Pressed;
	
    switch (pDrawItemInfo->Cmd) {
			case WIDGET_ITEM_CREATE:
				return BUTTON_DrawSkinFlex(pDrawItemInfo);
			case WIDGET_ITEM_DRAW_BACKGROUND:
				if (BUTTON_IsPressed(pDrawItemInfo->hWin)) 
					{
						Pressed = 1;
					}
				else if (Pressed) 
				{  // If pressed is set, but button not pressed we have a release
					Pressed = 0;
					ToggleButtonSkin ^= 1;
				}
				GUI_SetColor(aColor[ToggleButtonSkin]);
				GUI_FillRect(pDrawItemInfo->x0, pDrawItemInfo->y0, pDrawItemInfo->x1, pDrawItemInfo->y1);
				
			return 0;
			case WIDGET_ITEM_DRAW_BITMAP:
				return BUTTON_DrawSkinFlex(pDrawItemInfo);
			case WIDGET_ITEM_DRAW_TEXT:
				return BUTTON_DrawSkinFlex(pDrawItemInfo);
			default:
				BUTTON_DrawSkinFlex(pDrawItemInfo);
			break;
		}
	return 0;
}

