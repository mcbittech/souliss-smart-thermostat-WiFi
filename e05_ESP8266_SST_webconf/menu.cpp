#include <Arduino.h>
#include "constants.h"
#include <MenuSystem.h>


// Menu variables
MenuSystem ms;
Menu mm("");
MenuItem mm_mi1("Level 1 - Item 1 (Item)");
MenuItem mm_mi2("Level 1 - Item 2 (Item)");
Menu mu1("Level 1 - Item 3 (Menu)");
MenuItem mu1_mi1("Level 2 - Item 1 (Item)");

bool bRanCallback = false;
bool bForward = true;

void setbRanCallback(bool bVal){
  bRanCallback=bVal;
}

void setbForward(boolean bVal){
  bForward=bVal;
}

bool getbRanCallback(){
  return bRanCallback;
}

bool getbForward(){
  return bForward;
}

void on_item1_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("Item1 Selected");
  setbRanCallback(true);
  setbForward(true);
}

void on_item2_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("Item2 Selected");
  setbRanCallback(true);
}

void on_item3_selected(MenuItem* p_menu_item)
{
  SERIAL_OUT.println("Item3 Selected");
  setbRanCallback(true);
   setbForward(false);
}


void initMenu(){

   // Menu setup
  mm.add_item(&mm_mi1, &on_item1_selected);
  mm.add_item(&mm_mi2, &on_item2_selected);
  mm.add_menu(&mu1);
  mu1.add_item(&mu1_mi1, &on_item3_selected);
  ms.set_root_menu(&mm);
}

void printMenu(){
  // Display the menu
  Menu const* cp_menu = ms.get_current_menu();
  MenuComponent const* cp_menu_sel = cp_menu->get_selected();
 
for (int i = 0; i < cp_menu->get_num_menu_components(); ++i)
  {
    MenuComponent const* cp_m_comp = cp_menu->get_menu_component(i);
    SERIAL_OUT.print(cp_m_comp->get_name());
    
    if (cp_menu_sel == cp_m_comp)
      SERIAL_OUT.print("<<< ");
    
    SERIAL_OUT.println("");
  }
}

MenuSystem getMenu(){
 return ms;
}

