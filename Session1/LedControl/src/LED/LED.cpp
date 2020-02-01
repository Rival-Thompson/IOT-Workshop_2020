#include <Arduino.h>
#include "LED.hpp"

LED::LED(int pin)
{
    pinMode(pin, OUTPUT);
    _outputPin = pin;
}

void LED::On(){
  digitalWrite(_outputPin, HIGH);
}

void LED::Off(){
  digitalWrite(_outputPin, LOW);
}

void LED::PWM(int val){
  analogWrite(_outputPin, val);
}