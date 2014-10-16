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
//
//	GPIO_InitStructure.GPIO_Pin 				= GPIO_Pin_14;
//	GPIO_Init(GPIOD, &GPIO_InitStructure);
//
//	GPIO_ToggleBits(GPIOD, GPIO_Pin_14);

	adcInit();
	dacInit();
	Timer2Init();
	UART2_init(256000);

	int teller = 0;

	while(1)
    {
//		UART_sendData(2, teller++);
		// La La La La
    }
}
