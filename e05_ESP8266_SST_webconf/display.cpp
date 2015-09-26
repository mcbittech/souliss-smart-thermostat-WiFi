//ENCODER
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include "t_constants.h"
#include "language.h"
#include "ntp.h"

#include "Ucglib.h"

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


long lastClickTime = 0;  // the last time the output pin was toggled
//return 1 for timeout
boolean timerDisplay_setpoint() {
  if ((millis() - lastClickTime) > TIMER_DISPLAY_SETPOINT) {
    //lastClickTime = millis();
    return 1;
  } else {
    return 0;
  }
}

void timerDisplay_setpoint_Tick() {
  lastClickTime = millis();
}



//Stampa soltanto il setpoint grande al centro del display
void display_print_setpoint(Ucglib_ILI9341_18x240x320_HWSPI ucg, float setpoint) {

  ucg.setColor(102, 255, 0);    // Verde Chiaro

  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  ucg.setFont(ucg_font_inb53_mr);
  ucg.setScale2x2();
  ucg.setFontPosCenter();
  ucg.setPrintPos(ucg.getWidth() / 2 - 80, ucg.getHeight() / 2 - ucg.getFontAscent() / 2);

  ucg.print(setpoint, 1);

  // ucg.undoScale();
  // ucg.setPrintPos(280, 90);
  ucg.setFont(ucg_font_inb21_mr);
  ucg.print("°");
}

boolean flag_onetime_HomeScreen = false;
//compone la pagina dedicata al setpoint
void display_setpointPage(Ucglib_ILI9341_18x240x320_HWSPI ucg, float setpoint, float temp, float hum) {
  //TICK TIMER
  timerDisplay_setpoint_Tick();

  flag_onetime_HomeScreen = false;
  display_print_setpoint(ucg, setpoint);


  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  ucg.setFont(ucg_font_inb16_mr);

  ucg.setColor(0, 255, 255, 255);    // Bianco
  ucg.setFontPosBottom();
  ucg.setPrintPos(5, ucg.getHeight() - 5);
  ucg.setColor(111, 0, 255);    // Blu Elettrico
  ucg.print(HUM_TEXT);
  ucg.print(hum, 1);
  ucg.print("%");

  char* s;
  int i = strlen(TEMP_TEXT) + 5; //5 "00.0 "
  char charVal[i];
  strcpy(charVal, TEMP_TEXT);
  strcat(charVal, "00.00");

  ucg.setColor(0, 255, 255, 255);    // Bianco
  ucg.setPrintPos(ucg.getWidth() - ucg.getStrWidth(charVal) - 5, ucg.getHeight() - 5);
  ucg.print(TEMP_TEXT);
  ucg.print(temp, 1);
  ucg.print("°");
}

void display_print_splash_waiting_need_configuration(Ucglib_ILI9341_18x240x320_HWSPI ucg) {

  ucg.setColor(0, 255, 255, 255);    // Bianco
  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  ucg.setFont(ucg_font_inb21_mr);
  ucg.setPrintPos(4, 28);

  ucg.println(SPLASH_NEED_CONFIGURATION);
  ucg.print("IP ");
  ucg.print(WiFi.softAPIP());
}

void display_print_splash_waiting_connection_gateway(Ucglib_ILI9341_18x240x320_HWSPI ucg) {

  ucg.setColor(0, 255, 255, 255);    // Bianco
  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  ucg.setFont(ucg_font_inb21_mr);
  ucg.setPrintPos(4, 28);
  ucg.println(SPLASH_GW_LINE1);
  ucg.println(SPLASH_GW_LINE2);
  ucg.print("IP ");
  ucg.print(WiFi.localIP());
}

void display_print_splash_waiting_connection_peer(Ucglib_ILI9341_18x240x320_HWSPI ucg) {

  ucg.setColor(0, 255, 255, 255);    // Bianco
  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  ucg.setFont(ucg_font_inb21_mr);
  ucg.setPrintPos(4, 28);
  ucg.println(SPLASH_PEER_LINE1);
  ucg.setPrintPos(4, 58);
  ucg.println(SPLASH_PEER_LINE2);
  ucg.setPrintPos(4, 88);
  ucg.print("IP ");
  ucg.print(WiFi.localIP());
}

void display_print_B3(Ucglib_ILI9341_18x240x320_HWSPI ucg, String text, float temp) {

  ucg.setPrintPos(20, 220);
  ucg.setColor(102, 255, 0);    // Verde Chiaro
  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  ucg.setFont(ucg_font_inb16_mr);
  ucg.print(text);
  ucg.print(temp, 1);
}

void display_print_DateTime(Ucglib_ILI9341_18x240x320_HWSPI ucg, String text) {
  ucg.print(text);
}

time_t prevDisplay = 0; // when the digital clock was displayed
String sPrevDisplay;
//Stampa l'orologio. La zona B1 è quella in alto a sinistra
void display_print_B1(Ucglib_ILI9341_18x240x320_HWSPI ucg) {
  //NTP
  String dateAndTime = "";
  if (now() != prevDisplay) { //update the display only if time has changed
    prevDisplay = now();
    ucg.setColor(0, 255, 255, 255);    // Bianco
    dateAndTime = digitalClockDisplay();
    ucg.setFontPosTop();
    ucg.setPrintPos(5, 5);
    ucg.setColor(0, 255, 255, 255);    // Bianco
    ucg.setFontMode(UCG_FONT_MODE_SOLID);
    ucg.setFont(ucg_font_inb16_mr);
    display_print_DateTime(ucg, dateAndTime);
  }
}


float temp_prec = 0;
float setpoint_prec = 0;
void display_HomeScreen(Ucglib_ILI9341_18x240x320_HWSPI ucg, float temp, float setpoint) {

  //la funzione display_print_B1 aggiorna soltanto se l'orario è cambiato
  display_print_B1(ucg);

  //uso flag_onetime per visualizzare almeno una volta la schermata, anche in assenza di variazione di temperatura
  //flag_onetime_HomeScreen è rimessa a false display_setpointPage
  if (!flag_onetime_HomeScreen || arrotonda(temp) != arrotonda(temp_prec) || (arrotonda(setpoint) != arrotonda(setpoint_prec))) {
    ucg.clearScreen();
    ucg.setColor(0, 255, 255, 255);    // Bianco

    ucg.setFontMode(UCG_FONT_MODE_SOLID);
 
    ucg.setFont(ucg_font_inb53_mr);
    ucg.setScale2x2();
    ucg.setFontPosCenter();
    ucg.setPrintPos(ucg.getWidth() / 2 - 80, ucg.getHeight() / 2 - ucg.getFontAscent() / 2);
    // ucg.setScale2x2();

    ucg.print(temp, 1);
    //ucg.undoScale();
    //   ucg.setFont(ucg_font_inb16_mr);
    ucg.print("°");

    temp_prec = temp;
    setpoint_prec = setpoint;
    flag_onetime_HomeScreen = true;
    display_print_B3(ucg, SETPOINT_TEXT, setpoint);
    //     display_print_B1(ucg);
  }
}






