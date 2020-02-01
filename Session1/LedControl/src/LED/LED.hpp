#ifndef LED_H
#define LED_H

#include "Arduino.h"

class LED
{
    public:
        LED(int outputPin);
        void On();
        void Off();
        void PWM(int val);
    
    private:
        int _outputPin;

};

#endif