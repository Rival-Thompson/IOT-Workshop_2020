#include "Arduino.h"
#include "Sensor.hpp"

Sensor::Sensor(int pin){
  _pin = pin;
  pinMode(pin, INPUT);
}

bool Sensor::DigitalRead(){
  return digitalRead(_pin);
}

int Sensor::AnalogRead(){
  return analogRead(_pin);
}