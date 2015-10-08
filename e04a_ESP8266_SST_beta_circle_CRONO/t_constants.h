#include <Arduino.h>
#include <ESP8266WiFi.h>


//IO
#define GPIO0  0


//ENCODER
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define encoder0PinA  3
#define encoder0PinB  4


//TIMER DISPLAY
#define TIMER_DISPLAY_SETPOINT 3000

//TIMER NTP
const int timeZone = 2;     // Central European Time
#define MEMSET_NTP_START 300




#define SERIAL_OUT Serial

