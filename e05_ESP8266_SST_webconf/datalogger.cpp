#include "constants.h"
#include "datalogger.h"
#include "FS.h"
#include "ntp.h"
#include <ArduinoJson.h>

/*getNTPday()
 * 1.Sunday 2.Monday 3.Tuesday 4.Wednesday 5.Thursday 6.Friday 7.Saturday
 * SPIFFS.exists(path)
 * SPIFFS.remove(path)
 */
int iDay_prev;
 

void save_datalogger(float setpoint,float temperature,float humidity,bool relaystatus) {
  int iDay = getNTPday();
  String S_TimeDate = digitalClockDisplay_WBS();
  String S_filename = "/datalog/sst_datalogger" + String(getNTPday()) + ".csv";
  
/*
  Serial.print("iDay. ");Serial.println(iDay);
  Serial.print("iDay_prev. ");Serial.println(iDay_prev);
*/

  if(iDay_prev > 0 && (iDay != iDay_prev)) {
    if(SPIFFS.exists(S_filename)==1)  {
      Serial.print("    Delete older file: ");Serial.println(S_filename);
      SPIFFS.remove(S_filename);
    }
  }
  


  File sst_datalogger = SPIFFS.open(S_filename, "a");
  if (!sst_datalogger) {
    Serial.print(S_filename);Serial.println(" open failed");
  }
  Serial.print(S_filename);Serial.print(" size: ");Serial.println(sst_datalogger.size());
  sst_datalogger.print(S_TimeDate);sst_datalogger.print(",");sst_datalogger.print(setpoint,1);sst_datalogger.print(",");sst_datalogger.print(temperature,1);sst_datalogger.print(",");sst_datalogger.print(humidity,1);sst_datalogger.print(",");sst_datalogger.println(relaystatus);
  Serial.print("Salvo linea datalogger -> ");Serial.print(S_TimeDate);Serial.print(",");Serial.print(setpoint,1);Serial.print(",");Serial.print(temperature,1);Serial.print(",");Serial.print(humidity,1);Serial.print(",");Serial.println(relaystatus);
  Serial.print(S_filename);Serial.print(" size: ");Serial.println(sst_datalogger.size());
  yield();
  sst_datalogger.close();
  iDay_prev = getNTPday();
}


