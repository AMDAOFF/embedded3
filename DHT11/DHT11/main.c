#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include "stdio_setup.h"
#include "DHT11.h"

uint8_t temp, hum;
uint8_t *pTemp = &temp;
uint8_t *pHum = &hum;

int main(void)
{
	
	UartInit();

	while(1)
	{
		DHT_Read(pTemp, pHum);
		switch(GetDHTStatus()){
			case DHT_OK:
			printf("temp: %i\t\thum: %i\r\n", temp, hum);
			break;
			
			case DHT_Error_Timeout:
			printf("1");
			break;
			
			case DHT_Error_Temperature:
			printf("2");
			break;
			
			case DHT_Error_Humidity:
			printf("3");
			break;
			
			case DHT_Failed:
			printf("4");
			break;
		}

		_delay_ms(2000);
	}
}