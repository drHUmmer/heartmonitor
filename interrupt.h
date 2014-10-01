#ifndef INTERRUPT_HEADER
#define INTERRUPT_HEADER

#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"
#include "misc.h"

#include "peakDetect.h"

NVIC_InitTypeDef NVIC_InitStruct;

void TIM2_IRQHandler(void);
void TIM4_IRQHandler(void);
void NVICTimer2Init(void);
void NVICTimer4Init(void);

#endif /* INTERRUPT_HEADER */
