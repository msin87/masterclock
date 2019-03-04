#include "touch.h"
#include "flash.h"
#include "crc.h"
#include "backup.h"
#include "cmsis_os.h"
#include "main.h"
#define TOLERANCE 20

//unsigned int Xs_1=0,Xs_2=0,Xs_3=0,Xs_4=0,Ys_1=0,Ys_2=0,Ys_3=0,Ys_4=0; //јЗВјґҐЧш±кЦµ
char s[10];
GUI_PID_STATE touchState;
volatile int32_t cali_A = 0, cali_B = 0, cali_C = 0, cali_D = 0, cali_E = 0, cali_F = 0;

void Draw_Point(uint16_t x, uint16_t y, uint16_t color, uint8_t size)
{
	uint8_t j, i = 0;

	for (j = 0; j < size; j++)
	{
		Set_Cursor(x + j, y);
		for (i = 0; i < size; i++)
		{
			Lcd_Write_Data(color);
		}
	}
}
void Draw_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color, uint8_t size)
{
	int deltaX = abs(x2 - x1);
	int deltaY = abs(y2 - y1);
	int signX = x1 < x2 ? 1 : -1;
	int signY = y1 < y2 ? 1 : -1;
	int error = deltaX - deltaY;
	int error2 = error * 2;

	for (;;)
	{
		Draw_Point(x1, y1, color, size);

		if (x1 == x2 && y1 == y2)
			break;



		if (error2 > -deltaY)
		{
			error -= deltaY;
			x1 += signX;
		}

		if (error2 < deltaX)
		{
			error += deltaX;
			y1 += signY;
		}
	}
}
void DrawCross(u16 Y, u16 X, u16 L, unsigned int color)
{
	u16 x1_line1, x2_line1;
	u16 y1_line2, y2_line2;

	x1_line1 = X - (L / 2);
	x2_line1 = X + (L / 2);
	y1_line2 = Y - (L / 2);
	y2_line2 = Y + (L / 2);


	Draw_Line(x1_line1, Y, x2_line1, Y, color, 1);
	Draw_Line(X, y1_line2, X, y2_line2, color, 1);
}







uint8_t read_once(Variables* var)
{
	uint8_t a;
	uint32_t recieved;
	uint8_t buff;
	buff = CMD_RDX;
	TCS_SET(0);
	osDelay(1);
	HAL_SPI_Transmit(&hspi1, &buff, 1, 200);
	osDelay(1);
	buff = 0;
	HAL_SPI_TransmitReceive(&hspi1, &buff, &a, 1, 200);
	recieved = a << 8;
	//buff=0;
	HAL_SPI_TransmitReceive(&hspi1, &buff, &a, 1, 200);
	recieved |= a;
	osDelay(1);
	TCS_SET(1);
	var->Y = recieved >> 3;
	osDelay(1);
	TCS_SET(0);
	osDelay(1);
	buff = CMD_RDY;
	HAL_SPI_Transmit(&hspi1, &buff, 1, 10);
	osDelay(1);
	buff = 0;
	HAL_SPI_TransmitReceive(&hspi1, &buff, &a, 1, 200);
	recieved = a << 8;
	HAL_SPI_TransmitReceive(&hspi1, &buff, &a, 1, 200);
	recieved |= a;
	osDelay(1);
	var->X = recieved >> 3;
	TCS_SET(1);
	var->touch_it = !HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6);
	var->X = 4096 - var->X;
	if (var->X < 100)
	{
		var->X = 0;
	}
	if (var->X > 100 && var->Y > 100 && var->X < 4000 && var->Y < 4000)return 1;
	else return 0;
}

uint8_t ReadTouchXY(Variables *var)
{
	u8 readcomplete = 0;
	float X1, Y1;
	u16 buffer_x[10];
	u16 buffer_y[10];
	u16 x1, x2, y1, y2, temp = 0;
	u8 count = 0;
	u8 count2 = 0;
	u8 t1 = 0;


	//var->a=touch;

	while(var->touch_it&&count < 10)
	{
		if (read_once(var))
		{
			buffer_x[count] = var->X;
			buffer_y[count] = var->Y;
			count++;

		}
	}


	if (count == 10)
	{
		do
		{
			t1 = 0;
			for (count2 = 0; count2 < count - 1; count2++)
			{
				if (buffer_x[count2] > buffer_x[count2 + 1])
				{
					temp = buffer_x[count2 + 1];
					buffer_x[count2 + 1] = buffer_x[count2];
					buffer_x[count2] = temp;
					t1 = 1;
				}
			}
		} while (t1);

		do
		{
			t1 = 0;
			for (count2 = 0; count2 < count - 1; count2++)
			{
				if (buffer_y[count2] > buffer_y[count2 + 1])
				{
					temp = buffer_y[count2 + 1];
					buffer_y[count2 + 1] = buffer_y[count2];
					buffer_y[count2] = temp;
					t1 = 1;
				}
			}
		} while (t1);

		x1 = buffer_x[3]; x2 = buffer_x[4];
		y1 = buffer_y[3]; y2 = buffer_y[4];
		if (((x1 > x2) && (x1 > x2 + TOLERANCE)) || ((x2 > x1) && (x2 > x1 + TOLERANCE)) || ((y1 > y2) && (y1 > y2 + TOLERANCE)) || ((y2 > y1) && (y2 > y1 + TOLERANCE))) ;
		else
		{
			X1 = (buffer_x[3] + buffer_x[4]) / 2;
			Y1 = (buffer_y[3] + buffer_y[4]) / 2;
			if (X1 <= 4096 && Y1 <= 4096)
			{
				var->X = X1;
				var->Y = Y1;
				readcomplete = 1;
			}
		}

		var->a = PEN;
		count = 0;
	}
	if (readcomplete)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void touch_correct(Variables *var)
{
	var->X_filtered = (cali_A * var->X + cali_B * var->Y + cali_C) / RESCALE_FACTOR;
	var->Y_filtered = (cali_D * var->X + cali_E * var->Y + cali_F) / RESCALE_FACTOR;
}
void Calibrate(Variables *var)
{


	char complete = 0;
	double temp1, temp2;
	double cal_A = 0.0, cal_B = 0.0, cal_C = 0.0, cal_D = 0.0, cal_E = 0.0, cal_F = 0.0;
	uint32_t xt1, xt2, xt3;
	uint32_t yt1, yt2, yt3;
	struct Point
	{
		u16  X;
		u16 Y;
		unsigned int Color;
	};
	struct Point cpoint1, cpoint2, cpoint3;

	cpoint1.X = 32;
	cpoint1.Y = 120;
	cpoint1.Color = 0x001F;

	cpoint2.X = 160;
	cpoint2.Y = 216;
	cpoint2.Color = 0x07E0;

	cpoint3.X = 288;
	cpoint3.Y = 24;
	cpoint3.Color = 0xF800;

	DrawCross(cpoint1.X, cpoint1.Y, 20, cpoint1.Color);
	while (1)
	{
		if (var->touch_it == 1)
		{
			osDelay(340);
			var->a = PEN;
			if (var->a == 0)
			{
				while (var->a == 0)
				{
					osDelay(1);
					ReadTouchXY(var);
					osDelay(1);
					xt1 = var->X;
					yt1 = var->Y;
					//sprintf(s, "%4d %4d", xt1, yt1);
					//TFT_ShowString(32,90,(u8*)s, RED,LIGHTGRAY1);
					var->a = PEN;
					var->touch_it = 0;
					break;
				}
				break;
			}
			else var->touch_it = 0;
		}
	}
	var->touch_it = 0;
	DrawCross(cpoint2.X, cpoint2.Y, 20, cpoint2.Color);
	while (1)
	{
		if (var->touch_it == 1)
		{
			osDelay(340);
			var->a = PEN;
			if (var->a == 0)
			{
				while (var->a == 0)
				{
					osDelay(1);
					ReadTouchXY(var);
					osDelay(1);
					xt2 = var->X;
					yt2 = var->Y;
					//sprintf(s, "%4d %4d", xt2, yt2);
					//TFT_ShowString(180,200,(u8*)s, GREEN,LIGHTGRAY1);
					var->a = PEN;
					var->touch_it = 0;
					break;
				}
				break;
			}
			else var->touch_it = 0;
		}
	}
	var->touch_it = 0;
	DrawCross(cpoint3.X, cpoint3.Y, 20, cpoint3.Color);
	while (1)
	{
		if (var->touch_it == 1)
		{
			osDelay(340);
			var->a = PEN;
			if (var->a == 0)
			{
				while (var->a == 0)
				{
					osDelay(1);
					ReadTouchXY(var);
					osDelay(1);
					xt3 = var->X;
					yt3 = var->Y;
					//sprintf(s, "%4d %4d", xt3, yt3);
					//TFT_ShowString(240,40,(u8*)s, BLUE,LIGHTGRAY1);
					var->a = PEN;
					var->touch_it = 0;
					complete = 1;
					break;
				}
				break;
			}
			else var->touch_it = 0;
		}
	}
	if (complete == 1)
	{
		//A
		temp1 = ((double)cpoint1.X * ((double)yt2 - (double)yt3)) + ((double)cpoint2.X * ((double)yt3 - (double)yt1)) + ((double)cpoint3.X * ((double)yt1 - (double)yt2));
		temp2 = ((double)xt1 * ((double)yt2 - (double)yt3)) + ((double)xt2 * ((double)yt3 - (double)yt1)) + ((double)xt3 * ((double)yt1 - (double)yt2));
		cal_A = temp1 / temp2;
		cali_A = (int32_t)((double)cal_A * RESCALE_FACTOR);
		//sprintf(s, "A=%4d", cali_A);
		//TFT_ShowString(140,120,(u8*)s, GRED,LIGHTGRAY1);
		//B
		temp1 = (cal_A * ((double)xt3 - (double)xt2)) + (double)cpoint2.X - (double)cpoint3.X;
		temp2 = (double)yt2 - (double)yt3;
		cal_B = temp1 / temp2;
		cali_B = (int32_t)((double)cal_B * RESCALE_FACTOR);
		//sprintf(s, "B=%4d", cali_B);
		//TFT_ShowString(140,130,(u8*)s, GRED,LIGHTGRAY1);
		//C
		cal_C = (double)cpoint3.X - (cal_A * (double)xt3) - (cal_B * (double)yt3);
		cali_C = (int32_t)(cal_C * RESCALE_FACTOR);
		//sprintf(s, "C=%4d", cali_C);
		//TFT_ShowString(140,140,(u8*)s, GRED,LIGHTGRAY1);
		//D
		temp1 = ((double)cpoint1.Y * ((double)yt2 - (double)yt3)) + ((double)cpoint2.Y * ((double)yt3 - (double)yt1)) + ((double)cpoint3.Y * ((double)yt1 - (double)yt2));
		temp2 = ((double)xt1 * ((double)yt2 - (double)yt3)) + ((double)xt2 * ((double)yt3 - (double)yt1)) + ((double)xt3 * ((double)yt1 - (double)yt2));
		cal_D = (double)temp1 / (double)temp2;
		cali_D = (int32_t)(cal_D * RESCALE_FACTOR);
		//sprintf(s, "D=%4d", cali_D);
		//TFT_ShowString(140,150,(u8*)s, GRED,LIGHTGRAY1);
		//E
		temp1 = (cal_D * ((double)xt3 - (double)xt2)) + (double)cpoint2.Y - (double)cpoint3.Y;
		temp2 = (double)yt2 - (double)yt3;
		cal_E = (double)temp1 / (double)temp2;
		cali_E = (int32_t)(cal_E * RESCALE_FACTOR);
		//sprintf(s, "E=%4d", cali_E);
		//TFT_ShowString(140,160,(u8*)s, GRED,LIGHTGRAY1);
		//F
		cal_F = (double)cpoint3.Y - cal_D * (double)xt3 - cal_E * (double)yt3;
		cali_F = (int32_t)(cal_F * RESCALE_FACTOR);
		//sprintf(s, "F=%4d", cali_F);
		//TFT_ShowString(140,170,(u8*)s, GRED,LIGHTGRAY1);

		/*FlashSectorEarse(0);
		Save_int32_t(cali_A, 0x00);
		Save_int32_t(cali_B, 0x04);
		Save_int32_t(cali_C, 0x08);
		Save_int32_t(cali_D, 0x12);
		Save_int32_t(cali_E, 0x16);
		Save_int32_t(cali_F, 0x20);
		*/
		flash_unlock();
		flash_erase_page(0x0807F800);
		flash_write(FLASH_CALIA_OFFSET, cali_A);
		flash_write(FLASH_CALIB_OFFSET, cali_B);
		flash_write(FLASH_CALIC_OFFSET, cali_C);
		flash_write(FLASH_CALID_OFFSET, cali_D);
		flash_write(FLASH_CALIE_OFFSET, cali_E);
		flash_write(FLASH_CALIF_OFFSET, cali_F);
		flash_write(FLASH_CRC_OFFSET, calkCRCofFlash());
		flash_lock();
		var->calibrated = 1;

	}
}
void CalibrDataRead(Variables *var)
{
	uint8_t t[2];
	cali_A = flash_read(FLASH_CALIA_OFFSET);
	cali_B = flash_read(FLASH_CALIB_OFFSET);
	cali_C = flash_read(FLASH_CALIC_OFFSET);
	cali_D = flash_read(FLASH_CALID_OFFSET);
	cali_E = flash_read(FLASH_CALIE_OFFSET);
	cali_F = flash_read(FLASH_CALIF_OFFSET);
	if (isCRC_OK_Flash())
	{
		var->calibrated = 1;
	}
	else
	{
		var->calibrated = 0;
	}
	readTimeCalibrFromBKP();

}


void touch_control(Variables *var)
{


	var->a = PEN;
	var->touch_it = !HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6);
	if (var->calibrated)
	{
		if (var->touch_it == 1)
		{
			__TURN_BACKLIGHT_ON;
			masterClock.guiVars->lockCountDown = masterClock.guiVars->lockCountDownInitial;
			if (ReadTouchXY(var))
			{
				touch_correct(var);
				touchState.Pressed = 1;

				touchState.x = var->X_filtered;
				touchState.y = var->Y_filtered;

				GUI_TOUCH_StoreStateEx(&touchState);
			}
		}
		else
		{
			touchState.Pressed = 0;
			GUI_TOUCH_StoreStateEx(&touchState);

		}
	}

}






