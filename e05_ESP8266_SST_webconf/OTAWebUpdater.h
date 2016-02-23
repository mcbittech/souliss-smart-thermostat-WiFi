/**************************************************************************
    Souliss
    Copyright (C) 2015  Veseo
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    
    Modified by Dario Di Maio, original code from 
       https://github.com/esp8266/Arduino
    
***************************************************************************/
/*!
    \file 
    \ingroup
*/
#define OTA_WebUpdater_Setup()     				const char* host = "esp8266-webupdate";\
                                          ESP8266WebServer httpServer(80);\
									                        ESP8266HTTPUpdateServer httpUpdater;\

#define OTA_WebUpdater_Init()       									\
                                    MDNS.begin(host);\
                                    httpUpdater.setup(&httpServer);\
									                  httpServer.begin();\
                  									MDNS.addService("http", "tcp", 80);\
                   									Serial.printf("HTTPUpdateServer ready! Open http://%s.local/update in your browser\n", host);\
                  
#define OTA_WebUpdater_Process()    								httpServer.handleClient();\



