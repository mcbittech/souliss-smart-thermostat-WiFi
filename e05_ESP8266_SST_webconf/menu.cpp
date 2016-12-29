#include <Arduino.h>
#include "constants.h"
#include "preferences.h"
#include <MenuSystem.h>
#include "language.h"
#include "Ucglib.h"
#include "crono.h"
#include "ntp.h"
#include "read_save.h"

boolean bMenuEnabled;
int iDisplayBright;
boolean bClock;
boolean bSystem;
boolean bCrono;
boolean bProgCrono;
boolean bCronoLearn;
boolean bLayout1;
boolean bLayout2;
boolean bUIChanged;
boolean bSystemChanged;
int tZone;
boolean bDayLightSavingTime;
boolean bDoSystemReset=false;

// Menu variables
MenuSystem ms;

MenuItem mm_miBack(MENU_TEXT_BACK);
MenuItem mm_miExit(MENU_TEXT_BACK);
Menu muMenu(MENU_TEXT_MENU);

Menu muMenu_mi_Bright(MENU_TEXT_BRIGHT);
MenuItem muMenu_mi_Bright_100("100%");
MenuItem muMenu_mi_Bright_80("80%");
MenuItem muMenu_mi_Bright_60("60%");
MenuItem muMenu_mi_Bright_50("50%");
MenuItem muMenu_mi_Bright_30("30%");
MenuItem muMenu_mi_Bright_10("10%");
MenuItem muMenu_mi_Bright_5("5%");
MenuItem muMenu_mi_Bright_2("2%");

Menu muMenu_Clock(MENU_TEXT_CLOCK);
MenuItem muMenu_mi_Clock_ON(MENU_TEXT_ON);
MenuItem muMenu_mi_Clock_OFF(MENU_TEXT_OFF);

Menu muMenu_SetTimezone(MENU_TEXT_TIMEZONE_SET);
MenuItem muMenu_mi_Timezone_0(MENU_TIMEZONE_0);
MenuItem muMenu_mi_Timezone_1(MENU_TIMEZONE_1);
MenuItem muMenu_mi_Timezone_2(MENU_TIMEZONE_2);
MenuItem muMenu_mi_Timezone_3(MENU_TIMEZONE_3);
MenuItem muMenu_mi_Timezone_4(MENU_TIMEZONE_4);

Menu muMenu_SetDaylightSavingTime(MENU_TEXT_DAYLIGHTSAVINGTIME_SET);
MenuItem muMenu_mi_DaylightSavingTime_ON(MENU_DAYLIGHTSAVINGTIME_ON);
MenuItem muMenu_mi_DaylightSavingTime_OFF(MENU_DAYLIGHTSAVINGTIME_OFF);

Menu muMenu_Crono(MENU_TEXT_CRONO_ENABLE);
MenuItem muMenu_mi_Crono_OFF(MENU_TEXT_OFF);
MenuItem muMenu_mi_Crono_ON(MENU_TEXT_ON);
MenuItem muMenu_mi_Crono_LEARN(MENU_TEXT_LEARN);

MenuItem muMenu_mi_ProgCrono(MENU_TEXT_CRONO_PROGRAM);

Menu muMenu_SystemEnabled(MENU_TEXT_SYSTEM_ENABLED);
MenuItem muMenu_SystemEnabled_ON(MENU_TEXT_ON);
MenuItem muMenu_SystemEnabled_OFF(MENU_TEXT_OFF);

Menu muMenu_Layouts(MENU_TEXT_LAYOUTS);
MenuItem muMenu_mi_Layouts_1(MENU_TEXT_LAYOUT_1);
MenuItem muMenu_mi_Layouts_2(MENU_TEXT_LAYOUT_2);

Menu muMenu_System(MENU_TEXT_SYSTEM);
MenuItem muMenu_mi_System_1(MENU_TEXT_SYSTEM_1);

MenuSystem* getMenu() {
  return &ms;
}

boolean getMenuEnabled() {
  return bMenuEnabled;
}

void setMenuEnabled() {
  bMenuEnabled = true;
}

void resetMenuEnabled() {
  bMenuEnabled = false;
}

boolean getUIChanged() {
  return bUIChanged;
}

boolean getSystemChanged() {
  return bSystemChanged;
}

void setSystemChanged() {
  #ifdef DEBUG_DEV
    Serial.println("setSystemChanged()");
  #endif
  bSystemChanged = true;
}

void setUIChanged() {
  #ifdef DEBUG_DEV
    Serial.println("setUIChanged()");
  #endif
  bUIChanged = true;
}

void resetUIChanged() {
  #ifdef DEBUG_DEV
    Serial.println("resetUIChanged()");
  #endif
  bUIChanged = false;
}

void resetSystemChanged() {
  #ifdef DEBUG_DEV
    Serial.println("resetSystemChanged()");
  #endif
  bSystemChanged = false;
}

boolean getLocalSystem() {
  return bSystem;
}

void setSystem(boolean bVal) {
  #ifdef DEBUG_DEV
    Serial.print("Actual System State: "); Serial.println(getLocalSystem());
  #endif
  if (getLocalSystem() != bVal) {
    bSystem = bVal;
    #ifdef DEBUG_DEV
      Serial.print("System setted to "); Serial.println(bVal);
    #endif
    setSystemChanged();
  }
}

void on_item_MenuExit_selected(MenuItem* p_menu_item){ 
  #ifdef DEBUG_DEV
    Serial.println("Exit Selected");
  #endif
  resetMenuEnabled();
}

void on_itemBack_selected(MenuItem* p_menu_item){ 
  #ifdef DEBUG_DEV
    Serial.println("Back Selected");
  #endif
  ms.back();
}

void on_item_perc100_selected(MenuItem* p_menu_item){
  iDisplayBright = 100;
  save_spiffs_prefs(iDisplayBright, bClock, tZone, bDayLightSavingTime, bCrono, bCronoLearn, bSystem, bLayout1, bLayout2);
}

void on_item_perc80_selected(MenuItem* p_menu_item){
  iDisplayBright = 80;
  save_spiffs_prefs(iDisplayBright, bClock, tZone, bDayLightSavingTime, bCrono, bCronoLearn, bSystem, bLayout1, bLayout2);
}

void on_item_perc60_selected(MenuItem* p_menu_item){
  iDisplayBright = 60;
  save_spiffs_prefs(iDisplayBright, bClock, tZone, bDayLightSavingTime, bCrono, bCronoLearn, bSystem, bLayout1, bLayout2);
}

void on_item_perc50_selected(MenuItem* p_menu_item){
  iDisplayBright = 50;
  save_spiffs_prefs(iDisplayBright, bClock, tZone, bDayLightSavingTime, bCrono, bCronoLearn, bSystem, bLayout1, bLayout2);
}

void on_item_perc30_selected(MenuItem* p_menu_item){
  iDisplayBright = 30;
  save_spiffs_prefs(iDisplayBright, bClock, tZone, bDayLightSavingTime, bCrono, bCronoLearn, bSystem, bLayout1, bLayout2);
}

void on_item_perc5_selected(MenuItem* p_menu_item){
  iDisplayBright = 5;
  save_spiffs_prefs(iDisplayBright, bClock, tZone, bDayLightSavingTime, bCrono, bCronoLearn, bSystem, bLayout1, bLayout2);
}

void on_item_perc2_selected(MenuItem* p_menu_item){
  iDisplayBright = 2;
  save_spiffs_prefs(iDisplayBright, bClock, tZone, bDayLightSavingTime, bCrono, bCronoLearn, bSystem, bLayout1, bLayout2);
}

void on_item_clockON_selected(MenuItem* p_menu_item){ 
  #ifdef DEBUG_DEV
    Serial.println("on_item_clockON_selected");
  #endif
  bClock = true;
  save_spiffs_prefs(iDisplayBright, bClock, tZone, bDayLightSavingTime, bCrono, bCronoLearn, bSystem, bLayout1, bLayout2);
}

void on_item_clockOFF_selected(MenuItem* p_menu_item){ 
  #ifdef DEBUG_DEV
    Serial.println("on_item_clockOFF_selected");
  #endif
  bClock = false;
  save_spiffs_prefs(iDisplayBright, bClock, tZone, bDayLightSavingTime, bCrono, bCronoLearn, bSystem, bLayout1, bLayout2);
}

void on_item_Timezone0_selected(MenuItem* p_menu_item){ 
  #ifdef DEBUG_DEV
    Serial.println("on_item_Timezone0_selected");
  #endif
  tZone = 0;
  save_spiffs_prefs(iDisplayBright, bClock, tZone, bDayLightSavingTime, bCrono, bCronoLearn, bSystem, bLayout1, bLayout2);
  initNTP();
}

void on_item_Timezone1_selected(MenuItem* p_menu_item){ 
  #ifdef DEBUG_DEV
    Serial.println("on_item_Timezone1_selected");
  #endif
  tZone = 1;
  save_spiffs_prefs(iDisplayBright, bClock, tZone, bDayLightSavingTime, bCrono, bCronoLearn, bSystem, bLayout1, bLayout2);
  initNTP();
}

void on_item_Timezone2_selected(MenuItem* p_menu_item){ 
  #ifdef DEBUG_DEV
    Serial.println("on_item_Timezone2_selected");
  #endif
  tZone = 2;
  save_spiffs_prefs(iDisplayBright, bClock, tZone, bDayLightSavingTime, bCrono, bCronoLearn, bSystem, bLayout1, bLayout2);
  initNTP();
}

void on_item_Timezone3_selected(MenuItem* p_menu_item){ 
  #ifdef DEBUG_DEV
    Serial.println("on_item_Timezone3_selected");
  #endif
  tZone = 3;
  save_spiffs_prefs(iDisplayBright, bClock, tZone, bDayLightSavingTime, bCrono, bCronoLearn, bSystem, bLayout1, bLayout2);
  initNTP();
}

void on_item_Timezone4_selected(MenuItem* p_menu_item){ 
  #ifdef DEBUG_DEV
    Serial.println("on_item_Timezone4_selected");
  #endif
  tZone = 4;
  save_spiffs_prefs(iDisplayBright, bClock, tZone, bDayLightSavingTime, bCrono, bCronoLearn, bSystem, bLayout1, bLayout2);
  initNTP();
}

void on_item_DayLightSavingTimeON_selected(MenuItem* p_menu_item){ 
  #ifdef DEBUG_DEV
    Serial.println("on_item_DayLightSavingTimeON");
  #endif
  bDayLightSavingTime = true;
  save_spiffs_prefs(iDisplayBright, bClock, tZone, bDayLightSavingTime, bCrono, bCronoLearn, bSystem, bLayout1, bLayout2);
  initNTP();
}

void on_item_DaylightSavingTimeOFF_selected(MenuItem* p_menu_item){ 
  #ifdef DEBUG_DEV
    Serial.println("on_item_DaylightSavingTimeOFF");
  #endif
  bDayLightSavingTime = false;
  save_spiffs_prefs(iDisplayBright, bClock, tZone, bDayLightSavingTime, bCrono, bCronoLearn, bSystem, bLayout1, bLayout2);
  initNTP();
}


void on_item_cronoON_selected(MenuItem* p_menu_item){ 
  #ifdef DEBUG_DEV
    Serial.println("on_item_cronoON_selected");
  #endif
  bCrono = true;
  #ifdef DEBUG_DEV
    Serial.print("Variabile bCrono:");Serial.println(bCrono);
  #endif
  save_spiffs_prefs(iDisplayBright, bClock, tZone, bDayLightSavingTime, bCrono, bCronoLearn, bSystem, bLayout1, bLayout2);
}

void on_item_cronoOFF_selected(MenuItem* p_menu_item){ 
  #ifdef DEBUG_DEV
    Serial.println("on_item_cronoOFF_selected");
  #endif
  bCrono = false;
  #ifdef DEBUG_DEV
    Serial.print("Variabile bCrono:");Serial.println(bCrono);
  #endif
  save_spiffs_prefs(iDisplayBright, bClock, tZone, bDayLightSavingTime, bCrono, bCronoLearn, bSystem, bLayout1, bLayout2);
}

void on_item_cronoSET_selected(MenuItem* p_menu_item){ 
  #ifdef DEBUG_DEV
    Serial.println("on_item_cronoSET_selected");
  #endif
}

void on_item_ProgCrono_selected(MenuItem* p_menu_item){ 
  #ifdef DEBUG_DEV
    Serial.println("on_item_ProgCrono_selected");
  #endif
  bProgCrono = true;
  resetMenuEnabled();
}

void on_item_ProgCrono_deselected(){ 
  #ifdef DEBUG_DEV
    Serial.println("on_item_ProgCrono_deselected");
  #endif
  bProgCrono = false;
}

void on_item_cronoLEARN_selected(MenuItem* p_menu_item){ 
  #ifdef DEBUG_DEV
    Serial.println("on_item_cronoLEARN_selected");
  #endif
  bCronoLearn = true;
  save_spiffs_prefs(iDisplayBright, bClock, tZone, bDayLightSavingTime, bCrono, bCronoLearn, bSystem, bLayout1, bLayout2);
}

void on_item_systemEnabledON_selected(MenuItem* p_menu_item){ 
  #ifdef DEBUG_DEV
    Serial.println("on_item_systemEnabledON_selected");
  #endif
  setSystem(true);
  save_spiffs_prefs(iDisplayBright, bClock, tZone, bDayLightSavingTime, bCrono, bCronoLearn, bSystem, bLayout1, bLayout2);
}
void on_item_systemEnabledOFF_selected(MenuItem* p_menu_item){ 
  #ifdef DEBUG_DEV
    Serial.println("on_item_systemEnabledOFF_selected");
  #endif
  setSystem(false);
  save_spiffs_prefs(iDisplayBright, bClock, tZone, bDayLightSavingTime, bCrono, bCronoLearn, bSystem, bLayout1, bLayout2);
}


void on_item_layout1_selected(MenuItem* p_menu_item){ 
  #ifdef DEBUG_DEV
    Serial.println("on_item_layout1_selected");
  #endif
  bLayout1 = true;
  bLayout2 = false;
  save_spiffs_prefs(iDisplayBright, bClock, tZone, bDayLightSavingTime, bCrono, bCronoLearn, bSystem, bLayout1, bLayout2);
}
void on_item_layout2_selected(MenuItem* p_menu_item){ 
  #ifdef DEBUG_DEV
    Serial.println("on_item_layout2_selected");
  #endif
  bLayout1 = false;
  bLayout2 = true;
  save_spiffs_prefs(iDisplayBright, bClock, tZone, bDayLightSavingTime, bCrono, bCronoLearn, bSystem, bLayout1, bLayout2);
}

void on_item_system1_selected(MenuItem* p_menu_item)
{
  bDoSystemReset=true;

}


void initMenu() {

  // Menu setup
  muMenu.add_item(&mm_miExit, &on_item_MenuExit_selected);
  muMenu.add_menu(&muMenu_mi_Bright);
  muMenu_mi_Bright.add_item(&mm_miBack, &on_itemBack_selected);
  muMenu_mi_Bright.add_item(&muMenu_mi_Bright_100, &on_item_perc100_selected);
  muMenu_mi_Bright.add_item(&muMenu_mi_Bright_80, &on_item_perc80_selected);
  muMenu_mi_Bright.add_item(&muMenu_mi_Bright_60, &on_item_perc60_selected);
  muMenu_mi_Bright.add_item(&muMenu_mi_Bright_50, &on_item_perc50_selected);
  muMenu_mi_Bright.add_item(&muMenu_mi_Bright_30, &on_item_perc30_selected);
  muMenu_mi_Bright.add_item(&muMenu_mi_Bright_5, &on_item_perc5_selected);
  muMenu_mi_Bright.add_item(&muMenu_mi_Bright_2, &on_item_perc2_selected);


  muMenu.add_menu(&muMenu_Clock);
  muMenu_Clock.add_item(&mm_miBack, &on_itemBack_selected);
  muMenu_Clock.add_item(&muMenu_mi_Clock_ON, &on_item_clockON_selected);
  muMenu_Clock.add_item(&muMenu_mi_Clock_OFF, &on_item_clockOFF_selected);
  muMenu_Clock.add_menu(&muMenu_SetTimezone);
  muMenu_SetTimezone.add_item(&mm_miBack, &on_itemBack_selected);
  muMenu_SetTimezone.add_item(&muMenu_mi_Timezone_0, &on_item_Timezone0_selected);
  muMenu_SetTimezone.add_item(&muMenu_mi_Timezone_1, &on_item_Timezone1_selected);
  muMenu_SetTimezone.add_item(&muMenu_mi_Timezone_2, &on_item_Timezone2_selected);
  muMenu_SetTimezone.add_item(&muMenu_mi_Timezone_3, &on_item_Timezone3_selected);
  muMenu_SetTimezone.add_item(&muMenu_mi_Timezone_4, &on_item_Timezone4_selected);
  muMenu_Clock.add_menu(&muMenu_SetDaylightSavingTime);
  muMenu_SetDaylightSavingTime.add_item(&muMenu_mi_DaylightSavingTime_ON, &on_item_DayLightSavingTimeON_selected);
  muMenu_SetDaylightSavingTime.add_item(&muMenu_mi_DaylightSavingTime_OFF, &on_item_DaylightSavingTimeOFF_selected);

  muMenu.add_menu(&muMenu_Crono);
  muMenu_Crono.add_item(&mm_miBack, &on_itemBack_selected);
  muMenu_Crono.add_item(&muMenu_mi_Crono_ON, &on_item_cronoON_selected);
  muMenu_Crono.add_item(&muMenu_mi_Crono_OFF, &on_item_cronoOFF_selected);
  muMenu_Crono.add_item(&muMenu_mi_Crono_LEARN, &on_item_cronoLEARN_selected);
  // if (bCrono) {
  muMenu.add_item(&muMenu_mi_ProgCrono, &on_item_ProgCrono_selected);
  // }

  muMenu.add_menu(&muMenu_SystemEnabled);
  muMenu_SystemEnabled.add_item(&mm_miBack, &on_itemBack_selected);
  muMenu_SystemEnabled.add_item(&muMenu_SystemEnabled_ON, &on_item_systemEnabledON_selected);
  muMenu_SystemEnabled.add_item(&muMenu_SystemEnabled_OFF, &on_item_systemEnabledOFF_selected);

  muMenu.add_menu(&muMenu_Layouts);
  muMenu_Layouts.add_item(&mm_miBack, &on_itemBack_selected);
  muMenu_Layouts.add_item(&muMenu_mi_Layouts_1, &on_item_layout1_selected);
  muMenu_Layouts.add_item(&muMenu_mi_Layouts_2, &on_item_layout2_selected);

  muMenu.add_menu(&muMenu_System);
  muMenu_System.add_item(&mm_miBack, &on_itemBack_selected);
  muMenu_System.add_item(&muMenu_mi_System_1, &on_item_system1_selected);

  ms.set_root_menu(&muMenu);
}

Menu const* prec_cp_menu;
Menu const* cp_menu;
MenuComponent const* cp_menu_sel;
MenuComponent const* cp_m_comp;
boolean bFlagColour = true;
boolean bFirstPrint = true;
int x, y, y_step_plus , y_step;

void printMenuBody(Ucglib_ILI9341_18x240x320_HWSPI ucg, boolean bFlagFirstPrint) {
  x = 2;
  y = 4;
  y_step_plus = 5;
  y_step;

  bFirstPrint = false;
  // Display the menu
  cp_menu = ms.get_current_menu();
  if (cp_menu != prec_cp_menu) {
    ucg.clearScreen();
    prec_cp_menu = cp_menu;
    bFlagColour = true;
    ucg.setColor(0, 255, 255, 255);    // Bianco
    ucg.setFontMode(UCG_FONT_MODE_SOLID);
  }


  ucg.setColor(0, 255, 255, 255);    // Bianco
  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  ucg.setFont(FONT_SMALL);

  //Current menu name
  y_step = ucg.getFontAscent();
  y = y + y_step;
  ucg.setPrintPos(x, y);
  ucg.print(cp_menu->get_name());

  //One line space
  y = y + y_step;

  cp_menu_sel = cp_menu->get_selected();
  for (int i = 0; i < cp_menu->get_num_menu_components(); ++i)
  {
    cp_m_comp = cp_menu->get_menu_component(i);
    y = y + y_step + y_step_plus;
    ucg.setPrintPos(x, y);

    if (cp_menu_sel == cp_m_comp)
    {
      ucg.print("> ");
      if (bFlagFirstPrint) ucg.print(cp_m_comp->get_name());
      if (bFlagColour) {
        ucg.print("  *");
        bFlagColour = false;
      }
    }
    else
    {
      ucg.print("  ");
      if (bFlagFirstPrint) ucg.print(cp_m_comp->get_name());
    }
  }
}

void printMenuMove(Ucglib_ILI9341_18x240x320_HWSPI ucg) {
  printMenuBody( ucg, false);
}
void printMenu(Ucglib_ILI9341_18x240x320_HWSPI ucg) {
  printMenuBody( ucg, true);
}

boolean getLayout1() {
  return bLayout1;
}
boolean getLayout2() {
  return bLayout2;
}

int getDisplayBright() {
  return iDisplayBright;
}

boolean getCrono() {
  return bCrono;
}

boolean getProgCrono() {
  return bProgCrono;
}
boolean getClock() {
  return bClock;
}

boolean getCronoLearn() {
  return bCronoLearn;
}
int getTimeZone() {
  return tZone;
}

int getDaylightSavingTime() {
  return bDayLightSavingTime;
}

boolean getDoSystemReset() {
  return bDoSystemReset;
}

void ReadAllSettingsFromPreferences() {
  #ifdef DEBUG_DEV
    Serial.println("Read ALL Preferences value....");
  #endif
  iDisplayBright = BRIGHT_MIN_DEFAULT;
  bClock = CLOCK;
  bCrono = CRONO;
  bCronoLearn = CRONOLEARN;
  bSystem = SYSTEM_START_ON;
  bLayout1 = LAYOUT_LINEAR;
  bLayout2 = LAYOUT_CIRCULAR;
  tZone = TIME_ZONE;
  bDayLightSavingTime = DAYLIGHTSAVINGTIME;

  save_spiffs_prefs(iDisplayBright, bClock, tZone, bDayLightSavingTime, bCrono, bCronoLearn, bSystem, bLayout1, bLayout2);
}
void ReadAllSettingsFromSPIFFS() {
  //SPIFFS
  #ifdef DEBUG_DEV
    Serial.println(" ");
    Serial.print("Read All Settings From SPIFFS.... ");
  #endif
  iDisplayBright = read_spiffs_prefs("Luminosita");
  bClock = read_spiffs_prefs("Orologio");
  bCrono = read_spiffs_prefs("Crono");
  bCronoLearn = read_spiffs_prefs("CronoLearn");
  bSystem = read_spiffs_prefs("Dispositivo");
  bLayout1 = read_spiffs_prefs("Layout1");
  bLayout2 = read_spiffs_prefs("Layout2");
  tZone = read_spiffs_prefs("Tzone");
  bDayLightSavingTime = read_spiffs_prefs("DayLightSavingTime");
}
