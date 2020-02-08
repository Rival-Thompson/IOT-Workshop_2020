#include "Arduino.h"
#include "string.h"
#include "SoftwareSerial.h"

const int LED_PIN = 2;
const String OFF_STRING = "Off";
const String ON_STRING = "On";

SoftwareSerial arduino1(8,7);

void setup()
{
  Serial.begin(115200);
  arduino1.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  if (Serial.available() > 0){
    String input = Serial.readString();
    if(input.length() > 0){
      arduino1.print(input);
    }
  }

  if (arduino1.available() > 0){
    String msg = arduino1.readString();
    if (msg == ON_STRING)
    {
      digitalWrite(LED_PIN, HIGH);
    }else if (msg == OFF_STRING)
    {
      digitalWrite(LED_PIN, LOW);
    }
  }
}