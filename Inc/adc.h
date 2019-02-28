#ifndef ADC_H
#define ADC_H
#include "cmsis_os.h"
#include "guivars.h"
void _startCurrentSense(void);
void _stopCurrentSense(void);
#endif
void refreshCurrentMeter(CurrentSense*);