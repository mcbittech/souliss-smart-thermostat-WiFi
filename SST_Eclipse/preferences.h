#include <Arduino.h>

//LAYOUT
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define LAYOUT_LINEAR 1
#define LAYOUT_CIRCULAR 0

//LOCAL CRONO FUNCTION
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CRONO 1
#define CRONOLEARN 0

//CLOCK
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CLOCK 1
#define TIME_ZONE 1  // Central European Time
#define DAYLIGHTSAVINGTIME 0 // Ora legale

//SYSTEM AT BOOT
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SYSTEM_START_ON 1 if SST start at power on
//SYSTEM_START_ON 0 if SST start at power off.
#define SYSTEM_START_ON 1

//DISPLAY BRIGHT
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define BRIGHT_MAX 100         
#define BRIGHT_MIN_DEFAULT 15  
#define BRIGHT_STEP_FADE_IN 20 
#define BRIGHT_STEP_FADE_OUT 1

//WIFI CONNECTION
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//0 Static Connection
//1 Dynamic Connection
#define DYNAMIC_CONNECTION 0

//DHCP
//1 Use DHCP IP
//0 Use Static IP Address
//0 Only for DYNAMIC_CONNECTION = 0
#define DHCP_OPTION 1

//STATIC IP
// use commas between number
#define STATIC_IP 192,168,0,74
#define STATIC_SUBNET 255,255,255,0
#define STATIC_IP_GW 192,168,0,1

// **** Define the WiFi name and password ****
//Only for DYNAMIC_CONNECTION = 0
#define WIFICONF_INSKETCH
#define WiFi_SSID               "*** toConfigure ***"
#define WiFi_Password           "*** toConfigure ***"   

// Define the network configuration according to your router settingsuration according to your router settings
// and the other on the wireless oneless one
//Only for DYNAMIC_CONNECTION = 0
#define peer_address  0xAB21
#define myvNet_subnet 0xFF00
#define wifi_bridge_address    0xAB01 //gateway


//TOPICS PUBLISH&SUBSCRIBE
//Define if you want topics on display
#define ACTIVATETOPICSPAGE 1 
#define TOPICSPAGESNUMBER 2 // 1 if you have less than 3 topics subscribed, 2 if you have more than 3 topics subscribed

//ucg.setColor(255, 255, 255);    // White
//ucg.setColor(255, 0, 0); // Red
//ucg.setColor(255, 255, 102);    // Yellow
//ucg.setColor(0, 255, 255);   //light blue

#define C1_COLOR()  ucg.setColor(255, 0, 0); // Red
#define C1_AREA_UNITY "W"
#define C1_AREA_TEXT " Grid"
#define C1_AREA_TEXT_COLOR_LAYOUT2() ucg.setColor(255, 0, 0); //red

#define C2_COLOR()  ucg.setColor(255, 255, 102);    // Yellow
#define C2_AREA_UNITY "W"
#define C2_AREA_TEXT " Solar"
#define C2_AREA_TEXT_COLOR_LAYOUT2() ucg.setColor(255, 0, 0); //red

#define C3_COLOR()  ucg.setColor(0, 255, 255);   //light blue
#define C3_AREA_UNITY "^C" 
#define C3_AREA_TEXT " Boil"
#define C3_AREA_TEXT_COLOR_LAYOUT2() ucg.setColor(255, 0, 0); //red

#define C4_COLOR()  ucg.setColor(255, 255, 255);    // White
#define C4_AREA_UNITY "'"
#define C4_AREA_TEXT " topic"
#define C4_AREA_TEXT_COLOR_LAYOUT2() ucg.setColor(255, 0, 0); //red

#define C5_COLOR()  ucg.setColor(255, 255, 255);     // White
#define C5_AREA_UNITY "'"
#define C5_AREA_TEXT " topic"
#define C5_AREA_TEXT_COLOR_LAYOUT2() ucg.setColor(255, 0, 0); //red

#define C6_COLOR()  ucg.setColor(255, 255, 255);    // White
#define C6_AREA_UNITY "'"
#define C6_AREA_TEXT " topic"
#define C6_AREA_TEXT_COLOR_LAYOUT2() ucg.setColor(255, 0, 0); //red

