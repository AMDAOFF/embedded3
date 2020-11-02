#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include "stdio_setup.h"
//#include "DHT11.h"
#include "DHT11/DHT11_test.h"

uint8_t temp, hum;
uint8_t *pTemp = &temp;
uint8_t *pHum = &hum;

int main(void)
{
	//DHT_Init();
	UartInit();

	while(1)
	{		
		DHT_WakeUp();
		int array[5][8];
		if (DHT_Response())
		{
			DHT_Decode_Data(array);
			
			printf("Fugtighed: %i \r\n", ConvertToDecimal(array, 1));
			printf("Temp: %i \r\n", ConvertToDecimal(array, 3));
		}

		_delay_ms(2000);
	}
}