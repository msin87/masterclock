#ifndef LOCALTIMESETUPMENU_H
#define LOCALTIMESETUPMENU_H	

#include "DIALOG.H"
WM_HWIN CreateLocalTimeSeupWindow(void);
typedef struct
{
	WM_HWIN Handle_WINDOW;
	BUTTON_Handle Handle_BUTTON_0;
	BUTTON_Handle Handle_BUTTON_1;
	BUTTON_Handle Handle_BUTTON_2;
	BUTTON_Handle Handle_BUTTON_3; 
	BUTTON_Handle Handle_BUTTON_4;
	BUTTON_Handle Handle_BUTTON_5;
	BUTTON_Handle Handle_BUTTON_6;
	BUTTON_Handle Handle_BUTTON_7;
	HEADER_Handle Handle_HEADER_0;
	HEADER_Handle Handle_HEADER_1;
	BUTTON_Handle Handle_BUTTON_8;
} HandlesLTSW;
#endif