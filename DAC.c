#include "DAC.h"

void delay(void);

void dacInit(void){

	//dacSettings.DAC_Trigger = DAC_Trigger_None;
	//dacSettings.DAC_WaveGeneration = DAC_WaveGeneration_None;
	//dacSettings.DAC_OutputBuffer = DAC_OutputBuffer_Disable;



	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

	DAC_StructInit(&dacSettings);

	DAC_Init(DAC_Channel_1,&dacSettings);
	DAC_Cmd(DAC_Channel_1,ENABLE);

	DAC_Init(DAC_Channel_2, &dacSettings);
	DAC_Cmd(DAC_Channel_2,ENABLE);


	while(1){

		DAC_SetChannel1Data(DAC_Align_12b_R,0xfff);
		DAC_SetChannel2Data(DAC_Align_12b_R,0x000);
		delay();
		DAC_SetChannel1Data(DAC_Align_12b_R,0x000);
		DAC_SetChannel2Data(DAC_Align_12b_R,0xfff);
		delay();
	}


}
void delay(void){
	unsigned int i=10000;
	while(i){
		i--;
	}
}
