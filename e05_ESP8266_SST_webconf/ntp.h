#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <TimeLib.h> 

time_t getNtpTime();
void sendNTPpacket(IPAddress);

String digitalClockDisplay();
String digitalClockDisplay_simple();
String digitalDataDisplay();
String printDigits(int);
int getNTPday();
int getNTPhour();
int getNTPminute();

void initNTP();
