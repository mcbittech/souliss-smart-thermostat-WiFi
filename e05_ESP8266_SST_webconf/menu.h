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
void setSystem(boolean bVal);
boolean getSystem();
boolean getCrono();
boolean getCronoLearn();

boolean getChanged();
void setChanged();
void resetChanged();

void printMenu(Ucglib_ILI9341_18x240x320_HWSPI);
