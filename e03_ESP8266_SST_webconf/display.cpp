//ENCODER
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include "t_constants.h"
#include "language.h"
#include <ESP8266WiFi.h>

#include <Souliss_SmartT_ILI9341.h>
#include <Souliss_SmartT_ILI9341_GFX_Library.h>
// Color definitions
// ILI9341_BLACK
// ILI9341_NAVY
// ILI9341_DARKGREEN
// ILI9341_DARKCYAN
// ILI9341_MAROON
// ILI9341_PURPLE
// ILI9341_OLIVE
// ILI9341_LIGHTGREY
// ILI9341_DARKGREY
// ILI9341_BLUE
// ILI9341_GREEN
// ILI9341_CYAN
// ILI9341_RED
// ILI9341_MAGENTA
// ILI9341_YELLOW
// ILI9341_WHITE
// ILI9341_ORANGE
// ILI9341_GREENYELLOW
// ILI9341_PINK
float arrotonda(const float v)
{
  float vX10 = v * 10;
  //Serial.print("vX10: "); Serial.println(vX10);

  int vInt = (int) vX10;
  //Serial.print("vInt: "); Serial.println(vInt);

  float diff = abs(vX10 - vInt);
  //Serial.print("diff: "); Serial.println(diff);
  if (diff < 0.5) {
    return (float) vInt / 10;
  } else {
    return (float)(vInt + 1) / 10;
  }
}


void display_print_setpoint(Souliss_SmartT_ILI9341 tft, float setpoint) {
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);

  tft.setTextSize(10);
  tft.setCursor(4, 30);

  tft.setTextColor(ILI9341_DARKGREEN);
  tft.print(setpoint, 1);
  tft.setTextSize(4);
  tft.print("C");
  tft.setTextSize(2);
  tft.println("o");
  tft.setTextSize(5);
  tft.setCursor(4, 110);
  tft.setTextColor(ILI9341_WHITE);
  tft.print(SETPOINT_TEXT_SETPOINT_SCREEN);
}

boolean flag_onetime_HomeScreen=false;
void display_setpointPage(Souliss_SmartT_ILI9341 tft, float setpoint, float temp) {
  //TICK TIMER
    //timerDisplay_setpoint_Tick();  
  
  flag_onetime_HomeScreen=false;
  display_print_setpoint(tft, setpoint);

  tft.setCursor(4, 210);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.print(TEMP_TEXT);
  tft.print(temp,1);

}

void display_print_splash_waiting_need_configuration(Souliss_SmartT_ILI9341 tft) {
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(2, 10);
  tft.println(SPLASH_NEED_CONFIGURATION);
  tft.print("IP ");
  tft.print(WiFi.softAPIP());
}

void display_print_splash_waiting_connection_gateway(Souliss_SmartT_ILI9341 tft) {
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(2, 10);
  tft.println(SPLASH_GW_LINE1);
  tft.println(SPLASH_GW_LINE2);
  tft.print("IP ");
  tft.print(WiFi.localIP());
}

void display_print_splash_waiting_connection_peer(Souliss_SmartT_ILI9341 tft) {
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(2, 10);
  tft.println(SPLASH_PEER_LINE1);
  tft.println(SPLASH_PEER_LINE2);
  tft.print("IP ");
  tft.print(WiFi.localIP());
}
 
void display_print_B3(Souliss_SmartT_ILI9341 tft, String text, float temp) {
  tft.setCursor(20, 200);
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(2);
  tft.print(text);
  tft.print(temp,1);
}

float temp_prec=0;
void display_HomeScreen(Souliss_SmartT_ILI9341 tft, float temp, float setpoint) {
  //uso flag_onetime per visualizzare almeno una volta la schermata, anche in assenza di variazione di temperatura
  //flag_onetime_HomeScreen è rimessa a false display_setpointPage
 if(!flag_onetime_HomeScreen || arrotonda(temp)!=arrotonda(temp_prec)){
 tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);

  tft.setTextSize(10);
  tft.setCursor(15, 80);

  tft.setTextColor(ILI9341_WHITE);
  tft.print(temp, 1);
  tft.setTextSize(4);
  tft.print("C");
  tft.setTextSize(2);
  tft.println("o");
  temp_prec=temp;
  flag_onetime_HomeScreen=true;
  display_print_B3(tft, SETPOINT_TEXT, setpoint);
 }
}


long lastClickTime = 0;  // the last time the output pin was toggled
//return 1 for timeout
boolean timerDisplay_setpoint() {
    Serial.print("lastClickTime: ");Serial.println(lastClickTime);
     Serial.print("(millis() - lastClickTime): ");Serial.println(millis() - lastClickTime);
  if ((millis() - lastClickTime) > TIMER_DISPLAY_SETPOINT) {
    Serial.println("Return to home screen");
     lastClickTime = millis();
    return 1;
  } else {
   
    return 0;
  }
}

void timerDisplay_setpoint_Tick() {
   lastClickTime = millis();
}



