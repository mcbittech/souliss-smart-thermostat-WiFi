#define  SOULISS_DEBUG_INSKETCH
#define SOULISS_DEBUG       0
#define  MaCaco_DEBUG_INSKETCH
#define MaCaco_DEBUG        0

#define VNET_DEBUG_INSKETCH
#define VNET_DEBUG          0

/**************************************************************************
  Wi-Fi Smart Thermostat based on Souliss IoT Framework
    -Olimex ESP8266-EVB
    -ILI9341 with SPI connection, via UEXT connector
    -Rotary Encoder with pushbutton & status LED
    -DHT22 Temperature & Humidity Sensor

  This example is only supported on ESP8266.
  Developed by mcbittech & fazioa
***************************************************************************/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>
#include <WiFiUdp.h>
#include <DHT.h>
#include <ESP8266HTTPUpdateServer.h>

// Configure the Souliss framework
#include "bconf/MCU_ESP8266.h"              /** Load the code directly on the ESP8266 */
#include "preferences.h"
#include "OTAWebUpdater.h"

#if(DYNAMIC_CONNECTION)
#include "conf/RuntimeGateway.h"            // This node is a Peer and can became a Gateway at runtime
#include "conf/DynamicAddressing.h"         // Use dynamically assigned addresses
#include "conf/WEBCONFinterface.h"          // Enable the WebConfig interface
#include "connection_dynamic.h"
#else
#include "conf/IPBroadcast.h"
#include "connection_static.h"
#define USEEEPROM_INSKETCH
#define USEEEPROM             1
#endif

#include "Souliss.h"
#include "encoder.h"
#include "constants.h"
#include "display.h"
#include "display2.h"
#include "language.h"
#include "ntp.h"
#include <Time.h>
#include <MenuSystem.h>
#include "menu.h"
#include "crono.h"
#include "read_save.h"
#include "topics.h"
//*************************************************************************
//*************************************************************************

DHT dht(DHTPIN, DHTTYPE);
float temperature = 0;
float humidity = 0;
float setpoint = 0;
float encoderValue_prec = 0;

//DISPLAY
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <SPI.h>
#include <Arduino.h>
#include "Ucglib.h"


int backLEDvalue = 0;
int backLEDvalueHIGH = BRIGHT_MAX;
int backLEDvalueLOW = BRIGHT_MIN_DEFAULT;
bool FADE = 1;


// Menu
MenuSystem* myMenu;

// Use hardware SPI
Ucglib_ILI9341_18x240x320_HWSPI ucg(/*cd=*/ 2 , /*cs=*/ 15);

// Setup the libraries for Over The Air Update
OTA_WebUpdater_Setup()  ;

void setSoulissDataChanged() {
  if (data_changed != Souliss_TRIGGED) {
    //SERIAL_OUT.println("setSoulissDataChanged");
    data_changed = Souliss_TRIGGED;
  }
}

void set_ThermostatModeOn(U8 slot) {
  SERIAL_OUT.println("set_ThermostatModeOn");
  memory_map[MaCaco_OUT_s + slot] |= Souliss_T3n_HeatingMode | Souliss_T3n_SystemOn;
  // Trig the next change of the state
  setSoulissDataChanged();
}
void set_ThermostatOff(U8 slot) {
  SERIAL_OUT.println("set_ThermostatOff");
  //memory_map[MaCaco_IN_s + slot] = Souliss_T3n_ShutDown;
  memory_map[MaCaco_OUT_s + SLOT_THERMOSTAT] &= ~ (Souliss_T3n_SystemOn | Souliss_T3n_FanOn1 | Souliss_T3n_FanOn2 | Souliss_T3n_FanOn3 | Souliss_T3n_CoolingOn | Souliss_T3n_HeatingOn);
  setSoulissDataChanged();
}
void set_DisplayMinBright(U8 slot, U8 val) {
  memory_map[MaCaco_OUT_s + slot + 1] = val;
  // Trig the next change of the state

  setSoulissDataChanged();
}

void encoderFunction() {
  encoder();
}

boolean getSoulissSystemState() {
  return memory_map[MaCaco_OUT_s + SLOT_THERMOSTAT] & Souliss_T3n_SystemOn;
}
void getTemp() {
  // Read temperature value from DHT sensor and convert from single-precision to half-precision
  temperature = dht.readTemperature();
  //Import temperature into T31 Thermostat
  ImportAnalog(SLOT_THERMOSTAT + 1, &temperature);
  ImportAnalog(SLOT_TEMPERATURE, &temperature);

  // Read humidity value from DHT sensor and convert from single-precision to half-precision
  humidity = dht.readHumidity();
  ImportAnalog(SLOT_HUMIDITY, &humidity);

  SERIAL_OUT.print("acquisizione Temperature: "); SERIAL_OUT.println(temperature);
  SERIAL_OUT.print("acquisizione Humidity: "); SERIAL_OUT.println(humidity);
}
void initScreen() {
  ucg.clearScreen();
  SERIAL_OUT.println("clearScreen ok");
  if (getLayout1()) {
    SERIAL_OUT.println("HomeScreen Layout 1");

    display_layout1_HomeScreen(ucg, temperature, humidity, setpoint, getSoulissSystemState());
    getTemp();
  }
  else if (getLayout2()) {
    SERIAL_OUT.println("HomeScreen Layout 2");
    getTemp();
    display_layout2_HomeScreen(ucg, temperature, humidity, setpoint);
    display_layout2_print_circle_white(ucg);
    display_layout2_print_datetime(ucg);
    display_layout2_print_circle_black(ucg);
    yield();
    display_layout2_print_circle_green(ucg);
  }
}
void setSetpoint(float setpoint) {
  //SERIAL_OUT.print("Away: ");SERIAL_OUT.println(memory_map[MaCaco_OUT_s + SLOT_AWAY]);
  if (memory_map[MaCaco_OUT_s + SLOT_AWAY]) {
    //is Away

  } else {
    //is not Away
  }
  Souliss_HalfPrecisionFloating((memory_map + MaCaco_OUT_s + SLOT_THERMOSTAT + 3), &setpoint);
}
void bright(int lum) {
  int val = ((float)lum / 100) * 1023;
  if (val > 1023) val = 1023;
  if (val < 0) val = 0;
  analogWrite(BACKLED, val);
}

void setup()
{

  SERIAL_OUT.begin(115200);

  // EEPROM
  /////////////////////////////////////////////////////////////////////////////////////////////////////////
  Store_Init();

  if (read_eeprom_byte(1) == 1) {
    ReadAllSettingsFromEEPROM();
    ReadCronoMatrix();
    backLEDvalueLOW = getDisplayBright();
  } else {
    ReadAllSettingsFromPreferences();
    ReadCronoMatrix();
  }

  //DISPLAY INIT
  /////////////////////////////////////////////////////////////////////////////////////////////////////////
  ucg.begin(UCG_FONT_MODE_SOLID);

  //SPI Frequency
  SPI.setFrequency(80000000);

  ucg.setColor(0, 0, 0);
  ucg.setRotate90();
  //BACK LED
  /////////////////////////////////////////////////////////////////////////////////////////////////////////
  digitalWrite(BACKLED, HIGH);
  pinMode(BACKLED, OUTPUT);                     // Background Display LED

  display_print_splash_screen(ucg);
  Initialize();

#if(DYNAMIC_CONNECTION)
  DYNAMIC_CONNECTION_Init();
#else
#if(DHCP_OPTION)
  STATIC_CONNECTION_Init_DHCP();
#else
  STATIC_CONNECTION_Init_STATICIP();
#endif
#endif


  //*************************************************************************
  //*************************************************************************
  Set_T52(SLOT_TEMPERATURE);
  Set_T53(SLOT_HUMIDITY);
  Set_T19(SLOT_BRIGHT_DISPLAY);
  Set_T11(SLOT_AWAY);

  //set default mode
  Set_Thermostat(SLOT_THERMOSTAT);
  set_ThermostatModeOn(SLOT_THERMOSTAT);
  set_DisplayMinBright(SLOT_BRIGHT_DISPLAY, backLEDvalueLOW);

  // Define output pins
  pinMode(RELE, OUTPUT);    // Heater
  dht.begin();

  //ENCODER
  /////////////////////////////////////////////////////////////////////////////////////////////////////////
  pinMode (ENCODER_PIN_A, INPUT_PULLUP);
  pinMode (ENCODER_PIN_B, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_A), encoderFunction, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_B), encoderFunction, CHANGE);
  // SWITCH ENCODER
  digitalWrite(BACKLED, HIGH);
  pinMode(ENCODER_SWITCH, INPUT);

  //NTP
  /////////////////////////////////////////////////////////////////////////////////////////////////////////
  initNTP();
  delay(1000);
  //*************************************************************************
  //*************************************************************************

  //MENU
  /////////////////////////////////////////////////////////////////////////////////////////////////////////
  initMenu();
  myMenu = getMenu();

  // Init the OTA
  OTA_WebUpdater_Init();

  // Init HomeScreen
  initScreen();
}


uint8_t mypayload_len = 0;
uint8_t mypayload[10];
void loop()
{
  // Look for a new sketch to update over the air
  OTA_WebUpdater_Process();
  EXECUTEFAST() {
    UPDATEFAST();

    FAST_50ms() {
      //set point attuale
      setpoint = Souliss_SinglePrecisionFloating(memory_map + MaCaco_OUT_s + SLOT_THERMOSTAT + 3);
      //Stampa il setpoint solo se il valore dell'encoder è diverso da quello impostato nel T31
      if (!getMenuEnabled()) {
        if (arrotonda(getEncoderValue()) != arrotonda(encoderValue_prec)) {
          FADE = 1;
          //TICK TIMER
          timerDisplay_setpoint_Tick();
          //SETPOINT PAGE ////////////////////////////////////////////////////////////////

          if (getLayout1()) {
            SERIAL_OUT.println("display_setpointPage - layout 1");
            display_layout1_background(ucg, arrotonda(getEncoderValue()) - arrotonda(setpoint));
            display_layout1_setpointPage(ucg, getEncoderValue(), Souliss_SinglePrecisionFloating(memory_map + MaCaco_OUT_s + SLOT_THERMOSTAT + 1), humidity, getSoulissSystemState() );
          }
          else if (getLayout2()) {
            SERIAL_OUT.println("display_setpointPage - layout 2");
            display_layout2_Setpoint(ucg, getEncoderValue(),getSoulissSystemState());
          }
        }

        encoderValue_prec = getEncoderValue();
      } else {
        //Bright high if menu enabled
        FADE = 1;
        //Menu Command Section
        if (getEncoderValue() != encoderValue_prec)
        {
          if (getEncoderValue() > encoderValue_prec) {
            //Menu DOWN
            myMenu->next();
          } else {
            //Menu UP
            myMenu->prev();
          }
          printMenu(ucg);
          encoderValue_prec = getEncoderValue();
        }
      }

      Logic_T19(SLOT_BRIGHT_DISPLAY);
      Logic_T11(SLOT_AWAY);
    }

    FAST_110ms() {
      if (!getMenuEnabled()) {
        if (timerDisplay_setpoint()) {
          //timeout scaduto
          display_layout1_background_black(ucg);
          setEncoderValue(setpoint);
        } else {
          //timer non scaduto. Memorizzo
          setpoint = getEncoderValue();
          //memorizza il setpoint nel T31
          setSetpoint(setpoint);

          // Trig the next change of the state
          setSoulissDataChanged();
        }
      }

      //SWITCH ENCODER
      if (!digitalRead(ENCODER_SWITCH)) {
        if (!getMenuEnabled()) {
          //IF MENU NOT ENABLED
          setEnabled(true);
          //il flag viene impostato a true (indica che il menu è attivo). Quando si esce dal menu la homescreen viene aggiornata ed il flag riportato a false
          setChanged();
          ucg.clearScreen();
        } else {
          //IF MENU ENABLED
          myMenu->select(true);

          /// CRONO
          if (getProgCrono()) {
            byte menu;
            ucg.clearScreen();
            drawCrono(ucg);
            menu = 1;
            while (menu == 1 && exitmainmenu() == 0) {
              setDay(ucg);
              drawBoxes(ucg);
              setBoxes(ucg);
            }
          ucg.clearScreen();
          menu = 0;
          }
        }
        SERIAL_OUT.println("print Menu");
        printMenu(ucg);
      }

      //FADE
      if (FADE == 0) {
        //Raggiunge il livello di luminosità minima, che può essere variata anche da SoulissApp
        if ( backLEDvalue != backLEDvalueLOW) {
          if ( backLEDvalue > backLEDvalueLOW) {
            backLEDvalue -= BRIGHT_STEP_FADE_OUT;
          } else {
            backLEDvalue += BRIGHT_STEP_FADE_OUT;
          }
          bright(backLEDvalue);
        }
      } else  if (FADE == 1 && backLEDvalue < backLEDvalueHIGH) {
        backLEDvalue +=  BRIGHT_STEP_FADE_IN;
        bright(backLEDvalue);
      }
    }

    FAST_210ms() {   // We process the logic and relevant input and output
      //*************************************************************************
      //*************************************************************************
      Logic_Thermostat(SLOT_THERMOSTAT);
      // Start the heater and the fans
      nDigOut(RELE, Souliss_T3n_HeatingOn, SLOT_THERMOSTAT);    // Heater

      //if menu disabled and nothing changed
      if (!getMenuEnabled() && !getSystemChanged()) {
        if (getLocalSystem() != getSoulissSystemState())
          setSystem(getSoulissSystemState());
      }

      //*************************************************************************
      //*************************************************************************
    }

    FAST_510ms() {
      // Compare the acquired input with the stored one, send the new value to the
      // user interface if the difference is greater than the deadband
      Logic_T52(SLOT_TEMPERATURE);
      Logic_T53(SLOT_HUMIDITY);

    }


    FAST_710ms() {
      //HOMESCREEN ////////////////////////////////////////////////////////////////
      ///update homescreen only if menu exit
      if (!getMenuEnabled() && getSystemChanged()) {
        //EXIT MENU - Actions
        //write min bright on T19
        memory_map[MaCaco_OUT_s + SLOT_BRIGHT_DISPLAY + 1] = getDisplayBright();
        SERIAL_OUT.print("Set Display Bright: "); SERIAL_OUT.println(memory_map[MaCaco_OUT_s + SLOT_BRIGHT_DISPLAY + 1]);

        //write system ON/OFF
        if (getLocalSystem()) {
          //ON
          SERIAL_OUT.println("Set system ON ");
          set_ThermostatModeOn(SLOT_THERMOSTAT);        // Set System On
        } else {
          //OFF
          SERIAL_OUT.println("Set system OFF ");
          set_ThermostatOff(SLOT_THERMOSTAT);
        }

        memory_map[MaCaco_IN_s + SLOT_THERMOSTAT] = Souliss_T3n_RstCmd;          // Reset
        // Trig the next change of the state

        setSoulissDataChanged();

        SERIAL_OUT.println("Init Screen");
        initScreen();

        resetSystemChanged();
      }

    }

    FAST_910ms() {
      if (timerDisplay_setpoint()) {
        //if timeout read value of T19
        backLEDvalueLOW =  memory_map[MaCaco_OUT_s + SLOT_BRIGHT_DISPLAY + 1];
        FADE = 0;
        //HOMESCREEN ////////////////////////////////////////////////////////////////
        if (!getMenuEnabled()) {
          if (getLayout1()) {
            display_layout1_HomeScreen(ucg, temperature, humidity, setpoint, getSoulissSystemState());
          } else if (getLayout2()) {
            display_layout2_Setpoint(ucg, getEncoderValue(),getSoulissSystemState());
          }
        }
      }
    }
    FAST_2110ms() {
      // Receiver
      //      SERIAL_OUT.print("Memory_map: ");
      //      for (int i=0;i<50;i++){
      //        U8  _val=memory_map+MaCaco_QUEUE_s+i;
      //         SERIAL_OUT.print(_val);SERIAL_OUT.print(" ");
      //      }
      //       SERIAL_OUT.println(" ");


      if (subscribedata(ENERGY_TOPIC, mypayload, &mypayload_len)) {
        SERIAL_OUT.print("payload: "); SERIAL_OUT.println(mypayload_len);
        for (int i = 0; i < mypayload_len; i++) {
          SERIAL_OUT.print(mypayload[i]); SERIAL_OUT.print(" ");
        }
        SERIAL_OUT.println("");
        float output;
        float32((uint16_t*) mypayload,  &output);
        SERIAL_OUT.print("Float: "); SERIAL_OUT.println(output);
      }

      //    }
      //    FAST_510ms() {
      //      if (subscribe(Cloudy)) {
      //        SERIAL_OUT.println("Cloudy detected");
      //      }
    }


#if(DYNAMIC_CONNECTION)
    DYNAMIC_CONNECTION_fast();
#else
    STATIC_CONNECTION_fast();
#endif
  }

  EXECUTESLOW() {
    UPDATESLOW();

    SLOW_50s() {
      if (!getMenuEnabled()) {
        if (getLayout1()) {
          getTemp();
          if (getCrono()) {
            Serial.println("CRONO: aggiornamento");
            setSetpoint(checkNTPcrono(ucg));
            setEncoderValue(checkNTPcrono(ucg));
            Serial.print("CRONO: setpoint: "); Serial.println(setpoint);
          }
        } else if (getLayout2()) {
          display_layout2_print_circle_white(ucg);
          getTemp();
          display_layout2_print_circle_black(ucg);
          display_layout2_HomeScreen(ucg, temperature, humidity, setpoint);
          display_layout2_print_datetime(ucg);
          if (getCrono()) {
            Serial.println("CRONO: aggiornamento");
            setSetpoint(checkNTPcrono(ucg));
            setEncoderValue(checkNTPcrono(ucg));
            Serial.print("CRONO: setpoint: "); Serial.println(setpoint);
          } else {
            ucg.setColor(0, 0, 0);       // black
            ucg.drawDisc(156, 50, 5, UCG_DRAW_ALL);
            ucg.drawDisc(165, 62, 6, UCG_DRAW_ALL);
            ucg.drawDisc(173, 77, 7, UCG_DRAW_ALL);
            ucg.drawDisc(179, 95, 8, UCG_DRAW_ALL);
          }
          yield();
          display_layout2_print_circle_green(ucg);
        }
      }
    }

    SLOW_70s() {
      if (!getMenuEnabled()) {
        if (getLayout1()) {
          //
        } else if (getLayout2()) {
          calcoloAndamento(ucg, temperature);
          display_layout2_print_datetime(ucg);
          display_layout2_print_circle_green(ucg);
        }
      }
    }

    SLOW_15m() {
      //NTP
      /////////////////////////////////////////////////////////////////////////////////////////////////////////
      yield();
      initNTP();
      yield();
    }


#if(DYNAMIC_CONNECTION==1)
    DYNAMIC_CONNECTION_slow();
#endif
  }
}


