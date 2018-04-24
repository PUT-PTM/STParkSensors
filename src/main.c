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

int distance;
int main(void)
{
	hcconfig();
	int counter=0;
	for(;;)
	{
		if(counter >4000000)counter=0;
		hcrun(counter);
		distance = measurment();
		counter+=measurment();
	}
}
