#include <Arduino.h>
#include "constants.h"
#include "language.h"
#include "ntp.h"

#include "Ucglib.h"




void display_layout1_background_black(Ucglib_ILI9341_18x240x320_HWSPI ucg){
  ucg.setColor(1, 0, 0, 0); // BLACK for the background
}






