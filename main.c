#include "UART.h"

int main(void)
{
	UART2_init(1000000);
	UART4_init(1000000);

	uint8_t teller = 0;

    while(1) {
    	UART_sendData(2, teller++);
    	UART_sendData(4, teller++);
    }
}
