//ENCODER
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include "constants.h"


int encoder0Pos = 220;
int encoder_PinALast = LOW;
float encoderValue = 20.0;
int n;

float getEncoderValue() {
  //Serial.print("encoderValue: ");Serial.println(encoderValue);
  return encoderValue;
}

void setEncoderValue(float val) {
  encoder0Pos = val * 10;
  //encoderValue = encoder0Pos / 10.0;
  //Serial.print("encoder0Pos+encoderValue: ");Serial.print(encoder0Pos);Serial.print(" + ");Serial.println(encoderValue);
}

int encoder0PinALast = LOW;

void encoder() {
  int MSB = digitalRead(ENCODER_PIN_B); //MSB = most significant bit
  int LSB = digitalRead(ENCODER_PIN_A); //LSB = least significant bit

  int encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
  int sum  = (encoder0PinALast << 2) | encoded; //adding it to the previous encoded value

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoder0Pos ++;
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoder0Pos --;

  encoder0PinALast = encoded; //store this value for next time
  encoderValue = encoder0Pos / 10.0;
}

