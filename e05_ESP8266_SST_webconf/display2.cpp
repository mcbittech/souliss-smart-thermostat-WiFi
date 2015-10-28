#include <Arduino.h>
#include "constants.h"
#include "language.h"
#include "ntp.h"

#include "Ucglib.h"


float arrotonda2(const float v)
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

int dopovirgola2(const float v)
{
  float vX10 = v * 1;
  //Serial.print("vX10: "); Serial.println(vX10);
  int vInt = (int) vX10;
  //Serial.print("vInt: "); Serial.println(vInt);
  int result;
  float diff = abs(vX10 - vInt);
  //Serial.print("diff: "); Serial.println(diff);
  return result = diff * 10;
}


void display_layout2_Setpoint(Ucglib_ILI9341_18x240x320_HWSPI ucg, float setpoint) {
  ucg.setColor(0, 255, 255, 255);    // Bianco
  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  ucg.setPrintPos(25, 52);
  ucg.setFont(ucg_font_inb21_mr);
  ucg.print("Sp"); ucg.print(setpoint, 1);
  ucg.setFont(ucg_font_profont11_mr);
  ucg.setPrintPos(135, 36);
  ucg.print("o");
}

String s2PrevDisplay;
time_t prev2Display = 0; // when the digital clock was displayed
void display_layout2_print_datetime(Ucglib_ILI9341_18x240x320_HWSPI ucg) {

  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  ucg.setFont(FONT_SMALL);
  ucg.setFontPosTop();
  //NTP
  String dateAndTime = "";
  if (now() != prev2Display) { //update the display only if time has changed
    prev2Display = now();
    //NTP
    ////////////////////////////////////////////////////////////////////////////
    String Time = "";
    String Date = "";
    Time = digitalClockDisplay_simple();
    Date = digitalDataDisplay();
    ucg.setFont(ucg_font_inr19_mf);
    ucg.setColor(0, 255, 255, 255);       // Bianco
    ucg.setPrintPos(160, 5);
    ucg.print(Date);
    ucg.setFont(ucg_font_inb21_mr);
    ucg.setPrintPos(228, 52);
    ucg.print(Time);
  }
}

void display_layout2_print_circle_green(Ucglib_ILI9341_18x240x320_HWSPI ucg) {
  ucg.setColor(102, 255, 0);    // Verde Chiaro
  ucg.drawCircle(85, 120, 110, UCG_DRAW_ALL);
  ucg.drawCircle(85, 119, 110, UCG_DRAW_ALL);
  ucg.drawCircle(85, 120, 111, UCG_DRAW_ALL);
  ucg.drawCircle(85, 119, 111, UCG_DRAW_ALL);
  ucg.drawCircle(85, 120, 112, UCG_DRAW_ALL);
  ucg.drawCircle(85, 119, 112, UCG_DRAW_ALL);
  ucg.drawCircle(85, 120, 113, UCG_DRAW_ALL);
  ucg.drawCircle(85, 119, 113, UCG_DRAW_ALL);
  ucg.drawCircle(85, 120, 114, UCG_DRAW_ALL);
  ucg.drawCircle(85, 119, 114, UCG_DRAW_ALL);
  ucg.drawCircle(85, 120, 115, UCG_DRAW_ALL);
  ucg.drawCircle(85, 119, 115, UCG_DRAW_ALL);
  ucg.drawCircle(85, 120, 116, UCG_DRAW_ALL);
  ucg.drawCircle(85, 119, 116, UCG_DRAW_ALL);
  ucg.drawCircle(85, 120, 117, UCG_DRAW_ALL);
  ucg.drawCircle(85, 119, 117, UCG_DRAW_ALL);
  ucg.drawCircle(85, 120, 118, UCG_DRAW_ALL);
  ucg.drawCircle(85, 119, 118, UCG_DRAW_ALL);
  ucg.drawCircle(85, 120, 119, UCG_DRAW_ALL);
  ucg.drawCircle(85, 119, 119, UCG_DRAW_ALL);
}

void display_layout2_print_circle_white(Ucglib_ILI9341_18x240x320_HWSPI ucg) {
  ucg.setColor(255, 255, 255);    // Bianco
  ucg.drawCircle(85, 120, 119, UCG_DRAW_ALL);
  ucg.drawCircle(85, 119, 119, UCG_DRAW_ALL);
  ucg.drawCircle(85, 120, 118, UCG_DRAW_ALL);
  ucg.drawCircle(85, 119, 118, UCG_DRAW_ALL);
  ucg.drawCircle(85, 120, 117, UCG_DRAW_ALL);
  ucg.drawCircle(85, 119, 117, UCG_DRAW_ALL);
  ucg.drawCircle(85, 120, 116, UCG_DRAW_ALL);
  ucg.drawCircle(85, 119, 116, UCG_DRAW_ALL);
  ucg.drawCircle(85, 120, 115, UCG_DRAW_ALL);
  ucg.drawCircle(85, 119, 115, UCG_DRAW_ALL);
  ucg.drawCircle(85, 120, 114, UCG_DRAW_ALL);
  ucg.drawCircle(85, 119, 114, UCG_DRAW_ALL);
  ucg.drawCircle(85, 120, 113, UCG_DRAW_ALL);
  ucg.drawCircle(85, 119, 113, UCG_DRAW_ALL);
  ucg.drawCircle(85, 120, 112, UCG_DRAW_ALL);
  ucg.drawCircle(85, 119, 112, UCG_DRAW_ALL);
  ucg.drawCircle(85, 120, 111, UCG_DRAW_ALL);
  ucg.drawCircle(85, 119, 111, UCG_DRAW_ALL);
  ucg.drawCircle(85, 120, 110, UCG_DRAW_ALL);
  ucg.drawCircle(85, 119, 110, UCG_DRAW_ALL);
}

void display_layout2_print_circle_black(Ucglib_ILI9341_18x240x320_HWSPI ucg) {
  ucg.setColor(0, 0, 0);    // Nero
  ucg.drawCircle(85, 120, 119, UCG_DRAW_ALL);
  ucg.drawCircle(85, 119, 119, UCG_DRAW_ALL);
  ucg.drawCircle(85, 120, 118, UCG_DRAW_ALL);
  ucg.drawCircle(85, 119, 118, UCG_DRAW_ALL);
  ucg.drawCircle(85, 120, 117, UCG_DRAW_ALL);
  ucg.drawCircle(85, 119, 117, UCG_DRAW_ALL);
  ucg.drawCircle(85, 120, 116, UCG_DRAW_ALL);
  ucg.drawCircle(85, 119, 116, UCG_DRAW_ALL);
  ucg.drawCircle(85, 120, 115, UCG_DRAW_ALL);
  ucg.drawCircle(85, 119, 115, UCG_DRAW_ALL);
  ucg.drawCircle(85, 120, 114, UCG_DRAW_ALL);
  ucg.drawCircle(85, 119, 114, UCG_DRAW_ALL);
  ucg.drawCircle(85, 120, 113, UCG_DRAW_ALL);
  ucg.drawCircle(85, 119, 113, UCG_DRAW_ALL);
  ucg.drawCircle(85, 120, 112, UCG_DRAW_ALL);
  ucg.drawCircle(85, 119, 112, UCG_DRAW_ALL);
  ucg.drawCircle(85, 120, 111, UCG_DRAW_ALL);
  ucg.drawCircle(85, 119, 111, UCG_DRAW_ALL);
  ucg.drawCircle(85, 120, 110, UCG_DRAW_ALL);
  ucg.drawCircle(85, 119, 110, UCG_DRAW_ALL);
}


boolean flag_onetime2_HomeScreen = false;
float temp2_prec = 0;
float setpoint2_prec = 0;
void display_layout2_HomeScreen(Ucglib_ILI9341_18x240x320_HWSPI ucg, float temperature, float humidity, float setpoint) {
  //uso flag_onetime per visualizzare almeno una volta la schermata, anche in assenza di variazione di temperatura
  //flag_onetime_HomeScreen è rimessa a false display_layout1_setpointPage
  if (arrotonda2(temperature) != arrotonda2(temp2_prec) || (arrotonda2(setpoint) != arrotonda2(setpoint2_prec))) {
    if (!flag_onetime2_HomeScreen) {
      ucg.clearScreen();
    }
    //HOMESCREEN
    int temp = (int) temperature;
    int diff = dopovirgola2(temperature);
    //Temperatura
    //ucg.setColor(111, 0, 255);         // Blu Elettrico
    //ucg.setColor(0, 255, 255, 255);    // Bianco
    ucg.setColor(102, 255, 0);           // Verde Chiaro
    ucg.setFontMode(UCG_FONT_MODE_SOLID);
    ucg.setPrintPos(-4, 80);
    ucg.setScale2x2();
    ucg.setFont(ucg_font_inb46_mr);
    ucg.print(temp);
    ucg.undoScale();
    ucg.setFont(ucg_font_inb46_mr);
    ucg.setPrintPos(147, 160);
    ucg.print(diff);
    ucg.drawDisc(143, 156, 3, UCG_DRAW_ALL);
    ucg.drawDisc(187, 116, 3, UCG_DRAW_ALL);


    //Umidità
    ucg.setColor(30, 144, 255);    // Blu Dodger
    ucg.setFontMode(UCG_FONT_MODE_SOLID);
    ucg.setPrintPos(24, 209);
    ucg.setFont(ucg_font_inb21_mr);
    ucg.print("Hr"); ucg.print(humidity, 1);
    ucg.setFont(ucg_font_9x18_mf);
    ucg.setPrintPos(135, 209);
    ucg.print("%");
    //ucg.setFont(ucg_font_profont11_mr);
    //ucg.setPrintPos(60,190);
    ucg.undoScale();
    //ucg.print("UMIDITA'");

    

    temp2_prec = temp;
    setpoint2_prec = setpoint;
    flag_onetime2_HomeScreen = true;
  }
}


float deltaT = 0;
float pretemperature = 0;
void calcoloAndamento(Ucglib_ILI9341_18x240x320_HWSPI ucg, float temperature){
  //CALCOLO ANDAMENTO
    ///////////////////////////////////////////////////////////////////////////
    deltaT = temperature - pretemperature;
    Serial.print("DELTAT "); Serial.println(deltaT, DEC);
    if (temperature > pretemperature && deltaT || 0) {
      ucg.setColor(255, 0, 0);              // Rosso
      ucg.drawTriangle(0, 0, 0, 31, 10, 22);
      ucg.setColor(0, 0, 0);                //Nero
      ucg.drawTriangle(0, 240, 0, 209, 10, 218);
    } else if (deltaT == 0) {
      ucg.setColor(0, 0, 0);                //Nero
      ucg.drawTriangle(0, 240, 0, 209, 10, 218);
      ucg.setColor(0, 0, 0);                //Nero
      ucg.drawTriangle(0, 0, 0, 31, 10, 22);
    }
    else {
      ucg.setColor(65, 105, 225);           // Blu Reale
      ucg.drawTriangle(0, 240, 0, 209, 10, 218);
      ucg.setColor(0, 0, 0);                //Nero
      ucg.drawTriangle(0, 0, 0, 31, 10, 22);
    }
    pretemperature = temperature;
    ///////////////////////////////////////////////////////////////////////////

}



