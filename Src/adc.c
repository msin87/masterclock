#include "adc.h"
#include "stm32f1xx_hal.h"
#include "guivars.h"
#include <stdbool.h>
extern MasterClock masterClock;
extern ADC_HandleTypeDef hadc1;

bool isAnyLineOn(void)
{
	uint32_t linesState = 0;
	uint8_t i;
	for (i = 0; i < sizeof(masterClock.line) - 1; ++i)
	{
		linesState |= (masterClock.line[i].LineGPIOneg->ODR&masterClock.line[i].LinePinNeg);
		linesState |= (masterClock.line[i].LineGPIOpos->ODR&masterClock.line[i].LinePinPos);
	}
	return (linesState != 0) ? true : false;
}
void _startCurrentSense(void)
{
	if (!isAnyLineOn())
	{
		HAL_ADC_Start_DMA(&hadc1, (uint32_t*)masterClock.currentSense->ADCdata, sizeof(masterClock.currentSense->ADCdata));
	}
}
void _stopCurrentSense(void)
{
	if (!isAnyLineOn())
	{
		HAL_ADC_Stop_DMA(&hadc1);
	}
}