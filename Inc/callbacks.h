#ifndef CALLBACKS_H
#define CALLBACKS_H
#include "cmsis_os.h"
#include "DIALOG.h"
#define u8 uint8_t
#define u16 uint16_t

//callbacks.h
void _cbArrowUpButton(WM_MESSAGE * pMsg);
void _cbArrowDownButton(WM_MESSAGE * pMsg);
void _cbEnterButton(WM_MESSAGE * pMsg);
void _cbLineSetupSystemTime(WM_MESSAGE * pMsg);
void _cbPulseSetupButton(WM_MESSAGE * pMsg);
int _ProgbarSkin(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int _DrawSkin_BUTTON_WORDWRAP(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);

//Отказаться от этих двух функций
void TFT_LineSetupShowString(uint16_t x, uint16_t y, char *p, uint8_t fontsize, uint16_t color);
void TFT_LineSetupShowChar(u16 x, u16 y, u8 num, uint8_t fontsize, u16 color);



void pollButton(uint16_t id, uint8_t action, int8_t* val);
void menuLocker(WM_HWIN *CurrentMenuHandle);
void returnToMainMenu(WM_HWIN* hCurrentWindow);
#endif
