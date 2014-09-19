#ifndef UART_H
#define UART_H

#include <stdio.h>
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

// UART settings
#define UART2_SPEED		250000

#define UART4_SPEED		250000

// UART_PORT
#define	UART_NR_2		0x02
#define	UART_NR_4		0x04

/////////////////////////
// Function prototypes //
/////////////////////////
// UART 2 //
void UART2_init();
void UART2_sendData(uint16_t data);
uint16_t UART2_readData(void);

// UART 4 //
void UART4_init();
void UART4_sendData(uint16_t data);
uint16_t UART4_readData(void);




#endif //UART_H
