#include <Arduino.h>
#include "constants.h"
#include <MenuSystem.h>
#include "language.h"
#include "Ucglib.h"

// Menu variables
MenuSystem ms;
Menu mmRoot(MENU_TEXT_ROOT);
MenuItem mm_miBack(MENU_TEXT_BACK);
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


int iDisplayBright = 100;
MenuSystem* getMenu() {
  return &ms;
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
}
void on_item_clockOFF_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_clockOFF_selected");
}
void on_item_cronoON_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_cronoON_selected");
}
void on_item_cronoOFF_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_cronoOFF_selected");
}
void on_item_cronoLEARN_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_cronoLEARN_selected");
}

void on_item_systemON_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_systemON_selected");
}
void on_item_systemOFF_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_systemOFF_selected");
}


void on_item_layout1_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_layout1_selected");
}
void on_item_layout2_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("on_item_layout2_selected");
}
void initMenu() {

  // Menu setup
  mmRoot.add_item(&mm_miBack, &on_itemBack_selected);
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


//void printMenu() {
//  // Display the menu
//  Menu const* cp_menu;
//  cp_menu = ms.get_current_menu();
//
//  Serial.print("Current menu name: ");
//  Serial.println(cp_menu->get_name());
//
//  MenuComponent const* cp_menu_sel = cp_menu->get_selected();
//  for (int i = 0; i < cp_menu->get_num_menu_components(); ++i)
//  {
//    MenuComponent const* cp_m_comp = cp_menu->get_menu_component(i);
//    SERIAL_OUT.print(cp_m_comp->get_name());
//
//    if (cp_menu_sel == cp_m_comp)
//      SERIAL_OUT.print("<<< ");
//
//    SERIAL_OUT.println("");
//  }
//}




void printMenu(Ucglib_ILI9341_18x240x320_HWSPI ucg) {
  int x = 2;
  int y = 4;
  int y_step = 10;
  ucg.clearScreen();

  // Display the menu
  Menu const* cp_menu;
  cp_menu = ms.get_current_menu();


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
    y = y + y_step;
    ucg.setPrintPos(x, y);

    if (cp_menu_sel == cp_m_comp)
      ucg.print("> ");
    else
      ucg.print("  ");

    ucg.print(cp_m_comp->get_name());
  }
}






