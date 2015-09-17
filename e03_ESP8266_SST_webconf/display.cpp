//ENCODER
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include "t_constants.h"
#include "language.h"
#include <ESP8266WiFi.h>

#include <Souliss_SmartT_ILI9341.h>
#include <Souliss_SmartT_ILI9341_GFX_Library.h>

void display_print_setpoint(Souliss_SmartT_ILI9341 tft, float setpoint) {
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(10);
  tft.setCursor(2, 10);
  tft.print(setpoint,1);
  tft.setTextSize(4);
  tft.print("C");
  tft.setTextSize(2);
  tft.println("o");
  tft.setTextSize(4);
}

void display_print_splash_waiting_need_configuration(Souliss_SmartT_ILI9341 tft){
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(2, 10);
  tft.println(SPLASH_NEED_CONFIGURATION);
  tft.print("IP ");
  tft.print(WiFi.softAPIP());
}

void display_print_splash_waiting_connection_gateway(Souliss_SmartT_ILI9341 tft){
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(2, 10);
  tft.println(SPLASH_GW);
  tft.print("IP ");
  tft.print(WiFi.localIP());
}

void display_print_splash_waiting_connection_peer(Souliss_SmartT_ILI9341 tft){
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(2, 10);
  tft.println(SPLASH_PEER);
  tft.print("IP ");
  tft.print(WiFi.localIP());
}


