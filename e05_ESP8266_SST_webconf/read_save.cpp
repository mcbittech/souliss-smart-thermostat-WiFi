
/////////////////////////////////////////////////////////////////////////////////////////////////
// LOG EEPROM OCCUPATION
/*
DATE          AUTHOR       FILE        LINE              ALLOC        VARIABLE           SIZE  

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
#include "FS.h"
#include <ArduinoJson.h>

void save_spiffs_prefs(int json_iDisplayBright, int json_bClock, int json_timeZone, int json_bCrono, int json_bCronoLearn, int json_bSystem, int json_bLayout1,int json_bLayout2){
  SPIFFS.begin();
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["Luminosita"] = json_iDisplayBright;
  root["Orologio"] = json_bClock;
  root["Tzone"] = json_timeZone;
  root["Crono"] = json_bCrono;
  root["CronoLearn"] = json_bCronoLearn;
  root["Dispositivo"] = json_bSystem;
  root["Layout1"] = json_bLayout1;
  root["Layout2"] = json_bLayout2;
  //Serial.print("Ecco i dati in json: ");
  //root.printTo(Serial);
  char buffer[256];
  root.printTo(buffer, sizeof(buffer));
  //Serial.println();
   
  // open file for writing
  File sst_spiffs = SPIFFS.open("/sst_settings.json", "w");
  if (!sst_spiffs) { Serial.println("sst_settings.json open failed"); }
  //qui salvo il buffer su file
  sst_spiffs.println(buffer);
  Serial.print("Salvo in SPIFFS il buffer con i settings :");Serial.println(buffer);
  delay(1);
  //chiudo il file
  sst_spiffs.close();
}

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

const char* read_spiffs_prefs(const char*  valuedaleggere){
  File  sst_spiffs_inlettura = SPIFFS.open("/sst_settings.json", "r");
  if (!sst_spiffs_inlettura) { Serial.println("sst_settings.json open failed"); }
  String risultato= sst_spiffs_inlettura.readStringUntil('\n');
  //Serial.print("Ho letto dal file : ");Serial.println(risultato);  
  char json[200];
  risultato.toCharArray(json, 200);
  //Serial.print("Ecco l'array json convertito: ");Serial.println(json);  
  StaticJsonBuffer<200> jsonBuffer_inlettura;
  JsonObject& root_inlettura = jsonBuffer_inlettura.parseObject(json);
  if (!root_inlettura.success()) {    Serial.println("parseObject() failed");  }
  //leggo il valore e lo parso:
  const char* risultatoparsed = root_inlettura[valuedaleggere];
  Serial.print("Spiffs Json parsed value of ");Serial.print(valuedaleggere);Serial.print(" :");
  Serial.println(risultatoparsed);
  sst_spiffs_inlettura.close();
  return risultatoparsed;
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




