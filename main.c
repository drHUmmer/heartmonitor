#include "UART.h"

int main(void)
{
	UART2_init();
	UART4_init();


	uint16_t teller = 0;

    while(1) {
    	UART2_sendData(teller++);
    	UART4_sendData(teller++);
    }
}
