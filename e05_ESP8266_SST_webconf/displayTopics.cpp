#include <Arduino.h>
#include "constants.h"
#include "display.h"
#include "language.h"
#include "ntp.h"
#include "Ucglib.h"
#include "menu.h"
#include "preferences.h"
int ibaseH = 0;
boolean bTopicsPageEnabled = false;
String strVoid = "    "; //4 cifre
int iPortion = 0;
int integerPartNumber;

int getHeightPortion(Ucglib_ILI9341_18x240x320_HWSPI *ucg) {
  return ucg->getHeight() / 3 ;
}
void printNumber(Ucglib_ILI9341_18x240x320_HWSPI ucg, float fVal, String sUnity, String sText) {

  if (fVal == 0) {
    ucg.print("----");
  } else {
    integerPartNumber = (int) fVal;
    if (fVal - integerPartNumber > 0) {
      //se esiste la parte decimale, ne stampa una sola cifra
      ucg.print(arrotonda(fVal), 1);
    } else {
      // omette la parte decimale se è uguale a zero
      ucg.print(integerPartNumber);
    }
  }

  ucg.setFont(FONT_BIG_MIN_50_PERCENT);
  ucg.print(sUnity);
  ucg.print(sText);
}

float fPrecC1;
void display_print_C1(Ucglib_ILI9341_18x240x320_HWSPI ucg, float fVal) {
  C1_COLOR();
  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  ucg.setFont(FONT_BIG);

  ucg.setFontPosBaseline();
  //calcola ingombro testo
  String str = "    "; //4 cifre
  const char *c = str.c_str();
  iPortion = getHeightPortion(&ucg);
  ibaseH = ucg.getHeight()  - iPortion * 2 - iPortion / 2 + ucg.getFontAscent() / 2;
  ucg.setPrintPos(5 , ibaseH);
  //  ucg.clearScreen();

  printNumber(ucg, fVal, C1_AREA_UNITY, C1_AREA_TEXT);
  SERIAL_OUT.print("C1_AREA: "); SERIAL_OUT.print(fVal); SERIAL_OUT.print(C1_AREA_UNITY); SERIAL_OUT.println(C1_AREA_TEXT);
}

float fPrecC2;
void display_print_C2(Ucglib_ILI9341_18x240x320_HWSPI ucg, float fVal) {
  C2_COLOR();
  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  ucg.setFont(FONT_BIG);
  ucg.setFontPosBaseline();
  //calcola ingombro testo
  const char *c = strVoid.c_str();

  iPortion = getHeightPortion(&ucg);
  ibaseH = ucg.getHeight()  - iPortion - iPortion / 2 + ucg.getFontAscent() / 2;
  ucg.setPrintPos(5 , ibaseH);
  //   ucg.clearScreen();

  printNumber(ucg, fVal, C2_AREA_UNITY, C2_AREA_TEXT);

  SERIAL_OUT.print("C2_AREA: "); SERIAL_OUT.print(fVal); SERIAL_OUT.print(C2_AREA_UNITY); SERIAL_OUT.println(C2_AREA_TEXT);
}


float fPrecC3;
void display_print_C3(Ucglib_ILI9341_18x240x320_HWSPI ucg, float fVal) {
  C3_COLOR();
  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  ucg.setFont(FONT_BIG);

  ucg.setFontPosBaseline();
  //calcola ingombro testo
  const char *c = strVoid.c_str();

  iPortion = getHeightPortion(&ucg);
  ibaseH = ucg.getHeight()  - iPortion / 2 + ucg.getFontAscent() / 2;
  ucg.setPrintPos(5 , ibaseH);
  //   ucg.clearScreen();

  printNumber(ucg, fVal, C3_AREA_UNITY, C3_AREA_TEXT);

  SERIAL_OUT.print("C3_AREA: "); SERIAL_OUT.print(fVal); SERIAL_OUT.print(C3_AREA_UNITY); SERIAL_OUT.println(C3_AREA_TEXT);
}

float fC1_Value, fC2_Value, fC3_Value;
float fPrecC1_Value, fPrecC2_Value, fPrecC3_Value;

void displayTopics(Ucglib_ILI9341_18x240x320_HWSPI ucg, float fC1_Value, float fC2_Value, float fC3_Value) {
  //se uno dei valori è diverso dal precedente allora ripulisco lo schermo
  SERIAL_OUT.println("displayTopics");
  //fa in modo che sia fatto un cleanscreen del setpoint, al prossimo cambio pagina
  setOnetime_clear_SetpointPage();
  if ( getUIChanged() || fPrecC1_Value != fC1_Value || fPrecC2_Value != fC2_Value ||  fPrecC3_Value != fC3_Value) {
    ucg.clearScreen();
    resetUIChanged();
  }
  display_print_C1(ucg, fC1_Value);
  display_print_C2(ucg, fC2_Value);
  display_print_C3(ucg, fC3_Value);


  fPrecC1_Value = fC1_Value;
  fPrecC2_Value = fC2_Value;
  fPrecC3_Value = fC3_Value;
}

boolean getTopicsPageEnabled() {
  return bTopicsPageEnabled;
}

void setTopicsPageEnabled() {
  bTopicsPageEnabled = true;
}

void resetTopicsPageEnabled() {
  bTopicsPageEnabled = false;
}

