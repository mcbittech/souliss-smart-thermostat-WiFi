#include "constants.h"
#include "datalogger.h"
#include "FS.h"
#include "ntp.h"
#include <ArduinoJson.h>


void save_datalogger(float setpoint,float temperature,float humidity,bool relaystatus) {
  //NTP
  String TimeDate = "";
  TimeDate = digitalClockDisplay();
  
  File sst_datalogger = SPIFFS.open("/sst_datalogger.csv", "w");
  if (!sst_datalogger) {
    Serial.println("sst_datalogger.csv open failed");
  }
  sst_datalogger.print(TimeDate);sst_datalogger.print(",");sst_datalogger.print(setpoint);sst_datalogger.print(",");sst_datalogger.print(temperature);sst_datalogger.print(",");sst_datalogger.print(humidity);sst_datalogger.print(",");sst_datalogger.println(relaystatus);
  Serial.print("Salvo linea datalogger -> ");Serial.print(TimeDate);Serial.print(",");Serial.print(setpoint);Serial.print(",");Serial.print(temperature);Serial.print(",");Serial.print(humidity);Serial.print(",");Serial.println(relaystatus);
  delay(1);
  sst_datalogger.close();
}


