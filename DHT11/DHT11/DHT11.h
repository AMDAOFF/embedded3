/*
 * DHT11.h
 *
 * Created: 29-10-2020 09:35:24
 *  Author: Kenneth, Kristian og Jimmy ;)
 */ 

//

#ifndef DHT11_H_
#define DHT11_H_

#define F_CPU 16E6

#include <avr/io.h>

#define DHT_PIN PINB
#define DHT_PORT PORTB
#define DHT_DDR DDRB
#define DHT_BIT PB3

#define set_bit_high(port, bit) (port) |= (1 << (bit)) // Set Bit
#define set_bit_low(port, bit) (port) &= ~(1 << (bit)) // Clear Bit

enum DHT_Status_t{
	DHT_OK,
	DHT_Failed,
	DHT_Error_Temperature,
	DHT_Error_Timeout,
	DHT_Error_Humidity
	};
	
void DHT_Init(void);
void DHT_Read(uint8_t *pTemp, uint8_t *pHum);
//DHT_Status_t GetDHTStatus(void);

#endif /* DHT11_H_ */