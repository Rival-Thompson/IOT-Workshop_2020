#include "SwitchDevice.hpp"
#include "Arduino.h"
#include "ESP8266WiFi.h"
#include "PubSubClient.h"
#include "../Topics/Topics.hpp"
#include <ArduinoJson.h>

SwitchDevice::SwitchDevice(char *name, int pin)
{
  _pin = pin;

  pinMode(_pin, INPUT_PULLUP);
  _name = name;

  _baseTopic = "iotworkshop/base";
}

void SwitchDevice::MessageReceived(char *topic, const char *message)
{
}

void SwitchDevice::Loop(void (*postMessage)(const char *, const char *))
{
  bool currentState = digitalRead(_pin);
  if (currentState != _lastState)
  {
    char _topic[100];
    Topics::getDeviceTopicByName(_name, _topic);

    _outputState = !_outputState;
    StaticJsonDocument<JSON_OBJECT_SIZE(4)> doc;
    doc["name"] = _name;
    doc["type"] = "SWITCH";
    doc["power"] = _outputState;

    char output[JSON_OBJECT_SIZE(4)];
    serializeJson(doc, output);
    postMessage(output, _baseTopic);
  }
  _lastState = currentState;
}