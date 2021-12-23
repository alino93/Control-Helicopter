#include "KEY.h"

void Key_init(void){
  GPIO_InitTypeDef  GPIO_InitStructure;
	/* Keys Setup */
	RCC_AHB1PeriphClockCmd(KEY_GPIO_RCC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = Key1 | Key2;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(Key_Port, &GPIO_InitStructure);
}
