#include "UART.h"

void UART_init(uint8_t uart_id, uint32_t uart_speed) {

	GPIO_TypeDef* GPIOPORT;
	uint16_t GPIO_PIN_TX;
	uint16_t GPIO_PIN_RX;
	uint32_t CLOCK_CMD_1;
	uint32_t CLOCK_CMD_2;
	uint8_t  GPIO_AF_SET_TX;
	uint8_t  GPIO_AF_SET_RX;
	uint8_t  GPIO_PinSource_TX;
	uint8_t  GPIO_PinSource_RX;
	USART_TypeDef* UART_NAME	= GetUARTName(uart_id);

	switch(uart_id) {
		case (2):
			GPIOPORT 			= GPIOA;
			CLOCK_CMD_1 		= RCC_AHB1Periph_GPIOA;
			CLOCK_CMD_2 		= RCC_APB1Periph_USART2;
			GPIO_PIN_TX 		= GPIO_Pin_2;
			GPIO_PIN_RX 		= GPIO_Pin_3;
			GPIO_AF_SET_TX 		= GPIO_AF_USART2;
			GPIO_AF_SET_RX 		= GPIO_AF_USART2;
			GPIO_PinSource_TX 	= GPIO_PinSource2;
			GPIO_PinSource_RX 	= GPIO_PinSource3;

			break;

		case (4):
			GPIOPORT 			= GPIOA;
			CLOCK_CMD_1 		= RCC_AHB1Periph_GPIOA;
			CLOCK_CMD_2 		= RCC_APB1Periph_UART4;
			GPIO_PIN_TX 		= GPIO_Pin_0;
			GPIO_PIN_RX 		= GPIO_Pin_1;
			GPIO_AF_SET_TX 		= GPIO_AF_UART4;
			GPIO_AF_SET_RX 		= GPIO_AF_UART4;
			GPIO_PinSource_TX 	= GPIO_PinSource0;
			GPIO_PinSource_RX 	= GPIO_PinSource1;

			break;

		default: return;
	}

	  /* Structures */
	  GPIO_InitTypeDef GPIO_InitStructure;
	  USART_InitTypeDef USART_InitStructure;
	  USART_ClockInitTypeDef USART_ClockStructure;

	  /* Enable GPIO clock */
	  RCC_AHB1PeriphClockCmd(CLOCK_CMD_1, ENABLE);

	  /* Enable UART clock */
	  RCC_APB1PeriphClockCmd(CLOCK_CMD_2, ENABLE);

	  GPIO_PinAFConfig(GPIOPORT, GPIO_PinSource_TX, GPIO_AF_SET_TX); /* Connect PXx to USARTx_Tx*/
	  GPIO_PinAFConfig(GPIOPORT, GPIO_PinSource_RX, GPIO_AF_SET_RX);	/* Connect PXx to USARTx_Rx*/

	  /* Configure USART Tx as alternate function  */
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

	  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_TX;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);

	  /* Configure USART Rx as alternate function  */
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_RX;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);

	  // UART SETTING
	  USART_InitStructure.USART_BaudRate 			= uart_speed;
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
	  USART_Init(UART_NAME, &USART_InitStructure);

	  /* USART clock configuration */
	  USART_ClockInit(UART_NAME, &USART_ClockStructure);

	  /* Enable USART */
	  USART_Cmd(UART_NAME, ENABLE);

}

void UART_sendData(uint8_t uart_id, uint16_t data) {
	USART_TypeDef* uart_id_name = GetUARTName(uart_id);
	USART_SendData(uart_id_name, data);
	while(!(uart_id_name->SR & (1<<6)));			// While not empty wait
}

uint16_t UART_readData(uint8_t uart_id) {
	USART_TypeDef* uart_id_name = GetUARTName(uart_id);
	return USART_ReceiveData(uart_id_name);
}

USART_TypeDef* GetUARTName (uint8_t uart_id) {
	switch(uart_id) {
		case (2): return USART2;
		case (4): return UART4;
		default: return NULL;
	}

	return NULL;
}
