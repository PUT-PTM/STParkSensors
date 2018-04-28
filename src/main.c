/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "hc-sr04.h"
int micros=0;
int distance=250;

void TIM2_IRQHandler(void){
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET){
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		GPIO_ResetBits(GPIOB, GPIO_Pin_8);
		TIM_Cmd(TIM2, DISABLE);
	}
}

void TIM3_IRQHandler(void){
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET){
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
		micros++;
	}
}
int distance;

int main(void)
{
	hcconfig();
	for(;;)
	{
		//GPIO_SetBits(GPIOD, GPIO_Pin_15);
		measurment();
		distance = micros/58;
		micros=0;
		hcrun(distance);
		distance=0;


	}
}
