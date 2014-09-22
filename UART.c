#include "UART.h"

void UART_sendData(uint8_t uart_id, uint16_t data) {
	USART_TypeDef* uart_id_name = GetUARTName(uart_id); 	// Get UART ID
	while(!(uart_id_name->SR & (1<<6)));					// While not empty wait
	USART_SendData(uart_id_name, data);						// Send new data
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
}

//////////////////////////////
// INITIALISATION FUNCTIONS //
//////////////////////////////
void UART2_init(uint32_t uart_speed) {

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
	  USART_InitStructure.USART_BaudRate 			= uart_speed;				// Input variable
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

	  /* USART clock configuration */
	  USART_ClockInit(USART2, &USART_ClockStructure);

	  /* USART configuration */
	  USART_Init(USART2, &USART_InitStructure);

	  /* Enable USART */
	  USART_Cmd(USART2, ENABLE);

}

void UART4_init(uint32_t uart_speed) {

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
	  USART_InitStructure.USART_BaudRate 			= uart_speed;			// input variable
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


