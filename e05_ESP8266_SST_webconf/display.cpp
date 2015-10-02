#include <Arduino.h>
#include "constants.h"
#include "language.h"
#include "ntp.h"

#include "Ucglib.h"

float arrotonda(const float v)
{
  float vX10 = v * 10;
  int vInt = (int) vX10;
  float diff = abs(vX10 - vInt);
  if (diff < 0.5) {
    return (float) vInt / 10;
  } else {
    return (float)(vInt + 1) / 10;
  }
}

int dopovigola(const float v)
{
  float vX10 = v * 1;
  int vInt = (int) vX10;
  int result;
  float diff = abs(vX10 - vInt);
  return result = diff * 10;
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

void printBigChar(Ucglib_ILI9341_18x240x320_HWSPI ucg, float fValTemp) {
  ucg.setFont(FONT_BIG);
#if(FONT_BIG_SCALE2x2)
  ucg.setScale2x2();
#endif
  ucg.setFontPosBaseline();

  //calcolo ingombro testo
  String str = "00";
  const char *c = str.c_str();
  int vW = ucg.getStrWidth(c);
  ucg.setFont(FONT_BIG_MIN_50_PERCENT);
  str = ".0";
  c = str.c_str();
  vW += ucg.getStrWidth(c);
  ucg.setFont(FONT_SMALL_CENTIGRAD);
  str = "0";
  c = str.c_str();
  vW += ucg.getStrWidth(c);

  ucg.setFont(FONT_BIG);
  ucg.setPrintPos(ucg.getWidth() / 2 - vW / 2, ucg.getHeight() / 2 + ucg.getFontAscent() / 2);
  ucg.print((int) fValTemp);

  ucg.setFont(FONT_BIG_MIN_50_PERCENT);
  int diff = dopovigola(fValTemp);
  ucg.print(".");
  ucg.print(diff);

  //calcolo ingombro testo
  ucg.setFont(FONT_BIG);
  str = "00";
  c = str.c_str();
  vW = ucg.getStrWidth(c);
  ucg.setFont(FONT_BIG_MIN_50_PERCENT);
  str = ".0";
  c = str.c_str();
  vW += ucg.getStrWidth(c);

  ucg.setFont(FONT_SMALL_CENTIGRAD);
  int position_For_Ball = ucg.getWidth() / 2  + vW / 2 - FONT_SHIFT_POSITION_TO_SX_CENTIGRAD ;
  ucg.setPrintPos(position_For_Ball, ucg.getHeight() / 2 - ucg.getFontAscent() / 2);
  ucg.print("o");

#if(FONT_BIG_SCALE2x2)
  ucg.undoScale();
#endif

}

//Stampa soltanto il setpoint grande al centro del display
void display_print_setpoint(Ucglib_ILI9341_18x240x320_HWSPI ucg, float setpoint) {
  SERIAL_OUT.println("display_print_setpoint");
  ucg.setColor(102, 255, 0);    // Verde Chiaro
  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  printBigChar(ucg, setpoint);
}

void display_print_B3(Ucglib_ILI9341_18x240x320_HWSPI ucg, String text, float temp) {
  SERIAL_OUT.println("display_print_B3");
  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  ucg.setFont(FONT_SMALL);
  ucg.setFontPosBaseline();
  String str = text + "00.00";
  const char * c = str.c_str();

  ucg.setColor(102, 255, 0);    // Verde Chiaro
  ucg.setPrintPos(ucg.getWidth() - ucg.getStrWidth(c) - 5, ucg.getHeight() - 5);
  ucg.print(text);
  ucg.print(temp, 1);
  ucg.setFont(ucg_font_inb21_mr);
  ucg.print("°");
}

void display_print_B4(Ucglib_ILI9341_18x240x320_HWSPI ucg, String text, float temp) {
  SERIAL_OUT.println("display_print_B4");
  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  ucg.setFont(FONT_SMALL);
  ucg.setFontPosBaseline();

  ucg.setColor(0, 255, 255, 255);    // Bianco
  ucg.setPrintPos(5, ucg.getHeight() - 5);
  ucg.setColor(111, 0, 255);    // Blu Elettrico
  ucg.print(text);
  ucg.print(temp, 1);
  ucg.print("%");
}


boolean flag_onetime_HomeScreen = false;
boolean flag_onetime_clear_SetpointPage = false;
//compone la pagina dedicata al setpoint
void display_setpointPage(Ucglib_ILI9341_18x240x320_HWSPI ucg, float setpoint, float temp, float hum) {
  SERIAL_OUT.println("display_setpointPage");
  //TICK TIMER
  timerDisplay_setpoint_Tick();

  if (!flag_onetime_clear_SetpointPage) {
    //viene ripristinata in homepage
    flag_onetime_clear_SetpointPage = true;
    ucg.clearScreen();
  }


  flag_onetime_HomeScreen = false;

  display_print_setpoint(ucg, setpoint);

  display_print_B3(ucg, TEMP_TEXT, temp) ;
  display_print_B4(ucg, HUM_TEXT, hum) ;
}


void display_print_splash_screen(Ucglib_ILI9341_18x240x320_HWSPI ucg) {
  ucg.clearScreen();
  ucg.setColor(153, 203, 255);    // Celeste
  ucg.setFont(ucg_font_fub35_hr);
  ucg.setPrintPos(50, 100);
  ucg.print("SST WiFi");
  ucg.setFont(ucg_font_fub14_hr);
  ucg.setPrintPos(30, 130);
  ucg.print("Souliss Smart Thermostat");
  ucg.setPrintPos(135, 180);
  ucg.print(VERSION);
  delay(2000);
  ucg.clearScreen();
}

void display_print_splash_waiting_need_configuration(Ucglib_ILI9341_18x240x320_HWSPI ucg) {
  SERIAL_OUT.println("display_print_splash_waiting_need_configuration");
  ucg.setColor(0, 255, 255, 255);    // Bianco
  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  ucg.setFont(FONT_SPLASH_SCREEN);
  ucg.setPrintPos(4, 28);

  ucg.println(SPLASH_NEED_CONFIGURATION);
  ucg.print("IP ");
  ucg.print(WiFi.softAPIP());
}

void display_print_splash_waiting_connection_gateway(Ucglib_ILI9341_18x240x320_HWSPI ucg) {
  SERIAL_OUT.println("display_print_splash_waiting_connection_gateway");
  ucg.setColor(0, 255, 255, 255);    // Bianco
  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  ucg.setFont(FONT_SPLASH_SCREEN);
  ucg.setPrintPos(4, 28);
  ucg.println(SPLASH_GW_LINE1);
  ucg.println(SPLASH_GW_LINE2);
  ucg.print("IP ");
  ucg.print(WiFi.localIP());
}

void display_print_splash_waiting_connection_peer(Ucglib_ILI9341_18x240x320_HWSPI ucg) {
  SERIAL_OUT.println("display_print_splash_waiting_connection_peer");
  ucg.setColor(0, 255, 255, 255);    // Bianco
  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  ucg.setFont(FONT_SPLASH_SCREEN);
  ucg.setPrintPos(4, 28);
  ucg.println(SPLASH_PEER_LINE1);
  ucg.setPrintPos(4, 58);
  ucg.println(SPLASH_PEER_LINE2);
  ucg.setPrintPos(4, 88);
  ucg.print("IP ");
  ucg.print(WiFi.localIP());
}

void display_print_DateTime(Ucglib_ILI9341_18x240x320_HWSPI ucg, String text) {
  ucg.print(text);
}

time_t prevDisplay = 0; // when the digital clock was displayed
String sPrevDisplay;
//Stampa l'orologio. La zona B1 è quella in alto a sinistra
void display_print_B1_datetime(Ucglib_ILI9341_18x240x320_HWSPI ucg) {

  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  ucg.setFont(FONT_SMALL);
  ucg.setFontPosTop();
  //NTP
  String dateAndTime = "";
  if (now() != prevDisplay) { //update the display only if time has changed
    prevDisplay = now();
    ucg.setColor(0, 255, 255, 255);    // Bianco
    dateAndTime = digitalClockDisplay();
    ucg.setPrintPos(5, 5);
    display_print_DateTime(ucg, dateAndTime);
  }
}


float temp_prec = 0;
float setpoint_prec = 0;

void display_HomeScreen(Ucglib_ILI9341_18x240x320_HWSPI ucg, float temp, float hum, float setpoint) {
  //ripristina la variabile bool. Viene fatto il clear della pagina ogni volta soltato una volta
  flag_onetime_clear_SetpointPage = false;
  //uso flag_onetime per visualizzare almeno una volta la schermata, anche in assenza di variazione di temperatura
  //flag_onetime_HomeScreen è rimessa a false display_setpointPage
  if (arrotonda(temp) != arrotonda(temp_prec) || (arrotonda(setpoint) != arrotonda(setpoint_prec))) {
    if (!flag_onetime_HomeScreen) {
      ucg.clearScreen();
    }

    ucg.setColor(0, 255, 255, 255);    // Bianco

    ucg.setFontMode(UCG_FONT_MODE_SOLID);

    printBigChar(ucg, temp);

    temp_prec = temp;
    setpoint_prec = setpoint;
    flag_onetime_HomeScreen = true;
    display_print_B3(ucg, SETPOINT_TEXT, setpoint);
    display_print_B4(ucg, HUM_TEXT, hum) ;
  }

  //la funzione display_print_B1 aggiorna soltanto se l'orario è cambiato
  display_print_B1_datetime(ucg);
}








