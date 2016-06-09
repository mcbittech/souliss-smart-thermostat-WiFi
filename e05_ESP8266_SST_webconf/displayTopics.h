//DISPLAY
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include "Ucglib.h"

void display_print_C1(Ucglib_ILI9341_18x240x320_HWSPI, float);
void display_print_C2(Ucglib_ILI9341_18x240x320_HWSPI, float);
void display_print_C3(Ucglib_ILI9341_18x240x320_HWSPI, float);
void displayTopics(Ucglib_ILI9341_18x240x320_HWSPI, float, float, float);
void displayTopicsPage2(Ucglib_ILI9341_18x240x320_HWSPI, float, float, float);
void displayTopicsHomePageLayout2 (Ucglib_ILI9341_18x240x320_HWSPI, float, float, float, float, float, float);
void printNumber(Ucglib_ILI9341_18x240x320_HWSPI,float, float , String , String );

boolean getTopicsPageEnabled();
void setTopicsPageEnabled();
void resetTopicsPageEnabled();

int getWidthCenterW(Ucglib_ILI9341_18x240x320_HWSPI);
int getHeightCenterW(Ucglib_ILI9341_18x240x320_HWSPI);



