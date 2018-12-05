# STM32_DS3231

to use this lib you should be enable C99 Mode and Add --cpp to misc controls (in options for target --> C/C++ tab)

then you can add library to your project and use it

#include "DateTime.h"
#include "DS3231.hpp"


DateTime datetime;
DS3231 Ds3231(&hi2c1); // for example use hi2c1

datetime.setSecond(40);
datetime.setMinute(30);
datetime.setHour(23);
datetime.setDayOfWeek(5);
datetime.setDay(6);
datetime.setMonth(4);
datetime.setYear(18); // for example 2018/04/06   23:30:40
Ds3231.SetTime(datetime); // set time to DS3231
Ds3231.SetDate(datetime); // set Date to DS3231

  
Ds3231.GetTime(&datetime); // get current time from DS3231
Ds3231.GetDate(&datetime); // get current date from DS3231

float temp = Ds3231.GetTemperature(); // get temperature from DS3231 Sensor
