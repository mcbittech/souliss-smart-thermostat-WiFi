#include <Arduino.h>

//LANGUAGE
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define SPLASH_GW_LINE1 "Modo Gateway" 
#define SPLASH_GW_LINE2 "Preparazione..." 

#define SPLASH_PEER_LINE1 "Modo Peer" 
#define SPLASH_PEER_LINE2 "Connessione... " 

#define SPLASH_NEED_CONF_LINE1 "Eseguire la "
#define SPLASH_NEED_CONF_LINE2 "configurazione "
#define SPLASH_NEED_CONF_LINE3 "via WEB "
#define SPLASH_SSID_LINE1 "Connessione "


#define SETPOINT_TEXT_SETPOINT_SCREEN "SETPOINT"
#define SETPOINT_TEXT "Set: "
#define TEMP_TEXT "T: "
#define HUM_TEXT "H: "
#define SYSTEM_OFF_TEXT "SPENTO"

//TOPICS
#define C1_COLOR()  ucg.setColor(13, 105, 226);    // Blu
#define C1_AREA_UNITY " W"
#define C1_AREA_TEXT " Home"
#define C1_AREA_TEXT_COLOR_LAYOUT2() ucg.setColor(255, 0, 0); //red

#define C2_COLOR()  ucg.setColor(226, 183, 13);    // Giallo Chiaro
#define C2_AREA_UNITY " W"
#define C2_AREA_TEXT " Solar"
#define C2_AREA_TEXT_COLOR_LAYOUT2() ucg.setColor(255, 0, 0); //red

#define C3_COLOR()  ucg.setColor(226, 105, 13);    // Giallo Chiaro
#define C3_AREA_UNITY " C°"
#define C3_AREA_TEXT " Temp."
#define C3_AREA_TEXT_COLOR_LAYOUT2() ucg.setColor(255, 0, 0); //red

#define C4_COLOR()  ucg.setColor(13, 105, 226);    // Giallo Chiaro
#define C4_AREA_UNITY "°"
#define C4_AREA_TEXT " Esterno"
#define C4_AREA_TEXT_COLOR_LAYOUT2() ucg.setColor(255, 0, 0); //red

#define C5_COLOR()  ucg.setColor(0, 255, 255);    // Giallo Chiaro
#define C5_AREA_UNITY "W"
#define C5_AREA_TEXT " Casa"
#define C5_AREA_TEXT_COLOR_LAYOUT2() ucg.setColor(255, 0, 0); //red

#define C6_COLOR()  ucg.setColor(255, 255, 102);    // Giallo Chiaro
#define C6_AREA_UNITY "W"
#define C6_AREA_TEXT " Desk"
#define C6_AREA_TEXT_COLOR_LAYOUT2() ucg.setColor(255, 0, 0); //red

//MENU
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define MENU_TEXT_ROOT "Smart Souliss Thermostat"
#define MENU_TEXT_ON "ON"
#define MENU_TEXT_OFF "OFF"
#define MENU_TEXT_BACK "Torna"
#define MENU_TEXT_MENU "Menu"
#define MENU_TEXT_CRONO_PROGRAM "Programmazione Crono"
#define MENU_TEXT_CRONO_ENABLE "Crono"
#define MENU_TEXT_LEARN "Autoapprendimento"
#define MENU_TEXT_CLOCK "Orologio"
#define MENU_TEXT_BRIGHT "Luminosita'"
#define MENU_TEXT_SYSTEM "Dispositivo"
#define MENU_TEXT_LAYOUTS "Layouts"
#define MENU_TEXT_LAYOUT_1 "Lineare"
#define MENU_TEXT_LAYOUT_2 "Circolare"
#define MENU_TEXT_TIMEZONE_SET "Timezone"
#define MENU_TIMEZONE_0 "UTC+0 Eu West,Greenw."
#define MENU_TIMEZONE_1 "UTC+1 Eu Cent,Italia"
#define MENU_TIMEZONE_2 "UTC+2 Eu Est,Romania"
#define MENU_TIMEZONE_3 "UTC+3 Eu Est,Bel,Russia"
#define MENU_TIMEZONE_4 "UTC+4 Turchia,Azerb."


