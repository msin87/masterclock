#ifndef BACKUP_H
#define BACKUP_H
#include "cmsis_os.h"
void rtc_write_backup_reg(uint16_t BackupRegister, uint16_t data);
uint16_t rtc_read_backup_reg(uint16_t BackupRegister);
void saveDateToBKP(void);
void saveLineToBKP(uint8_t lineNumber);
void saveDaylightSavingToBKP(void);
void readDaylightSavingFromBKP(void);
void saveTimeCalibrToBKP(void);
void readTimeCalibrFromBKP(void);
void saveLinesPolarityToBKP(void);
void readLinesPolarityFromBKP(void);
uint16_t rtc_read_backup_reg(uint16_t BackupRegister);
void readSettingsFromBKP(void);
void saveSettingsToBKP(void);
#endif