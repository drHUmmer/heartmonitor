#include "DAC.h"

void gpioInit(void);


int main(void)
{
	dacInit();
	dacPut(0xccc);

	while(1)
    {

    }
}
