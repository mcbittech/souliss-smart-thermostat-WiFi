#include "constants.h"
#include "datalogger.h"
#include "FS.h"
#include "ntp.h"
#include <ArduinoJson.h>


void save_datalogger(float setpoint,float temperature,float humidity,bool relaystatus) {
  int iDay = getNTPday();
  String S_TimeDate = digitalClockDisplay_WBS();
  String S_filename = "/datalog/sst_datalogger" + String(getNTPday()) + ".csv";

/*  if(iDay!=iDay_prev){
    
  }
*/
  
  File sst_datalogger = SPIFFS.open(S_filename, "a");
  if (!sst_datalogger) {
    Serial.println("sst_datalogger.csv open failed");
  }
  Serial.print(S_filename);Serial.print(" size: ");Serial.println(sst_datalogger.size());
  sst_datalogger.print(S_TimeDate);sst_datalogger.print(",");sst_datalogger.print(setpoint,1);sst_datalogger.print(",");sst_datalogger.print(temperature,1);sst_datalogger.print(",");sst_datalogger.print(humidity,1);sst_datalogger.print(",");sst_datalogger.println(relaystatus);
  Serial.print("Salvo linea datalogger -> ");Serial.print(S_TimeDate);Serial.print(",");Serial.print(setpoint,1);Serial.print(",");Serial.print(temperature,1);Serial.print(",");Serial.print(humidity,1);Serial.print(",");Serial.println(relaystatus);
  Serial.print(S_filename);Serial.print(" size: ");Serial.println(sst_datalogger.size());
  delay(1);
  sst_datalogger.close();
  int iDay_prev = getNTPday();
}


