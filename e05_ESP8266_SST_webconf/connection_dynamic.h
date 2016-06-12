/**************************************************************************
    Souliss
    Copyright (C) 2016  Veseo
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
#define DYNAMIC_CONNECTION_Init()              /** Read the IP configuration from the EEPROM, if not available start the node as access point */ \
  SERIAL_OUT.println("start DYNAMIC_CONNECTION_Init"); \
  if (!ReadIPConfiguration()) \
  { \
    /** Start the node as access point with a configuration WebServer */ \
    SetAccessPoint();\
    startWebServer();\
    SERIAL_OUT.println("display_print_splash_waiting_need_configuration"); \
    display_print_splash_waiting_need_configuration(ucg); \
    /** We have nothing more than the WebServer for the configuration */ \
    /** to run, once configured the node will quit this. */ \
    while (1) \
    { \
      yield(); \
      runWebServer(); \
    } \
  } \
  if (IsRuntimeGateway())  \
  { \
    SERIAL_OUT.println("display_print_splash_waiting_connection_gateway"); \
    /** Connect to the WiFi network and get an address from DHCP*/ \
    SetAsGateway(myvNet_dhcp);       /** Set this node as gateway for SoulissApp */ \
    display_print_splash_waiting_connection_gateway(ucg); \
    SetAddressingServer(); \
    display_print_splash_waiting_connection_gateway(ucg); \
  } \
  else \
  { \
    SERIAL_OUT.println("display_print_splash_waiting_connection_peer"); \
    /** This board request an address to the gateway at runtime, no need */ \
    /** to configure any parameter here. */ \
    SetDynamicAddressing(); \
    display_print_splash_waiting_connection_peer(ucg); \
    GetAddress(); \
    SERIAL_OUT.println("Address received"); \
    display_print_splash_waiting_connection_peer(ucg); \
  } \

#define DYNAMIC_CONNECTION_fast()      /** Run communication as Gateway or Peer */ \
  if (IsRuntimeGateway())   \
    FAST_GatewayComms();    \
  else                      \
    FAST_PeerComms();       \


#define DYNAMIC_CONNECTION_slow()      /** Run communication as Peer */ \
  /** If running as Peer */ \
  if (!IsRuntimeGateway()) {  \
    SLOW_PeerJoin(); \
  }\
