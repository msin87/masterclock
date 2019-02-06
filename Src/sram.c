#include "sram.h"


u16 SPI_ReadByte(u8 a)
{
  return (SPI_SendByte(a));
}
u16 SPI_SendByte(u8 tx_buff)
{
	uint8_t rx_buff;
  HAL_SPI_TransmitReceive(&hspi1,&tx_buff, &rx_buff, 1, 100); 
	return rx_buff;
}
void FlashWaitBusy(void)//Flash???
{

  u8 FLASH_Status = 0;

  Select_Flash();	

  SPI_ReadByte(RDSR);//???

  do
  {

    FLASH_Status = SPI_ReadByte(Dummy_Byte);

  }
  while ((FLASH_Status & WIP_Flag) == SET); 
  NotSelect_Flash();	   

}
void FlashSectorEarse(u16 page) //??????,???0-4095
{	

  FlashWaitBusy();//Flash???
  Select_Flash(); //CS?"0"
  SPI_ReadByte(WREN);	//???
  NotSelect_Flash(); //CS?"1"

  FlashWaitBusy();//Flash???
  Select_Flash(); //CS?"0"
  SPI_ReadByte(SE);  //???
  SPI_ReadByte((page & 0xFF0000) >> 16);
  SPI_ReadByte((page & 0x00FF00) >> 8);
  SPI_ReadByte(page &  0x0000FF);
  NotSelect_Flash(); //CS?"1"

}
void WriteToSRAM(u8 *buffer, unsigned int start_address,unsigned int length)
{
  unsigned int i;

  FlashWaitBusy();
  Select_Flash(); 
  
	SPI_ReadByte(WREN);	
  NotSelect_Flash(); 
  FlashWaitBusy();
  Select_Flash();
	
  SPI_ReadByte(PP);
  SPI_ReadByte((start_address & 0xFF0000) >> 16);
  SPI_ReadByte((start_address & 0xFF00) >> 8);
  SPI_ReadByte(start_address & 0xFF);
  for (i=0;i<length;i++)SPI_ReadByte(buffer[i]);

  NotSelect_Flash();
}
void ReadFromSRAM(u8 *buffer, unsigned int start_address,unsigned int length)
{
	unsigned int i;
	
	FlashWaitBusy(); 
	Select_Flash();	

  SPI_ReadByte(READ);

  SPI_ReadByte((start_address & 0xFF0000) >> 16);
  SPI_ReadByte((start_address & 0xFF00) >> 8);
  SPI_ReadByte(start_address & 0xFF);
	
	for (i=0;i<length;i++)
	{
		buffer[i] = SPI_ReadByte(0);
	}

	NotSelect_Flash();
}

void Save_int32_t(int32_t data, unsigned int address)
{
	u8 writebuffer[4];
	writebuffer[0]=((data&0xFF000000) >> 24 );
	writebuffer[1]=((data&0x00FF0000) >> 16 );
	writebuffer[2]=((data&0x0000FF00) >> 8  ) ;
	writebuffer[3]= (data&0x000000FF) ;

	WriteToSRAM(writebuffer,address,4);
}

int32_t Read_int32_t(unsigned int address)
{
	u8 readbuffer[4];
	int32_t temp;
	
	ReadFromSRAM(readbuffer, address,4);
	temp=(int32_t)((readbuffer[0]<<24) + (readbuffer[1]<<16)+(readbuffer[2]<<8)+readbuffer[3]);
	return temp;
}
