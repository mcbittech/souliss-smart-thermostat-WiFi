#include "constants.h"
#include "preferences.h"
#include "datalogger.h"
#include "FS.h"
#include "ntp.h"
#include <ESP8266HTTPClient.h>
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
      #ifdef DEBUG_DEV
        Serial.print("    Delete older file: ");Serial.println(S_filename);
      #endif
      SPIFFS.remove(S_filename);
    }
  }
  


  File sst_datalogger = SPIFFS.open(S_filename, "a");
  if (!sst_datalogger) {
    #ifdef DEBUG_DEV
    Serial.print(S_filename);Serial.println(" open failed");
    #endif
  }
  #ifdef DEBUG_DEV
    Serial.print(S_filename);Serial.print(" size: ");Serial.println(sst_datalogger.size());
  #endif
  sst_datalogger.print(S_TimeDate);sst_datalogger.print(",");sst_datalogger.print(setpoint,1);sst_datalogger.print(",");sst_datalogger.print(temperature,1);sst_datalogger.print(",");sst_datalogger.print(humidity,1);sst_datalogger.print(",");sst_datalogger.println(relaystatus);
  #ifdef DEBUG_DEV
    Serial.print("Salvo linea datalogger -> ");Serial.print(S_TimeDate);Serial.print(",");Serial.print(setpoint,1);Serial.print(",");Serial.print(temperature,1);Serial.print(",");Serial.print(humidity,1);Serial.print(",");Serial.println(relaystatus);
    Serial.print(S_filename);Serial.print(" size: ");Serial.println(sst_datalogger.size());
  #endif
  yield();
  sst_datalogger.close();
  iDay_prev = getNTPday();
  ////////////////////////
  #ifdef TTD
   ///*
      #ifdef DEBUG_DEV
        Serial.println("SEND KEEPALIVE");
      #endif
      HTTPClient clienthttp_SST;
      const char* host="http://www.google-analytics.com/collect";
      String eventData = "v=1&t=event&tid=UA-89261240-1&cid=555&ec=SST"+String(VERSION)+"&ea=KEEPALIVE&el="+String(ESP.getChipId(), HEX);
      clienthttp_SST.begin(host);
      clienthttp_SST.addHeader("User-agent", "Mozilla/5.0 (X11; Linux x86_64; rv:12.0) Gecko/20100101 Firefox/21.0");
      clienthttp_SST.POST(eventData);
      clienthttp_SST.writeToStream(&Serial);
      clienthttp_SST.end();
      #ifdef DEBUG_DEV
        Serial.println("KEEPALIVE CLOSED");
      #endif
      //*/
  #endif    
}

