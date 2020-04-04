#include "key.h"
#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
#include "oled.h"


static uint16_t KEY1_ReadPin(void)
{
   return  KEY1_READPIN(); //返回函数的返回值
}

static uint16_t KEY2_ReadPin(void)
{
   return KEY2_READPIN();
}

static uint16_t KEY3_ReadPin(void)
{
   return KEY3_READPIN();
}

static uint16_t KEY4_ReadPin(void)
{
   return KEY4_READPIN();
}
KEY_COMPONENTS KEY_BUF[KEY_NUM] = {
{1,0,0,1,KEY_NULL,KEY_NULL,KEY1_ReadPin},
{1,0,0,1,KEY_NULL,KEY_NULL,KEY2_ReadPin},
{1,0,0,1,KEY_NULL,KEY_NULL,KEY3_ReadPin},
{1,0,0,1,KEY_NULL,KEY_NULL,KEY4_ReadPin},
};
//unsigned int key_scan()
//{
//	static enum key_status_e key_status = KEY_S1;
////	static int press = 0; //计算长按可用
//	u16 key_val = 0;
//	switch(key_status)
//	{
//		//检测按键按下，检测对应IO口电平，如果按下跳s2
//		case KEY_S1: 
//					if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) == 1)	key_status = KEY_S2;
//					
////					if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13) == 1)	key_state = KEY_S2;
//			
//			break;
//		
//		//按键已经按下，消抖按检测对应IO口电平同s1，
//		//则按键按下跳s3检测释放，否则跳s1
//		case KEY_S2:
//					if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) == 1)
//						key_status = KEY_S3;	
//						else 
//							key_status = KEY_S1;
//						
////						if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13) == 1)
////						key_state = KEY_S3;	
////						else 
////							key_state = KEY_S1;
//			
//			break;
//		
//		//检测按键释放，再次检测IO电平，翻转则已经释放，跳s1，
//		//否则继续保持，直到按键释放
//		case KEY_S3:   
//					if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) == 0)
//					{
//						key_status = KEY_S1;
//						key_val = 1;
//					}
//			
//			break;
//		
//		default:
//			key_status = KEY_S1;
//		//  press = 0;
//			break;
//	}
//	return key_val;
//	 
//}

static void GET_KEY_LEVEL()
{
	u8 i;
	for(i = 0; i<KEY_NUM;i++)
	{
			if(KEY_BUF[i].KEY_SHIELD == 0)
				continue;
			if(KEY_BUF[i].READ_PIN() == KEY_BUF[i].KEY_DOWN_LEVEL )
				KEY_BUF[i].KEY_LEVEL = 1;
			else 
				KEY_BUF[i].KEY_LEVEL = 0;
			
	}
}

void ReadKeyStatus(void)
{
    uint8_t i; 
    
    GET_KEY_LEVEL();
	static uint16_t KEY_LONG_DOWN_DELAY = 100 ; //1S
    
    for(i = 0;i < KEY_NUM;i++)
    {
        switch(KEY_BUF[i].KEY_STATUS)
        {
            //状态0：没有按键按下
            case KEY_NULL:
                if(KEY_BUF[i].KEY_LEVEL == 1)//有按键按下
                {
                    KEY_BUF[i].KEY_STATUS = KEY_SURE;//转入状态1
                    KEY_BUF[i].KEY_EVENT = KEY_NULL;//空事件
                }
                else
                {
                    KEY_BUF[i].KEY_EVENT = KEY_NULL;//空事件
                }
                break;
            //状态1：按键按下确认
            case KEY_SURE:
                if(KEY_BUF[i].KEY_LEVEL == 1)//确认和上次相同
                {
                    KEY_BUF[i].KEY_STATUS = KEY_DOWN;//转入状态2
                    KEY_BUF[i].KEY_EVENT = KEY_DOWN;//按下事件
                    KEY_BUF[i].KEY_COUNT = 0;//计数器清零
                }
                else
                {
                    KEY_BUF[i].KEY_STATUS = KEY_NULL;//转入状态0
                    KEY_BUF[i].KEY_EVENT = KEY_NULL;//空事件
                }
                break;
            //状态2：按键按下
            case KEY_DOWN:
                if(KEY_BUF[i].KEY_LEVEL != 1)//按键释放，端口高电平
                {
                    KEY_BUF[i].KEY_STATUS = KEY_NULL;//转入状态0
                    KEY_BUF[i].KEY_EVENT = KEY_UP;//松开事件
                }
                else if((KEY_BUF[i].KEY_LEVEL == 1) && (++KEY_BUF[i].KEY_COUNT >= KEY_LONG_DOWN_DELAY)) //超过KEY_LONG_DOWN_DELAY没有释放
                {
                    KEY_BUF[i].KEY_STATUS = KEY_LONG;//转入状态3
                    KEY_BUF[i].KEY_EVENT = KEY_LONG;//长按事件
                    KEY_BUF[i].KEY_COUNT = 0;//计数器清零
                }
                else
                {
                    KEY_BUF[i].KEY_EVENT = KEY_NULL;//空事件
                }
                break;
            //状态3：按键连续按下
            case KEY_LONG:
                if(KEY_BUF[i].KEY_LEVEL != 1)//按键释放，端口高电平
                {
                    KEY_BUF[i].KEY_STATUS = KEY_NULL;//转入状态0
                    KEY_BUF[i].KEY_EVENT = KEY_UP;//松开事件
                    KEY_BUF[i].KEY_EVENT = KEY_NULL;
                }
                else if((KEY_BUF[i].KEY_LEVEL == 1) 
                && (++KEY_BUF[i].KEY_COUNT >= KEY_LONG_DOWN_DELAY)) //超过KEY_LONG_DOWN_DELAY没有释放
                {
                    KEY_BUF[i].KEY_EVENT = KEY_LONG;//长按事件
                    KEY_BUF[i].KEY_COUNT = 0;//计数器清零
                }
                else
                {
                    KEY_BUF[i].KEY_EVENT = KEY_NULL;//空事件
                }
                break;  
        }
    }
}

