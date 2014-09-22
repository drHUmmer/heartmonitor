#include "stm32f4xx.h"
#include "ADC.h"
#include "DAC.h"


int main(void)
{
	//SystemInit();

	//while(!(RCC->CR & (1 << 25)));
	//RCC_HSICmd(ENABLE);
	//RCC->CR &= ~(1 << 16); // disable HSE



	/* Reset the RCC clock configuration to the default reset state ------------*/
	/* Set HSION bit */
	RCC->CR |= (uint32_t)0x00000001;

	/* Reset CFGR register */
	RCC->CFGR = 0x00000000;

	/* Reset HSEON, CSSON and PLLON bits */
	RCC->CR &= (uint32_t)0xFEF6FFFF;

	/* Reset PLLCFGR register */
	RCC_PLLConfig(RCC_PLLSource_HSI,10,210,2,7);

	/* Reset HSEBYP bit */
	RCC->CR &= (uint32_t)0xFFFBFFFF;

	/* Disable all interrupts */
	RCC->CIR = 0x00000000;

	/* Select regulator voltage output Scale 1 mode, System frequency up to 168 MHz */
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR |= PWR_CR_VOS;

    /* HCLK = SYSCLK / 1*/
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

    /* PCLK2 = HCLK / 2*/
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV4;

    /* PCLK1 = HCLK / 4*/
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;

    /* Configure main PLL */
    RCC_PLLConfig(RCC_PLLSource_HSI,10,210,2,7);

    /* Enable the main PLL */
    RCC->CR |= RCC_CR_PLLON;

	/* Wait till the main PLL is ready */
	while((RCC->CR & RCC_CR_PLLRDY) == 0)
	{
	}

	/* Configure Flash prefetch, Instruction cache, Data cache and wait state */
	FLASH->ACR = FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_5WS;

	/* Select the main PLL as system clock source */
	RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
	RCC->CFGR |= RCC_CFGR_SW_PLL;

	/* Wait till the main PLL is used as system clock source */
	while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL);
	{
	}


	RCC_ClocksTypeDef *Clocks_freqs;

	uint32_t CLK_SRC = RCC_GetSYSCLKSource();

	RCC_GetClocksFreq(Clocks_freqs);
	uint32_t HCLK_var 	= Clocks_freqs->HCLK_Frequency;
	uint32_t PCLK1_var 	= Clocks_freqs->PCLK1_Frequency;
	uint32_t PCLK2_var 	= Clocks_freqs->PCLK2_Frequency;
	uint32_t SYSCLK_var = Clocks_freqs->SYSCLK_Frequency;


/*
	RCC_PLLCmd(DISABLE);
	RCC_PLLConfig(RCC_PLLSource_HSI,10,210,2,7);

	while(!(RCC->CR & (1 << 25)));
*/
//	adcInit();
//	dacInit();


	/* GPIOD Periph clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

/*	while(1)
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_12);
		GPIO_ResetBits(GPIOD, GPIO_Pin_12);

	}*/

	while(1)
    {
		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
		//uint16_t adcData = adcGet();
		//dacPut(adcData);
		GPIO_SetBits(GPIOD, GPIO_Pin_12);

    }
}
