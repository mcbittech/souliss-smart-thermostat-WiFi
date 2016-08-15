#include <Arduino.h>
#include "constants.h"
#include "language.h"
#include "ntp.h"
#include "Ucglib.h"
#include "menu.h"
#include "preferences.h"

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


void setBianco(Ucglib_ILI9341_18x240x320_HWSPI *ucg) {
  ucg->setColor(0, 255, 255, 255);    // Bianco
}
void setVerde(Ucglib_ILI9341_18x240x320_HWSPI *ucg) {
  ucg->setColor(102, 255, 0);    // Verde Chiaro
}
void setBlu(Ucglib_ILI9341_18x240x320_HWSPI *ucg) {
  ucg->setColor(111, 0, 255);    // Blu Elettrico
}

void setRosso(Ucglib_ILI9341_18x240x320_HWSPI *ucg) {
  ucg->setColor(233, 4, 4);    // Rosso
}

int startW = 0;
int baseH = 0;
int vW_pos_before_point, vW_pos_after_point, vW_pos_grade, baseH_Grade;
String sTempToPrint = "";



void display_layout1_printBigChar(Ucglib_ILI9341_18x240x320_HWSPI ucg, float fValTemp) {
  ucg.setFont(FONT_BIG);
#if(FONT_BIG_SCALE2x2)
  ucg.setScale2x2();
#endif
  ucg.setFontPosBaseline();

  //calcolo ingombro testo
  String str = "00";
  const char *c = str.c_str();
  int vW = ucg.getStrWidth(c);

  str = "0";
  c = str.c_str();
  vW_pos_before_point = vW - ucg.getStrWidth(c) / 8; //arretra di un sesto dello spazio di un carattere, per avvicinare il punto
  ucg.setFont(FONT_BIG_MIN_50_PERCENT);
  str = ".";
  c = str.c_str();
  vW += ucg.getStrWidth(c);
  vW_pos_after_point = vW_pos_before_point + ucg.getStrWidth(c) - ucg.getStrWidth(c) / 8; //aggiunge lo spazio del punto meno un sesto
  str = "0";
  c = str.c_str();
  vW += ucg.getStrWidth(c);

  ucg.setFont(FONT_SMALL_CENTIGRAD);
  str = "o";
  c = str.c_str();
  vW += ucg.getStrWidth(c) / 2; //aggiunge metà dello spazio di un carattere. Il ° verrà parzialmente sovrapposto alla vifra decimale

  ucg.setFont(FONT_BIG);
  startW = (ucg.getWidth() - vW) / 2 ;
  baseH = ucg.getHeight() / 2 + ucg.getFontAscent() / 2;
  baseH_Grade = baseH - ucg.getFontAscent() + ucg.getFontAscent() / 6;
  ucg.setPrintPos(startW, baseH );
  sTempToPrint = (int) fValTemp;
  if (((int) fValTemp) <= -10) {
    sTempToPrint = "-- ";
    ucg.print(sTempToPrint);
    SERIAL_OUT.print("sTempToPrint: "); SERIAL_OUT.println(sTempToPrint);
  } else if (((int) fValTemp) >= 100) {
    sTempToPrint = "++ ";
    ucg.print(sTempToPrint);
    SERIAL_OUT.print("sTempToPrint: "); SERIAL_OUT.println(sTempToPrint);
  } else {

    if ((((int) fValTemp) < 10) && ((int) fValTemp > 0)) {
      sTempToPrint = " " + sTempToPrint;
      SERIAL_OUT.print("sTempToPrint: "); SERIAL_OUT.println(sTempToPrint);
    }

    ucg.print(sTempToPrint);
    ucg.setFont(FONT_BIG_MIN_50_PERCENT);
    ucg.setPrintPos(startW + vW_pos_before_point, baseH);
    int diff = dopovigola(fValTemp);
    ucg.print(".");
    ucg.setPrintPos(startW + vW_pos_after_point, baseH);
    ucg.print(diff);

    //print °

    ucg.setFont(FONT_SMALL_CENTIGRAD);
    vW_pos_grade = startW + vW_pos_after_point;   // - FONT_SHIFT_POSITION_TO_SX_CENTIGRAD ;
    ucg.setPrintPos(vW_pos_grade, baseH_Grade);
    ucg.print("o");
  }
#if(FONT_BIG_SCALE2x2)
  ucg.undoScale();
#endif

}

//Stampa soltanto il setpoint grande al centro del display
void display_layout1_print_setpoint(Ucglib_ILI9341_18x240x320_HWSPI ucg, float setpoint) {
  SERIAL_OUT.println("display_print_setpoint");
  ucg.setColor(102, 255, 0);    // Verde Chiaro
  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  display_layout1_printBigChar(ucg, setpoint);
}

void display_layout1_print_B3(Ucglib_ILI9341_18x240x320_HWSPI ucg, String text, float temp) {
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

void display_layout1_print_B3_ChildLock(Ucglib_ILI9341_18x240x320_HWSPI ucg, String text) {
  SERIAL_OUT.println("display_print_B4 [ChildClocked]");
  SERIAL_OUT.println("display_print_B3");
  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  ucg.setFont(FONT_SMALL);
  ucg.setFontPosBaseline();
  String str = text;
  const char * c = str.c_str();
  setRosso(&ucg);
  ucg.setPrintPos(ucg.getWidth() - ucg.getStrWidth(c) - 5, ucg.getHeight() - 5);
  ucg.print(text);
}

void display_layout1_print_B4_Hum(Ucglib_ILI9341_18x240x320_HWSPI ucg, String text, float temp) {
  SERIAL_OUT.println("display_print_B4 [Humidity]");
  SERIAL_OUT.println("display_print_B4 [Humidity]");
  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  ucg.setFont(FONT_SMALL);
  ucg.setFontPosBaseline();
  ucg.setPrintPos(5, ucg.getHeight() - 5);
  setBlu(&ucg);
  ucg.print(text);
  ucg.print(temp, 1);
  ucg.print("%");
}

void display_layout1_print_B4_SystemOff(Ucglib_ILI9341_18x240x320_HWSPI ucg, String text) {
  SERIAL_OUT.println("display_print_B4 [SystemOff]");
  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  ucg.setFont(FONT_SMALL);
  ucg.setFontPosBaseline();
  setRosso(&ucg);
  ucg.setPrintPos(5, ucg.getHeight() - 5);
  ucg.print(text);
}


boolean flag_onetime_HomeScreen = false;
boolean flag_onetime_clear_SetpointPage = false;
void setOnetime_clear_SetpointPage() {
  flag_onetime_clear_SetpointPage = false;
}

//compone la pagina dedicata al setpoint
void display_layout1_setpointPage(Ucglib_ILI9341_18x240x320_HWSPI ucg, float setpoint, float temp, float hum, boolean bSystemOn) {
  SERIAL_OUT.println("display_setpointPage");

  if (!flag_onetime_clear_SetpointPage) {
    //viene ripristinata in homepage
    flag_onetime_clear_SetpointPage = true;
    ucg.clearScreen();
  }
  flag_onetime_HomeScreen = false;

  display_layout1_print_setpoint(ucg, setpoint);
  display_layout1_print_B3(ucg, TEMP_TEXT, temp) ;

  if (bSystemOn)
    display_layout1_print_B4_Hum(ucg, HUM_TEXT, hum) ;
  else
    display_layout1_print_B4_SystemOff(ucg, SYSTEM_OFF_TEXT) ;
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
  ucg.println(SPLASH_NEED_CONF_LINE1);
  ucg.setPrintPos(4, 58);
  ucg.println(SPLASH_NEED_CONF_LINE2);
  ucg.setPrintPos(4, 88);
  ucg.println(SPLASH_NEED_CONF_LINE3);
  ucg.setPrintPos(4, 118);
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
  ucg.setPrintPos(4, 58);
  ucg.println(SPLASH_GW_LINE2);
  ucg.setPrintPos(4, 88);
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

void display_print_splash_connection_to_home_wifi(Ucglib_ILI9341_18x240x320_HWSPI ucg) {
  SERIAL_OUT.println("display_print_splash_connection_to_home_wifi");
  setBianco(&ucg);    // Bianco
  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  ucg.setFont(FONT_SPLASH_SCREEN);
  ucg.setPrintPos(4, 28);
  ucg.println(SPLASH_SSID_LINE1);
  ucg.setPrintPos(4, 58);
  ucg.print("WiFi SSID: ");
  ucg.setPrintPos(4, 88);
  ucg.print(WiFi_SSID);
  ucg.setPrintPos(4, 118);
  ucg.print("IP ");
  ucg.print(WiFi.localIP());
}

void display_layout1_print_DateTime(Ucglib_ILI9341_18x240x320_HWSPI ucg, String text) {
  if (getClock())
    ucg.print(text);
}

time_t prevDisplay = 0; // when the digital clock was displayed
String sPrevDisplay;
//Stampa l'orologio. La zona B1 è quella in alto a sinistra
void display_layout1_print_B1_datetime(Ucglib_ILI9341_18x240x320_HWSPI ucg) {

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
    display_layout1_print_DateTime(ucg, dateAndTime);
  }
}


float temp_prec = 0;
float setpoint_prec = 0;

void display_layout1_HomeScreen(Ucglib_ILI9341_18x240x320_HWSPI ucg, float temp, float hum, float setpoint, boolean bSystemOn, boolean bChildLock) {
  //ripristina la variabile bool. Viene fatto il clear della pagina ogni volta soltato una volta
  setOnetime_clear_SetpointPage();
  //uso flag_onetime per visualizzare almeno una volta la schermata, anche in assenza di variazione di temperatura
  //flag_onetime_HomeScreen è rimessa a false display_layout1_setpointPage
  //flag_initScreen è impostato true all'uscita dal menu
  if ( getUIChanged() || arrotonda(temp) != arrotonda(temp_prec) || (arrotonda(setpoint) != arrotonda(setpoint_prec))) {
    if (!flag_onetime_HomeScreen) {
      ucg.clearScreen();
      resetUIChanged();
      flag_onetime_HomeScreen = true;
    }


    ucg.setFontMode(UCG_FONT_MODE_SOLID);

    display_layout1_printBigChar(ucg, temp);

    temp_prec = temp;
    setpoint_prec = setpoint;

    if (!bChildLock) {
      display_layout1_print_B3(ucg, SETPOINT_TEXT, setpoint);
    } else
    {
      display_layout1_print_B3_ChildLock(ucg, CHILDLOCK_TEXT);
    }

    if (bSystemOn) {
      display_layout1_print_B4_Hum(ucg, HUM_TEXT, hum) ;
    }
    else
    {
      display_layout1_print_B4_SystemOff(ucg, SYSTEM_OFF_TEXT);
    }
    resetUIChanged();
  }
  //la funzione display_layout1_print_B1 aggiorna soltanto se l'orario è cambiato
  display_layout1_print_B1_datetime(ucg);
}

void display_layout1_background(Ucglib_ILI9341_18x240x320_HWSPI ucg, float diff) {
  SERIAL_OUT.print("diff:"); SERIAL_OUT.println(diff);
  if (diff > 0) {
    //SFONDO ROSSO
    SERIAL_OUT.println("SFONDO ROSSO");
    ucg.setColor(1, 159, 33, 33); // RED for the background
  } else {
    //SFONDO BLU
    SERIAL_OUT.println("SFONDO BLU");
    ucg.setColor(1, 0, 73, 221); // BLUE for the background
  }
}

void display_layout1_background_black(Ucglib_ILI9341_18x240x320_HWSPI ucg) {
  ucg.setColor(1, 0, 0, 0); // BLACK for the background
}





