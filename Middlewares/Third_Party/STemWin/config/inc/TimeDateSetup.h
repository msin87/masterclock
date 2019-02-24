#ifndef TIMEDATESETUP_H
#define TIMEDATESETUP_H	
#define ID_WINDOW_DATETIMESETUP   (GUI_ID_USER + 0x40)
#define ID_BUTTON_DTS_Dplus   (GUI_ID_USER + 0x41)
#define ID_HEADER_DTS_DMY   (GUI_ID_USER + 0x42)
#define ID_HEADER_DTS_VALS   (GUI_ID_USER + 0x43)
#define ID_BUTTON_DTS_Mplus   (GUI_ID_USER + 0x44)
#define ID_BUTTON_DTS_Yplus   (GUI_ID_USER + 0x45)
#define ID_BUTTON_DTS_Mminus     (GUI_ID_USER + 0x46)
#define ID_BUTTON_DTS_Yminus   (GUI_ID_USER + 0x47)
#define ID_BUTTON_DTS_ENTER   (GUI_ID_USER + 0x48)
#define ID_BUTTON_DTS_Dminus   (GUI_ID_USER + 0x49)
#define ID_BUTTON_DTS_BACK    (GUI_ID_USER + 0x4A)
#define ID_HEADER_DTS   (GUI_ID_USER + 0x4B)
#include "DIALOG.h"

WM_HWIN CreateTimeDateWindow(void);


#endif
