//DISPLAY
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include "Ucglib.h"

void display_layout1_setpointPage(Ucglib_ILI9341_18x240x320_HWSPI, float, float, float, boolean);
void display_layout1_HomeScreen(Ucglib_ILI9341_18x240x320_HWSPI, float, float, float, boolean);


void display_layout1_print_setpoint(Ucglib_ILI9341_18x240x320_HWSPI, float);
void display_layout1_print_B3(Ucglib_ILI9341_18x240x320_HWSPI, String , float);
void display_layout1_print_B4_Hum(Ucglib_ILI9341_18x240x320_HWSPI, String , float);
void display_layout1_print_B4_SystemOff(Ucglib_ILI9341_18x240x320_HWSPI, String);
void display_layout1_print_B1_datetime(Ucglib_ILI9341_18x240x320_HWSPI);
void display_layout1_print_DateTime(Ucglib_ILI9341_18x240x320_HWSPI, String);
void display_layout1_setFont_Zone_B3_B4(Ucglib_ILI9341_18x240x320_HWSPI);

void display_print_splash_waiting_need_configuration(Ucglib_ILI9341_18x240x320_HWSPI);
void display_print_splash_waiting_connection_gateway(Ucglib_ILI9341_18x240x320_HWSPI);
void display_print_splash_waiting_connection_peer(Ucglib_ILI9341_18x240x320_HWSPI);
void display_print_splash_connection_to_home_wifi(Ucglib_ILI9341_18x240x320_HWSPI);

void display_print_splash_screen(Ucglib_ILI9341_18x240x320_HWSPI);
void display_layout1_printBigChar();
void display_layout1_background(Ucglib_ILI9341_18x240x320_HWSPI, float);
void display_layout1_background_black(Ucglib_ILI9341_18x240x320_HWSPI);

void setBlu(Ucglib_ILI9341_18x240x320_HWSPI *);
void setBianco(Ucglib_ILI9341_18x240x320_HWSPI *);
void setVerde(Ucglib_ILI9341_18x240x320_HWSPI *);
void setRosso(Ucglib_ILI9341_18x240x320_HWSPI *);

boolean timerDisplay_setpoint();//return 1 for timeout
void timerDisplay_setpoint_Tick();
float arrotonda(const float);


