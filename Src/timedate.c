#include "timedate.h"
extern GUI_Vars gui_Vars;
extern Lines line[4];

bool isDaylightSavingTimeUS(unsigned char day, unsigned char month, unsigned char dow)
{
	//January, february, and december are out.
	if(month < 3 || month > 11)
	{
		return false;
	}
	//April to October are in
	if(month > 3 && month < 11)
	{
		return true;
	}
	int previousSunday = day - dow;
	//In march, we are DST if our previous sunday was on or after the 8th.
	if(month == 3) { return previousSunday >= 8; }
	//In november we must be before the first sunday to be dst.
	//That means the previous sunday must be before the 1st.
	return previousSunday <= 0;
}
bool isDaylightSavingTimeEU(unsigned char day, unsigned char month, unsigned char dow)
{
	if (month < 3 || month > 10)  return false;
	if (month > 3 && month < 10)  return true;

	int previousSunday = day - dow;

	if (month == 3) return previousSunday >= 25;
	if (month == 10) return previousSunday < 25;

	return false; // this line never gonna happend
}
void correctDate(RTC_DateTypeDef* Date)
{
	if (Date->Date > 28)
	{
		char outString[3];
		if (Date->Month == 1 || Date->Month == 3 || Date->Month == 5 || Date->Month == 7 || Date->Month == 8 || Date->Month == 10 || Date->Month == 12)
		{
			if (Date->Date > 31)
			{
				Date->Date = 31;
			}
		}
		else if (Date->Month == 4 || Date->Month == 6 || Date->Month == 9 || Date->Month == 11)
		{
			if (Date->Date > 30)
			{
				Date->Date = 30;
			}
		}
		else if (Date->Month == 2) //Если февраль
			{
				if ((Date->Year % 400 == 0 || (Date->Year % 4 == 0 && Date->Year % 100 != 0))) //Если високосный год
					{
						if (Date->Date > 29)
						{
							Date->Date = 29;
						}
					}
				else

				{
					if (Date->Date > 28)
					{
						Date->Date = 28;
					}
				}
			}
	}
}
uint8_t increaseDay(RTC_DateTypeDef* Date)
{
	if (Date->Month == 1 || Date->Month == 3 || Date->Month == 5 || Date->Month == 7 || Date->Month == 8 || Date->Month == 10 || Date->Month == 12)
	{
		if (Date->Date != 31)
		{
			Date->Date++;
		}
	}
	else if (Date->Month == 4 || Date->Month == 6 || Date->Month == 9 || Date->Month == 11)
	{
		if (Date->Date != 30)
		{
			Date->Date++;
		}
	}
	else if (Date->Month == 2) //Если февраль
		{
			if ((Date->Year % 400 == 0 || (Date->Year % 4 == 0 && Date->Year % 100 != 0))) //Если високосный год
				{
					if (Date->Date != 29)
					{
						Date->Date++;
					}
				}
			else

			{
				if (Date->Date != 28)
				{
					Date->Date++;
				}
			}
		}
}

uint8_t getLastDayOfMonth(RTC_DateTypeDef* Date)
{
	if (Date->Month == 1 || Date->Month == 3 || Date->Month == 5 || Date->Month == 7 || Date->Month == 8 || Date->Month == 10 || Date->Month == 12)
	{
		return 31;
	}
	else if (Date->Month == 4 || Date->Month == 6 || Date->Month == 9 || Date->Month == 11)
	{
		return 30;
	}
	else if (Date->Month == 2) //Если февраль
		{
			if ((Date->Year % 400 == 0 || (Date->Year % 4 == 0 && Date->Year % 100 != 0))) //Если високосный год
				{
					return 29;
				}
			else

			{
				return 28;
			}
		}
}
uint8_t hoursToUTC(int8_t hours, int8_t timeZone)
{
	hours %= 24;
	hours = hours - timeZone;
	if (hours < 0)
	{
		hours = 24 + hours;
	}
	return hours % 24;
}
uint8_t correctHours(int8_t hours)
{
	hours %= 24;
	if (hours < 0)
	{
		hours = 24 + hours;
	}
	return hours;
}