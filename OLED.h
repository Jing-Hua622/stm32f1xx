
//
//  文 件 名   : main.c
//  版 本 号   : v2.0

//  最近修改   : 
//  功能描述   : 0.69寸OLED 接口演示例程(STM32F103ZE系列IIC)
//              说明: 
//              ----------------------------------------------------------------
//              GND   电源地
//              VCC   接5V或3.3v电源
//              SCL   接PD6（SCL）
//              SDA   接PD7（SDA）            
//              ----------------------------------------------------------------

#ifndef __OLED_H
#define __OLED_H			  	 
//#include "sys.h"
#include "stdlib.h"	
#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"

#define OLED_MODE 0
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED IIC端口定义----------------  					   

#define OLED_SCLK_Clr() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,GPIO_PIN_RESET)//SCL
#define OLED_SCLK_Set() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,GPIO_PIN_SET)

#define OLED_SDIN_Clr() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7,GPIO_PIN_RESET)//SDA
#define OLED_SDIN_Set() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7,GPIO_PIN_SET)

 		     
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据
typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;



typedef struct 
{
	uint16_t Edit_Choose_Mark;
	uint32_t Lift_Num;
	uint32_t Right_Num;
	uint32_t Wait_Time ;
	uint32_t Realy_Time ;
}System_Data_typedef;

extern System_Data_typedef System_Data;

typedef enum MARK_LIST
{
	 Main_Mark,
	 Password_Mark,
	 Menu_Mark,
	 Edit_Mark,
	 Edit_WaitTime_Mark,
	 Edit_RealyTime_Mark,	
	 Oled_Status_Num
}MARK_LISK;


//OLED控制用函数
void OLED_WR_Byte(unsigned dat,unsigned cmd);  
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y, u8 *p,u8 Char_Size);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void Delay_50ms(unsigned int Del_50ms);
void Delay_1ms(unsigned int Del_1ms);
void fill_picture(unsigned char fill_Data);
void IIC_Start(void);
void IIC_Stop(void);
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
void Write_IIC_Byte(unsigned char IIC_Byte);
void delay_ms(u16 nms);
void IIC_Wait_Ack(void);

void Main_interface(void);
void Menu_interface(void);
void Edit_interface(void);
void Password_interface(void);
void Show_UI(void);
void FlashData_Init(void);
#endif  
	 



