#ifndef TOUCH_H
#define TOUCH_H	
#include "cmsis_os.h"
#include "stm32f1xx_hal.h"
#include "callbacks.h"
#include "DIALOG.h"
#include "sram.h"
#include "GUI.h"
#include "lcdcmd.h"
#include <stdlib.h>
#include "guivars.h"
#define CMD_RDX 0X90  //0B10010000
#define CMD_RDY	0XD0  //0B11010000
#define TCS   (1<<7)  // PB7   
#define TCS_SET(x) GPIOB->BSRR=(x ? GPIO_BSRR_BS7:GPIO_BSRR_BR7)
#define PEN  HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6)
#define RESCALE_FACTOR 1000000

#define u8 uint8_t
#define u16 uint16_t


typedef struct
{
	uint8_t counter;
	uint8_t touch_it;
	uint8_t a;
	uint16_t X;
	uint16_t Y;
	int32_t X_filtered, Y_filtered;
	uint8_t calibrated;
} Variables;

//u16 SPI_SendByte(u8 byte);
//u16 SPI_ReadByte(u8 a);

extern SPI_HandleTypeDef hspi1;
uint8_t read_once(Variables* var);
extern unsigned int X, Y;
void Calibrate(Variables *var);
void touch_correct(Variables *var);
void CalibrDataRead(Variables *var);
uint8_t ReadTouchXY(Variables *var);
extern char s[10];
extern TimeCalibration timeCalibr;
void touch_control(Variables *var);




#endif
