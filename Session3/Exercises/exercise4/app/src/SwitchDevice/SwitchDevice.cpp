#include "SwitchDevice.hpp"
#include "Arduino.h"
#include "ESP8266WiFi.h"
#include "PubSubClient.h"
#include "../Topics/Topics.hpp"

SwitchDevice::SwitchDevice(char* name, int pin){
  _pin = pin;

  pinMode(_pin, INPUT_PULLUP);
  _name = name;

  _baseTopic = "iotworkshop/base";
}

void SwitchDevice::MessageReceived(char* topic, const char* message){
  
}

void SwitchDevice::Loop(void (*postMessage)(const char* , const char*)){
  bool currentState = digitalRead(_pin);
  if (currentState != _lastState && currentState)
  {
    char _topic[100];
    Topics::getDeviceTopicByName(_name,_topic);

    _outputState != _outputState;
    if (_outputState)
    {
      postMessage("ON", _topic);
    }
    else {
      postMessage("OFF", _topic);
    }
    
  }
  _lastState = currentState;
  
}