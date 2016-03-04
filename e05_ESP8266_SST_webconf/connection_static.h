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

#define STATIC_CONNECTION_Init_DHCP()              \
  SERIAL_OUT.println("start STATIC_CONNECTION_Init_DHCP"); \
  display_print_splash_connection_to_home_wifi(ucg); \
  /** Connect to the WiFi network and get an address from DHCP*/ \
  GetIPAddress(); \
  SERIAL_OUT.println("Address received"); \
  /** This is the vNet address for this node, used to communicate with other */ \
  /** nodes in your Souliss network*/ \
  SetAddress(peer_address, myvNet_subnet, wifi_bridge_address);          /* Address on the wireless interface*/ \
  
#define STATIC_CONNECTION_Init_STATICIP()              \
  SERIAL_OUT.println("start STATIC_CONNECTION_Init_STATICIP"); \
  /** Connect to the WiFi network and set static IP Address written in Webconfig*/ \
  ReadIPConfiguration(); \
  SERIAL_OUT.println("Address set to static IP"); \
  display_print_splash_connection_to_home_wifi(ucg); \
  SetAddress(peer_address, myvNet_subnet, wifi_bridge_address);          /* Address on the wireless interface*/ \

#define STATIC_CONNECTION_fast()       \
FAST_PeerComms();\

