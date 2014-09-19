#include "stm32f4xx.h"
#include "ADC.h"


int main(void)
{
    adcInit();



	while(1)
    {
		uint16_t adcData = adcGet();
    }
}
