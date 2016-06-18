#include <Arduino.h>
#include <EEPROM.h>
#include "constants.h"
#include "tools/store/store.h"
#include "read_save.h"
#include "FS.h"
#include <ArduinoJson.h>

char json[200];

void save_spiffs_prefs(int json_iDisplayBright, int json_bClock, int json_timeZone, int json_DayLightSavingTime, int json_bCrono, int json_bCronoLearn, int json_bSystem, int json_bLayout1, int json_bLayout2) {
  SPIFFS.begin();
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["Luminosita"] = json_iDisplayBright;
  root["Orologio"] = json_bClock;
  root["Tzone"] = json_timeZone;
  root["DayLightSavingTime"] = json_DayLightSavingTime;
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
  if (!sst_spiffs) {
    Serial.println("sst_settings.json open failed");
  }
  //qui salvo il buffer su file
  sst_spiffs.println(buffer);
  Serial.print("Salvo in SPIFFS il buffer con i settings :"); Serial.println(buffer);
  delay(1);
  //chiudo il file
  sst_spiffs.close();
}

boolean read_spiffs_prefs() {
  File  sst_spiffs_inlettura = SPIFFS.open("/sst_settings.json", "r");
  if (!sst_spiffs_inlettura) {
    Serial.println("sst_settings.json open failed");
    return false;
  }
  String risultato = sst_spiffs_inlettura.readStringUntil('\n');
  char json[200];
  risultato.toCharArray(json, 200);

  sst_spiffs_inlettura.close();
  return true;
}

int read_JSON_integer(const char* itemName) {
  //Serial.print("Ecco l'array json convertito: ");Serial.println(json);
  StaticJsonBuffer<200> jsonBuffer_inlettura;
  JsonObject& root_JSON = jsonBuffer_inlettura.parseObject(json);
int iValue=0;
  if (root_JSON.success()) {
    //leggo il valore e lo parso:
    iValue = root_JSON[itemName];
    Serial.print("Spiffs Json parsed value of "); Serial.print(itemName); Serial.print(" : ");
    Serial.println(iValue);
  } else {
    Serial.println("parseObject() failed");
  }

  return iValue;
}



