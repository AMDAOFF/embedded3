#define F_CPU 16000000U
#include <avr/io.h>
#include <stdio.h>
#include <string.h>

#include "USART.h"
#include "i2cmaster.h"
#include "ds3231.h"
void DS3231_getDateTime(void);

char msg[64];

rtc_t today;

int main(void)
{
	init_usart();
	i2c_init();
	init_ds3231();
	rtc_t rtc;
	
	rtc.hour = dec2bcd(8);
	rtc.min =  dec2bcd(55);
	rtc.sec =  dec2bcd(10);
	rtc.date = dec2bcd(29);  // 28
	rtc.month = dec2bcd(10); // 10
	rtc.year = dec2bcd(20);  // 2020
	rtc.weekDay = 3;         // Wednesday: 3rd day of week considering Monday as first day.
	
	ds3231_SetDateTime(&rtc);
	while (1)
	{
		DS3231_getDateTime();
		_delay_ms(1000);
	}
}

struct DateTime {
	char hours[3];
	char minutes[3];
	char seconds[3];
	char years[3];
	char months[3];
	char days[3];
};

void DS3231_getDateTime(void)
{
	struct DateTime dateAndTime;
	
	ds3231_GetDateTime(&today);
	
	//Converts the Binary Coded Decimal (BCD) to Decimal value and converts it to a number 
	
	itoa(bcd2dec(today.hour) , dateAndTime.hours, 10); //hour
	itoa(bcd2dec(today.min), dateAndTime.minutes, 10);  //min
	itoa(bcd2dec(today.sec), dateAndTime.seconds, 10);   //sec
	itoa(bcd2dec(today.date), dateAndTime.days, 10);  //day
	itoa(bcd2dec(today.month), dateAndTime.months, 10); //month
	itoa(bcd2dec(today.year), dateAndTime.years, 10);  //year
	
	strcat(msg,"Time: ");
	strcat(msg,dateAndTime.hours);   //hour
	strcat(msg,":");

	strcat(msg,dateAndTime.minutes);  //min
	strcat(msg,":");
	
	strcat(msg,dateAndTime.seconds);   //sec
	strcat(msg," Date: ");
	
	strcat(msg,dateAndTime.days);   //day
	strcat(msg,"/");
	
	strcat(msg,dateAndTime.months);   //month
	strcat(msg,"/20");
	
	strcat(msg,dateAndTime.years);   //year
	
	send_char(msg);
	SendString("\n");
	memset(msg,0,64); //The memset() function returns a pointer to the memory area dest.
}
