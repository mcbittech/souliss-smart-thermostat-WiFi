#include <Arduino.h>

#include <ESP8266WiFi.h>
#define VERSION "v0.5"

//DHT22
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DHTPIN 12
#define DHTTYPE DHT22

//ENCODER
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define ENCODER_PIN_A   3
#define ENCODER_PIN_B   4
#define ENCODER_SWITCH  0

//DISPLAY
/////////////////////////////////////////////////////////////////////////////////////////////////////////
#define TFT_DC 2
#define TFT_CS 15
#define BRIGHT_MAX 100          //%
#define BRIGHT_MIN_DEFAULT 15  //%
#define BRIGHT_STEP_FADE_IN 20 //%
#define BRIGHT_STEP_FADE_OUT 1

//SLOT
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define SLOT_THERMOSTAT        0
#define SLOT_TEMPERATURE        5     // This is the memory slot used for the execution of the logic in network_address1
#define SLOT_HUMIDITY        7     // This is the memory slot used for the execution of the logic
#define SLOT_BRIGHT_DISPLAY        9



//PIN
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// **** Define here the right pin for your ESP module ****
#define RELE                  5
#define BACKLED  16


//TIMER DISPLAY
#define TIMER_DISPLAY_SETPOINT 3000

//TIMER NTP
const int timeZone = 2;     // Central European Time
#define MEMSET_NTP_START 300

#define SERIAL_OUT Serial

//FONT
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#define FONT_BIG ucg_font_inb63_mn
//#define FONT_BIG ucg_font_inb46_mr
//#define FONT_BIG_MIN_50_PERCENT ucg_font_inb33_mr
#define FONT_BIG ucg_font_inb53_mn
#define FONT_BIG_MIN_50_PERCENT ucg_font_inb24_mr

#define FONT_BIG_SCALE2x2             1     //1 Scale - 0 Don't Scale
#define FONT_SMALL ucg_font_inb16_mr
#define FONT_SMALL_CENTIGRAD ucg_font_helvB10_hr
#define FONT_SMALLEST ucg_font_4x6_mf
#define FONT_SPLASH_SCREEN ucg_font_inb21_mr

#define FONT_SHIFT_POSITION_TO_SX_CENTIGRAD 5

