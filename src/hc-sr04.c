
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
}


void hcrun(int counter){


			if(counter > 0 && counter <1000000-1) {GPIO_SetBits(GPIOD, GPIO_Pin_12);}
			else if(counter > 1000000 && counter <2000000-1) {GPIO_SetBits(GPIOD, GPIO_Pin_13);}
			else if(counter > 2000000 && counter <3000000-1) {GPIO_SetBits(GPIOD, GPIO_Pin_14);}
			else  {GPIO_SetBits(GPIOD, GPIO_Pin_15);}
			GPIO_ResetBits(GPIOD, GPIO_Pin_12);
			GPIO_ResetBits(GPIOD, GPIO_Pin_13);
			GPIO_ResetBits(GPIOD, GPIO_Pin_14);
			GPIO_ResetBits(GPIOD, GPIO_Pin_15);
}

int measurment(){

	int distance = 1;
	trig();
	echo();
	return distance;
}

void trig(){};

void echo(){};
