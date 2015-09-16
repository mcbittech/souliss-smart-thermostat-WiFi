//ENCODER
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include "t_constants.h"
#include <Souliss_SmartT_ILI9341.h>
#include <Souliss_SmartT_ILI9341_GFX_Library.h>

void display_print_setpoint(Souliss_SmartT_ILI9341 tft, float setpoint) {
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(11);
  tft.setCursor(5, 10);
  tft.print(setpoint,1);
  tft.setTextSize(4);
  tft.print("C");
  tft.setTextSize(2);
  tft.println("o");
  tft.setTextSize(4);
}


