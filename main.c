#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "misc.h"
#include "ADC.h"
#include "DAC.h"

void TIM3_IRQHandler(void){




	//clr interrupt

}

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
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;

    /* PCLK1 = HCLK / 4*/
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;

    /* Configure main PLL */
    RCC_PLLConfig(RCC_PLLSource_HSI,10,210,2,7);

    /* Enable the main PLL */
    RCC->CR |= RCC_CR_PLLON;

	/* Wait till the main PLL is ready */
	while((RCC->CR & RCC_CR_PLLRDY) == 0);


	/* Configure Flash prefetch, Instruction cache, Data cache and wait state */
	FLASH->ACR = FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_5WS;

	/* Select the main PLL as system clock source */
	RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
	RCC->CFGR |= RCC_CFGR_SW_PLL;

	/* Wait till the main PLL is used as system clock source */
	while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL);



	RCC_ClocksTypeDef Clocks_freqs;

	uint32_t CLK_SRC = RCC_GetSYSCLKSource();

	RCC_GetClocksFreq(&Clocks_freqs);
	uint32_t HCLK_var 	= Clocks_freqs.HCLK_Frequency;
	uint32_t PCLK1_var 	= Clocks_freqs.PCLK1_Frequency;
	uint32_t PCLK2_var 	= Clocks_freqs.PCLK2_Frequency;
	uint32_t SYSCLK_var = Clocks_freqs.SYSCLK_Frequency;


	/**********************************************
	 * timer 2 init (32-bit timer)
	 **********************************************/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;

	TIM_TimeBaseInitStruct.TIM_ClockDivision 	= TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode 		= TIM_CounterMode_Down;
	TIM_TimeBaseInitStruct.TIM_Period 			= 0x0000;
	TIM_TimeBaseInitStruct.TIM_Prescaler 		= 0x0000;

	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);


	// enable nvic
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel 					= TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority 	= 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority 			= 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd 					= ENABLE;

	NVIC_Init(&NVIC_InitStruct);

	TIM_TypeDef TIM3_IntInitStruct;

	TIM3_IntInitStruct.CR1;         /*!< TIM control register 1,              Address offset: 0x00 */
	TIM3_IntInitStruct.CR2;         /*!< TIM control register 2,              Address offset: 0x04 */
	TIM3_IntInitStruct.SMCR;        /*!< TIM slave mode control register,     Address offset: 0x08 */
	TIM3_IntInitStruct.DIER;        /*!< TIM DMA/interrupt enable register,   Address offset: 0x0C */
	TIM3_IntInitStruct.SR;          /*!< TIM status register,                 Address offset: 0x10 */
	TIM3_IntInitStruct.EGR;         /*!< TIM event generation register,       Address offset: 0x14 */
	TIM3_IntInitStruct.CCMR1;       /*!< TIM capture/compare mode register 1, Address offset: 0x18 */
	TIM3_IntInitStruct.CCMR2;       /*!< TIM capture/compare mode register 2, Address offset: 0x1C */
	TIM3_IntInitStruct.CCER;        /*!< TIM capture/compare enable register, Address offset: 0x20 */
	TIM3_IntInitStruct.CNT;         /*!< TIM counter register,                Address offset: 0x24 */
	TIM3_IntInitStruct.PSC;         /*!< TIM prescaler,                       Address offset: 0x28 */
	TIM3_IntInitStruct.ARR;         /*!< TIM auto-reload register,            Address offset: 0x2C */
	TIM3_IntInitStruct.RCR;         /*!< TIM repetition counter register,     Address offset: 0x30 */
	TIM3_IntInitStruct.CCR1;        /*!< TIM capture/compare register 1,      Address offset: 0x34 */
	TIM3_IntInitStruct.CCR2;        /*!< TIM capture/compare register 2,      Address offset: 0x38 */
	TIM3_IntInitStruct.CCR3;        /*!< TIM capture/compare register 3,      Address offset: 0x3C */
	TIM3_IntInitStruct.CCR4;        /*!< TIM capture/compare register 4,      Address offset: 0x40 */
	TIM3_IntInitStruct.BDTR;        /*!< TIM break and dead-time register,    Address offset: 0x44 */
	TIM3_IntInitStruct.DCR;         /*!< TIM DMA control register,            Address offset: 0x48 */
	TIM3_IntInitStruct.DMAR;        /*!< TIM DMA address for full transfer,   Address offset: 0x4C */
	TIM3_IntInitStruct.OR;          /*!< TIM option register,                 Address offset: 0x50 */



	TIM_ITConfig(TIM3_IntInitStruct, TIM_IT_Update)





	/**********************************************
	 * gpio init
	 **********************************************/

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


//	// output clk PA8
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);



	RCC_MCO1Config(RCC_MCO1Source_PLLCLK,RCC_MCO1Div_2);

//

//	// output clk PC9
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);



	RCC_MCO2Config(RCC_MCO2Source_SYSCLK,RCC_MCO2Div_2);

//


	uint32_t i;
	while(1)
    {
		//uint16_t adcData = adcGet();
		//dacPut(adcData);
		GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
		i=1000000;
		while(i--);
    }
}
