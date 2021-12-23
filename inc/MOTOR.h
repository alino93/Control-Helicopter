#include "stm32f4xx.h"

#define MOTORPin         GPIO_Pin_12
#define MOTORPinSource   GPIO_PinSource12
#define MOTOR_PORT     	 GPIOD
#define MOTOR_GPIO_RCC   RCC_AHB1Periph_GPIOD
void MOTOR_init(void);
