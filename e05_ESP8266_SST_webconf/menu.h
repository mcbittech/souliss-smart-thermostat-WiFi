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
boolean getCronoSet();
boolean getProgCrono();
boolean getCronoLearn();

boolean getFlag_initScreen();
void setFlag_initScreen(boolean);
void on_item_ProgCrono_deselected();
void printMenu(Ucglib_ILI9341_18x240x320_HWSPI);
void ReadAllSettingsFromEEPROM();
