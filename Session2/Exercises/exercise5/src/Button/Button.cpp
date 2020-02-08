#include "Button.hpp"
#include "Arduino.h"
#include "Stream.h"

Button::Button(int pin, Stream &serial):_serial(serial){
  _pin = pin;
  _state = false;

  pinMode(_pin, INPUT_PULLUP);
}

void Button::Listen(){
  bool buttonValue = digitalRead(_pin);

  if(_state != buttonValue){
    if (buttonValue)
    {
      _serial.print(ON_STRING);
      Serial.println(ON_STRING);
    }else {
      _serial.print(OFF_STRING);
      Serial.println(OFF_STRING);
    }
    _state = buttonValue;
  }
}

