#include <Arduino.h>
#include <string.h>

const int LED_PIN = 2;
const String OFF_STRING = "Off";
const String ON_STRING = "On";

void setup()
{
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
}

void loop()
{

  if (Serial.available() > 0)
  {
    String input = Serial.readString();

    if (input == ON_STRING)
    {
      digitalWrite(LED_PIN, HIGH);
    }else if (input == OFF_STRING)
    {
      digitalWrite(LED_PIN, LOW);
    }
  }
}