
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void hcconfig(){

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		GPIO_InitTypeDef GPIOStruct;
		GPIOStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
		GPIOStruct.GPIO_Mode = GPIO_Mode_OUT;
		GPIOStruct.GPIO_OType = GPIO_OType_PP;
		GPIOStruct.GPIO_Speed = GPIO_Speed_100MHz;
		GPIOStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;

		GPIO_Init(GPIOD, &GPIOStruct);
		//Trigger Pin
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		GPIOStruct.GPIO_Pin = GPIO_Pin_8;
		GPIOStruct.GPIO_Mode = GPIO_Mode_OUT;
		GPIOStruct.GPIO_OType = GPIO_OType_PP;
		GPIOStruct.GPIO_Speed = GPIO_Speed_100MHz;
		GPIOStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;

		GPIO_Init(GPIOB, &GPIOStruct);
		//Echo pin
		GPIOStruct.GPIO_Pin = GPIO_Pin_9;
		GPIOStruct.GPIO_Mode = GPIO_Mode_IN;
		GPIOStruct.GPIO_Speed = GPIO_Speed_100MHz;
		GPIOStruct.GPIO_PuPd = GPIO_PuPd_DOWN;

		GPIO_Init(GPIOB, &GPIOStruct);

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		//10 us timer
		TIM_TimeBaseInitTypeDef Timmer2;
		Timmer2.TIM_Period = 9;
		Timmer2.TIM_Prescaler = 83;
		Timmer2.TIM_ClockDivision = TIM_CKD_DIV1;
		Timmer2.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM2, &Timmer2);

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		TIM_TimeBaseInitTypeDef Timmer3;
		//1 us timer
		Timmer3.TIM_Period = 1;
		Timmer3.TIM_Prescaler = 41;
		Timmer3.TIM_ClockDivision = TIM_CKD_DIV1;
		Timmer3.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM3, &Timmer3);

		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

		//Setup NVIC for tim2
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

		//Setup NVIC for tim3
		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

}


void hcrun(int distance){
			if(distance >= 0 && distance <50)
			{
				GPIO_SetBits(GPIOD, GPIO_Pin_14);
				GPIO_ResetBits(GPIOD, GPIO_Pin_12);
				GPIO_ResetBits(GPIOD, GPIO_Pin_13);
				GPIO_ResetBits(GPIOD, GPIO_Pin_15);
			}
			else if(distance > 50 && distance <100)
			{
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				GPIO_ResetBits(GPIOD, GPIO_Pin_12);
				GPIO_ResetBits(GPIOD, GPIO_Pin_14);
				GPIO_ResetBits(GPIOD, GPIO_Pin_15);
			}
			else if(distance > 100 && distance<150)
			{
				GPIO_SetBits(GPIOD, GPIO_Pin_15);
				GPIO_ResetBits(GPIOD, GPIO_Pin_12);
				GPIO_ResetBits(GPIOD, GPIO_Pin_13);
				GPIO_ResetBits(GPIOD, GPIO_Pin_14);
			}
			else
			{
				GPIO_SetBits(GPIOD, GPIO_Pin_12);
				GPIO_ResetBits(GPIOD, GPIO_Pin_13);
				GPIO_ResetBits(GPIOD, GPIO_Pin_14);
				GPIO_ResetBits(GPIOD, GPIO_Pin_15);
			}

}

void trig(){

	GPIO_SetBits(GPIOB, GPIO_Pin_8);
	TIM_Cmd(TIM2,ENABLE);

};

void echo(){
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==0);
	TIM_Cmd(TIM3,ENABLE);
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==1);
	TIM_Cmd(TIM3,DISABLE);
};

void measurment(){
	trig();
	echo();
}


