#include <Arduino.h>
#include <MenuSystem.h>


void initMenu();
MenuSystem* getMenu();
boolean getMenuEnabled();
void setEnabled(boolean);
boolean getLayout1();
boolean getLayout2();
int getDisplayBright();
boolean getClock();
void setSystem(boolean bVal);
boolean getLocalSystem();
boolean getCrono();
boolean getCronoLearn();

boolean getUIChanged();
boolean getSystemChanged();
void setChanged();

void resetUIChanged();
void resetSystemChanged();

void printMenu(Ucglib_ILI9341_18x240x320_HWSPI);
