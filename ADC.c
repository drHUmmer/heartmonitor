#include "ADC.h"


void adcInit(void){
/******************************************************
 * - Init DAC I/O ch1 (PA4)
 * - Init DAC settings
 * 		o no trigger
 * 		o no waveform
 * 		o output buffer enable
 ******************************************************/

// Init ADC I/O
	// write access GPIO settings
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_StructInit(&GPIO_InitStructure);

	//for ADC1 on PC0 using IN10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOC, &GPIO_InitStructure);


// Init ADC settings
	// write access ADC settings
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;

	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;

	ADC_CommonInit(&ADC_CommonInitStructure);

	ADC_InitStructure.ADC_Resolution 			= ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode 			= DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode 	= ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge 	= ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_ExternalTrigConv 		= ADC_ExternalTrigConv_T1_CC1;
	ADC_InitStructure.ADC_DataAlign 			= ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion 		= 1;


	ADC_StructInit(&ADC_InitStructure);

	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_3Cycles);
	ADC_EOCOnEachRegularChannelCmd(ADC1, ENABLE);

	ADC_Cmd(ADC1, ENABLE);    //The ADC is powered on by setting the ADON bit in the ADC_CR2 register.
	//When the ADON bit is set for the first time, it wakes up the ADC from the Power-down mode.

}

uint16_t adcGet(void){
/******************************************************
 * Get ADC 1 value
 ******************************************************/

	ADC_SoftwareStartConv(ADC1);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);

	return ADC_GetConversionValue(ADC1);
}
