#include "TIMER.h"

/* PWM Initialization*/
void TM_PWM_Init(void) {
	uint16_t period = 8399;
	GPIO_InitTypeDef            GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef     TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef           TIM_OCInitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOD, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 10000-1;
	TIM_TimeBaseInitStruct.TIM_Period = period;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStruct);
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse = ((period+1)/2) - 1;
	TIM_OC1Init(TIM4, &TIM_OCInitStruct);

	TIM_Cmd(TIM4, ENABLE);
}
/*	Set PWM frequency */
void Set_Freq(int freq){
		TIM_PrescalerConfig(TIM4,10000/freq-1,TIM_PSCReloadMode_Update);
}
/*	pulse_length = ((TIM_Period + 1) * DutyCycle) / 100 - 1 */
/*	We changed duty to a fraction of 8400 instead of 100 */
/*  due to high sensivity to duty cycle */
void Set_Duty_Cycle(int dty_cyl){
		int pulse_length=((8399 + 1) * dty_cyl) / 8400 - 1;
		TIM_SetCompare1(TIM4,pulse_length);
}

