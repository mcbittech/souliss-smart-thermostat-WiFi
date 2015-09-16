/**************************************************************************
   Souliss - Web Configuration

    This example demonstrate a complete web configuration of ESP8266 based
	nodes, the node starts as access point and allow though a web interface
	the configuration of IP and Souliss parameters.

	This example is only supported on ESP8266.
***************************************************************************/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <WiFiUdp.h>
#include <DHT.h>

// Configure the Souliss framework
#include "bconf/MCU_ESP8266.h"              // Load the code directly on the ESP8266
#include "conf/RuntimeGateway.h"            // This node is a Peer and can became a Gateway at runtime
#include "conf/DynamicAddressing.h"         // Use dynamically assigned addresses
#include "conf/WEBCONFinterface.h"          // Enable the WebConfig interface

#include "Souliss.h"

#include "t_encoder.h"
#include "t_constants.h"
#include "display.h"

//*************************************************************************
//*************************************************************************
DHT dht(DHTPIN, DHTTYPE);
float temperature = 0;
float humidity = 0;
float setpoint = 0;
float setpoint_prec = 0;

//DISPLAY
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <SPI.h>
#include <Arduino.h>
#include <Souliss_SmartT_ILI9341_GFX_Library.h>
#include <Souliss_SmartT_ILI9341.h>

// Use hardware SPI
/////////////////////////////////////////////////////////////////////////////////////////////////////////
Souliss_SmartT_ILI9341 tft = Souliss_SmartT_ILI9341(TFT_CS, TFT_DC);


bool dbackLED = 0;
//*************************************************************************
//*************************************************************************


void setup()
{
  SERIAL_OUT.begin(115200);
  Initialize();

  // Read the IP configuration from the EEPROM, if not available start
  // the node as access point
  if (!ReadIPConfiguration())
  {
    // Start the node as access point with a configuration WebServer
    SetAccessPoint();
    startWebServer();

    // We have nothing more than the WebServer for the configuration
    // to run, once configured the node will quit this.
    while (1)
    {
      yield();
      runWebServer();
    }

  }

  if (IsRuntimeGateway())
  {
    // Connect to the WiFi network and get an address from DHCP
    SetAsGateway(myvNet_dhcp);       // Set this node as gateway for SoulissApp
    SetAddressingServer();
  }
  else
  {
    // This board request an address to the gateway at runtime, no need
    // to configure any parameter here.
    SetDynamicAddressing();
    GetAddress();
  }

  //*************************************************************************
  //*************************************************************************
  // Set the typical to use in slot 0
  Set_Thermostat(SLOT_THERMOSTAT);
  Set_T52(SLOT_TEMPERATURE);
  Set_T53(SLOT_HUMIDITY);
  // Define output pins
  pinMode(RELE, OUTPUT);    // Heater
  dht.begin();
  tft.begin();

  //ENCODER
  /////////////////////////////////////////////////////////////////////////////////////////////////////////
  pinMode (ENCODER_PIN_A, INPUT);
  pinMode (ENCODER_PIN_B, INPUT);
  //*************************************************************************
  //*************************************************************************

}

void loop()
{
  EXECUTEFAST() {
    UPDATEFAST();

    FAST_10ms() {
      tickEncoder();
    }

    FAST_30ms() {
      //set point attuale
      setpoint = Souliss_SinglePrecisionFloating(memory_map + MaCaco_OUT_s + SLOT_THERMOSTAT + 3);

      //Stampa il setpoint solo se il valore dell'encoder è diverso da quello impostato nel T31
      if (arrotonda(getEncoderValue()) != arrotonda(setpoint)) {
        display_print_setpoint(tft, getEncoderValue());
        setpoint = getEncoderValue();
        //memorizza il setpoint nel T31
        SERIAL_OUT.print("getEncoderValue arrotondato: "); SERIAL_OUT.println(arrotonda(getEncoderValue()));
        SERIAL_OUT.print("setpoint Souliss arrotondato: "); SERIAL_OUT.println(arrotonda(setpoint));
          
        Souliss_HalfPrecisionFloating((memory_map + MaCaco_OUT_s + SLOT_THERMOSTAT + 3), &setpoint);
      }

 setpoint = floor(setpoint);
    }

    FAST_50ms() {   // We process the logic and relevant input and output every 50 milliseconds
      //*************************************************************************
      //*************************************************************************
      Logic_Thermostat(SLOT_THERMOSTAT);
      // Start the heater and the fans
      nDigOut(RELE, Souliss_T3n_HeatingOn, SLOT_THERMOSTAT);    // Heater
      //*************************************************************************
      //*************************************************************************
    }

    FAST_510ms() {
      // Compare the acquired input with the stored one, send the new value to the
      // user interface if the difference is greater than the deadband
      Logic_T52(SLOT_TEMPERATURE);
      Logic_T53(SLOT_HUMIDITY);

      //   SERIAL_OUT.print("Encoder setpoint: "); SERIAL_OUT.println(getEncoderValue());
    }

    // Run communication as Gateway or Peer
    if (IsRuntimeGateway())
      FAST_GatewayComms();
    else
      FAST_PeerComms();
  }

  EXECUTESLOW() {
    UPDATESLOW();

    SLOW_10s() {
      //*************************************************************************
      //*************************************************************************

      // Read temperature value from DHT sensor and convert from single-precision to half-precision
      temperature = dht.readTemperature();
      ImportAnalog(SLOT_TEMPERATURE, &temperature);

      // Read humidity value from DHT sensor and convert from single-precision to half-precision
      humidity = dht.readHumidity();
      ImportAnalog(SLOT_HUMIDITY, &humidity);

      //Import temperature into T31 Thermostat
      ImportAnalog(SLOT_THERMOSTAT + 1, &temperature);

      setpoint = Souliss_SinglePrecisionFloating(memory_map + MaCaco_OUT_s + SLOT_THERMOSTAT + 3);

      SERIAL_OUT.print("Temperature: "); SERIAL_OUT.println(temperature);
      SERIAL_OUT.print("Humidity: "); SERIAL_OUT.println(humidity);
      SERIAL_OUT.print("Set point: "); SERIAL_OUT.println(setpoint);


      //*************************************************************************
      //*************************************************************************
    }

    // If running as Peer
    if (!IsRuntimeGateway())
      SLOW_PeerJoin();
  }
}


float arrotonda(const float v)
{
  return (int(v*10))/10; //100=10^2 per 2 cifre decimali 
}


