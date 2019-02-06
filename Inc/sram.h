#ifndef SRAM_H
#define SRAM_H
#include "cmsis_os.h"
#include "stm32f1xx_hal.h"

/* Private typedef -----------------------------------------------------------*/
#define SPI_FLASH_PageSize    0x100

/* Private define ------------------------------------------------------------*/
#define PP      0x02  /* Write to Memory instruction */
#define WRSR       0x01  /* Write Status Register instruction */
#define WREN       0x06  /* Write enable instruction */

#define READ       0x03  /* Read from Memory instruction */
#define RDSR       0x05  /* Read Status Register instruction  */
#define RDID       0x9F  /* Read identification */
#define SE         0xD8  /* Sector Erase instruction */
#define BE         0xC7  /* Bulk Erase instruction */

#define WIP_Flag   0x01  /* Write In Progress (WIP) flag */

#define Dummy_Byte 0xA5
/* Select SPI FLASH: ChipSelect pin low  */
#define Select_Flash()     GPIOA->BSRR=GPIO_BSRR_BR4
/* Deselect SPI FLASH: ChipSelect pin high */
#define NotSelect_Flash()    GPIOA->BSRR=GPIO_BSRR_BS4

#define u16 uint16_t
#define u8 uint8_t
#define u32 uint32_t
u16 SPI_SendByte(u8 tx_buff);
u16 SPI_ReadByte(u8 a);
extern SPI_HandleTypeDef hspi1;
void WriteToSRAM(u8 *buffer, unsigned int start_address,unsigned int length);
void ReadFromSRAM(u8 *buffer, unsigned int start_address,unsigned int length);
void FlashSectorEarse(u16 page);
void Save_int32_t(int32_t data, unsigned int address);
int32_t Read_int32_t(unsigned int address);
extern u8 readbuffer[20];

#endif

