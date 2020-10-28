/* blink.c */
#include <stdio.h>
#include <avr/io.h>
#include "stdio_setup.h"

#define DDR_SPI		DDRB
#define DD_MOSI		DDB2
#define DD_MISO		DDB3
#define DD_SCK		DDB1
#define DD_SS		DDB0

#define P_MOSI		PB2
#define P_MISO		PB3
#define P_SCK		PB1
#define P_SS		PB0

void SPI_MasterInit(void)
{
	
	/* Set MOSI, SCK and SS as output, all others input */
	DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS);
	
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0)|~(1<<CPOL)|~(1<<CPHA); //Set Enable SPI, Master, set clock rate fck/16, set CPHA and CPOL to 0
}

void TimerInit(void)
{	
	OCR1A  = 31249; // Timer triggers half a second because of prescaler 256
	TCCR1B = (1 << WGM12) | (1 << CS12);
}

void SPI_MasterTransmit(char cData)
{
	printf("Sending %u to slave\r\n", cData);
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)))
	;
}



int main(void)
{
	UartInit();
	SPI_MasterInit();
	TimerInit();

	unsigned int seconds = 0;

	while(1)
	{
		if (TIFR1 & (1 << OCF1A)) { // Every 500 milliseconds
			SPI_MasterTransmit('A');
			//SPI_MasterTransmit(++seconds);
			TIFR1 = (1 << OCF1A);
		}
	}
}