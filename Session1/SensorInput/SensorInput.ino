#include "Arduino.h"
#include "src/Sensor/Sensor.hpp"

Sensor digitalSensor(14);
Sensor analogSensor(A0);

void setup()
{
  Serial.begin(115200)
}

void loop()
{
  Serial.println("Reading sensor values ...");
  Serial.print("  Digital: ");
  Serial.println(digitalSensor.DigitalRead());
  Serial.print("  Analog: ");
  Serial.println(analogSensor.AnalogRead());
  delay(1000);
}