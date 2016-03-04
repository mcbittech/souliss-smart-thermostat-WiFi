#include <Arduino.h>
#include "constants.h"
#include "display.h"
#include "language.h"
#include "ntp.h"
#include "Ucglib.h"
#include "menu.h"
#include "preferences.h"
int ibaseH = 0;
boolean bTopicsPageEnabled=false;

int getWidthCenterW(Ucglib_ILI9341_18x240x320_HWSPI *ucg) {
  return ucg->getWidth() / 2 ;
}
int getHeightCenterW(Ucglib_ILI9341_18x240x320_HWSPI *ucg) {
  return ucg->getHeight() / 2 ;
}

void display_print_C1(Ucglib_ILI9341_18x240x320_HWSPI ucg, float fVal) {
  ucg.setFont(FONT_BIG);

  ucg.setFontPosBaseline();
   setBianco(&ucg);
  //calcola ingombro testo
  String str = "    "; //4 cifre
  const char *c = str.c_str();

  ibaseH = getHeightCenterW(&ucg)  - ((getHeightCenterW(&ucg) - ucg.getFontAscent()) / 2);
  ucg.setPrintPos(getWidthCenterW(&ucg) - ((getWidthCenterW(&ucg) + ucg.getStrWidth(c)) / 2) , ibaseH);
  SERIAL_OUT.println("fVal: "); SERIAL_OUT.println(fVal);
  String sValToPrint = "";
  sValToPrint = (int) fVal;
  SERIAL_OUT.println("sValToPrint: "); SERIAL_OUT.println(sValToPrint);
  ucg.clearScreen();
  ucg.print(sValToPrint);ucg.print(C1_AREA_UNITY);
}

void display_print_C2(Ucglib_ILI9341_18x240x320_HWSPI ucg, String text, float temp) {
  setBianco(&ucg);
}

void display_print_C3(Ucglib_ILI9341_18x240x320_HWSPI ucg, String text, float temp) {
  setBianco(&ucg);
}

void display_print_C4(Ucglib_ILI9341_18x240x320_HWSPI ucg, String text, float temp) {
  setBianco(&ucg);
}

boolean getTopicsPageEnabled(){
  return bTopicsPageEnabled;
}

void setTopicsPageEnabled(){
  bTopicsPageEnabled=true;
}

void resetTopicsPageEnabled(){
  bTopicsPageEnabled=false;
}

