#ifndef LINES_H
#define LINES_H
#include "cmsis_os.h"
#include "guivars.h"


void pollLinesOutput(uint8_t waitMinutes);
void lineSendSignal(uint8_t lineNumber);
uint16_t get_sTimeLinesDiff(Lines* lineToCheck, uint8_t waitMinutes);
void linesIncreaseMinute(uint8_t lineNumber);
void LinesInit(void);
#endif