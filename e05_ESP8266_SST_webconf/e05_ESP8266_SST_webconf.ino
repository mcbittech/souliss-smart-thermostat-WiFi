/**************************************************************************
  Wi-Fi Smart Thermostat based on Souliss IoT Framework
    -Olimex ESP8266-EVB
    -ILI9341 with SPI connection, via UEXT connector
    -Rotary Encoder with pushbutton & status LED
    -DHT22 Temperature & Humidity Sensor

  This example is only supported on ESP8266.
  Developed by mcbittech & fazioa
***************************************************************************/
// Let the IDE point to the Souliss framework
#include "SoulissFramework.h"

#include <ESP8266WiFi.h>
//#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>
#include "FS.h" //SPIFFS
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <DHT.h>

// Configure the Souliss framework
#include "bconf/MCU_ESP8266.h"              /** Load the code directly on the ESP8266 */
#include "preferences.h"
#include "multiClick.h"

#if(DYNAMIC_CONNECTION)
#include "conf/RuntimeGateway.h"            // This node is a Peer and can became a Gateway at runtime
#include "conf/DynamicAddressing.h"         // Use dynamically assigned addresses
#include "conf/WEBCONFinterface.h"          // Enable the WebConfig interface
#include "connection_dynamic.h"
#else
#include "conf/IPBroadcast.h"
#include "connection_static.h"
#endif

#define USEEEPROM_INSKETCH
#define USEEEPROM             1


#include "Souliss.h"
#include "encoder.h"
#include "constants.h"
#include "display.h"
#include "display2.h"
#include "displayTopics.h"
#include "language.h"
#include "ntp.h"
#include <TimeLib.h>
#include <MenuSystem.h>
#include "menu.h"
#include "crono.h"
#include "read_save.h"
#include "topics.h"
#include "pagesStruct.h"
//*************************************************************************
//*************************************************************************
Page SSTPage;

DHT dht(DHTPIN, DHTTYPE);
float temperature = 0;
float humidity = 0;
float fVal = 0;
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
uint8_t mypayload_len = 0;
uint8_t mypayload[2];
float fTopic_C1_Output;
float fTopic_C2_Output;
float fTopic_C3_Output;
float fTopic_C4_Output;
float fTopic_C5_Output;
float fTopic_C6_Output;

boolean bChildLock = false;

// Menu
MenuSystem* myMenu;

// Use hardware SPI
Ucglib_ILI9341_18x240x320_HWSPI ucg(/*cd=*/ 2 , /*cs=*/ 15);



void subscribeTopics() {
  if (subscribedata(TOPIC1, mypayload, &mypayload_len)) {
    float32((uint16_t*) mypayload,  &fTopic_C1_Output);
    SERIAL_OUT.print("TOPIC1: "); SERIAL_OUT.println(fTopic_C1_Output);
  } else if (subscribedata(TOPIC2, mypayload, &mypayload_len)) {
    float32((uint16_t*) mypayload,  &fTopic_C2_Output);
    SERIAL_OUT.print("TOPIC2: "); SERIAL_OUT.println(fTopic_C2_Output);
  } else if (subscribedata(TOPIC3, mypayload, &mypayload_len)) {
    float32((uint16_t*) mypayload,  &fTopic_C3_Output);
    SERIAL_OUT.print("TOPIC3: "); SERIAL_OUT.println(fTopic_C3_Output);
  } else if (subscribedata(TOPIC4, mypayload, &mypayload_len)) {
    float32((uint16_t*) mypayload,  &fTopic_C4_Output);
    SERIAL_OUT.print("TOPIC4: "); SERIAL_OUT.println(fTopic_C4_Output);
  } else if (subscribedata(TOPIC5, mypayload, &mypayload_len)) {
    float32((uint16_t*) mypayload,  &fTopic_C5_Output);
    SERIAL_OUT.print("TOPIC5: "); SERIAL_OUT.println(fTopic_C5_Output);
  } else if (subscribedata(TOPIC6, mypayload, &mypayload_len)) {
    float32((uint16_t*) mypayload,  &fTopic_C6_Output);
    SERIAL_OUT.print("TOPIC6: "); SERIAL_OUT.println(fTopic_C6_Output);
  }
}


void setSoulissDataChanged() {
  if (data_changed != Souliss_TRIGGED) {

    data_changed = Souliss_TRIGGED;
  }
}

void set_ThermostatModeOn(U8 slot) {
  SERIAL_OUT.println("set_ThermostatModeOn");
  memory_map[MaCaco_OUT_s + slot] |= Souliss_T3n_SystemOn;
  memory_map[MaCaco_OUT_s + slot] &= ~Souliss_T3n_HeatingMode;

  // Trig the next change of the state
  setSoulissDataChanged();
}
void set_ThermostatOff(U8 slot) {
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

boolean T_or_H_isNan = false;
boolean bFlagBegin = false;
void getTemp() {
  // Read temperature value from DHT sensor and convert from single-precision to half-precision
  fVal = dht.readTemperature();
  SERIAL_OUT.print("acquisizione Temperature: "); SERIAL_OUT.println(fVal);
  if (!isnan(fVal)) {
    temperature = fVal; //memorizza temperatura se non è Not A Number
    //Import temperature into T31 Thermostat
    ImportAnalog(SLOT_THERMOSTAT + 1, &temperature);
    ImportAnalog(SLOT_TEMPERATURE, &temperature);
  } else {
    bFlagBegin = true;
  }

  // Read humidity value from DHT sensor and convert from single-precision to half-precision
  fVal = dht.readHumidity();
  SERIAL_OUT.print("acquisizione Humidity: "); SERIAL_OUT.println(fVal);
  if (!isnan(fVal)) {
    humidity = fVal;
    ImportAnalog(SLOT_HUMIDITY, &humidity);
  } else {
    bFlagBegin = true;
  }

  if ( bFlagBegin) {
    //if DHT fail then try to reinit
    dht.begin();
    SERIAL_OUT.println(" dht.begin();");
  }
}

void initScreen() {
  ucg.clearScreen();
  SERIAL_OUT.println("clearScreen ok");
  if (getLayout1()) {
    SERIAL_OUT.println("HomeScreen Layout 1");

    display_layout1_HomeScreen(ucg, temperature, humidity, setpoint, getSoulissSystemState(), bChildLock);
    getTemp();
  }
  else if (getLayout2()) {
    SERIAL_OUT.println("HomeScreen Layout 2");
    getTemp();
    display_layout2_HomeScreen(ucg, temperature, humidity, setpoint);
    display_layout2_print_circle_white(ucg);
    display_layout2_print_datetime(ucg);
    if (ACTIVATETOPICSPAGE == 1) {
      displayTopicsHomePageLayout2(ucg, fTopic_C1_Output, fTopic_C2_Output, fTopic_C3_Output, fTopic_C4_Output, fTopic_C5_Output, fTopic_C6_Output);
    }
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

  //SPIFFS
  /////////////////////////////////////////////////////////////////////////////////////////////////////////
  SPIFFS.begin();
  File  sst_spiffs_verifica = SPIFFS.open("/sst_settings.json", "r");
  if (!sst_spiffs_verifica) {
    Serial.println(" ");
    Serial.println("Non riesco a leggere sst_settings.json! formatto la SPIFFS...");
    SPIFFS.format();
    Serial.println("Spiffs formatted");
    ReadAllSettingsFromPreferences();
    ReadCronoMatrixSPIFFS();
  }
  else
  {
    ReadAllSettingsFromSPIFFS();
    ReadCronoMatrixSPIFFS();
    //ReadCronoMatrix();
    backLEDvalueLOW = getDisplayBright();
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
  // Set Hostname.
  String hostname(HOSTNAME);
  hostname += String(ESP.getChipId(), HEX);
  SERIAL_OUT.print("set OTA hostname: ");SERIAL_OUT.println(hostname);
  ArduinoOTA.setHostname((const char *)hostname.c_str());
  ArduinoOTA.begin();

  // Init HomeScreen
  initScreen();
}

void loop()
{
  EXECUTEFAST() {
    UPDATEFAST();

    switch (SSTPage.actualPage) {
      case PAGE_MENU :
        if (getMenuEnabled() && !bChildLock) {
          //Bright high if menu enabled
          FADE = 1;
          //Menu Command Section
          if (getEncoderValue() != encoderValue_prec)
          {
            if (getEncoderValue() > encoderValue_prec) {
              //Menu DOWN
              myMenu->next();
              SERIAL_OUT.println("Menu Down");
            } else {
              //Menu UP
              myMenu->prev();
              SERIAL_OUT.println("Menu Up");
            }
            printMenuMove(ucg);
            encoderValue_prec = getEncoderValue();
          }
        }
        if (getMenuEnabled() && !digitalRead(ENCODER_SWITCH)) {
          //IF MENU ENABLED
          myMenu->select(true);
          ucg.clearScreen();
          printMenu(ucg);
        }

    }

    SHIFT_50ms(0) {
      //set point attuale
      setpoint = Souliss_SinglePrecisionFloating(memory_map + MaCaco_OUT_s + SLOT_THERMOSTAT + 3);
      //Stampa il setpoint solo se il valore dell'encoder è diverso da quello impostato nel T31
      switch (SSTPage.actualPage) {
        case PAGE_MENU :
          if (!getMenuEnabled()) {
            SSTPage.actualPage = PAGE_HOME;
            initScreen();
            setUIChanged();
          }
          break;
        case PAGE_CRONO :
          break;
        default:
          if (arrotonda(getEncoderValue()) != arrotonda(encoderValue_prec) && !bChildLock) {
            FADE = 1;
            //TICK TIMER
            timerDisplay_setpoint_Tick();
            //SETPOINT PAGE ////////////////////////////////////////////////////////////////

            if (getLayout1()) {
              SERIAL_OUT.println("display_setpointPage - layout 1");
              display_layout1_background(ucg, arrotonda(getEncoderValue()) - arrotonda(setpoint));
              display_layout1_setpointPage(ucg, getEncoderValue(), Souliss_SinglePrecisionFloating(memory_map + MaCaco_OUT_s + SLOT_THERMOSTAT + 1), humidity, getSoulissSystemState());
            }
            else if (getLayout2()) {
              SERIAL_OUT.println("display_setpointPage - layout 2");
              display_layout2_Setpoint(ucg, getEncoderValue(), getSoulissSystemState());
            }
          }
          encoderValue_prec = getEncoderValue();
          break;
      }
    }
    SHIFT_50ms(3) {
      Logic_T19(SLOT_BRIGHT_DISPLAY);
      Logic_T11(SLOT_AWAY);
    }

    SHIFT_110ms(0) {
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
    }


    SHIFT_110ms(4) {
      //SWITCH ENCODER
      //Al click in base al valore attuale di SSTPage, si imposta la pagina successiva

      int b = checkButton(ENCODER_SWITCH);
      if (b == 2) SERIAL_OUT.println("Double Click");
      if (b == 3) {
        SERIAL_OUT.println("Hold");
        bChildLock = !bChildLock;
        SERIAL_OUT.print("Child Lock: "); SERIAL_OUT.println(bChildLock);
        ucg.clearScreen();
        setUIChanged();
      }
      if (b == 4) SERIAL_OUT.println("Long Hold");

      if (b == 1) {
        switch (SSTPage.actualPage) {
          case PAGE_HOME:
            if (ACTIVATETOPICSPAGE > 0) {
              SERIAL_OUT.println("from PAGE_HOME to PAGE_TOPICS1");
              SSTPage.actualPage = PAGE_TOPICS1;
              setUIChanged();
            } else {
              SERIAL_OUT.println("from PAGE_HOME to PAGE_MENU");
              SSTPage.actualPage = PAGE_MENU;
              setUIChanged();
              ucg.clearScreen();
              setMenuEnabled();
              //se system and UI changed
              setUIChanged();
              SERIAL_OUT.println("Print Menu");
              printMenu(ucg);
            }
            break;
          case PAGE_TOPICS1:
            if (TOPICSPAGESNUMBER == 1) {
              SERIAL_OUT.println("from PAGE_TOPICS1 to PAGE_MENU");
              SSTPage.actualPage = PAGE_MENU;

              setUIChanged();
              ucg.clearScreen();
              setMenuEnabled();

              SERIAL_OUT.println("Print Menu");
              printMenu(ucg);
            }
            else if (TOPICSPAGESNUMBER == 2) {
              SERIAL_OUT.println("from PAGE_TOPICS1 to PAGE_TOPICS2");
              SSTPage.actualPage = PAGE_TOPICS2;
              setUIChanged();
            }
            break;
          case PAGE_TOPICS2:
            SERIAL_OUT.println("from PAGE_TOPICS2 to PAGE_MENU");
            SSTPage.actualPage = PAGE_MENU;
            setUIChanged();
            ucg.clearScreen();
            setMenuEnabled();
            //se system and UI changed
            setUIChanged();
            SERIAL_OUT.println("Print Menu");
            printMenu(ucg);
            break;
          case PAGE_MENU:

            break;
          case PAGE_CRONO:

            break;
        }
      } else {
        //se progCrono è attivo allora passo alla pagina CRONO
        if (getProgCrono()) {
          SSTPage.actualPage = PAGE_CRONO;
          byte menu;
          SERIAL_OUT.println("Crono");
          ucg.clearScreen();
          drawCrono(ucg);
          SERIAL_OUT.println("drawCrono ok");
          menu = 1;
          //save encoder value before crono programmation
          setpoint = getEncoderValue();
          while (menu == 1 && exitmainmenu() == 0) {
            setDay(ucg);
            drawBoxes(ucg);
            setBoxes(ucg);
            if (exitmainmenu())
            {
              SERIAL_OUT.println("from PAGE_CRONO to PAGE_HOME");
              SSTPage.actualPage = PAGE_HOME;
              initScreen();
              setUIChanged();
              menu = 0;
            }
          }
          //restore encoder value
          setEncoderValue(setpoint);
        }
      }
    }

    SHIFT_210ms(0) {
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

    SHIFT_210ms(2) {   // We process the logic and relevant input and output
      //*************************************************************************
      //*************************************************************************
      Logic_Thermostat(SLOT_THERMOSTAT);
      // Start the heater and the fans
      nDigOut(RELE, Souliss_T3n_HeatingOn, SLOT_THERMOSTAT);    // Heater


      // We are not handling the cooling mode, if enabled by the user, force it back
      // to disable
      if (mOutput(SLOT_THERMOSTAT) & Souliss_T3n_CoolingOn)
        mOutput(SLOT_THERMOSTAT) &= ~Souliss_T3n_CoolingOn;

      //if menu disabled and nothing changed
      if (SSTPage.actualPage != PAGE_MENU) {
        if (!getSystemChanged()) {
          if (getLocalSystem() != getSoulissSystemState())
            setSystem(getSoulissSystemState());
        }
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
      if (getSystemChanged()) {
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


    SHIFT_210ms(3) {
      if (timerDisplay_setpoint()) {
        //if timeout read value of T19
        backLEDvalueLOW =  memory_map[MaCaco_OUT_s + SLOT_BRIGHT_DISPLAY + 1];
        FADE = 0;
        //HOMESCREEN ////////////////////////////////////////////////////////////////
        switch (SSTPage.actualPage) {
          case PAGE_HOME:
            if (getLayout1()) {
              display_layout1_HomeScreen(ucg, temperature, humidity, setpoint, getSoulissSystemState(), bChildLock);
            } else if (getLayout2()) {
              display_layout2_Setpoint(ucg, getEncoderValue(), getSoulissSystemState());
            }
            break;
          case PAGE_TOPICS1:
            //************************************************
            //TOPICS PAGE n.1
            //************************************************
            if (ACTIVATETOPICSPAGE == 1) {
              displayTopics(ucg, fTopic_C1_Output, fTopic_C2_Output, fTopic_C3_Output);
            }
            break;

          case PAGE_TOPICS2:
            //************************************************
            //TOPICS PAGE n.2
            //************************************************
            if (ACTIVATETOPICSPAGE == 1) {
              displayTopicsPage2(ucg, fTopic_C4_Output, fTopic_C5_Output, fTopic_C6_Output);
            }
            break;
        }
      } else {
        //segnala che la pagina attuale al termine del timeut deve essere aggiornata
        setUIChanged();
      }
    }

    SHIFT_910ms(1) {
      subscribeTopics();
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
      if (getLayout2()) {
        display_layout2_print_circle_white(ucg);
        display_layout2_print_circle_black(ucg);
        display_layout2_HomeScreen(ucg, temperature, humidity, setpoint);
        display_layout2_print_datetime(ucg);
        ucg.setColor(0, 0, 0);       // black
        ucg.drawDisc(156, 50, 5, UCG_DRAW_ALL);
        ucg.drawDisc(165, 62, 6, UCG_DRAW_ALL);
        ucg.drawDisc(173, 77, 7, UCG_DRAW_ALL);
        ucg.drawDisc(179, 95, 8, UCG_DRAW_ALL);
        yield();
        display_layout2_print_circle_green(ucg);
        if (ACTIVATETOPICSPAGE == 1) {
          displayTopicsHomePageLayout2(ucg, fTopic_C1_Output, fTopic_C2_Output, fTopic_C3_Output, fTopic_C4_Output, fTopic_C5_Output, fTopic_C6_Output);
        }
      }
      getTemp();
      if (getCrono()) {
        Serial.println("CRONO: aggiornamento");
        setSetpoint(checkNTPcrono(ucg));
        setEncoderValue(checkNTPcrono(ucg));
        Serial.print("CRONO: setpoint: "); Serial.println(setpoint);
      }
    }


    SLOW_70s() {

      if (getLayout1()) {
        //
      } else if (getLayout2()) {
        calcoloAndamento(ucg, temperature);
        display_layout2_print_datetime(ucg);
        display_layout2_print_circle_green(ucg);
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

  // Look for a new sketch to update over the air
  ArduinoOTA.handle();
  yield();
}


