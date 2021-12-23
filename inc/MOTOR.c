#include "MOTOR.h" 

/* Output Pin Initialization*/
void MOTOR_init(void){
  GPIO_InitTypeDef  GPIO_InitStructure;
	/* Alternating functions for pin */
	GPIO_PinAFConfig(MOTOR_PORT, MOTORPinSource, GPIO_AF_TIM4);
	/* Setup Output Pin */
  RCC_AHB1PeriphClockCmd(MOTOR_GPIO_RCC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = MOTORPin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(MOTOR_PORT, &GPIO_InitStructure);	
}
