#ifndef __KEY_H
#define __KEY_H

#include "oled.h"
#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"

#define KEY1_READPIN() HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0);
#define KEY2_READPIN() HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13);
#define KEY3_READPIN() HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1);
#define KEY4_READPIN() HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_6);


typedef enum _KEY_STATUS_LIST
{
    KEY_NULL = 0x00,
    KEY_SURE = 0x01,
    KEY_UP   = 0x02,
    KEY_DOWN = 0x04,
    KEY_LONG = 0x08,
}KEY_STATUS_LIST;

typedef enum KEY_LIST
{
	KEY1, //up
	KEY2, //down 
	KEY3, //check
	KEY4,
	KEY_NUM
}	KEY_LIST;

typedef struct 
{
	uint16_t KEY_SHIELD; //1 不屏蔽按键 0 屏蔽
	uint16_t KEY_COUNT;  //按下开始计数
	uint16_t KEY_LEVEL;  //虚拟当前的电平
	uint16_t KEY_DOWN_LEVEL; //按下时io电平
	uint16_t KEY_STATUS;//按键状态
	uint16_t KEY_EVENT;//按键事件
	uint16_t (*READ_PIN)(void);
}KEY_COMPONENTS;

extern KEY_COMPONENTS KEY_BUF[KEY_NUM];



static void GET_KEY_LEVEL(void);
static uint16_t KEY1_ReadPin(void);
static uint16_t KEY2_ReadPin(void);
static uint16_t KEY3_ReadPin(void);
static uint16_t KEY4_ReadPin(void);

void ReadKeyStatus(void);

//unsigned int key_scan(); 
#endif 
