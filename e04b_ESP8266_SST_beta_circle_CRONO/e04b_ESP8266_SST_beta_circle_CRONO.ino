


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
#include "t_constants.h"


//OTA
//#include <GDBStub.h> 


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
#define DEADBAND                  0.01

//DHT22
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DHTPIN 12 
#define DHTTYPE DHT22 

DHT dht(DHTPIN, DHTTYPE);
float temperature = 0;
float pretemperature = 0;
float deltaT = 0;
float humidity = 0;
float hyst = 0.2;


//ENCODER
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int val; 
int encoder0Pos = 220;
int encoder0PinALast = LOW;
bool encSetpointEnable=1;

//NTP
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "ntp.h"
#include <Time.h> 

//DISPLAY
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <SPI.h>
#include <Arduino.h>
#include "Ucglib.h"

// Use hardware SPI
Ucglib_ILI9341_18x240x320_HWSPI ucg(/*cd=*/ 2 , /*cs=*/ 15);

#define SERIAL_OUT Serial

int backLED = 16;
int backLEDvalue=0;
int backLEDvalueHIGH=1000;
int backLEDvalueLOW=100;
bool FADE=1;
float setpoint=20.5;

//CRONO
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "crono.h"


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
    pinMode(GPIO0, INPUT);
    pinMode(RELE, OUTPUT);                        // Use pin as output 
    pinMode(backLED, OUTPUT);                     // Background Display LED
    analogWrite(backLED,30);
    dht.begin();
  
/////////////////////////////////////////////////////////////////////////////////////////////////////////  
  SERIAL_OUT.begin(115200);

//ENCODER
/////////////////////////////////////////////////////////////////////////////////////////////////////////
   pinMode (encoder0PinA,INPUT);
   pinMode (encoder0PinB,INPUT);
   attachInterrupt(digitalPinToInterrupt(encoder0PinA), encoder, CHANGE);
   attachInterrupt(digitalPinToInterrupt(encoder0PinB), encoder, CHANGE);
 
//NTP
/////////////////////////////////////////////////////////////////////////////////////////////////////////
initNTP();
     
//DISPLAY
/////////////////////////////////////////////////////////////////////////////////////////////////////////
   SPI.setFrequency(40000000);
   ucg.begin(UCG_FONT_MODE_SOLID);
   ucg.setColor(0, 0, 0);
   ucg.drawBox(0, 0, ucg.getWidth(), ucg.getHeight());
   analogWrite(backLED,1000);
   ucg.setRotate90();
   delay(500);
            //SPLASH SCREEN
            ucg.setColor(153, 203, 255);    // Celeste
            ucg.setFont(ucg_font_fub35_hr);
            ucg.setPrintPos(50,100);
            ucg.print("SST WiFi");
            ucg.setFont(ucg_font_fub14_hr);
            ucg.setPrintPos(30,130);
            ucg.print("Souliss Smart Thermostat");
            ucg.setPrintPos(135,180);
            ucg.print("v0.2");
            
   delay(5000);
   ucg.setColor(0, 0, 0);                //Nero
   ucg.drawBox(0, 0, ucg.getWidth(), ucg.getHeight());
   FADE=1;
}

void loop()
{ 
    // Here we start to play
    EXECUTEFAST() {                     
        UPDATEFAST();   
        FAST_10ms() {
        if (FADE==1 and backLEDvalue<backLEDvalueHIGH){
          backLEDvalue=backLEDvalue+5;
          analogWrite(backLED,backLEDvalue);      
          }
        }
        
        FAST_110ms() {   // We process the logic and relevant input and output every 50 milliseconds
            Logic_SimpleLight(CALDAIA);
            DigOut(RELE, Souliss_T1n_Coil,CALDAIA);
            
            Souliss_Logic_T52(memory_map, TEMPERATURA, DEADBAND, &data_changed);
            Souliss_Logic_T53(memory_map, UMIDITA, DEADBAND, &data_changed);
            /////////////////////////////////////////////////////////////////////////////////////////////
            
            ucg.setColor(0, 255, 255, 255);    // Bianco
            ucg.setFontMode(UCG_FONT_MODE_SOLID);
            ucg.setPrintPos(25,52);
            ucg.setFont(ucg_font_inb21_mr);
            ucg.print("Sp");ucg.print(setpoint,1);
            ucg.setFont(ucg_font_profont11_mr);
            ucg.setPrintPos(135,36);
            ucg.print("o"); 
        //FADE
        if(FADE==0 and backLEDvalue>backLEDvalueLOW){
        backLEDvalue=backLEDvalue-5;
        analogWrite(backLED,backLEDvalue);
            } 
        FAST_210ms(){
                byte menu;
                if(digitalRead(GPIO0)==LOW){
                  Serial.println("Entro MENU'");
                  encSetpointEnable=0;
                  drawCrono(ucg);
                  menu=1;
                  while(menu==1){
                    setDay(ucg);
                    drawBoxes(ucg);
                    setBoxes(ucg);
                    delay(2000);
                    if(digitalRead(GPIO0)==LOW){
                    menu=0;
                    }
                  }
                  Serial.println("Esco MENU'");
                  clearScreen(ucg);
                  encSetpointEnable=1;
                }
             }    
              
        // Here we handle here the communication with Android
        FAST_PeerComms();
                                    
    }
  }  
       EXECUTESLOW()
  {
    UPDATESLOW();

      SLOW_50s(){
        //NTP
        ////////////////////////////////////////////////////////////////////////////
            String Time = "";
            String Date = "";
            Time = digitalClockDisplay();
            Date = digitalDataDisplay();
            ucg.setFont(ucg_font_inr19_mf);
            ucg.setColor(0, 255, 255, 255);       // Bianco
            ucg.setPrintPos(160,24);
            ucg.print(Date);
            ucg.setFont(ucg_font_inb21_mr);
            ucg.setPrintPos(228,52);
            ucg.print(Time);
            
        ////////////////////////////////////////////////////////////////////////////
            
            ucg.setColor(0, 255, 255, 255);    // Bianco
            ucg.drawCircle(85, 120, 119, UCG_DRAW_ALL);
            ucg.drawCircle(85, 119, 119, UCG_DRAW_ALL);
            ucg.drawCircle(85, 120, 118, UCG_DRAW_ALL);
            ucg.drawCircle(85, 119, 118, UCG_DRAW_ALL);
            ucg.drawCircle(85, 120, 117, UCG_DRAW_ALL);
            ucg.drawCircle(85, 119, 117, UCG_DRAW_ALL);
            ucg.drawCircle(85, 120, 116, UCG_DRAW_ALL);
            ucg.drawCircle(85, 119, 116, UCG_DRAW_ALL);
            ucg.drawCircle(85, 120, 115, UCG_DRAW_ALL);
            ucg.drawCircle(85, 119, 115, UCG_DRAW_ALL);
            ucg.drawCircle(85, 120, 114, UCG_DRAW_ALL);
            ucg.drawCircle(85, 119, 114, UCG_DRAW_ALL);
            ucg.drawCircle(85, 120, 113, UCG_DRAW_ALL);
            ucg.drawCircle(85, 119, 113, UCG_DRAW_ALL);
            ucg.drawCircle(85, 120, 112, UCG_DRAW_ALL);
            ucg.drawCircle(85, 119, 112, UCG_DRAW_ALL);
            ucg.drawCircle(85, 120, 111, UCG_DRAW_ALL);
            ucg.drawCircle(85, 119, 111, UCG_DRAW_ALL);
            ucg.drawCircle(85, 120, 110, UCG_DRAW_ALL);
            ucg.drawCircle(85, 119, 110, UCG_DRAW_ALL);
        
        temperature = dht.readTemperature(); 
        int temp = (int) temperature;       
        int diff=dopovirgola(temperature);
        Serial.print("DHT: ");Serial.println(temperature,2);   
        /*Serial.print("TEMP: ");Serial.println(temp);     
        Serial.print("DIFF: ");Serial.println(diff);
        */
        humidity = dht.readHumidity();
        Souliss_ImportAnalog(memory_map, TEMPERATURA, &temperature);
        Souliss_ImportAnalog(memory_map, UMIDITA, &humidity);

            ucg.setColor(0, 0, 0);                //Nero
            ucg.drawCircle(85, 120, 119, UCG_DRAW_ALL);
            ucg.drawCircle(85, 119, 119, UCG_DRAW_ALL);
            ucg.drawCircle(85, 120, 118, UCG_DRAW_ALL);
            ucg.drawCircle(85, 119, 118, UCG_DRAW_ALL);
            ucg.drawCircle(85, 120, 117, UCG_DRAW_ALL);
            ucg.drawCircle(85, 119, 117, UCG_DRAW_ALL);
            ucg.drawCircle(85, 120, 116, UCG_DRAW_ALL);
            ucg.drawCircle(85, 119, 116, UCG_DRAW_ALL);
            ucg.drawCircle(85, 120, 115, UCG_DRAW_ALL);
            ucg.drawCircle(85, 119, 115, UCG_DRAW_ALL);
            ucg.drawCircle(85, 120, 114, UCG_DRAW_ALL);
            ucg.drawCircle(85, 119, 114, UCG_DRAW_ALL);
            ucg.drawCircle(85, 120, 113, UCG_DRAW_ALL);
            ucg.drawCircle(85, 119, 113, UCG_DRAW_ALL);
            ucg.drawCircle(85, 120, 112, UCG_DRAW_ALL);
            ucg.drawCircle(85, 119, 112, UCG_DRAW_ALL);
            ucg.drawCircle(85, 120, 111, UCG_DRAW_ALL);
            ucg.drawCircle(85, 119, 111, UCG_DRAW_ALL);
            ucg.drawCircle(85, 120, 110, UCG_DRAW_ALL);
            ucg.drawCircle(85, 119, 110, UCG_DRAW_ALL);
            
            //Temperatura
            //ucg.setColor(111, 0, 255);         // Blu Elettrico
            //ucg.setColor(0, 255, 255, 255);    // Bianco
            ucg.setColor(102, 255, 0);           // Verde Chiaro
            ucg.setFontMode(UCG_FONT_MODE_SOLID);
            ucg.setPrintPos(-4,80);
            ucg.setScale2x2();
            ucg.setFont(ucg_font_inb46_mr);
            ucg.print(temp);
            ucg.undoScale();
            ucg.setFont(ucg_font_inb46_mr);
            ucg.setPrintPos(147,160);
            ucg.print(diff);
            ucg.drawDisc(143, 156, 3, UCG_DRAW_ALL);
            ucg.drawDisc(187, 116, 3, UCG_DRAW_ALL);


            //Umidità
            ucg.setColor(30, 144, 255);    // Blu Dodger
            ucg.setFontMode(UCG_FONT_MODE_SOLID);
            ucg.setPrintPos(24,209);
            ucg.setFont(ucg_font_inb21_mr);
            ucg.print("Hr");ucg.print(humidity,1);
            ucg.setFont(ucg_font_9x18_mf);             
            ucg.setPrintPos(135,209);
            ucg.print("%");
            //ucg.setFont(ucg_font_profont11_mr);
            //ucg.setPrintPos(60,190);
            ucg.undoScale();
            //ucg.print("UMIDITA'");
            
            //TEST
            ucg.setColor(102, 255, 0);    // Verde Chiaro
            ucg.drawCircle(85, 120, 119, UCG_DRAW_ALL);
            ucg.drawCircle(85, 119, 119, UCG_DRAW_ALL);
            ucg.drawCircle(85, 120, 118, UCG_DRAW_ALL);
            ucg.drawCircle(85, 119, 118, UCG_DRAW_ALL);
            ucg.drawCircle(85, 120, 117, UCG_DRAW_ALL);
            ucg.drawCircle(85, 119, 117, UCG_DRAW_ALL);
            ucg.drawCircle(85, 120, 116, UCG_DRAW_ALL);
            ucg.drawCircle(85, 119, 116, UCG_DRAW_ALL);
            ucg.drawCircle(85, 120, 115, UCG_DRAW_ALL);
            ucg.drawCircle(85, 119, 115, UCG_DRAW_ALL);
            ucg.drawCircle(85, 120, 114, UCG_DRAW_ALL);
            ucg.drawCircle(85, 119, 114, UCG_DRAW_ALL);
            ucg.drawCircle(85, 120, 113, UCG_DRAW_ALL);
            ucg.drawCircle(85, 119, 113, UCG_DRAW_ALL);
            ucg.drawCircle(85, 120, 112, UCG_DRAW_ALL);
            ucg.drawCircle(85, 119, 112, UCG_DRAW_ALL);
            ucg.drawCircle(85, 120, 111, UCG_DRAW_ALL);
            ucg.drawCircle(85, 119, 111, UCG_DRAW_ALL);
            ucg.drawCircle(85, 120, 110, UCG_DRAW_ALL);
            ucg.drawCircle(85, 119, 110, UCG_DRAW_ALL);
        //CALCOLO ANDAMENTO
        ///////////////////////////////////////////////////////////////////////////
        deltaT=temperature-pretemperature;
        Serial.print("DELTAT ");Serial.println(deltaT,DEC);
        if(temperature > pretemperature && deltaT || 0){
            ucg.setColor(255, 0, 0);              // Rosso
            ucg.drawTriangle(0,0, 0,31, 10,22);
            ucg.setColor(0, 0, 0);                //Nero
            ucg.drawTriangle(0,240, 0,209, 10,218);                
        }else if (deltaT == 0){
            ucg.setColor(0, 0, 0);                //Nero
            ucg.drawTriangle(0,240, 0,209, 10,218);
            ucg.setColor(0, 0, 0);                //Nero
            ucg.drawTriangle(0,0, 0,31, 10,22);  
        }
        else{
            ucg.setColor(65, 105, 225);           // Blu Reale
            ucg.drawTriangle(0,240, 0,209, 10,218);     
            ucg.setColor(0, 0, 0);                //Nero
            ucg.drawTriangle(0,0, 0,31, 10,22);        
        }
        ///////////////////////////////////////////////////////////////////////////
        
        if(temperature<setpoint-hyst){
          //Souliss_Input(memory_map, CALDAIA) = Souliss_T1n_OnCmd;
          mInput(CALDAIA) = Souliss_T1n_OnCmd;
          }
        if(temperature>setpoint+hyst){
          mInput(CALDAIA) = Souliss_T1n_OffCmd;
          }        
        pretemperature=temperature;
        FADE=0;    
        }
    }   
} 


int dopovirgola(const float v)
{
  float vX10 = v * 1;
  //Serial.print("vX10: "); Serial.println(vX10);
  int vInt = (int) vX10;
  //Serial.print("vInt: "); Serial.println(vInt);
  int result;
  float diff = abs(vX10 - vInt);
  //Serial.print("diff: "); Serial.println(diff);
  return result = diff * 10;
}
         
void encoder(){
if(encSetpointEnable==1){ 
  int MSB = digitalRead(encoder0PinA); //MSB = most significant bit
  int LSB = digitalRead(encoder0PinB); //LSB = least significant bit
 
  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (encoder0PinALast << 2) | encoded; //adding it to the previous encoded value
 
  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoder0Pos --;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoder0Pos ++;
 
  encoder0PinALast = encoded; //store this value for next time
  setpoint=encoder0Pos/10.0; 
  FADE=1;
  }
}


