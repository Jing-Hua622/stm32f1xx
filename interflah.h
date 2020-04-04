#ifndef __INTERNAL_FLASH_H
#define __INTERNAL_FLASH_H

#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"


#define Write_Frist_Flag_ADDR  ((uint32_t)0x0800F000)
#define WaitTime_ADDR					 ((uint32_t)0x0800F004)      //设置每个32位数据占位8个字节（实际32位占 4个字节）
#define RealyTime_ADDR				 ((uint32_t)0x0800F008)



void WriteFlash(uint32_t WriteData, uint32_t WriteAddr);

uint32_t ReadFlash(uint32_t ReadAddr);

#endif
