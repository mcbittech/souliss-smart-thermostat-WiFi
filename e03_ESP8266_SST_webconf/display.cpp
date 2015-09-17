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

void display_print_setpoint(Souliss_SmartT_ILI9341 tft, float setpoint) {
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  
  tft.setTextSize(10);
  tft.setCursor(4, 30);

  tft.setTextColor(ILI9341_DARKGREEN);
  tft.print(setpoint,1);
  tft.setTextSize(4);
  tft.print("C");
  tft.setTextSize(2);
  tft.println("o");
  tft.setTextSize(4);
  tft.setCursor(4, 110);
  tft.setTextColor(ILI9341_WHITE);
  tft.print(SETPOINT_TEXT);
}

void setpointPage(Souliss_SmartT_ILI9341 tft, float setpoint, float temp){
  display_print_setpoint(tft, setpoint);

        tft.setCursor(4, 210);
        tft.setTextColor(ILI9341_WHITE);  
        tft.setTextSize(2);
        tft.print(TEMP_TEXT);
        tft.print(temp);

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

void display_print_B3 (Souliss_SmartT_ILI9341 tft, float temp) {
        tft.setCursor(20, 200);
        tft.setTextColor(ILI9341_RED);  
        tft.setTextSize(3);
        tft.print(SETPOINT_TEXT);
        tft.print(temp);
}

