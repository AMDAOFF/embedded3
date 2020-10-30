/*
* DHT11.c
*
* Created: 29-10-2020 09:35:13
*  Author: Kenneth, Kristian og Jimmy ;)
*/



#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdio.h>
#include <util/delay.h>
#define F_CPU 16E6
#include "DHT11.h"

enum DHT_Status_t __DHT_STATUS;

void DHT_Init(void)
{
	DHT_DDR |= (1<<DHT_PIN);		// Sets the PB4 to output
	
	DHT_PORT &= ~(1<<DHT_PIN);		// Sets the port to low
	_delay_ms(18);
	DHT_PORT |= (1<<DHT_PIN);		// Sets the port to high
	
	_delay_ms(0.040);
	DHT_DDR &= ~(1<<DHT_PIN);		// Sets the PB4 to input
}

void DHT_ReadRaw(uint8_t Data[4]){
	uint8_t buffer[5] = {0,0,0,0,0};
	uint8_t retries, i, j;
	__DHT_STATUS = DHT_OK;
	retries = i = j = 0;
	
	if (__DHT_STATUS == DHT_OK)
	{
		set_bit_low(DHT_PORT, DHT_BIT); // DHT_PIN = 0;
		set_bit_high(DHT_DDR, DHT_BIT); // DHT_PIN = Output
		_delay_ms(20);
		
		
		set_bit_high(DHT_PORT, DHT_BIT); // DHT_PIN = 1 (Pull-up Resistor)
		set_bit_low(DHT_DDR, DHT_BIT); // DHT_PIN = Input
		
		retries = 0;
		while (bit_is_set(DHT_PIN, DHT_BIT))
		{
			_delay_us(2);
			retries += 2;
			if (retries > 60)
			{
				__DHT_STATUS =DHT_Error_Timeout;
				break;
			}
		};
		
		// Step 2
		
		if (__DHT_STATUS == DHT_OK)
		{
			while (bit_is_clear(DHT_PIN, DHT_BIT))
			{
				_delay_us(2);
				retries += 2;
				if (retries > 70)
				{
					__DHT_STATUS = DHT_Error_Timeout;
					break;
				}
			}
		}
		
		// Step 3
		if (__DHT_STATUS == DHT_OK)
		{
			for (i = 0; i < 5; i++)
			for (j = 7; j >= 0; j--)
			{
				retries = 0;
				while (bit_is_clear(DHT_PIN, DHT_BIT))
				{
					_delay_us(2);
					retries += 2;
					if (retries > 70)
					{
						__DHT_STATUS = DHT_Error_Timeout;
						j = -1;
						i = 5;
						break;
					}
				}
			}
		}
		
		// Step 4
		if (__DHT_STATUS == DHT_OK)
		{
			_delay_us(35);
			if (bit_is_set(DHT_PIN, DHT_BIT))
			set_bit(buffer[i], j);
			retries = 0;
			while (bit_is_set(DHT_PIN, DHT_BIT))
			{
				_delay_us(2);
				retries += 2;
				if (retries > 100)
				{
					__DHT_STATUS = DHT_Error_Timeout;
					break;
				}
			}
		}
		
	}
	}
DHT_Status_t GetDHTStatus(void){
	return __DHT_STATUS;
}
void DHT_Read(uint8_t *pTemp, uint8_t *pHum)
{
	uint8_t data[4] = {0, 0, 0, 0};
	
	DHT_ReadRaw(data);
	
	if (__DHT_STATUS ==DHT_OK)
	{
		//Calculate values
		*pTemp = data[2];
		*pHum = data[0];
		
		if ((*pTemp < 0) || (*pTemp > 50))
		__DHT_STATUS = DHT_Error_Temperature;
		else if ((*pHum < 10) || (*pHum > 100))
		__DHT_STATUS = DHT_Error_Humidity;
	}
}