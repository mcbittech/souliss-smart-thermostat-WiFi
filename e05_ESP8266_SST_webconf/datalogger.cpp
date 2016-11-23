#include "constants.h"
#include "datalogger.h"
#include "FS.h"
#include "ntp.h"
#include <ArduinoJson.h>


void save_datalogger(float setpoint,float temperature,float humidity,bool relaystatus) {
  //NTP
  String TimeDate = "";
  TimeDate = digitalClockDisplay();
  
  File sst_datalogger = SPIFFS.open("/sst_datalogger.csv", "a");
  if (!sst_datalogger) {
    Serial.println("sst_datalogger.csv open failed");
  }
  Serial.print("sst_datalogger size: ");Serial.println(sst_datalogger.size());
  sst_datalogger.print(TimeDate);sst_datalogger.print(",");sst_datalogger.print(setpoint,1);sst_datalogger.print(",");sst_datalogger.print(temperature,1);sst_datalogger.print(",");sst_datalogger.print(humidity,1);sst_datalogger.print(",");sst_datalogger.println(relaystatus);
  Serial.print("Salvo linea datalogger -> ");Serial.print(TimeDate);Serial.print(",");Serial.print(setpoint,1);Serial.print(",");Serial.print(temperature,1);Serial.print(",");Serial.print(humidity,1);Serial.print(",");Serial.println(relaystatus);
  Serial.print("sst_datalogger size: ");Serial.println(sst_datalogger.size());
  delay(1);
  sst_datalogger.close();
}


