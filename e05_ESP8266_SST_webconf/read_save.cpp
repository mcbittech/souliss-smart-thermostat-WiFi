
/////////////////////////////////////////////////////////////////////////////////////////////////
// LOG EEPROM OCCUPATION
/*
DATE          AUTHOR       FILE        LINE              ALLOC        VARIABLE           SIZE  
02/03/2016    mcbittech    menu.cpp    451               1            use_eeprom         byte
02/03/2016    mcbittech    menu.cpp    81 e seguenti     2            iDisplayBright     byte
17/02/2016    Dariocdj     menu.cpp    125,131           3            bClock             byte
17/02/2016    Dariocdj     menu.cpp    137,145           4            bCrono             byte
17/02/2016    Dariocdj     menu.cpp    172               5            bCronoLearn        byte
17/02/2016    Dariocdj     menu.cpp    179,185           6            bSystem            byte
17/02/2016    Dariocdj     menu.cpp    194,202           7            bLayout1           byte
17/02/2016    Dariocdj     menu.cpp    195,203           8            bLayout2           byte
01/03/2016    Dariocdj     menu.cpp    175 e seguenti    9            timeZone           byte
22/02/2016    mcbittech    crono.cpp   511 e seguenti    10-394       dHourSel[7][48]    byte 7*48 matrix
22/02/2016    mcbittech    crono.cpp   511 e seguenti    400-410      setP[1...5]        byte 7*48 matrix


 
 */
/////////////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include <EEPROM.h>
#include "constants.h"
#include "tools/store/store.h"          
#include "read_save.h" 

void save_eeprom_byte(int index,byte value){ 
  Store_8bit(index+offset,value);
  Serial.print("SaveEepromByte index:");Serial.print(index+offset);Serial.print(" value:");Serial.println(value);
  Store_Commit();
  delay(1);
}

void save_eeprom_int(int index,int value){ 
  Store_16bit(index+offset,value);
  Serial.print("SaveEepromInt index:");Serial.print(index+offset);Serial.print(" value:");Serial.println(value);
  Store_Commit();
  delay(1);
}

byte read_eeprom_byte(int index){
 byte value;
 value=Return_8bit(index+offset);
 Serial.print("readEepromByte index:");Serial.print(index+offset);Serial.print(" value:");Serial.println(value);
 return value;
 delay(1);
}

int read_eeprom_int(int index){
 int value;
 value=Return_16bit(index+offset);
 Serial.print("ReadEepromInt index:");Serial.print(index+offset);Serial.print(" value:");Serial.println(value);
 return value;
 delay(1);
}




