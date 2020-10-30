/*
 * DHT11.c
 *
 * Created: 29-10-2020 09:35:13
 *  Author: Kenneth
 */ 

#define F_CPU 16E6

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "DHT11.h"

void DHT_Init(void)
{
	DHT_DDR |= (1<<DHT_PIN);		// Sets the PB4 to output
	
	DHT_PORT &= ~(1<<DHT_PIN);		// Sets the port to low
	_delay_ms(18);
	DHT_PORT |= (1<<DHT_PIN);		// Sets the port to high
		
	_delay_ms(0.040);
	DHT_DDR &= ~(1<<DHT_PIN);		// Sets the PB4 to input
}

void DHT_Read(void)
{
	int count = 0;
	while(DHT_PORT &= ~(1<<DHT_PIN))
	{
		_delay_ms(0.002);
		count++;
		if (count > 10)
		{
			break;
		}
	}
}