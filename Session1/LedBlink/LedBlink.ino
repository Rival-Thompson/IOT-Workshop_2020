#include<Arduino.h>
#include "src/LED/LED.hpp"

LED led1(0);

void setup(){

}

void loop(){
  led1.On();
  delay(500);
  led1.Off();
  delay(500);
}