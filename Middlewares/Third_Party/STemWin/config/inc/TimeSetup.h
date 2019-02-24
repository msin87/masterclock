#ifndef TIMESETUP_H
#define TIMESETUP_H

#define ID_WINDOW_TIMESETUP   (GUI_ID_USER + 0x20)
#define ID_BUTTON_HOURplus   (GUI_ID_USER + 0x21)
#define ID_HEADER_HMS   (GUI_ID_USER + 0x22)
#define ID_HEADER_HMS_VALUE   (GUI_ID_USER + 0x23)
#define ID_BUTTON_MINplus   (GUI_ID_USER + 0x24)
#define ID_BUTTON_SECplus   (GUI_ID_USER + 0x25)
#define ID_BUTTON_ENTER   (GUI_ID_USER + 0x26)
#define ID_BUTTON_CALIBRATE   (GUI_ID_USER + 0x27)
#define ID_BUTTON_DATE   (GUI_ID_USER + 0x28)
#define ID_BUTTON_HOURminus   (GUI_ID_USER + 0x29)
#define ID_BUTTON_MINminus   (GUI_ID_USER + 0x2A)
#define ID_BUTTON_SECminus   (GUI_ID_USER + 0x2B)
#define ID_BUTTON_BACK   (GUI_ID_USER + 0x2C)

#define ID_HEADER_WINDOW_TIMESETUP   (GUI_ID_USER + 0x2D)
#define ID_BUTTON_TIMESETUP_ZONE   (GUI_ID_USER + 0x2E)


#include "DIALOG.h"


WM_HWIN CreateTimeSetupWindow(void);

#endif
