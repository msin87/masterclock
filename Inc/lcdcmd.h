#ifndef LCDCMD_H
#define LCDCMD_H
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#define ENTRY_MODE 0<<15|0<<14|0<<12|0<<7|0<<5|0<<4|0<<3
//									TRI		DFM		BGR		ORG	 I/D[1:0]	 AM
	/*******************************************************************/
// Определяем адреса, по которым будем записывать данные
// Для записи данных
	#define LCD_DATA    			    ((unsigned int)0x60020000)    
	// Для записи команд
	#define LCD_REG   		  	    ((unsigned int)0x60000000)	
	void writeLCDCommand(uint16_t reg,uint16_t value);
	void writeLCDData(uint16_t data);	
	unsigned int readPixel(int x, int y);
	void plotpx(int x, int y, uint16_t color);
	void LCD_Init(void);
	void clearLCD(int x1, int x2, int y1, int y2, uint16_t color );
	uint16_t LCD_ReadReg(uint16_t LCD_Reg);
	void Lcd_Write_Index(uint16_t index);
void Lcd_Write_Data(uint16_t data);
void Lcd_Write_Reg(uint16_t lcd_reg, uint16_t lcd_data);
uint16_t Lcd_Read_Reg(uint16_t reg_addr);
	void Set_Work_Area(uint16_t y1, uint16_t x1, uint16_t y2, uint16_t x2);
	void Set_Cursor(uint16_t x_kur, uint16_t y_kur);
	void Init_SSD1289(void);
	
	#define yellow 	  0x07FF
#define magneta   0xF81F
#define cyan      0xFFE0
#define	red		  	0X001F
#define	green	  	0X07E0
#define	blue      0XF800
#define white     0XFFFF
#define black     0X3185
	
#endif
