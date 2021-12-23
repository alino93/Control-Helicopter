//*	Additional defines in "Options for Target" > "C/C++" > "Defines"
// *		- ARM_MATH_CM4
// *		- __FPU_PRESENT = 1

#include "stm32f4xx.h"
#include "MOTOR.h"
#include "TIMER.h"
#include "Inputs.h"
#include "arm_math.h"
#include "arm_pid_init_f32.c"
#include "arm_pid_reset_f32.c"
#include <stdio.h>

#define PID_PARAM_KP		0.06			  /* Proporcional */
#define PID_PARAM_KI		0.00000001	/* Integral */
#define PID_PARAM_KD		0.03			  /* Derivative */

int main(void){
	
	int freq = 250, duty = 0;
	float pid_error, feedback = 0, reference = 2400, F = 0;
	
	/* Configure ADC(input), Motor pin(output) and PWM(timer) */
	smm_Adc1_Ch10_config();
	MOTOR_init(); 
	TM_PWM_Init();
 	
	/* ARM PID Instance, float_32 format */
	arm_pid_instance_f32 PID;
	
	/* Set PID parameters */
	PID.Kp = PID_PARAM_KP;		/* Proporcional */
	PID.Ki = PID_PARAM_KI;		/* Integral */
	PID.Kd = PID_PARAM_KD;		/* Derivative */
	
	/* Initialize PID system, float32_t format */
	arm_pid_init_f32(&PID, 1);
	
	/* Initialize ADC1 */
	ADC_SoftwareStartConv(ADC1);
		
	while(1){
			/*update freq*/
			Set_Freq(freq);	
			
			/*Input read*/	
			while( !ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) );	
			feedback = (float)ADC_GetConversionValue(ADC1);
				
			/* Calculate error */
			pid_error = reference - feedback;
			
			/* Calculate PID here, argument is error */
			/* Thrust will be returned */
			F = arm_pid_f32(&PID, pid_error);
		
			/* Transform F to duty cycle */
			duty = F + 3868;
		
			/* Set limits on duty cycle */
			if (duty > 3872) {
				duty = 3872;
			} else if (duty <3800) {
				duty = 3800;
			}

			/* Set PWM duty cycle for DC motor */
			Set_Duty_Cycle(duty);		
	}
}
