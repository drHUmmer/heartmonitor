#include "main.h"

int main(void)
{
	PLLInit();

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);					/* Enable GPIO clock */
	GPIO_InitStructure.GPIO_OType 				= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd	 			= GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed 				= GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode 				= GPIO_Mode_OUT;

	GPIO_InitStructure.GPIO_Pin 				= GPIO_Pin_13;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin 				= GPIO_Pin_14;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_ToggleBits(GPIOD, GPIO_Pin_14);

	Timer4Init();
	adcInit();
	dacInit();
	UART2_init(250000);

	while(1)
    {
		// La La La La
    }
}
