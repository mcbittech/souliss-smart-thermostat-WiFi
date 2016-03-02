#include <Arduino.h>
#include "constants.h"
#include "preferences.h"
#include <MenuSystem.h>
#include "language.h"
#include "Ucglib.h"
#include "crono.h"
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

Menu muMenu_Crono(MENU_TEXT_CRONO_ENABLE);
MenuItem muMenu_mi_Crono_OFF(MENU_TEXT_OFF);
MenuItem muMenu_mi_Crono_ON(MENU_TEXT_ON);
MenuItem muMenu_mi_Crono_LEARN(MENU_TEXT_LEARN);

Menu muMenu_SetCrono(MENU_TEXT_CRONO_SET);
MenuItem muMenu_mi_ProgCrono(MENU_TEXT_CRONO_PROGRAM);

Menu muMenu_System(MENU_TEXT_SYSTEM);
MenuItem muMenu_mi_System_ON(MENU_TEXT_ON);
MenuItem muMenu_mi_System_OFF(MENU_TEXT_OFF);

Menu muMenu_Layouts(MENU_TEXT_LAYOUTS);
MenuItem muMenu_mi_Layouts_1(MENU_TEXT_LAYOUT_1);
MenuItem muMenu_mi_Layouts_2(MENU_TEXT_LAYOUT_2);

MenuSystem* getMenu() {
  return &ms;
}
boolean getUIChanged() {
  return bUIChanged;
}
boolean getSystemChanged() {
  return bSystemChanged;
}
void setChanged() {
  bUIChanged = true;
  bSystemChanged = true;
}

void resetUIChanged() {
  bUIChanged = false;
}
void resetSystemChanged() {
  bSystemChanged = false;
}

boolean getLocalSystem() {
  return bSystem;
}

void setSystem(boolean bVal) {
  SERIAL_OUT.print("Actual System State: "); SERIAL_OUT.println(getLocalSystem());
  if (getLocalSystem() != bVal) {
    bSystem = bVal;
    SERIAL_OUT.print("System setted to "); SERIAL_OUT.println(bVal);
    setChanged();
  }

}
void on_item_MenuExit_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("Exit Selected");
  bMenuEnabled = false;
}

void on_itemBack_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("Back Selected");
  ms.back();
}

void on_item_perc100_selected(MenuItem* p_menu_item)
{
  iDisplayBright = 100;
  save_eeprom_byte(2, iDisplayBright);
}

void on_item_perc80_selected(MenuItem* p_menu_item)
{
  iDisplayBright = 80;
  save_eeprom_byte(2, iDisplayBright);
}

void on_item_perc60_selected(MenuItem* p_menu_item)
{
  iDisplayBright = 60;
  save_eeprom_byte(2, iDisplayBright);

}

void on_item_perc50_selected(MenuItem* p_menu_item)
{
  iDisplayBright = 50;
  save_eeprom_byte(2, iDisplayBright);
}

void on_item_perc30_selected(MenuItem* p_menu_item)
{
  iDisplayBright = 30;
  save_eeprom_byte(2, iDisplayBright);
}

void on_item_perc5_selected(MenuItem* p_menu_item)
{
  iDisplayBright = 5;
  save_eeprom_byte(2, iDisplayBright);
}

void on_item_perc2_selected(MenuItem* p_menu_item)
{
  iDisplayBright = 2;
  save_eeprom_byte(2, iDisplayBright);
}

void on_item_clockON_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_clockON_selected");
  bClock = true;
  save_eeprom_byte(3, bClock);
}
void on_item_clockOFF_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_clockOFF_selected");
  bClock = false;
  save_eeprom_byte(3, bClock);
}

void on_item_Timezone0_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_Timezone0_selected");
  tZone = 0;
  save_eeprom_byte(9, tZone);
}

void on_item_Timezone1_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_Timezone1_selected");
  tZone = 1;
  save_eeprom_byte(9, tZone);
}
void on_item_Timezone2_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_Timezone2_selected");
  tZone = 2;
  save_eeprom_byte(9, tZone);
}
void on_item_Timezone3_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_Timezone3_selected");
  tZone = 3;
  save_eeprom_byte(9, tZone);
}
void on_item_Timezone4_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_Timezone4_selected");
  tZone = 4;
  save_eeprom_byte(9, tZone);
}

void on_item_cronoON_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_cronoON_selected");
  bCrono = true;
  save_eeprom_byte(4, bCrono);
  SERIAL_OUT.print("Variabile bCrono:");
  SERIAL_OUT.println(bCrono);
}
void on_item_cronoOFF_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_cronoOFF_selected");
  bCrono = false;
  save_eeprom_byte(4, bCrono);
  SERIAL_OUT.print("Variabile bCrono:");
  SERIAL_OUT.println(bCrono);
}
void on_item_cronoSET_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_cronoSET_selected");
}

void on_item_ProgCrono_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_ProgCrono_selected");
  bProgCrono = true;
}

void on_item_ProgCrono_deselected()
{
  SERIAL_OUT.println("on_item_ProgCrono_deselected");
  bProgCrono = false;
}

void on_item_cronoLEARN_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_cronoLEARN_selected");
  bCronoLearn = true;
  save_eeprom_byte(5, bCronoLearn);
}

void on_item_systemON_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_systemON_selected");
  setSystem(true);
  save_eeprom_byte(6, bSystem);
}
void on_item_systemOFF_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_systemOFF_selected");
  setSystem(false);
  save_eeprom_byte(6, bSystem);
}


void on_item_layout1_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_layout1_selected");
  bLayout1 = true;
  bLayout2 = false;
  save_eeprom_byte(7, bLayout1);
  save_eeprom_byte(8, bLayout2);
}
void on_item_layout2_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_layout2_selected");
  bLayout1 = false;
  bLayout2 = true;
  save_eeprom_byte(7, bLayout1);
  save_eeprom_byte(8, bLayout2);
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
  
  muMenu.add_menu(&muMenu_Crono);
  muMenu_Crono.add_item(&mm_miBack, &on_itemBack_selected);
  muMenu_Crono.add_item(&muMenu_mi_Crono_ON, &on_item_cronoON_selected);
  muMenu_Crono.add_item(&muMenu_mi_Crono_OFF, &on_item_cronoOFF_selected);
  muMenu_Crono.add_item(&muMenu_mi_Crono_LEARN, &on_item_cronoLEARN_selected);
  muMenu_Crono.add_menu(&muMenu_SetCrono);
  muMenu_SetCrono.add_item(&mm_miBack, &on_itemBack_selected);
  if (bCrono) {
  muMenu.add_item(&muMenu_mi_ProgCrono, &on_item_ProgCrono_selected);
  SERIAL_OUT.println("Aggiungo la voce di menu ProgCrono");   
  }

  muMenu.add_menu(&muMenu_System);
  muMenu_System.add_item(&mm_miBack, &on_itemBack_selected);
  muMenu_System.add_item(&muMenu_mi_System_ON, &on_item_systemON_selected);
  muMenu_System.add_item(&muMenu_mi_System_OFF, &on_item_systemOFF_selected);

  muMenu.add_menu(&muMenu_Layouts);
  muMenu_Layouts.add_item(&mm_miBack, &on_itemBack_selected);
  muMenu_Layouts.add_item(&muMenu_mi_Layouts_1, &on_item_layout1_selected);
  muMenu_Layouts.add_item(&muMenu_mi_Layouts_2, &on_item_layout2_selected);

  ms.set_root_menu(&muMenu);
}

Menu const* prec_cp_menu;
boolean bFlagColour = true;
void printMenu(Ucglib_ILI9341_18x240x320_HWSPI ucg) {
  int x = 2;
  int y = 4;
  int y_step_plus = 5;
  int y_step;

  // Display the menu
  Menu const* cp_menu;
  cp_menu = ms.get_current_menu();
  if (cp_menu != prec_cp_menu) {
    ucg.clearScreen();
    prec_cp_menu = cp_menu;
    bFlagColour = true;
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

  MenuComponent const* cp_menu_sel = cp_menu->get_selected();
  for (int i = 0; i < cp_menu->get_num_menu_components(); ++i)
  {
    MenuComponent const* cp_m_comp = cp_menu->get_menu_component(i);
    y = y + y_step + y_step_plus;
    ucg.setPrintPos(x, y);

    if (cp_menu_sel == cp_m_comp)
    {
      ucg.print("> ");
      ucg.print(cp_m_comp->get_name());
      if (bFlagColour) {
        ucg.print("  *");
        bFlagColour = false;
      }

    }
    else
    {
      ucg.print("  ");
      ucg.print(cp_m_comp->get_name());
    }
  }
}

boolean getMenuEnabled() {
  return bMenuEnabled;
}

void setEnabled(boolean bVal) {
  bMenuEnabled = bVal;
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

void ReadAllSettingsFromEEPROM() {
  //EEPROM
  SERIAL_OUT.println("Read ALL EEPROM value....");
  iDisplayBright=read_eeprom_byte(2);
  bClock=read_eeprom_byte(3);
  bCrono=read_eeprom_byte(4);
  bCronoLearn=read_eeprom_byte(5);
  bSystem=read_eeprom_byte(6);
  bLayout1=read_eeprom_byte(7);
  bLayout2=read_eeprom_byte(8);
  tZone=read_eeprom_byte(9);
}

void ReadAllSettingsFromPreferences(){
  SERIAL_OUT.println("Read ALL Preferences value....");
  iDisplayBright=BRIGHT_MIN_DEFAULT;
  bClock=CLOCK;
  bCrono=CRONO;
  bCronoLearn=CRONOLEARN;
  bSystem=true;
  bLayout1=LAYOUT_LINEAR;
  bLayout2=LAYOUT_CIRCULAR;
  tZone=TIME_ZONE;

  save_eeprom_byte(2, iDisplayBright);
  save_eeprom_byte(3, bClock);
  save_eeprom_byte(4, bCrono);
  save_eeprom_byte(5, bCronoLearn);
  save_eeprom_byte(6, bSystem);
  save_eeprom_byte(7, bLayout1);
  save_eeprom_byte(8, bLayout2);  
  save_eeprom_byte(9, tZone);
  save_eeprom_byte(1, 1);
}

