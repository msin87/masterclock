#include "backup.h"
#include "stm32f1xx_hal.h"
#include "guivars.h"
#include "crc.h"
#include <stdbool.h>
extern RTC_HandleTypeDef hrtc;

void rtc_write_backup_reg(uint16_t BackupRegister, uint16_t data)
{
	uint32_t bkpCRC = 0;
	RTC_HandleTypeDef RtcHandle;
	RtcHandle.Instance = RTC;
	HAL_PWR_EnableBkUpAccess();
	HAL_RTCEx_BKUPWrite(&RtcHandle, BackupRegister, data);
	
	bkpCRC = calcCRCofBKP();                  //рассчет новой CRC для регистров BKP
	HAL_RTCEx_BKUPWrite(&RtcHandle, BKP_CRC_OFFSET_HIGH, bkpCRC >> 16);                  //запись старших 16 бит CRC (Маска 0xFFFF0000)
	HAL_RTCEx_BKUPWrite(&RtcHandle, BKP_CRC_OFFSET_LOW, bkpCRC & 0xFFFF);                  //запись младших 16 бит CRC
}
uint16_t rtc_read_backup_reg(uint16_t BackupRegister)
{
	RTC_HandleTypeDef RtcHandle;
	RtcHandle.Instance = RTC;
	return HAL_RTCEx_BKUPRead(&RtcHandle, BackupRegister);
}
void saveDateToBKP(void)
{
	uint16_t write = 0;
	RTC_DateTypeDef Date;

	HAL_RTC_GetDate(&hrtc, &Date, RTC_FORMAT_BIN);
	write = Date.Date;
	write |= (Date.Month << 5);
	write |= (Date.Year << 9);
	rtc_write_backup_reg(BKP_DATE_OFFSET, write);
}
void saveLineToBKP(uint8_t lineNumber)
{
	uint16_t dataToBKP = 0;
	uint8_t shift = 0, i;
	uint16_t buff = 0;
	//line timeZone:
	//	4	3	2	1	0
	//	\----timezone---/
	//		01111 = +16
	//		10000 = -16
	rtc_write_backup_reg(lineNumber + BKP_LINE1_OFFSET, ((masterClock.line[lineNumber].Hours * 60) + masterClock.line[lineNumber].Minutes) | (masterClock.line[lineNumber].Width << 11) | masterClock.line[lineNumber].Status << 14);
	if (lineNumber == 0) return;

	for (i = 1; i < LINES_AMOUNT; ++i)
	{

		if ((int8_t)masterClock.line[i].TimeZone >= 0)
		{
			dataToBKP = masterClock.line[i].TimeZone;
		}
		else
		{
			dataToBKP = (~(masterClock.line[i].TimeZone)) & 0xFF;                  //если отрицательное, то инверсия и флаг отрицательного.
			dataToBKP |= 0b10000;
		}
		buff |= (dataToBKP << ((i - 1) * 5));
	}

	rtc_write_backup_reg(BKP_LINES_TIMEZONE_OFFSET, buff);

}
void saveDaylightSavingToBKP(void)
{
	//daylight
	// 		7	6	5	4	3	2	1	0
	//		|	\---/	\----timezone---/
	//		|	  |			01111 = +16
	//		|	  |			10000 = -16
	//		|	  |
	//		|	TimeShift 
	//		|	 00 disable
	//		|	 01 +1
	//		|	 10	-1	
	//		|
	//		EnableDLS
	uint16_t dataToBKP = 0;

	if ((int8_t)masterClock.daylightSaving->timeZone >= 0)
	{
		dataToBKP = masterClock.daylightSaving->timeZone;
	}
	else
	{
		dataToBKP = (~(masterClock.daylightSaving->timeZone)) & 0xFF;                  //если отрицательное, то инверсия и флаг отрицательного.
		dataToBKP |= 0b10000;
	}
	if (masterClock.daylightSaving->timeShift < 0)
	{
		dataToBKP |= (0b10 << 5);                  //отрицательный флаг для timeShift
	}
	else
	{
		dataToBKP |= 1 << 5;
	}
	if (masterClock.daylightSaving->enableDLS == true)
	{
		dataToBKP |= 1 << 7;
	}
	rtc_write_backup_reg(BKP_DAYLIGHTSAVING_OFFSET, dataToBKP);
}
void readDaylightSavingFromBKP(void)
{
	uint16_t dataInBKP = rtc_read_backup_reg(BKP_DAYLIGHTSAVING_OFFSET);
	if (dataInBKP & 0b10000) //если флаг отрицательного числа
		{
			masterClock.daylightSaving->timeZone = (char)(~(dataInBKP & 0b1111));
		}
	else
	{
		masterClock.daylightSaving->timeZone = (char)(dataInBKP & 0b1111);
	}
	if (dataInBKP & 0b1000000) //если отрицательный флаг
		{
			masterClock.daylightSaving->timeShift = -1;

		}
	else
	{
		masterClock.daylightSaving->timeShift = (dataInBKP >> 5) & 0b11;
	}
	masterClock.daylightSaving->enableDLS = (dataInBKP >> 7);
}
void saveTimeCalibrToBKP(void)
{
	uint16_t writeBuff = 0;
	writeBuff = masterClock.timeCalibration->days;
	writeBuff |= (masterClock.timeCalibration->seconds << 8);
	//	15	14	13	12	11	10	9	8	7	6	5	4	3	2	1	0
	//  \----------seconds----------/    \---------days-------------/
	rtc_write_backup_reg(BKP_TIMECALIBR_OFFSET, writeBuff);
}
void readTimeCalibrFromBKP(void)
{
	uint16_t readBuff = 0;
	readBuff = rtc_read_backup_reg(BKP_TIMECALIBR_OFFSET);
	masterClock.timeCalibration->days = readBuff & 0xFF;
	masterClock.timeCalibration->seconds = (int8_t)(readBuff >> 8);
}
void saveLinesPolarityToBKP(void)
{
	uint16_t writeBuff = 0;
	writeBuff = rtc_read_backup_reg(BKP_DAYLIGHTSAVING_OFFSET);
	writeBuff &= 0x00FF;
	writeBuff |= (masterClock.guiVars->linesPolarity << 8);
	rtc_write_backup_reg(BKP_LINESPOLARITY_OFFSET, writeBuff);

}
void readLinesPolarityFromBKP(void)
{
	uint16_t readBuff = 0;
	readBuff = rtc_read_backup_reg(BKP_DAYLIGHTSAVING_OFFSET);
	masterClock.guiVars->linesPolarity = readBuff >> 8;
}