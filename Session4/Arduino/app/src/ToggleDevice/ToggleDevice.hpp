
#ifndef ToggleDevice_H
#define ToggleDevice_H

#include "Arduino.h"
#include "ESP8266WiFi.h"
#include <ArduinoJson.h>


class ToggleDevice
{
    public:
        ToggleDevice(char* name, int pin);
        void Loop(void (*postMessage)(const char* , const char*));
        void MessageReceived(char* topic, const char* message);
        char* _name;

    protected:
        const char* _baseTopic;

    private:
        bool _state;
        long _lastPosted;
        int _pin;
};

#endif