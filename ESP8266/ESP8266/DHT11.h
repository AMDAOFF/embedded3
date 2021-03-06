/*
 * DHT11.h
 *
 * Created: 02-11-2020 08:17:18
 *  Author: Kenneth, Krisitan og Jimmy ;)
 */ 


#ifndef DHT11_H_
#define DHT11_H_


#ifndef  F_CPU
#define F_CPU 16000000UL
#endif
#define DHT_PORT PORTB
#define DHT_DDR DDRB
#define DHT_PIN PINB
#define DHT_BIT PB3

#define bit_is_set(sfr,bit) \
(_SFR_BYTE(sfr) & _BV(bit))
#define bit_is_clear(sfr,bit) \
(!(_SFR_BYTE(sfr) & _BV(bit)))
#define set_bit(port, bit) (port) |= (1<<(bit))
#define clear_bit(port, bit) (port) &= ~(1<<(bit))

void DHT_WakeUp(void);
int DHT_Response(void);
void DHT_Decode_Data(int (*array)[8]);
int ConvertToDecimal(int (*array)[8], int byte);


#endif /* DHT11_H_ */