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
			

int main(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitTypeDef GPIOStruct;
	GPIOStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIOStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIOStruct.GPIO_OType = GPIO_OType_PP;
	GPIOStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIOStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOD, &GPIOStruct);
	int licznik=0;
	for(;;)
	{
		if(licznik >4000000)licznik=0;
		if(licznik > 0 && licznik <1000000-1) {GPIO_SetBits(GPIOD, GPIO_Pin_12);}
		else if(licznik > 1000000 && licznik <2000000-1) {GPIO_SetBits(GPIOD, GPIO_Pin_13);}
		else if(licznik > 2000000 && licznik <3000000-1) {GPIO_SetBits(GPIOD, GPIO_Pin_14);}
		else  {GPIO_SetBits(GPIOD, GPIO_Pin_15);}
		licznik++;
		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
		GPIO_ResetBits(GPIOD, GPIO_Pin_14);
		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
	}
}
