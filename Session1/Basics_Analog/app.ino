#include "Arduino.h"
uint8_t LEDPIN = LED_BUILTIN;
uint8_t SENSORPIN = D2;

void setup()
{
  pinMode(LEDPIN, OUTPUT);
  pinMode(SENSORPIN, INPUT);
}

void loop()
{
  int value = analogRead(SENSORPIN);
  analogWrite(LEDPIN, value);
  delay(100);
}