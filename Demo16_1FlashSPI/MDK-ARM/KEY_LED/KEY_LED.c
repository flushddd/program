#include "Key_Led.h"
//��ѯ����ɨ���ĸ����������ذ���ֵtimeout �ĵ�λλms����timeout=0��ʾһֱɨ�裬ֱ���м�����

KEYS ScanPressdKey(uint32_t timeout)
{
	KEYS key=KEY_NONE;
	uint32_t tickstart = HAL_GetTick();//��ǰ����ֵ
	const uint32_t btnDelay=20;
	GPIO_PinState keyState;//��������״̬
	while(1)
	{
		#ifdef KeyLeft_Pin  // ��������˺꣬�ͼ��KeyLeft�ļ����룬��������Ч
		keyState=HAL_GPIO_ReadPin(KeyLeft_GPIO_Port,KeyLeft_Pin);
		if(keyState==GPIO_PIN_RESET)
		{
			HAL_Delay(btnDelay);
			keyState=HAL_GPIO_ReadPin(KeyLeft_GPIO_Port,KeyLeft_Pin);
			 if(keyState == GPIO_PIN_RESET) 
				 return KEY_LEFT;
		 }
	 
#endif
	 
 

#ifdef KeyRight_Pin //��������˺꣬�ͼ��KeyRight�����룬��������Ч
				keyState=HAL_GPIO_ReadPin(KeyRight_GPIO_Port,KeyRight_Pin);
 if(keyState == GPIO_PIN_RESET)
 {
	 HAL_Delay(btnDelay);
	 keyState=HAL_GPIO_ReadPin(KeyRight_GPIO_Port,KeyRight_Pin);
	 if(keyState == GPIO_PIN_RESET)
		 return KEY_RIGHT;
 }
 #endif
 
 
#ifdef  KeyDown_Pin//��������˺꣬�ͼ��keydown�����룬��������Ч
        keyState=HAL_GPIO_ReadPin(KeyDown_GPIO_Port,KeyDown_Pin);
        if(keyState == GPIO_PIN_RESET)
				{
	HAL_Delay(btnDelay);
					keyState=HAL_GPIO_ReadPin(KeyDown_GPIO_Port,KeyDown_Pin);
					if(keyState== GPIO_PIN_RESET)
						return KEY_DOWN;
				}
#endif
				
#ifdef KeyUp_Pin  //��������˺꣬�ͼ��KeyUP�������룬��������Ч
				keyState=HAL_GPIO_ReadPin(KeyUp_GPIO_Port,KeyUp_Pin);
				if(keyState==GPIO_PIN_SET)
				{
					HAL_Delay(btnDelay);
					keyState=HAL_GPIO_ReadPin(KeyUp_GPIO_Port,KeyUp_Pin);
					if(keyState ==GPIO_PIN_SET)
        return KEY_UP;
				}
				#endif
				
				if(timeout != KEY_WAIT_ALWAYS)  //timeout ������һ����ʱ��ֵ��Hal_gettick������ȡϵͳ�ṩ�����ֵ��
					//Ȼ���ȥ�������ֵ���Եõ��������е�ʱ�䣬����Ϳ����õ�timeout�������ֵΪ�㣬�ͱ�ʾһֱ�ȴ���ֱ����������
				{
					if((HAL_GetTick()- tickstart)> timeout)
						break;
				}
				return key;
			}			
		}
