#include "stm32f4xx.h"
#include "ADC.h"

#include "DAC.h"

void gpioInit(void);


int main(void)
{
    adcInit();

	dacInit();
	dacPut(0xccc);


	while(1)
    {
		uint16_t adcData = adcGet();
    }
}
