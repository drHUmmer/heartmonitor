#include "UART.h"

int main(void)
{
	UART_init(2, 250000);
	UART_init(4, 152000);

	uint16_t teller = 0;

    while(1) {
    	UART_sendData(2, teller++);
    	UART_sendData(4, teller++);
    }
}
