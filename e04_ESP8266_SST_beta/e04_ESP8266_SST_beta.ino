/**************************************************************************
    Souliss - Hello World for Expressif ESP8266 with TFT SPI ILI9341
    
    This is the basic example, create a software push-button on Android
    using SoulissApp (get it from Play Store).  
    
    Load this code on ESP8266 board using the porting of the Arduino core
    for this platform.

        
***************************************************************************/

// Configure the framework
#include "bconf/MCU_ESP8266.h"              // Load the code directly on the ESP8266
#include "conf/IPBroadcast.h"

// **** Define the WiFi name and password ****
#define WIFICONF_INSKETCH
#define WiFi_SSID               ""
#define WiFi_Password           ""    

// Include framework code and libraries
#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include "Souliss.h"
#include <DHT.h>

// Define the network configuration
uint8_t ip_address[4]  = {192, 168, 1, 25};
uint8_t subnet_mask[4] = {255, 255, 255, 0};
uint8_t ip_gateway[4]  = {192, 168, 1, 1};
#define Gateway_address 18
#define  PEER4          25
#define myvNet_address  ip_address[3]       // The last byte of the IP address (18) is also the vNet address
#define myvNet_subnet   0xFF00
#define myvNet_supern   Gateway_address

//SLOT
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This identify the number of the LED logic
#define TEMPERATURA               0
#define UMIDITA                   2
#define CALDAIA                   4
         
// **** Define here the right pin for your ESP module **** 
#define RELE                      5



//DeadBand
#define DEADBAND                  0.05

//DHT22
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DHTPIN 12 
#define DHTTYPE DHT22 

DHT dht(DHTPIN, DHTTYPE);
float temperature = 0;
float humidity = 0;
float hyst = 0.2;

//ENCODER
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 int val; 
 int encoder0PinA = 3;
 int encoder0PinB = 4;
 int encoder0Pos = 220;
 int encoder0PinALast = LOW;
 int n = LOW;


//DISPLAY
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <SPI.h>
#include "Ucglib.h"

 
// Use hardware SPI
Ucglib_ILI9341_18x240x320_HWSPI ucg(/*cd=*/ 2 , /*cs=*/ 15);

#define SERIAL_OUT Serial
int backLED = 16;
float setpoint=22.0;


void setup()
{   
  //SOULISS
  ///////////////////////////////////////////////////////////////////////////////////////////////////////
    Souliss_SetIPAddress(ip_address, subnet_mask, ip_gateway);                    

    // This is the vNet address for this node, used to communicate with other
    // nodes in your Souliss network
    SetAddress(0xAB02, 0xFF00, 0xAB01);
    
    Set_SimpleLight(CALDAIA);                     // Define a simple LED light logic
    Souliss_SetT52(memory_map, TEMPERATURA);
    Souliss_SetT53(memory_map, UMIDITA);
    pinMode(RELE, OUTPUT);                        // Use pin as output 
    pinMode(backLED, OUTPUT);                     // Background Display LED
    analogWrite(backLED,50);
    dht.begin();
  
/////////////////////////////////////////////////////////////////////////////////////////////////////////  
  SERIAL_OUT.begin(115200);

//ENCODER
/////////////////////////////////////////////////////////////////////////////////////////////////////////
   pinMode (encoder0PinA,INPUT);
   pinMode (encoder0PinB,INPUT);

   ucg.begin(UCG_FONT_MODE_SOLID);
   ucg.setColor(0, 0, 0);
   ucg.drawBox(0, 0, ucg.getWidth(), ucg.getHeight());
}

void loop()
{ 
    // Here we start to play
    EXECUTEFAST() {                     
        UPDATEFAST();   
        FAST_10ms() {
            n = digitalRead(encoder0PinA);
            if ((encoder0PinALast == LOW) && (n == HIGH)) {
            if (digitalRead(encoder0PinB) == LOW) {
            analogWrite(backLED,1023);
            encoder0Pos--;
              } else {
            encoder0Pos++;
              }
            setpoint=encoder0Pos/10.0;
            
            ucg.setRotate90();
            ucg.setColor(0, 255, 255, 255);    // Bianco
            ucg.setFontMode(UCG_FONT_MODE_SOLID);
            ucg.setPrintPos(4,28);
            ucg.setFont(ucg_font_inb21_mr);
            ucg.print(setpoint,1);
            ucg.setFont(ucg_font_profont11_mr);
            ucg.setPrintPos(80,12);
            ucg.print("o");
            ucg.setPrintPos(15,41);
            ucg.print("SETPOINT");            
             
             } 
            encoder0PinALast = n; 
            //digitalWrite(backLED,dbackLED);
        }
        FAST_50ms() {   // We process the logic and relevant input and output every 50 milliseconds
            Logic_SimpleLight(CALDAIA);
            DigOut(RELE, Souliss_T1n_Coil,CALDAIA);
            
            Souliss_Logic_T52(memory_map, TEMPERATURA, DEADBAND, &data_changed);
            Souliss_Logic_T53(memory_map, UMIDITA, DEADBAND, &data_changed);
            /////////////////////////////////////////////////////////////////////////////////////////////
             
            } 
            
              
        // Here we handle here the communication with Android
        FAST_PeerComms();
                                    
    }
       EXECUTESLOW()
  {
    UPDATESLOW();
    
      SLOW_10s(){
        temperature = dht.readTemperature();
        humidity = dht.readHumidity();
        Souliss_ImportAnalog(memory_map, TEMPERATURA, &temperature);
        Souliss_ImportAnalog(memory_map, UMIDITA, &humidity);

            //Temperatura
            //ucg.setColor(111, 0, 255);    // Blu Elettrico
            //ucg.setColor(0, 255, 255, 255);    // Bianco
            ucg.setColor(102, 255, 0);    // Verde Chiaro
            ucg.setFontMode(UCG_FONT_MODE_SOLID);
            ucg.setPrintPos(15,75);
            ucg.setScale2x2();
            //ucg.setFont(ucg_font_logisoso38_tf);
            ucg.setFont(ucg_font_inb38_mr);
            ucg.print(temperature,1);
            ucg.undoScale();
            ucg.setPrintPos(280,90);
            ucg.setFont(ucg_font_inb21_mr);
            ucg.print("o");


            //Umidità
            ucg.setColor(111, 0, 255);    // Blu Elettrico
            ucg.setFontMode(UCG_FONT_MODE_SOLID);
            ucg.setPrintPos(222,236);
            ucg.setFont(ucg_font_inb21_mr);
            ucg.print(humidity,1);ucg.print("%");
            ucg.setFont(ucg_font_profont11_mr);
            ucg.setPrintPos(248,210);
            ucg.print("UMIDITA'");
        
      }

      //
      SLOW_50s(){
        if(temperature<setpoint-hyst){
          //Souliss_Input(memory_map, CALDAIA) = Souliss_T1n_OnCmd;
          mInput(CALDAIA) = Souliss_T1n_OnCmd;
          }
        if(temperature>setpoint+hyst){
          mInput(CALDAIA) = Souliss_T1n_OffCmd;
          }
        analogWrite(backLED,50);
        }
      }       
} 






