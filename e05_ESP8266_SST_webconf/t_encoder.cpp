//ENCODER
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include "t_constants.h"


int encoder0Pos = 220;
int encoder_PinALast = LOW;
float encoderValue = 18.0;
int n;

float getEncoderValue() {
  return encoderValue;
}

void setEncoderValue(float val) {
  encoder0Pos = val * 10;
}

 int encoder0PinALast = LOW;
void encoder(){
  n = digitalRead(ENCODER_PIN_A);
      if ((encoder0PinALast == LOW) && (n == HIGH)) {  
          if (digitalRead(ENCODER_PIN_B) == LOW) {
            encoder0Pos--;
            analogWrite(BACKLED,1023);  
              } else {
            encoder0Pos++;
            analogWrite(BACKLED,1023);  
              }
            encoderValue=encoder0Pos/10.0;          
              } 
            encoder0PinALast = n; 
             }

