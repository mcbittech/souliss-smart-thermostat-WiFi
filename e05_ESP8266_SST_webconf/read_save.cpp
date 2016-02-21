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


/////////////////////////////////////////////////////////////////////////////////////////////////
// LOG COMMIT SU EEPROM
/*
DATA          AUTORE       FILE        RIGA              ALLOCAZIONE  VAR                DIMENSIONE  
17/02/2016    Dariocdj     menu.cpp    81 e seguenti     1            iDisplayBright     int
17/02/2016    Dariocdj     menu.cpp    125,131           3            bClock             byte
17/02/2016    Dariocdj     menu.cpp    137,145           4            bCrono             byte
17/02/2016    Dariocdj     menu.cpp    172               5            bCronoLearn        byte
17/02/2016    Dariocdj     menu.cpp    179,185           6            bSystem            byte
17/02/2016    Dariocdj     menu.cpp    194,202           7            bLayout1           byte
17/02/2016    Dariocdj     menu.cpp    195,203           8            bLayout2           byte
17/02/2016    mcbittech    crono.cpp   377 e seguenti    9-345        dHourSel[7][48]    byte 7*48 matrix



 
 */
/////////////////////////////////////////////////////////////////////////////////////////////////


