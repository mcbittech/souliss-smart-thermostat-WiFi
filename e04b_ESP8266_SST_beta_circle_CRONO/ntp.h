#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Time.h> 

time_t getNtpTime();
void sendNTPpacket(IPAddress);
String digitalClockDisplay();
String digitalDataDisplay();
String printDigits(int);

void initNTP();
