#include "adc.h"
#include "stm32f1xx_hal.h"
#include <stdbool.h>
extern MasterClock masterClock;
extern ADC_HandleTypeDef hadc1;

bool isAnyLineOn(void)
{
	uint32_t linesState = 0;
	uint8_t i;
	for (i = 0; i < (sizeof(masterClock.line) / sizeof(masterClock.line[0])) - 1; ++i)
	{
		linesState |= (masterClock.line[i].LineGPIOneg->ODR&masterClock.line[i].LinePinNeg);
		linesState |= (masterClock.line[i].LineGPIOpos->ODR&masterClock.line[i].LinePinPos);
	}
	return (linesState != 0) ? true : false;
}
void _startCurrentSense(void)
{
	uint32_t size = sizeof(masterClock.currentSense->ADCdata);
	if (!isAnyLineOn())
	{
		HAL_ADC_Start_DMA(&hadc1, (uint32_t*)masterClock.currentSense->ADCdata, sizeof(masterClock.currentSense->ADCdata) / 2);
	}
}
void _stopCurrentSense(void)
{
	if (!isAnyLineOn())
	{
		HAL_ADC_Stop_DMA(&hadc1);
	}
}
static uint32_t _filterAverage(uint16_t* buffer)
{
	uint8_t i = 0;
	uint32_t result = 0;
	for (i = 0; i < (sizeof(buffer) / 2); i++)
	{
		result += buffer[i];
	}
	result /= (sizeof(buffer) / 2);
	return result;
}

void refreshCurrentMeter(CurrentSense* currentSense)
{
	if (currentSense->DMAtransferComplete)
	{
		WM_MESSAGE msg;
		currentSense->currentLevel = _filterAverage(currentSense->ADCdata);
		msg.MsgId = WM_CURRENTMETER_UPDATE;
		sendMsg(masterClock.handles->hMainMenu, WM_CURRENTMETER_UPDATE); 
		currentSense->DMAtransferComplete = 0;
	}
}