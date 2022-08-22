#include"main.h"

typedef enum {
	KEY_NONE=0,//如果没有按键被按下
  KEY_LEFT,//左键
	KEY_RIGHT,//右键
	KEY_UP,//上键
	KEY_DOWN//下键
}KEYS;

#define    KEY_WAIT_ALWAYS    0//作为函数的一种参数，表示一直等待按键输入
//轮询方法扫描按键 
KEYS ScanPressdKey(uint32_t timeout);

#ifdef  LED1_Pin//LED1的控制
  #define LED1_Toggle()  HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin)
	#define LED1_ON()    HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET)
  #define LED1_OFF()  HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET)
#endif

#ifdef LED2_Pin//LED2的控制
  #define LED2_Toggle()  HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin)
  #define LED2_ON()  		HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET)
	#define LED2_OFF()     HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET)
#endif


//#ifdef Buzzer_Pin//蜂鸣器的控制
//#define Buzzer_Toggle() HAL_GPIO_TogglePin(Buzzer_GPIO_Port,Buzzer_Pin)
//#define Buzzer_ON()   HAL_GPIO_WritePin(Buzzer_GPIO_Port,Buzzer_Pin,GPIO_PIN_RESET)
////输出0，蜂鸣器响
//#define Buzzer_OFF()  HAl_GPIO_WritePin(Buzzer_GPIO_Port,Buzzer_Pin,GPIO_PIN_SET)
////输出1，蜂鸣器不响
//#endif
