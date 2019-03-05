#include "crc.h"
#include "backup.h"
#include "guivars.h"
#include "flash.h"
uint32_t calcCRCofBKP(void)
{
	uint32_t dataInBKP[5] = { 0, 0, 0, 0, 0 };
	dataInBKP[0] = rtc_read_backup_reg(BKP_DATE_OFFSET);  						 //date
	dataInBKP[0] |= (rtc_read_backup_reg(BKP_LINE1_OFFSET) << 16);                   //line 1
	dataInBKP[1] = rtc_read_backup_reg(BKP_LINE2_OFFSET);  						 //line 2 
	dataInBKP[1] |= (rtc_read_backup_reg(BKP_LINE3_OFFSET) << 16);                   //line 3
	dataInBKP[2] = rtc_read_backup_reg(BKP_LINE4_OFFSET);  						 //line 4
	dataInBKP[2] |= (rtc_read_backup_reg(BKP_DAYLIGHTSAVING_OFFSET) << 16);          //daylightsaving 8 бит из 16.
	dataInBKP[3] = rtc_read_backup_reg(BKP_TIMECALIBR_OFFSET);  				     //
	dataInBKP[3] |= (rtc_read_backup_reg(BKP_LINES_TIMEZONE_OFFSET) << 16);
	dataInBKP[4] = rtc_read_backup_reg(BKP_SETTINGS_OFFSET);
	CRC->CR |= CRC_CR_RESET;
	CRC->DR = dataInBKP[0];
	CRC->DR = dataInBKP[1];
	CRC->DR = dataInBKP[2];
	CRC->DR = dataInBKP[3];
	CRC->DR = dataInBKP[4];
	return CRC->DR;
}
uint32_t calkCRCofFlash(void)
{
	uint32_t dataInFLASH[6] = { 0, 0, 0, 0, 0, 0 };
	dataInFLASH[0] = flash_read(FLASH_CALIA_OFFSET);
	dataInFLASH[1] = flash_read(FLASH_CALIB_OFFSET);
	dataInFLASH[2] = flash_read(FLASH_CALIC_OFFSET);
	dataInFLASH[3] = flash_read(FLASH_CALID_OFFSET);
	dataInFLASH[4] = flash_read(FLASH_CALIE_OFFSET);
	dataInFLASH[5] = flash_read(FLASH_CALIF_OFFSET);
	CRC->CR |= CRC_CR_RESET;
	CRC->DR = dataInFLASH[0];
	CRC->DR = dataInFLASH[1];
	CRC->DR = dataInFLASH[2];
	CRC->DR = dataInFLASH[3];
	CRC->DR = dataInFLASH[4];
	CRC->DR = dataInFLASH[5];
	return CRC->DR;


}
uint8_t isCRC_OK_Flash(void)
{
	uint32_t CRCinFLASH = 0;
	CRCinFLASH = flash_read(FLASH_CRC_OFFSET);
	if (CRCinFLASH == calkCRCofFlash())
	{
		return 1;
	}
	else
	{
		return 0;
	}
	return 0;
}
uint8_t isCRC_OK_BKP(void)
{
	uint32_t calculatedCRC = calcCRCofBKP();
	uint32_t CRCinBKP = 0;
	CRCinBKP = rtc_read_backup_reg(BKP_CRC_OFFSET_LOW);
	CRCinBKP |= (rtc_read_backup_reg(BKP_CRC_OFFSET_HIGH) << 16);
	if (CRCinBKP == calculatedCRC)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	return 0;
}