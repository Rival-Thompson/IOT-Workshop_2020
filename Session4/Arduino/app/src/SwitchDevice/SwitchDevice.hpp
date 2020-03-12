
#ifndef SwitchDevice_H
#define SwitchDevice_H

#include "Arduino.h"
#include "ESP8266WiFi.h"
#include "PubSubClient.h"
#include <ArduinoJson.h>

class SwitchDevice
{
    public:
        SwitchDevice(char* name, int pin);
        void Loop(void (*postMessage)(const char* , const char*));
        void MessageReceived(char* topic, const char* message);
        char* _name;

    protected:
        const char* _baseTopic;
    
    private:
        int _pin;
        bool _lastState;
        bool _outputState;
};

#endif