#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include "stdio_setup.h"
#include "DHT11.h"

int main(void)
{
	
	UartInit();
	printf("test");

	DHT_Init();
	DHT_Read();

	while(1) {
	}
}