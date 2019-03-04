#ifndef TIMEDATE_H
#define TIMEDATE_H
#include "cmsis_os.h"
#include "guivars.h"
#include <stdbool.h>

bool isDaylightSavingTimeUS(unsigned char day, unsigned char month, unsigned char dow);
bool isDaylightSavingTimeEU(unsigned char day, unsigned char month, unsigned char dow);
void correctDate(RTC_DateTypeDef* Date);
uint8_t increaseDay(RTC_DateTypeDef* Date);
uint8_t getLastDayOfMonth(RTC_DateTypeDef* Date);
uint8_t hoursToUTC(int8_t hours, int8_t timeZone);
uint8_t correctHours(int8_t hours);

#endif