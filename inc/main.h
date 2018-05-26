//Includes
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "codec.h"

//Defines
#define LED_BLUE_ON   GPIOD->BSRRL = GPIO_Pin_15;
#define LED_BLUE_OFF  GPIOD->BSRRH = GPIO_Pin_15;

#define NOTEFREQUENCY 0.015		//frequency of saw wave: f0 = 0.5 * NOTEFREQUENCY * 48000 (=sample rate)
#define NOTEAMPLITUDE 500.0		//amplitude of the saw wave


typedef struct {
	double tabs[8];
	double params[8];
	uint8_t currIndex;
} fir_8;


// struct to initialize GPIO pins
GPIO_InitTypeDef GPIO_InitStructure;


volatile uint32_t sampleCounter = 0;
volatile int16_t sample = 0;

double sawWave = 0.0;

double filteredSaw = 0.0;

double updateFilter(fir_8* theFilter, double newValue);

void initFilter(fir_8* theFilter);

