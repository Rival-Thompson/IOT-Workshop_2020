#include "LED.hpp"
#include "Arduino.h"
#include "Stream.h"

LED::LED(int pin, Stream &serial):_serial(serial){
  _pin = pin;
  _state = false;

  pinMode(_pin, OUTPUT);
}

void LED::Listen(){
  if (_serial.available() > 0){
    String msg = _serial.readString();
    if (msg == ON_STRING)
    {
      digitalWrite(_pin, HIGH);
      Serial.println("LED ON");

    }else if (msg == OFF_STRING)
    {
      digitalWrite(_pin, LOW);
      Serial.println("LED OFF");

    }
  }
}

