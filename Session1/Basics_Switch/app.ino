#include "Arduino.h"
uint8_t LEDPIN = LED_BUILTIN;
uint8_t SWITCHPIN = D2;

void setup()
{
  pinMode(LEDPIN, OUTPUT);
  pinMode(SWITCHPIN, INPUT);
}

void loop()
{
  bool isOn = digitalRead(SWITCHPIN);

  digitalWrite(LEDPIN, isOn);
  delay(1000);
}