#include "DAC.h"
#include "GPIO.h"

void gpioInit(void);


int main(void)
{
	gpioInit();
	dacInit();


	while(1)
    {

    }
}
