/*
 * DHT11.h
 *
 * Created: 29-10-2020 09:35:24
 *  Author: Kenneth
 */ 

//

#ifndef DHT11_H_
#define DHT11_H_

#define F_CPU 16E6

#include <avr/io.h>

#define DHT_PIN PB3
#define DHT_PORT PORTB
#define DHT_DDR DDRB
#define DHT_BIT 0

#define set_bit(port, bit)
#define clear_bit(port, bit)

void DHT_Init(void);
int DHT_Read(void);
void DHT_Response(void);

#endif /* DHT11_H_ */