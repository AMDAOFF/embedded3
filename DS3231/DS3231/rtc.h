

#include <avr\io.h>
#include <util\delay.h>

typedef struct
{
  uint8_t sec;
  uint8_t min;
  uint8_t hour;
  uint8_t weekDay;
  uint8_t date;
  uint8_t month;
  uint8_t year;  
}rtc_t;

	int8_t t_low;
	uint8_t t_high;

#define DS3231_ReadMode_U8          0xD1u  
#define DS3231_WriteMode_U8         0xD0u  
#define DS3231_REG_Seconds          (0x00)
#define DS3231_REG_Minutes          (0x01)
#define DS3231_REG_Hour             (0x02)
#define DS3231_REG_Day              (0x03)
#define DS3231_Date                 (0x04)
#define DS3231_Month                (0x05)
#define DS3231_Year                 (0x06)
#define DS3231_REG_ALARM_1          (0x07)
#define DS3231_REG_ALARM_2          (0x0B)
#define DS3231_REG_CONTROL          (0x0E)
#define DS3231_REG_STATUS           (0x0F)
#define DS3231_REG_TEMPERATURE      (0x11)
/***************************************************************************************************
                             Function Prototypes
***************************************************************************************************/
void RTC_Init(void);
void RTC_SetDateTime(rtc_t *rtc);
void RTC_GetDateTime(rtc_t *rtc);
void I2C_Init();
void I2C_Start();
void I2C_Stop(void);
void I2C_Write(uint8_t v_i2cData_u8);
uint8_t I2C_Read(uint8_t v_ackOption_u8);
int8_t rtc_get_temp();
/**************************************************************************************************/


void RTC_Init(void)
{
    I2C_Init();                             // Initialize the I2c module.
    I2C_Start();                            // Start I2C communication

    I2C_Write(C_Ds1307WriteMode_U8);        // Connect to DS1307 by sending its ID on I2c Bus
    I2C_Write(C_Ds1307ControlRegAddress_U8);// Select the Ds1307 ControlRegister to configure Ds1307

    I2C_Write(0x00);                        // Write 0x00 to Control register to disable SQW-Out

    I2C_Stop();                             // Stop I2C communication after initializing DS1307
}


/***************************************************************************************************
                    void RTC_SetDateTime(rtc_t *rtc)
****************************************************************************************************
 * I/P Arguments: rtc_t *: Pointer to structure of type rtc_t. Structure contains hour,min,sec,day,date,month and year 
 * Return value    : none

 * description  :This function is used to update the Date and time of Ds1307 RTC.
                 The new Date and time will be updated into the non volatile memory of Ds1307.
        Note: The date and time should be of BCD format, 
             like 0x12,0x39,0x26 for 12hr,39min and 26sec.    
                  0x15,0x08,0x47 for 15th day,8th month and 47th year.                 
***************************************************************************************************/
void RTC_SetDateTime(rtc_t *rtc)
{
    I2C_Start();                          // Start I2C communication

    I2C_Write(C_Ds1307WriteMode_U8);      // connect to DS1307 by sending its ID on I2c Bus
    I2C_Write(C_Ds1307SecondRegAddress_U8); // Request sec RAM address at 00H

    I2C_Write(rtc->sec);                    // Write sec from RAM address 00H
    I2C_Write(rtc->min);                    // Write min from RAM address 01H
    I2C_Write(rtc->hour);                    // Write hour from RAM address 02H
    I2C_Write(rtc->weekDay);                // Write weekDay on RAM address 03H
    I2C_Write(rtc->date);                    // Write date on RAM address 04H
    I2C_Write(rtc->month);                    // Write month on RAM address 05H
    I2C_Write(rtc->year);                    // Write year on RAM address 06h

    I2C_Stop();                              // Stop I2C communication after Setting the Date
}

/***************************************************************************************************
                     void RTC_GetDateTime(rtc_t *rtc)
****************************************************************************************************
 * I/P Arguments: rtc_t *: Pointer to structure of type rtc_t. Structure contains hour,min,sec,day,date,month and year 
 * Return value    : none

 * description  :This function is used to get the Date(d,m,y) from Ds1307 RTC.

    Note: The date and time read from Ds1307 will be of BCD format, 
          like 0x12,0x39,0x26 for 12hr,39min and 26sec.    
               0x15,0x08,0x47 for 15th day,8th month and 47th year.              
***************************************************************************************************/
void RTC_GetDateTime(rtc_t *rtc)
{
    I2C_Start();                            // Start I2C communication

    I2C_Write(C_Ds1307WriteMode_U8);        // connect to DS3231 by sending its ID on I2c Bus
    I2C_Write(C_Ds1307SecondRegAddress_U8); // Request Sec RAM address at 00H

    I2C_Stop();                                // Stop I2C communication after selecting Sec Register

    I2C_Start();                            // Start I2C communication
    I2C_Write(C_Ds1307ReadMode_U8);            // connect to DS1307(Read mode) by sending its ID

    rtc->sec = I2C_Read(1);                // read second and return Positive ACK
    rtc->min = I2C_Read(1);                 // read minute and return Positive ACK
    rtc->hour= I2C_Read(1);               // read hour and return Negative/No ACK
    rtc->weekDay = I2C_Read(1);           // read weekDay and return Positive ACK
    rtc->date= I2C_Read(1);              // read Date and return Positive ACK
    rtc->month=I2C_Read(1);            // read Month and return Positive ACK
    rtc->year =I2C_Read(0);             // read Year and return Negative/No ACK

    I2C_Stop();                              // Stop I2C communication after reading the Date
}

uint8_t dec2bcd(char num)
{
	return ((num/10 * 16) + (num % 10));
}
// Convert Binary Coded Decimal (BCD) to Decimal
uint8_t bcd2dec(char num)
{
	return ((num/16 * 10) + (num % 16));
}

void I2C_Init()
{
    TWSR=0x00; //set presca1er bits to zero
    TWBR=0x46; //SCL frequency is 50K for 16Mhz
    TWCR=0x04; //enab1e TWI module
}
void I2C_Start()
{
    TWCR = ((1<<TWINT) | (1<<TWSTA) | (1<<TWEN));
    while (!(TWCR & (1<<TWINT)));
}

void I2C_Stop(void)
{
    TWCR = ((1<< TWINT) | (1<<TWEN) | (1<<TWSTO));
    _delay_ms(100) ; //wait for a short time
}

void I2C_Write(uint8_t v_i2cData_u8)
{
    TWDR = v_i2cData_u8 ;
    TWCR = ((1<< TWINT) | (1<<TWEN));
    while (!(TWCR & (1 <<TWINT)));
}

uint8_t I2C_Read(uint8_t v_ackOption_u8)
{
    TWCR = ((1<< TWINT) | (1<<TWEN) | (v_ackOption_u8<<TWEA));
    while ( !(TWCR & (1 <<TWINT)));
    return TWDR;
}


int8_t rtc_get_temp()
{
	int8_t t_H;
	int8_t t_L;
	I2C_Start();                          // Start I2C communication
	I2C_Write(C_Ds1307WriteMode_U8);      // connect to DS1307 by sending its ID on I2c Bus
	I2C_Write(DS3231_REG_TEMPERATURE);    // Request Sec RAM address at 11H
	I2C_Stop();                           // Stop I2C communication after selecting Sec Register
	I2C_Start();                          // Start I2C communication
	I2C_Write(C_Ds1307ReadMode_U8);       // connect to DS3231(Read mode) by sending its ID
	t_L = I2C_Read(1);                    // read second and return Positive ACK
	t_H = I2C_Read(0);                    // read minute and return Positive ACK
	I2C_Stop();                           // Stop I2C communication after reading the Date
	
     t_low= t_L;
     t_high=t_H;
	return (t_L);
}