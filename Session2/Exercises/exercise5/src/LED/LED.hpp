#ifndef LED_H
#define LED_H

#include "Arduino.h"
#include "Stream.h"

    #ifndef OnOFStrings
    #define OnOFStrings
    static const String OFF_STRING = "Off";
    static const String ON_STRING = "On";
    #endif

class LED
{
    public:
        LED(int pin, Stream &serial);
        void Listen();
    
    private:
        int _pin;
        bool _state;
        Stream &_serial;

};

#endif