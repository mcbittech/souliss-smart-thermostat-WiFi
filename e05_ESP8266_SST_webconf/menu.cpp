#include <Arduino.h>
#include "constants.h"
#include <MenuSystem.h>
#include "language.h"
#include "Ucglib.h"

boolean bMenuEnabled = false;
int iDisplayBright = 30;
boolean bClock = true;
boolean bSystem = true;
boolean bCrono = false;
boolean bCronoLearn = false;
boolean bLayout1 = true;
boolean bLayout2 = false;


// Menu variables
MenuSystem ms;
Menu mmRoot(MENU_TEXT_ROOT);
MenuItem mm_miBack(MENU_TEXT_BACK);
MenuItem mm_miExit(MENU_TEXT_BACK);
Menu muMenu(MENU_TEXT_MENU);
Menu muCrono(MENU_TEXT_CRONO_SCREEN);

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

Menu muMenu_Crono(MENU_TEXT_CRONO_ENABLE);
MenuItem muMenu_mi_Crono_ON(MENU_TEXT_ON);
MenuItem muMenu_mi_Crono_OFF(MENU_TEXT_OFF);
MenuItem muMenu_mi_Crono_LEARN(MENU_TEXT_LEARN);

Menu muMenu_System(MENU_TEXT_SYSTEM);
MenuItem muMenu_mi_System_ON(MENU_TEXT_ON);
MenuItem muMenu_mi_System_OFF(MENU_TEXT_OFF);

Menu muMenu_Layouts(MENU_TEXT_LAYOUTS);
MenuItem muMenu_mi_Layouts_1(MENU_TEXT_LAYOUT_1);
MenuItem muMenu_mi_Layouts_2(MENU_TEXT_LAYOUT_2);

MenuSystem* getMenu() {
  return &ms;
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
}

void on_item_perc80_selected(MenuItem* p_menu_item)
{
  iDisplayBright = 80;
}

void on_item_perc60_selected(MenuItem* p_menu_item)
{
  iDisplayBright = 60;

}

void on_item_perc50_selected(MenuItem* p_menu_item)
{
  iDisplayBright = 50;
}

void on_item_perc30_selected(MenuItem* p_menu_item)
{
  iDisplayBright = 30;
}

void on_item_perc5_selected(MenuItem* p_menu_item)
{
  iDisplayBright = 5;
}

void on_item_perc2_selected(MenuItem* p_menu_item)
{
  iDisplayBright = 2;
}

void on_item_clockON_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_clockON_selected");
  bClock = true;
}
void on_item_clockOFF_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_clockOFF_selected");
  bClock = false;
}
void on_item_cronoON_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_cronoON_selected");
  bCrono = true;
}
void on_item_cronoOFF_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_cronoOFF_selected");
  bCrono = false;
}
void on_item_cronoLEARN_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_cronoLEARN_selected");
  bCronoLearn = true;
}

void on_item_systemON_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_systemON_selected");
  bSystem = true;
}
void on_item_systemOFF_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_systemOFF_selected");
  bSystem = false;
}


void on_item_layout1_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_layout1_selected");
  bLayout1 = true;
  bLayout2 = false;
}
void on_item_layout2_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_layout2_selected");
  bLayout1 = false;
  bLayout2 = true;
}

void initMenu() {

  // Menu setup
  mmRoot.add_item(&mm_miExit, &on_item_MenuExit_selected);
  mmRoot.add_menu(&muMenu);
  mmRoot.add_menu(&muCrono);

  muMenu.add_item(&mm_miBack, &on_itemBack_selected);
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


  muMenu.add_menu(&muMenu_Crono);
  muMenu_Crono.add_item(&mm_miBack, &on_itemBack_selected);
  muMenu_Crono.add_item(&muMenu_mi_Crono_ON, &on_item_cronoON_selected);
  muMenu_Crono.add_item(&muMenu_mi_Crono_OFF, &on_item_cronoOFF_selected);
  muMenu_Crono.add_item(&muMenu_mi_Crono_LEARN, &on_item_cronoLEARN_selected);

  muMenu.add_menu(&muMenu_System);
  muMenu_System.add_item(&mm_miBack, &on_itemBack_selected);
  muMenu_System.add_item(&muMenu_mi_System_ON, &on_item_systemON_selected);
  muMenu_System.add_item(&muMenu_mi_System_OFF, &on_item_systemOFF_selected);

  muMenu.add_menu(&muMenu_Layouts);
  muMenu_Layouts.add_item(&mm_miBack, &on_itemBack_selected);
  muMenu_Layouts.add_item(&muMenu_mi_Layouts_1, &on_item_layout1_selected);
  muMenu_Layouts.add_item(&muMenu_mi_Layouts_2, &on_item_layout2_selected);

  ms.set_root_menu(&mmRoot);
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


boolean getEnabled() {
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

boolean getClock() {
  return bClock;
}

boolean getSystem() {
  return bSystem;
}

boolean getCrono() {
  return bCrono;
}
boolean getCronoLearn() {
  return bCronoLearn;
}

