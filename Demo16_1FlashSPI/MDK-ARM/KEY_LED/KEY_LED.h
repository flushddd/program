#include"main.h"

typedef enum {
	KEY_NONE=0,//���û�а���������
  KEY_LEFT,//���
	KEY_RIGHT,//�Ҽ�
	KEY_UP,//�ϼ�
	KEY_DOWN//�¼�
}KEYS;

#define    KEY_WAIT_ALWAYS    0//��Ϊ������һ�ֲ�������ʾһֱ�ȴ���������
//��ѯ����ɨ�谴�� 
KEYS ScanPressdKey(uint32_t timeout);

#ifdef  LED1_Pin//LED1�Ŀ���
  #define LED1_Toggle()  HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin)
	#define LED1_ON()    HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET)
  #define LED1_OFF()  HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET)
#endif

#ifdef LED2_Pin//LED2�Ŀ���
  #define LED2_Toggle()  HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin)
  #define LED2_ON()  		HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET)
	#define LED2_OFF()     HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET)
#endif


//#ifdef Buzzer_Pin//�������Ŀ���
//#define Buzzer_Toggle() HAL_GPIO_TogglePin(Buzzer_GPIO_Port,Buzzer_Pin)
//#define Buzzer_ON()   HAL_GPIO_WritePin(Buzzer_GPIO_Port,Buzzer_Pin,GPIO_PIN_RESET)
////���0����������
//#define Buzzer_OFF()  HAl_GPIO_WritePin(Buzzer_GPIO_Port,Buzzer_Pin,GPIO_PIN_SET)
////���1������������
//#endif
