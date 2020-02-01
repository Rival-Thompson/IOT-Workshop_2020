#include "Arduino.h"
#include "src/LED/LED.hpp"
#include "src/Sensor/Sensor.hpp"

Sensor _analogSensor(A0);
Sensor _digitalSensor(D1);
LED _led1(D2);
LED _led2(D3);

void setup()
{
  
}

void loop()
{
  bool led1Active = _digitalSensor.DigitalRead();
  int led2PWMValue = _analogSensor.AnalogRead();

  if (led1Active)
  {
    _led1.On();
  }
  else
  {
    _led1.Off();
  }

  _led2.PWM(led2PWMValue);

  delay(1000);

}