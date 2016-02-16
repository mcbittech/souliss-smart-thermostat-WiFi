#include <Arduino.h>
#include <EEPROM.h>
#include "tools/store/store.h"          
#include "read_save.h"



void save_eeprom_byte(int index,byte value){ 
  Store_8bit(index,value);
  Serial.print("SaveEepromByte index");Serial.print(index);Serial.println(value);
  Store_Commit();
}

void save_eeprom_int(int index,int value){ 
  Store_16bit(index,value);
  Serial.print("SaveEepromInt index");Serial.print(index);Serial.println(value);
  Store_Commit();
}


void read_eeprom_byte(int index,int value){
  value=Return_8bit(index);
  Serial.print("readEepromByte index");Serial.print(index);Serial.println(value);
}


void read_eeprom_int(int index,int value){
  value=Return_16bit(index);
  Serial.print("ReadEepromInt index");Serial.print(index);Serial.println(value);
}
