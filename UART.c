#include "UART.h"

void UART2_init(uint8_t UART_PORT) {

	GPIO_TypeDef* GPIOPORT 		= null;
	uint16_t GPIO_PIN_TX 		= null;
	uint16_t GPIO_PIN_RX 		= null;
	uint32_t CLOCK_CMD_1 		= null;
	uint32_t CLOCK_CMD_2 		= null;
	uint8_t  GPIO_AF_SET_TX 	= null;
	uint8_t  GPIO_AF_SET_RX 	= null;
	uint8_t  GPIO_PinSource_TX 	= null;
	uint8_t  GPIO_PinSource_RX 	= null;
	uint32_t UART_SPEED			= null;
	USART_TypeDef* UART_NAME	= null;


	switch(UART_PORT) {
		case (UART_NR_2):
			GPIOPORT 			= GPIOA;
			CLOCK_CMD_1 		= RCC_AHB1Periph_GPIOA;
			CLOCK_CMD_2 		= RCC_APB1Periph_USART2;
			GPIO_PIN_TX 		= GPIO_Pin_2;
			GPIO_PIN_RX 		= GPIO_Pin_3;
			GPIO_AF_SET_TX 		= GPIO_AF_USART2;
			GPIO_AF_SET_RX 		= GPIO_AF_USART2;
			GPIO_PinSource_TX 	= GPIO_PinSource2;
			GPIO_PinSource_RX 	= GPIO_PinSource3;
			UART_SPEED			= UART2_SPEED;
			UART_NAME			= USART2;

			break;

		case (UART_NR_4):
			GPIOPORT 			= GPIOA;
			CLOCK_CMD_1 		= RCC_AHB1Periph_GPIOA;
			CLOCK_CMD_2 		= RCC_APB1Periph_USART4;
			GPIO_PIN_TX 		= GPIO_Pin_0;
			GPIO_PIN_RX 		= GPIO_Pin_1;
			GPIO_AF_SET_TX 		= GPIO_AF_UART4;
			GPIO_AF_SET_RX 		= GPIO_AF_UART4;
			GPIO_PinSource_TX 	= GPIO_PinSource0;
			GPIO_PinSource_RX 	= GPIO_PinSource1;
			UART_SPEED			= UART4_SPEED;
			UART_NAME			= UART4;

			break;

		default: return;
	}

	  /* Structures */
	  GPIO_InitTypeDef GPIO_InitStructure;
	  USART_InitTypeDef USART_InitStructure;
	  USART_ClockInitTypeDef USART_ClockStructure;

	  /* Enable GPIO clock */
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	  /* Enable UART clock */
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2); /* Connect PXx to USARTx_Tx*/
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);	/* Connect PXx to USARTx_Rx*/

	  /* Configure USART Tx as alternate function  */
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);

	  /* Configure USART Rx as alternate function  */
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);

	  // UART SETTING
	  USART_InitStructure.USART_BaudRate 			= UART_SPEED;				// SETTING
	  USART_InitStructure.USART_WordLength 			= USART_WordLength_8b;
	  USART_InitStructure.USART_StopBits 			= USART_StopBits_2;
	  USART_InitStructure.USART_Parity 				= USART_Parity_No;
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	  USART_InitStructure.USART_Mode 				= USART_Mode_Rx | USART_Mode_Tx;

	  // UART CLOCK SETTING
	  USART_ClockStructure.USART_CPHA				= DISABLE;
	  USART_ClockStructure.USART_CPOL				= DISABLE;
	  USART_ClockStructure.USART_Clock				= ENABLE;
	  USART_ClockStructure.USART_LastBit			= DISABLE;

	  /* USART configuration */
	  USART_Init(USART2, &USART_InitStructure);

	  /* USART clock configuration */
	  USART_ClockInit(USART2, &USART_ClockStructure);

	  /* Enable USART */
	  USART_Cmd(USART2, ENABLE);

}

void UART2_sendData(uint16_t data) {
	USART_SendData(USART2, data);
	while(!(USART2->SR & (1<<6)));			// While not empty wait
}

uint16_t UART2_readData(void) {
	return USART_ReceiveData(USART2);
}

////////////
// UART 4 //
////////////

void UART4_init(void) {

	  /* Structures */
	  GPIO_InitTypeDef GPIO_InitStructure;
	  USART_InitTypeDef USART_InitStructure;
	  USART_ClockInitTypeDef USART_ClockStructure;

	  /* Enable GPIO clock */
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	  /* Enable UART clock */
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_UART4); /* Connect PXx to USARTx_Tx*/
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4);	/* Connect PXx to USARTx_Rx*/

	  /* Configure USART Tx as alternate function  */
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);

	  /* Configure USART Rx as alternate function  */
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);

	  // UART SETTING
	  USART_InitStructure.USART_BaudRate 			= UART4_SPEED;
	  USART_InitStructure.USART_WordLength 			= USART_WordLength_8b;
	  USART_InitStructure.USART_StopBits 			= USART_StopBits_2;
	  USART_InitStructure.USART_Parity 				= USART_Parity_No;
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	  USART_InitStructure.USART_Mode 				= USART_Mode_Rx | USART_Mode_Tx;

	  // UART CLOCK SETTING
	  USART_ClockStructure.USART_CPHA				= DISABLE;
	  USART_ClockStructure.USART_CPOL				= DISABLE;
	  USART_ClockStructure.USART_Clock				= ENABLE;
	  USART_ClockStructure.USART_LastBit			= DISABLE;

	  /* USART configuration */
	  USART_Init(UART4, &USART_InitStructure);

	  /* USART clock configuration */
	  USART_ClockInit(UART4, &USART_ClockStructure);

	  /* Enable USART */
	  USART_Cmd(UART4, ENABLE);

}

void UART4_sendData(uint16_t data) {
	USART_SendData(UART4, data);
	while(!(UART4->SR & (1<<6)));			// While not empty wait
}

uint16_t UART4_readData(void) {
	return USART_ReceiveData(UART4);
}
