#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include "stdio_setup.h"
#include "DHT11.h"

uint16_t data[5];

int main(void)
{
	
	UartInit();
	DHT_Init();				/* send start pulse */
	DHT_Response();			/* receive response */


	
 while(1)
 {			

	 data[0]=Receive_data();	/* store first eight bit in I_RH */
	 data[1]=Receive_data();	/* store next eight bit in D_RH */
	 data[2]=Receive_data();	/* store next eight bit in I_Temp */
	 data[3]=Receive_data();	/* store next eight bit in D_Temp */
	 data[4]=Receive_data();/* store next eight bit in CheckSum */
	 
	 printf(data[0]);
	 _delay_ms(500);
 }
}