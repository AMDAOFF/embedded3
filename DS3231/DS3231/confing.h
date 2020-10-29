/*
 * confing.h
 *
 * Created: 18/01/06 2:16:31 AM
 *  Author: ghola
 */ 


#ifndef CONFING_H_
#define CONFING_H_

#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>



char t[]="Time: ";
char da[]=" Date: ";
char msg[64];
rtc_t today;
rtc_t nt;

 uint8_t y;
 uint8_t m;
 uint8_t d;

 uint8_t h;
 uint8_t mi;
 uint8_t s;


void rtc_data(void);


void rtc_data(void)
{
	
	RTC_GetDateTime(&today);
	char d_y[4];
	char d_m[4];
	char d_d[4];
	char d_h[4];
	char d_mi[4];
	char d_s[4];
	char d_tmp[4];
	itoa(bcd2dec(today.hour) , d_h, 10); //hour
	itoa(bcd2dec(today.min), d_mi, 10);  //min
	itoa(bcd2dec(today.sec), d_s, 10);   //sec
	itoa(bcd2dec(today.date), d_d, 10);  //day
	itoa(bcd2dec(today.month), d_m, 10); //month
	itoa(bcd2dec(today.year), d_y, 10);  //year
	
	
	strcat(msg,t);
	strcat(msg,d_h);   //hour
	strcat(msg,":");

	strcat(msg,d_mi);  //min
	strcat(msg,":");
	
	strcat(msg,d_s);   //sec
	strcat(msg,da);
	
	strcat(msg,d_d);   //day
	strcat(msg,".");
	
	strcat(msg,d_m);   //month
	strcat(msg,".20");
	
	strcat(msg,d_y);   //year

	strcat(msg," ** Tmp: ");
	
	itoa(rtc_get_temp(), d_tmp, 10);  
	strcat(msg,d_tmp);  //temperature
	
	send_char(msg);
	SendString(" C\n");
	memset(msg,0,64);
}






#endif /* CONFING_H_ */
