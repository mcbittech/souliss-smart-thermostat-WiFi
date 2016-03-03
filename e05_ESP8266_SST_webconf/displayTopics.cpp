#include <Arduino.h>
#include "constants.h"
#include "display.h"
#include "language.h"
#include "ntp.h"
#include "Ucglib.h"
#include "menu.h"
#include "preferences.h"
int ibaseH=0;

int getWidthCenterW(Ucglib_ILI9341_18x240x320_HWSPI *ucg){
	return ucg->getWidth() / 2 ;
}
int getHeightCenterW(Ucglib_ILI9341_18x240x320_HWSPI *ucg){
	return ucg->getHeight() / 2 ;
}



void display_print_C1(Ucglib_ILI9341_18x240x320_HWSPI ucg, String text, float temp){
	setBianco(&ucg);
	//calcola ingombro testo
String str = text + "00.0";
  const char * c = str.c_str();
	ibaseH = ucg.getHeight() / 2 - getHeightCenterW(&ucg) + ucg.getFontAscent() / 2;
		ucg.setPrintPos(getWidthCenterW(&ucg) - ((getWidthCenterW(&ucg) + ucg.getStrWidth(c)) / 2) , ibaseH);
		ucg.print(text);
		ucg.print(temp);
}

void display_print_C2(Ucglib_ILI9341_18x240x320_HWSPI ucg, String text, float temp){
	setBianco(&ucg);
}

void display_print_C3(Ucglib_ILI9341_18x240x320_HWSPI ucg, String text, float temp){
	setBianco(&ucg);
}

void display_print_C4(Ucglib_ILI9341_18x240x320_HWSPI ucg, String text, float temp){
	setBianco(&ucg);
	
}
