#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2017-11-22 09:22:42

#include "Arduino.h"
#include "SoulissFramework.h"
#define T3N_DEADBAND_INSKETCH
#define Souliss_T3n_DeadBand      0.1
#define T3N_HYSTERESIS_INSKETCH
#define Souliss_T3n_Hysteresis      0.1
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>
#include "FS.h"
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <MenuSystem.h>
#include <DHT.h>
#include "bconf/MCU_ESP8266.h"
#include "preferences.h"
#include "multiClick.h"
#include "conf/RuntimeGateway.h"
#include "conf/DynamicAddressing.h"
#include "conf/WEBCONFinterface.h"
#include "connection_dynamic.h"
#include "conf/IPBroadcast.h"
#include "connection_static.h"
#define USEEEPROM_INSKETCH
#define USEEEPROM             1
#include "Souliss.h"
#include "encoder.h"
#include "constants.h"
#include "display.h"
#include "display2.h"
#include "displayTopics.h"
#include "language.h"
#include "ntp.h"
#include <TimeLib.h>
#include "menu.h"
#include "crono.h"
#include "read_save.h"
#include "topics.h"
#include "pagesStruct.h"
#include <SPI.h>
#include <Arduino.h>
#include "Ucglib.h"
void EEPROM_Reset() ;
void subscribeTopics() ;
void setSoulissDataChanged() ;
void set_ThermostatModeOn(U8 slot) ;
void set_ThermostatOff(U8 slot) ;
void set_DisplayMinBright(U8 slot, U8 val) ;
void encoderFunction() ;
boolean getSoulissSystemState() ;
void getTemp() ;
void initScreen() ;
void setSetpoint(float setpoint) ;
void bright(int lum) ;
void publishHeating_ON_OFF() ;
void setup() ;
void loop() ;

#include "SST_Eclipse.ino"


#endif
