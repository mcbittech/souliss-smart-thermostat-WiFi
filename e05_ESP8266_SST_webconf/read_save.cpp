#include <Arduino.h>
#include <EEPROM.h>
#include "tools/store/store.h"          
#include "read_save.h"

byte a=0;

void save_eeprom(){ 
  //Store_8bit(index,value);
  Store_8bit(400,2);
}

void read_eeprom(){ 
  //Return_8bit(index);
  a=Return_8bit(400);
}
