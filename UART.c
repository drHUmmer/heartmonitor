#include "UART.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"

USART_InitTypeDef USART2_InitStructure;
USART_ClockInitTypeDef USART2_ClockStructure;

void UART2_init(void) {

	  GPIO_InitTypeDef GPIO_InitStructure;

	  /* Enable GPIO clock */
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	  /* Enable UART clock */
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	  /* Connect PXx to USARTx_Tx*/
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);

	  /* Connect PXx to USARTx_Rx*/ // U2
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

	  /* Configure USART Tx as alternate function  */
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);

	  /* Configure USART Rx as alternate function  */
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);

	  // UART SETTING
	  USART2_InitStructure.USART_BaudRate 			= UART2_SPEED;
	  USART2_InitStructure.USART_WordLength 			= USART_WordLength_8b;
	  USART2_InitStructure.USART_StopBits 			= USART_StopBits_1;
	  USART2_InitStructure.USART_Parity 				= USART_Parity_No;
	  USART2_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	  USART2_InitStructure.USART_Mode 				= USART_Mode_Rx | USART_Mode_Tx;

	  // UART CLOCK SETTING
	  USART2_ClockStructure.USART_CPHA				= DISABLE;
	  USART2_ClockStructure.USART_CPOL				= DISABLE;
	  USART2_ClockStructure.USART_Clock				= ENABLE;
	  USART2_ClockStructure.USART_LastBit			= DISABLE;

	  /* USART clock configuration */
	  USART_ClockInit(USART2, &USART2_ClockStructure);

	  /* USART configuration */
	  USART_Init(USART2, &USART2_InitStructure);

	  /* Enable USART */
	  USART_Cmd(USART2, ENABLE);

}

void UART2_sendData() {
	//USART_Word_Length ();
}

void UART2_readData() {
	//USART_Word_Length ();
}
