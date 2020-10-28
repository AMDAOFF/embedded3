/* blink.c */
#include <stdio.h>
#include <avr/io.h>
#include "stdio_setup.h"

#define DDR_SPI		DDRB
#define DD_MOSI		DDB2
#define DD_MISO		DDB3
#define DD_SCK		DDB1
#define DD_SS		DDB0

void SPI_SlaveInit(void)
{
	/* Set MISO output, all others input */
	DDR_SPI = (1<<DD_MISO);
	/* Enable SPI */
	SPCR = (1<<SPE);
}
char SPI_SlaveReceive(void)
{
	printf("Waiting for master");
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)))
	;
	/* Return Data Register */
	return SPDR;
}

int main(void)
{
	printf("Before waiting for master");
	SPI_SlaveInit();
	while (1)
	{
		printf("Waiting for master");
		//printf(SPI_SlaveReceive());
	}
}