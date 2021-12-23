#include "stm32f4xx.h"
#define Key_Port      GPIOC
#define Key1     		  GPIO_Pin_6
#define Key2     		  GPIO_Pin_7
#define KEY_GPIO_RCC  RCC_AHB1Periph_GPIOC
void Key_init(void);
