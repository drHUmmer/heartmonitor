// Include the header file
#include "UART.h"

/** CAUTION **
 * Only UART2 and UART4 are working in this version of the software
 */

/**
 * Function that allows the user to send data using a specific UART.
 * @param uart_id		The UART number you want to use
 * @param data			THe data you want to send
 */
void UART_sendData(uint8_t uart_id, uint16_t data) {
	USART_TypeDef* uart_id_name = GetUARTName(uart_id); 	// Get UART ID
	while(!(uart_id_name->SR & (1<<6)));					// While not empty wait
	USART_SendData(uart_id_name, data);						// Send new data
}

/**
 * Get the data from a specific UART buffer
 * @param  uart_id		The UART number you want to read
 * @return				The data in the buffer
 */
uint16_t UART_readData(uint8_t uart_id) {
	USART_TypeDef* uart_id_name = GetUARTName(uart_id);
	return USART_ReceiveData(uart_id_name);
}

/**
 * PRIVATE FUNCTION
 * Gives functions the correct name of a UART.
 * Reason is to have more generic functions for reading and sending
 * @param  uart_id		The ID of the UART
 * @return				The name of the UART
 */
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
/**
 * UART initialisation for the UART2.
 * @param uart_baudrate		Set the baudrate for UART2
 */
void UART2_init(uint32_t uart_baudrate) {

	  /* Structures */
	  GPIO_InitTypeDef GPIO_InitStructure;
	  USART_InitTypeDef USART_InitStructure;
	  USART_ClockInitTypeDef USART_ClockStructure;


	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);					/* Enable GPIO clock */
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);				/* Enable UART clock */

	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2); 			/* Connect PXx to USARTx_Tx*/
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);				/* Connect PXx to USARTx_Rx*/

	  /* Configure USART Tx as alternate function  */
	  GPIO_InitStructure.GPIO_OType 				= GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd	 				= GPIO_PuPd_DOWN;
	  GPIO_InitStructure.GPIO_Speed 				= GPIO_Speed_50MHz;

	  GPIO_InitStructure.GPIO_Pin 					= GPIO_Pin_2;
	  GPIO_InitStructure.GPIO_Mode 					= GPIO_Mode_AF;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);

	  /* Configure USART Rx as alternate function  */
	  GPIO_InitStructure.GPIO_Pin 					= GPIO_Pin_3;
	  GPIO_InitStructure.GPIO_Mode 					= GPIO_Mode_AF;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);

	  /* UART control settings */
	  USART_InitStructure.USART_BaudRate 			= uart_baudrate;		/* Function input variable */
	  USART_InitStructure.USART_WordLength 			= USART_WordLength_8b;
	  USART_InitStructure.USART_StopBits 			= USART_StopBits_2;
	  USART_InitStructure.USART_Parity 				= USART_Parity_No;
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	  USART_InitStructure.USART_Mode 				= USART_Mode_Rx | USART_Mode_Tx;

	  /* UART clock settings */
	  USART_ClockStructure.USART_CPHA				= DISABLE;
	  USART_ClockStructure.USART_CPOL				= DISABLE;
	  USART_ClockStructure.USART_Clock				= ENABLE;
	  USART_ClockStructure.USART_LastBit			= DISABLE;

	  
	  USART_ClockInit(USART2, &USART_ClockStructure);	/* USART clock configuration */
	  USART_Init(USART2, &USART_InitStructure);			/* USART configuration */
	  USART_Cmd(USART2, ENABLE); 						/* Enable USART */
}

/**
 * Initialisation for UART4
 * @param uart_baudrate		Set the baudrate for UART4
 */
void UART4_init(uint32_t uart_baudrate) {

	  /* Structures */
	  GPIO_InitTypeDef GPIO_InitStructure;
	  USART_InitTypeDef USART_InitStructure;
	  USART_ClockInitTypeDef USART_ClockStructure;

	  
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);				/* Enable GPIO clock */
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);				/* Enable UART clock */

	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_UART4); 			/* Connect PXx to USARTx_Tx*/
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4);			/* Connect PXx to USARTx_Rx*/

	  /* Configure USART Tx as alternate function  */
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);

	  /* Configure USART Rx as alternate function  */
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);

	  /* UART control settings */
	  USART_InitStructure.USART_BaudRate 			= uart_baudrate;		/* Function input variable */
	  USART_InitStructure.USART_WordLength 			= USART_WordLength_8b;
	  USART_InitStructure.USART_StopBits 			= USART_StopBits_2;
	  USART_InitStructure.USART_Parity 				= USART_Parity_No;
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	  USART_InitStructure.USART_Mode 				= USART_Mode_Rx | USART_Mode_Tx;

	  /* UART clock settings */
	  USART_ClockStructure.USART_CPHA				= DISABLE;
	  USART_ClockStructure.USART_CPOL				= DISABLE;
	  USART_ClockStructure.USART_Clock				= ENABLE;
	  USART_ClockStructure.USART_LastBit			= DISABLE;

	  USART_Init(UART4, &USART_InitStructure);			/* USART configuration */
	  USART_ClockInit(UART4, &USART_ClockStructure);	/* USART clock configuration */
	  USART_Cmd(UART4, ENABLE); 						/* Enable USART */
}
