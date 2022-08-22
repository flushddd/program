#include "Key_Led.h"
//轮询方法扫描四个按键，返回按键值timeout 的单位位ms，若timeout=0表示一直扫描，直到有键按下

KEYS ScanPressdKey(uint32_t timeout)
{
	KEYS key=KEY_NONE;
	uint32_t tickstart = HAL_GetTick();//当前计数值
	const uint32_t btnDelay=20;
	GPIO_PinState keyState;//引脚输入状态
	while(1)
	{
		#ifdef KeyLeft_Pin  // 如果定义了宏，就检测KeyLeft的键输入，低输入有效
		keyState=HAL_GPIO_ReadPin(KeyLeft_GPIO_Port,KeyLeft_Pin);
		if(keyState==GPIO_PIN_RESET)
		{
			HAL_Delay(btnDelay);
			keyState=HAL_GPIO_ReadPin(KeyLeft_GPIO_Port,KeyLeft_Pin);
			 if(keyState == GPIO_PIN_RESET) 
				 return KEY_LEFT;
		 }
	 
#endif
	 
 

#ifdef KeyRight_Pin //如果定义了宏，就检测KeyRight键输入，低输入有效
				keyState=HAL_GPIO_ReadPin(KeyRight_GPIO_Port,KeyRight_Pin);
 if(keyState == GPIO_PIN_RESET)
 {
	 HAL_Delay(btnDelay);
	 keyState=HAL_GPIO_ReadPin(KeyRight_GPIO_Port,KeyRight_Pin);
	 if(keyState == GPIO_PIN_RESET)
		 return KEY_RIGHT;
 }
 #endif
 
 
#ifdef  KeyDown_Pin//如果定义了宏，就检测keydown键输入，低输入有效
        keyState=HAL_GPIO_ReadPin(KeyDown_GPIO_Port,KeyDown_Pin);
        if(keyState == GPIO_PIN_RESET)
				{
	HAL_Delay(btnDelay);
					keyState=HAL_GPIO_ReadPin(KeyDown_GPIO_Port,KeyDown_Pin);
					if(keyState== GPIO_PIN_RESET)
						return KEY_DOWN;
				}
#endif
				
#ifdef KeyUp_Pin  //如果定义了宏，就检测KeyUP键的输入，高输入有效
				keyState=HAL_GPIO_ReadPin(KeyUp_GPIO_Port,KeyUp_Pin);
				if(keyState==GPIO_PIN_SET)
				{
					HAL_Delay(btnDelay);
					keyState=HAL_GPIO_ReadPin(KeyUp_GPIO_Port,KeyUp_Pin);
					if(keyState ==GPIO_PIN_SET)
        return KEY_UP;
				}
				#endif
				
				if(timeout != KEY_WAIT_ALWAYS)  //timeout 定义了一个超时的值，Hal_gettick函数获取系统提供的嘀嗒值，
					//然后减去最初计数值可以得到函数运行的时间，这个就看设置的timeout，如果其值为零，就表示一直等待，直到按键按下
				{
					if((HAL_GetTick()- tickstart)> timeout)
						break;
				}
				return key;
			}			
		}
