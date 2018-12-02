#ifndef __DS3231_H
#define __DS3231_H

#include "stm32f1xx_hal.h"
#include "stdint.h"
#include "DateTime.h"


#define  DS3231_ADDRESS  	0xD0

/* Timekeeper Registers */
#define  Seconds_ADDRESS  	0x00
#define  Minutes_ADDRESS  	0x01
#define  Hours_ADDRESS   	0x02
#define  Day_ADDRESS     	0x03
#define  Date_ADDRESS    	0x04
#define  Month_ADDRESS  	0x05
#define  Year_ADDRESS    	0x06
#define  Control_ADDRESS 	0x07

#define  Temperature_ADDRESS	0x11


class DS3231
{
public:
	DS3231(I2C_HandleTypeDef *_hi2c);
	void GetTime(DateTime *_time);
	void GetDate(DateTime *_date);
	void SetTime(DateTime _time);
	void SetDate(DateTime _date);
	float GetTemperature();
private:
	I2C_HandleTypeDef *hi2c1;
	unsigned char hex2bcd (unsigned char x);
	unsigned char bcd2bin(unsigned char x);
};



#endif
