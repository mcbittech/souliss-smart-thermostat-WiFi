//DISPLAY
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include <Souliss_SmartT_ILI9341.h>
#include <Souliss_SmartT_ILI9341_GFX_Library.h>

void setpointPage(Souliss_SmartT_ILI9341, float, float);

void display_print_setpoint(Souliss_SmartT_ILI9341, float);
void display_B3(Souliss_SmartT_ILI9341);

void display_print_splash_waiting_need_configuration(Souliss_SmartT_ILI9341);
void display_print_splash_waiting_connection_gateway(Souliss_SmartT_ILI9341);
void display_print_splash_waiting_connection_peer(Souliss_SmartT_ILI9341);
