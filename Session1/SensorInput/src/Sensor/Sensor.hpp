#ifndef Sensor_H
#define Sensor_H

#include "Arduino.h"

class Sensor
{
    public:
        Sensor(int pin);
        int AnalogRead();
        bool DigitalRead();
    
    private:
        int _pin;

};

#endif