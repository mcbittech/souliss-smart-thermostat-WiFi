#include <Arduino.h>

//LAYOUT
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define LAYOUT_LINEAR 0
#define LAYOUT_CIRCULAR 1

//LOCAL CRONO FUNCTION
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CRONO 1
#define CRONOLEARN 0

//CLOCK
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CLOCK 1
#define TIME_ZONE 1  // Central European Time

//DISPLAY BRIGHT
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define BRIGHT_MAX 100         
#define BRIGHT_MIN_DEFAULT 15  
#define BRIGHT_STEP_FADE_IN 20 
#define BRIGHT_STEP_FADE_OUT 1

//OTA Name
#define HOST_NAME_INSKETCH
#define HOST_NAME "Souliss-Thermostat"

//WIFI CONNECTION
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//0 Static Connection
//1 Dynamic Connection
#define DYNAMIC_CONNECTION 0 

//DHCP
//1 Use DHCP IP
//0 Use Static IP Address
#define DHCP_OPTION 0

//STATIC IP 
// use commas between number
#define STATIC_IP 192,168,1,120
#define STATIC_SUBNET 255,255,255,0
#define STATIC_IP_GW 192,168,1,1

// **** Define the WiFi name and password ****
//Only for DYNAMIC_CONNECTION = 0
#define WIFICONF_INSKETCH
#define WiFi_SSID               ""
#define WiFi_Password           ""  

// Define the network configuration according to your router settingsuration according to your router settings
// and the other on the wireless oneless one
//Only for DYNAMIC_CONNECTION = 0
#define peer_address  0xAB20
#define myvNet_subnet 0xFF00
#define wifi_bridge_address    0xAB10 //gateway


