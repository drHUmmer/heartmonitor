#include "stm32f4xx.h"
#include "ADC.h"
#include "DAC.h"


int main(void)
{
    SystemInit();

	adcInit();
	dacInit();




	while(1)
    {
		uint16_t adcData = adcGet();
		dacPut(adcData);
    }
}
