#include "DS3231.hpp"


DS3231::DS3231(I2C_HandleTypeDef *_hi2c)
{
	__disable_irq();
	hi2c1 = _hi2c;
	__enable_irq();
}

void DS3231::SetDate(DateTime _date)
{
	__disable_irq();
	uint8_t data[2];
	
	data[0]=Day_ADDRESS;
	data[1]=hex2bcd(_date.getDayOfWeek());
	HAL_I2C_Master_Transmit(hi2c1,DS3231_ADDRESS,data,2,50);
	
	data[0]=Date_ADDRESS;
	data[1]=hex2bcd(_date.getDay());
	HAL_I2C_Master_Transmit(hi2c1,DS3231_ADDRESS,data,2,50);
	
	
	data[0]=Month_ADDRESS;
	data[1]=hex2bcd(_date.getMonth());
	HAL_I2C_Master_Transmit(hi2c1,DS3231_ADDRESS,data,2,50);
	
	data[0]=Year_ADDRESS;
	data[1]=hex2bcd(_date.getYear());
	HAL_I2C_Master_Transmit(hi2c1,DS3231_ADDRESS,data,2,50);
	__enable_irq();
	
}

void DS3231::SetTime(DateTime _time)
{
	__disable_irq();
	uint8_t data[2];
	
	
	data[0]=Seconds_ADDRESS;
	data[1]=0x7f;
	HAL_I2C_Master_Transmit(hi2c1,DS3231_ADDRESS,data,2,50);
	
	
  data[0]=Seconds_ADDRESS;
	data[1]=hex2bcd(_time.getSecond());
	HAL_I2C_Master_Transmit(hi2c1,DS3231_ADDRESS,data,2,50);

	
	data[0]=Minutes_ADDRESS;
	data[1]=hex2bcd(_time.getMinute());
	HAL_I2C_Master_Transmit(hi2c1,DS3231_ADDRESS,data,2,50);
	
	data[0]=Hours_ADDRESS;
	data[1]=hex2bcd(_time.getHour());
	HAL_I2C_Master_Transmit(hi2c1,DS3231_ADDRESS,data,2,50);
	__enable_irq();
		
}

void DS3231::GetDate(DateTime *_date)
{
	__disable_irq();
	uint8_t day;
	uint8_t date;
	uint8_t mount;
	uint8_t year;
	uint8_t data[1];
	
	data[0]=Day_ADDRESS;
	HAL_I2C_Master_Transmit(hi2c1,DS3231_ADDRESS,data,1,1);
	HAL_I2C_Master_Receive(hi2c1,DS3231_ADDRESS,&day,1,1);
	_date->setDayOfWeek(bcd2bin(day));


	data[0]=Date_ADDRESS;
	HAL_I2C_Master_Transmit(hi2c1,DS3231_ADDRESS,data,1,1);
	HAL_I2C_Master_Receive(hi2c1,DS3231_ADDRESS,&date,1,1);
	_date->setDay(bcd2bin(date));


	data[0]=Month_ADDRESS;
	HAL_I2C_Master_Transmit(hi2c1,DS3231_ADDRESS,data,1,1);
	HAL_I2C_Master_Receive(hi2c1,DS3231_ADDRESS,&mount,1,1);
	_date->setMonth(bcd2bin(mount));


	data[0]=Year_ADDRESS;
	HAL_I2C_Master_Transmit(hi2c1,DS3231_ADDRESS,data,1,1);
	HAL_I2C_Master_Receive(hi2c1,DS3231_ADDRESS,&year,1,1);
	_date->setYear(bcd2bin(year));
	__enable_irq();
}
	
void DS3231::GetTime(DateTime *_time)
{
	__disable_irq();
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t data[1];

	data[0]=Seconds_ADDRESS;
	HAL_I2C_Master_Transmit(hi2c1,DS3231_ADDRESS,data,1,1);
	HAL_I2C_Master_Receive(hi2c1,DS3231_ADDRESS,&sec,1,1);
	_time->setSecond(bcd2bin(sec));
	
	data[0]=Minutes_ADDRESS;
	HAL_I2C_Master_Transmit(hi2c1,DS3231_ADDRESS,data,1,1);
	HAL_I2C_Master_Receive(hi2c1,DS3231_ADDRESS,&min,1,1);
	_time->setMinute(bcd2bin(min));

	
	data[0]=Hours_ADDRESS;
	HAL_I2C_Master_Transmit(hi2c1,DS3231_ADDRESS,data,1,1);
	HAL_I2C_Master_Receive(hi2c1,DS3231_ADDRESS,&hour,1,1);
	_time->setHour(bcd2bin(hour));
	__enable_irq();
	
}

unsigned char DS3231::bcd2bin(unsigned char x)
{
  uint8_t bin;
	bin=((x & 0xf0)>>4)*10 +(x & 0x0f);
  return (bin);
}

unsigned char DS3231::hex2bcd (unsigned char x)
{
	uint8_t y;
	y = (x/10) <<4;
	y = y | (x % 10);
	return (y);
}

float DS3231::GetTemperature()
{
	__disable_irq();
	float temp3231 = -999;
	uint8_t data[1];
	
	data[0] = Temperature_ADDRESS;
	HAL_I2C_Master_Transmit(hi2c1,DS3231_ADDRESS,data,1,1);
	HAL_I2C_Master_Receive(hi2c1,DS3231_ADDRESS,data,2,50);
	
	temp3231 = ((((short)data[0] << 8) | (short)data[1]) >> 6) / 4.0;
	
	__enable_irq();
	return temp3231;
}
