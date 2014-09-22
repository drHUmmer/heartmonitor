#ifndef UART_H
#define UART_H

#include <stdio.h>
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

/////////////////////////
// Function prototypes //
/////////////////////////
// Public functions
void UART2_init(uint32_t uart_speed);
void UART4_init(uint32_t uart_speed);
void UART_sendData(uint8_t uart_id, uint16_t data);
uint16_t UART_readData(uint8_t uart_id);

// Private function
USART_TypeDef* GetUARTName (uint8_t uart_id);

#endif //UART_H
