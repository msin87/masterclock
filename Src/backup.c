#include "backup.h"
#include "stm32f1xx_hal.h"
#include "guivars.h"

extern RTC_HandleTypeDef hrtc;
extern MasterClock masterClock;
void rtc_write_backup_reg(uint16_t BackupRegister, uint16_t data)
{
	uint32_t bkpCRC = 0;
	RTC_HandleTypeDef RtcHandle;
	RtcHandle.Instance = RTC;
	HAL_PWR_EnableBkUpAccess();
	HAL_RTCEx_BKUPWrite(&RtcHandle, BackupRegister, data);
	bkpCRC = calcCRCofBKP();                 //рассчет новой CRC для регистров BKP
	HAL_RTCEx_BKUPWrite(&RtcHandle, BKP_CRC_OFFSET_HIGH, bkpCRC >> 16);                 //запись старших 16 бит CRC (Маска 0xFFFF0000)
	HAL_RTCEx_BKUPWrite(&RtcHandle, BKP_CRC_OFFSET_LOW, bkpCRC & 0xFFFF);                 //запись младших 16 бит CRC
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
			dataToBKP = (~(masterClock.line[i].TimeZone)) & 0xFF;                 //если отрицательное, то инверсия и флаг отрицательного.
			dataToBKP |= 0b10000;
		}
		buff |= (dataToBKP << ((i - 1) * 5));
	}

	rtc_write_backup_reg(BKP_LINES_TIMEZONE_OFFSET, buff);

}