#include <Arduino.h>
#include <MenuSystem.h>


void initMenu();
MenuSystem* getMenu();
boolean getEnabled();
void setEnabled(boolean);
boolean getLayout1();
boolean getLayout2();
int getDisplayBright();
boolean getClock();
boolean getSystem();
boolean getCrono();
boolean getCronoLearn();

void printMenu(Ucglib_ILI9341_18x240x320_HWSPI);
