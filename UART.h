#ifndef UART_H
#define UART_H

///////////////
// Libraries //
///////////////
#include <stdio.h>
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

/////////////
// DEFINES //
/////////////
#define NO_WAIT 0
#define WAIT	1

/////////////////////////
// Function prototypes //
/////////////////////////
// Public functions
void UART2_init(uint32_t uart_baudrate);
void UART4_init(uint32_t uart_baudrate);
void UART_sendData(uint8_t uart_id, uint16_t data, u8 wait);
uint16_t UART_readData(uint8_t uart_id);

// Private function
USART_TypeDef* GetUARTName (uint8_t uart_id);

#endif // UART_H
