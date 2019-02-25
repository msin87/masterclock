#ifndef CRC_H
#define CRC_H
#include "cmsis_os.h"
uint32_t calkCRCofFlash(void);
uint32_t calcCRCofBKP(void);
uint8_t isCRC_OK_BKP(void);
uint8_t isCRC_OK_Flash(void);
#endif