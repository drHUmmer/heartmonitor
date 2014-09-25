#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "misc.h"
#include "ADC.h"
#include "DAC.h"
#include "PLL.h"






int main(void)
{

	PLLInit();
	Timer2Init();
	adcInit();
	dacInit();


	RCC_ClocksTypeDef Clocks_freqs;

	uint32_t CLK_SRC = RCC_GetSYSCLKSource();

	RCC_GetClocksFreq(&Clocks_freqs);
	uint32_t HCLK_var 	= Clocks_freqs.HCLK_Frequency;
	uint32_t PCLK1_var 	= Clocks_freqs.PCLK1_Frequency;
	uint32_t PCLK2_var 	= Clocks_freqs.PCLK2_Frequency;
	uint32_t SYSCLK_var = Clocks_freqs.SYSCLK_Frequency;


	/* GPIOD Periph clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);


	while(1)
    {
		uint16_t adcData = adcGet();
		dacPut(adcData);
		//GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
    }
}
