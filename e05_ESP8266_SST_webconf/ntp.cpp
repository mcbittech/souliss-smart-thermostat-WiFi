#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "constants.h"
#include <TimeLib.h>
#include "read_save.h"
//NTP
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int localPort = 8888;  // local port to listen for UDP packets
// NTP Servers:
//IPAddress timeServer(132, 163, 4, 101); // time-a.timefreq.bldrdoc.gov
IPAddress timeServer(193, 204, 114, 232); // ntp1.inrim.it


// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp_NTP;
/*-------- NTP code ----------*/

const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets


// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address)
{
  // set all bytes in the buffer to 0
  //memset(packetBuffer, MEMSET_NTP_START, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  udp_NTP.beginPacket(address, 123); //NTP requests are to port 123
  udp_NTP.write(packetBuffer, NTP_PACKET_SIZE);
  udp_NTP.endPacket();
}

time_t getNtpTime()
{
  while (udp_NTP.parsePacket() > 0) ; // discard any previously received packets
  SERIAL_OUT.println("Transmit NTP Request");
  sendNTPpacket(timeServer);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = udp_NTP.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      SERIAL_OUT.println("Receive NTP Response");
      udp_NTP.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      //return secsSince1900 - 2208988800UL + read_eeprom_byte(9) * SECS_PER_HOUR;
      int tZonetemp =read_spiffs_prefs("Tzone");
      int tDayLighttemp = read_spiffs_prefs("DayLightSavingTime");

      if (tDayLighttemp == 0)
       {
       SERIAL_OUT.print("This is NTP Response with tzone: ");SERIAL_OUT.print(tZonetemp);SERIAL_OUT.println(" and tDayLighttemp OFF");
       
       return secsSince1900 - 2208988800UL + tZonetemp * SECS_PER_HOUR;       
       }
       else 
       {
       SERIAL_OUT.print("This is NTP Response with tzone: ");SERIAL_OUT.print(tZonetemp);SERIAL_OUT.println(" and tDayLighttemp ON");
       return secsSince1900 - 2208988800UL + (tZonetemp + 1) * SECS_PER_HOUR;
       } 
    }
  }
  SERIAL_OUT.println("No NTP Response :-(");
  return 0; // return 0 if unable to get the time
}



String printDigits(int digits) {
  // utility for digital clock display: prints preceding colon and leading 0
 String  s = "";
  if (digits < 10)
    s = "0";
  s = s + digits;

  return s;
}

String digitalClockDisplay() {
  // digital clock display of the time
  return printDigits(hour()) + ":" + printDigits(minute()) + ":" + printDigits(second()) +  " " + day() + "/" + month() + "/" + year();
}

String digitalClockDisplay_simple() {
  // digital clock display of the time
  return printDigits(hour()) + ":" + printDigits(minute());
}


String digitalDataDisplay() {
  // digital clock display of the time
  return printDigits(day()) + "." + (month()) + "." + (year());
}

//Crono var
//Day of week  Sunday is day 0 
int getNTPday(){
  return weekday();  
}
//Hour of day
int getNTPhour(){
  return hour();
}
//minute of day
int getNTPminute(){
  return minute();
}

void initNTP() {

  udp_NTP.begin(localPort);
  SERIAL_OUT.print("waiting for sync");
  setSyncProvider(getNtpTime);
}


