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


int getHeightPortion(Ucglib_ILI9341_18x240x320_HWSPI *ucg) {
  return ucg->getHeight() / 3 ;
}

float fPrecC1;
void display_print_C1(Ucglib_ILI9341_18x240x320_HWSPI ucg, float fVal) {
  //if (fPrecC1 != fVal) {
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

  if (fVal == 0) {
    ucg.print("----");
  } else {
    ucg.print((int) fVal);
  }
  ucg.setFont(FONT_BIG_MIN_50_PERCENT);
  ucg.print(C1_AREA_UNITY);
  ucg.print(C1_AREA_TEXT);

  SERIAL_OUT.print("C1_AREA: "); SERIAL_OUT.print((int) fVal); SERIAL_OUT.print(C1_AREA_UNITY); SERIAL_OUT.println(C1_AREA_TEXT);

  //  }
  //  fPrecC1 = fVal;
}

float fPrecC2;
void display_print_C2(Ucglib_ILI9341_18x240x320_HWSPI ucg, float fVal) {
  // if (fPrecC2 != fVal) {
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

  if (fVal == 0) {
    ucg.print("----");
  } else {
    ucg.print((int) fVal);
  }
  ucg.setFont(FONT_BIG_MIN_50_PERCENT);
  ucg.print(C2_AREA_UNITY);
  ucg.print(C2_AREA_TEXT);

  SERIAL_OUT.print("C2_AREA: "); SERIAL_OUT.print((int) fVal); SERIAL_OUT.print(C2_AREA_UNITY); SERIAL_OUT.println(C2_AREA_TEXT);

  // }
  //  fPrecC2 = fVal;
}


float fPrecC3;
void display_print_C3(Ucglib_ILI9341_18x240x320_HWSPI ucg, float fVal) {
  //  if (fPrecC3 != fVal) {
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

  if (fVal == 0) {
    ucg.print("----");
  } else {
    ucg.print((int) fVal);
  }
  ucg.setFont(FONT_BIG_MIN_50_PERCENT);
  ucg.print(C3_AREA_UNITY);
  ucg.print(C3_AREA_TEXT);

  SERIAL_OUT.print("C3_AREA: "); SERIAL_OUT.print((int) fVal); SERIAL_OUT.print(C3_AREA_UNITY); SERIAL_OUT.println(C3_AREA_TEXT);

  //  }
  //  fPrecC3 = fVal;
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

