#include "ToggleDevice.hpp"
#include "Arduino.h"
#include "ESP8266WiFi.h"
#include "../Topics/Topics.hpp"

#include "PubSubClient.h"

ToggleDevice::ToggleDevice(char *name, int pin)
{
  _pin = pin;
  _lastPosted = 0;

  pinMode(_pin, OUTPUT);

  _name = name;
  _baseTopic = "iotworkshop/base";
}

void ToggleDevice::MessageReceived(char *topic, const char *message)
{
  char dTopic[100];
  Topics::getDeviceTopicByName(_name, dTopic);
  Serial.print(topic);
  Serial.print("  =  ");
  Serial.println(dTopic);
  Serial.println(String(dTopic).equals(topic));
  if (String(dTopic).equals(topic) == 1)
  {
    if (String("ON").equalsIgnoreCase(message))
    {
      Serial.println("ON");
      digitalWrite(_pin, HIGH);
    }
    else if (String("OFF").equalsIgnoreCase(message))
    {
      Serial.println("OFF");
      digitalWrite(_pin, LOW);
    }
  }
}

void ToggleDevice::Loop(void (*postMessage)(const char *, const char *))
{
  long now = millis();
  if (now - _lastPosted >= 60000 || now - _lastPosted <= 0)
  {
    _lastPosted = now;

    char _topic[100];
    Topics::getDeviceTopicByName(_name, _topic);

    postMessage(_topic, _baseTopic);
  }
}