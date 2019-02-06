#include "lcdcmd.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"

__inline void Lcd_Write_Index(uint16_t index)
{
	*(uint16_t *) (LCD_REG) = index;	
}
////////////////////////

__inline void Lcd_Write_Data(uint16_t data)
{   
    *(uint16_t *) (LCD_DATA)= data; 	
}
///////////////////
uint16_t Lcd_Read_Data()
{
		uint16_t data = * (uint16_t *)(LCD_DATA);
		return data;	
}
////////////////////////
//??? ????? ????? ????	
uint16_t Lcd_Read_Reg(uint16_t reg_addr)
{
	volatile uint16_t data = 0;
	
	Lcd_Write_Index(reg_addr);
	data = Lcd_Read_Data();
	
	return data;
}
void Set_Work_Area(uint16_t y1, uint16_t x1, uint16_t y2, uint16_t x2)
{
	
	Lcd_Write_Reg(0x0044,((x2 << 8) | x1));
	Lcd_Write_Reg(0x0045,y1);
	Lcd_Write_Reg(0x0046,y2);
	Set_Cursor(x1, y1);
}
void Set_Cursor(uint16_t x_kur, uint16_t y_kur)
{	
	Lcd_Write_Reg(0x004e,x_kur);
	Lcd_Write_Reg(0x004f,y_kur);
	Lcd_Write_Index(0x0022);

}
///////////////////////
//??? ????? ?????????
void Lcd_Write_Reg(uint16_t reg,uint16_t value)
{	
    *(uint16_t *) (LCD_REG) = reg;	
    *(uint16_t *) (LCD_DATA) = value;
}
//////////////////
//??? ???? ??? ????

////////////////////////
//??? ????????? ?????????
void Lcd_Clear(uint16_t color)
{
	uint32_t index = 0;
	
	Set_Cursor(0,0);	
	
	  for(index=0;index < 76800;index++)
	  { 			
		  Lcd_Write_Data(color);
	  }
}
/*******************************************************************/
// Так мы будем писать команды в регистры LCD
void writeLCDCommand(uint16_t reg,uint16_t value)
{	
    *(uint16_t*) (LCD_REG) = reg;	
    *(uint16_t*) (LCD_DATA) = value;
}
 
 
 
/*******************************************************************/
// А так данные..
void writeLCDData(uint16_t data)
{   
    *(uint16_t*) (LCD_DATA)= data; 	
}

uint16_t LCD_ReadReg(uint16_t LCD_Reg)
{
	uint16_t data;
    *(unsigned short*) (LCD_REG) = LCD_Reg;
    data = * (unsigned short *)(LCD_DATA);
	return data;
}

unsigned int readPixel(int x, int y)
{
		unsigned short data=0;
  	//writeLCDCommand(32, x);
  	//writeLCDCommand(33, y);
	  writeLCDCommand(0x004e, x);
  	writeLCDCommand(0x004f, y);
		*(unsigned short*) (LCD_REG) = 0x22;
  	data = * (unsigned short *)(LCD_DATA);
	  data = 0;
  	data = * (unsigned short *)(LCD_DATA);
		return data;
}
void plotpx(int x, int y, uint16_t color)
{
		/*writeLCDCommand(32, x);
  	writeLCDCommand(33, y);
		*(unsigned short*) (LCD_REG) = 0x22;
		writeLCDData(color);*/
	 
		writeLCDCommand(0x004e, x);
		writeLCDCommand(0x004f, y	); 
		*(uint16_t*) (LCD_REG) = 0x22;
		writeLCDData(color);
}
void LCD_Init(void)
{
//    uint16_t id=0;
		
		GPIOE->BSRR |= GPIO_BSRR_BR1; 
    HAL_Delay(50);				   
    GPIOE->BSRR |= GPIO_BSRR_BS1;  	 
    HAL_Delay(50);
    
		writeLCDCommand(0x0000,0x0001);    HAL_Delay(50);   /* Enable LCD Oscillator */
	    writeLCDCommand(0x0003,0xA8A4);    HAL_Delay(50);   
	    writeLCDCommand(0x000C,0x0000);    HAL_Delay(50);   
	    writeLCDCommand(0x000D,0x080C);    HAL_Delay(50);   
	    writeLCDCommand(0x000E,0x2B00);    HAL_Delay(50);   
	    writeLCDCommand(0x001E,0x00B0);    HAL_Delay(50);   
		Lcd_Write_Reg(0x0001,0<<15|1<<14|1<<13|0<<12|0<<11|0<<10|1<<9|1<<8|0<<7|0<<6|1<<5|1<<4|1<<3|1<<2|1<<1|1);
    HAL_Delay(50);   /* 320*240 0x2B3F */
	    writeLCDCommand(0x0002,0x0600);    HAL_Delay(50);
	    writeLCDCommand(0x0010,0x0000);    HAL_Delay(50);
	    Lcd_Write_Reg(0x0011,0<<15|1<<14|1<<13|0<<12|1<<11|0<<10 |0<<9  |0<<8  |0<<7|0<<6|1<<5|1<<4|0<<3|0<<2|0<<1|0);
;    HAL_Delay(50);
	    writeLCDCommand(0x0005,0x0000);    HAL_Delay(50);
	    writeLCDCommand(0x0006,0x0000);    HAL_Delay(50);
	    writeLCDCommand(0x0016,0xEF1C);    HAL_Delay(50);
	    writeLCDCommand(0x0017,0x0003);    HAL_Delay(50);
	    writeLCDCommand(0x0007,0x0133);    HAL_Delay(50);         
	    writeLCDCommand(0x000B,0x0000);    HAL_Delay(50);
	    writeLCDCommand(0x000F,0x0000);    HAL_Delay(50);
	    writeLCDCommand(0x0041,0x0000);    HAL_Delay(50);
	    writeLCDCommand(0x0042,0x0000);    HAL_Delay(50);
	    writeLCDCommand(0x0048,0x0000);    HAL_Delay(50);
	    writeLCDCommand(0x0049,0x013F);    HAL_Delay(50);
	    writeLCDCommand(0x004A,0x0000);    HAL_Delay(50);
	    writeLCDCommand(0x004B,0x0000);    HAL_Delay(50);
	    writeLCDCommand(0x0044,0xEF00);    HAL_Delay(50);
	    writeLCDCommand(0x0045,0x0000);    HAL_Delay(50);
	    writeLCDCommand(0x0046,0x013F);    HAL_Delay(50);
	    writeLCDCommand(0x0030,0x0707);    HAL_Delay(50);
	    writeLCDCommand(0x0031,0x0204);    HAL_Delay(50);
	    writeLCDCommand(0x0032,0x0204);    HAL_Delay(50);
	    writeLCDCommand(0x0033,0x0502);    HAL_Delay(50);
	    writeLCDCommand(0x0034,0x0507);    HAL_Delay(50);
	    writeLCDCommand(0x0035,0x0204);    HAL_Delay(50);
	    writeLCDCommand(0x0036,0x0204);    HAL_Delay(50);
	    writeLCDCommand(0x0037,0x0502);    HAL_Delay(50);
	    writeLCDCommand(0x003A,0x0302);    HAL_Delay(50);
	    writeLCDCommand(0x003B,0x0302);    HAL_Delay(50);
	    writeLCDCommand(0x0023,0x0000);    HAL_Delay(50);
	    writeLCDCommand(0x0024,0x0000);    HAL_Delay(50);
	    writeLCDCommand(0x0025,0x8000);    HAL_Delay(50);
	    writeLCDCommand(0x004f,0);
	    writeLCDCommand(0x004e,0);
			writeLCDCommand(0x0011,0x6068);
		//clearLCD(0,240,0,320,blue);
}
 
void clearLCD(int x1, int x2, int y1, int y2, uint16_t color )
{
	int x;
	writeLCDCommand(0x004e, x1);
  writeLCDCommand(0x004f, y1);
  *(uint16_t*) (LCD_REG) = 0x0022;
	 for (x=x1; x <= (x2*y2); x++)
	{
			    writeLCDData(color);
	
	}
	x=0;
}
/*******************************************************************/

void Init_SSD1289(void)
{
	/*
	 // Reset дисплея
    GPIOE->BSRR |= GPIO_BSRR_BR1; 
    HAL_Delay(50);				   
    GPIOE->BSRR |= GPIO_BSRR_BS1;  	 
    HAL_Delay(50);

    //delay(10);
 
    Lcd_Write_Reg(0x0007,0x0021);
    Lcd_Write_Reg(0x0000,0x0001);
    Lcd_Write_Reg(0x0007,0x0023);
    Lcd_Write_Reg(0x0010,0x0000);

    HAL_Delay(300);
    Lcd_Write_Reg(0x007,0x0033);
		//									VSMode DFM1	 DFM0	 TRANS OEDef WMode1 WMode1 DMode0 TY1		TY0	ID1	 ID0	 AM		LG2 LG1  LG0
    Lcd_Write_Reg(0x0011,0<<15|1<<14|1<<13|0<<12|1<<11|0<<10 |0<<9  |0<<8  |0<<7|0<<6|1<<5|1<<4|0<<3|0<<2|0<<1|0);
		//										 0    RL		REV		CAD		BGR		SM		TB	MUX8 MUX7 MUX6 MUX5 MUX4 MUX3 MUX2 MUX1 MUX0
		Lcd_Write_Reg(0x0001,0<<15|1<<14|1<<13|0<<12|0<<11|0<<10|1<<9|1<<8|0<<7|0<<6|1<<5|1<<4|1<<3|1<<2|1<<1|1);
    Lcd_Write_Reg(0x0002,0x0600);
		
	  Lcd_Clear(blue);
		*/
	
}
