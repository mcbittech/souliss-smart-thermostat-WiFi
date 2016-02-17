#include <Arduino.h>
#include <EEPROM.h>
#include "tools/store/store.h"          
#include "read_save.h"

int offset=100;

void save_eeprom_byte(int index,byte value){ 
  Store_8bit(index+offset,value);
  Serial.print("SaveEepromByte index");Serial.print(index+offset);Serial.println(value);
  Store_Commit();
}

void save_eeprom_int(int index,int value){ 
  Store_16bit(index+offset,value);
  Serial.print("SaveEepromInt index");Serial.print(index+offset);Serial.println(value);
  Store_Commit();
}

byte read_eeprom_byte(int index){
  byte value;
  value=Return_8bit(index+offset);
  Serial.print("readEepromByte index");Serial.print(index+offset);Serial.println(value);
  return value;
}

int read_eeprom_int(int index){
  int value;
  value=Return_16bit(index+offset);
  Serial.print("ReadEepromInt index");Serial.print(index+offset);Serial.println(value);
  return value;
}
