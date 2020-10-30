/*
* DHT11.c
*
* Created: 29-10-2020 09:35:13
*  Author: Kenneth, Kristian og Jimmy :)
*/

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#define F_CPU 16E6
#include "DHT11.h"

uint8_t c=0;

void DHT_Init(void)
{
	printf("Initializing \r\n");
	DHT_DDR |= (1<<DHT_PIN);		// Sets the PB4 to output
	
	DHT_PORT &= ~(1<<DHT_PIN);		// Sets the port to low
	_delay_ms(18);
	DHT_PORT |= (1<<DHT_PIN);		// Sets the port to high
	
	_delay_ms(0.040);
	printf("Finished - Initializing \r\n");
}

void DHT_Response(void)						/* receive response from DHT11 */
{
	DHT_DDR &= ~(1<<DHT_PIN);
	printf("Started - Response \r\n");
	printf("Finished - Response \r\n");
}

uint8_t* Receive_data()							/* receive data */
{
	printf("Started - Receive_data \r\n");
	uint8_t bits[8];
	for (int bit=0; bit<8; bit++)
	{
		while((DHT_PORT & (1<<DHT_PIN)) == 0);	/* check received bit 0 or 1 */
		_delay_us(30);
		if(DHT_PORT & (1<<DHT_PIN))				/* if high pulse is greater than 30ms */
		bits[bit] = (c<<1)|(0x01);						/* then its logic HIGH */
		else									/* otherwise its logic LOW */
		bits[bit] = (c<<1);
		while(DHT_PORT & (1<<DHT_PIN));
	}
	printf("Finished - Receive_data \r\n");
	return bits;
}

int DHT_Read(void)
{
	int count = 0;
	while(DHT_PORT & (1<<DHT_PIN))
	{
		_delay_ms(0.002);
		count++;
		if (count > 30)
		{
			break;
		}
	}
}