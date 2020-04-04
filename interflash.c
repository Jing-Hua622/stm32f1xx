#include "internal_flash.h"
#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
#include "string.h"

 FLASH_EraseInitTypeDef Data_Flash;
 
uint32_t FlashData_Addr[3] = {Write_Frist_Flag_ADDR,WaitTime_ADDR,RealyTime_ADDR};
uint32_t FlashData_Save[3];
 
void WriteFlash(uint32_t WriteData, uint32_t WriteAddr)
{
	uint32_t PageError = 0; //如果错误会被设置为出错的flash地址
	
	uint32_t Write_Flash_Data = WriteData;
	
	uint32_t Write_Flash_Addr = WriteAddr;
	
	for(uint8_t i = 0;i < sizeof(FlashData_Addr)/sizeof(uint32_t);i++) //将要擦除的Flash页数据缓存起来
	{
		FlashData_Save[i] = ReadFlash(FlashData_Addr[i]);
	}
	
	for(uint8_t j = 0;j < sizeof(FlashData_Addr)/sizeof(uint32_t);j++) //将要新写入的数据缓存 
	{
		if(Write_Flash_Addr == FlashData_Addr[j])
		{
			FlashData_Save[j] = Write_Flash_Data;
		}
	}
	
	
	HAL_FLASH_Unlock();
	
	Data_Flash.TypeErase = FLASH_TYPEERASE_PAGES; //执行页面只做擦除操作
	
	Data_Flash.PageAddress = Write_Flash_Addr;  //数据存储页地址 
	
	Data_Flash.NbPages = 1; //数据存储页地址只有1页，如果数据过大，可使用计算方法计算要擦除的页大小
	                        //NbPages = (写入结束地址 - 写入开始地址)/页大小 FLASH_PAGE_SIZE
	
	HAL_FLASHEx_Erase(&Data_Flash, &PageError);  //调用擦除函数擦除
	
	for(uint8_t k = 0;k < sizeof(FlashData_Save)/sizeof(uint32_t);k++)
	{
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,FlashData_Addr[k], FlashData_Save[k]); //写入数据小于1页，可连续写入		
	}
	 HAL_FLASH_Lock();
	
}

uint32_t ReadFlash(uint32_t ReadAddr)
{
	uint32_t Read_Flash_Data;
	
	uint32_t Read_Flash_Addr = ReadAddr;
	
	Read_Flash_Data = *(__IO uint16_t*)(Read_Flash_Addr);
	
	return Read_Flash_Data;
}

