#include "Arduino.h"
#include "string.h"
#include "SoftwareSerial.h"

SoftwareSerial arduino1(8,7);

void setup()
{
  Serial.begin(115200);
  arduino1.begin(9600);
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
    if(msg.length() > 0) {
      Serial.println(msg);
    }
  }
}