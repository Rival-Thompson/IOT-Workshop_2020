#include "Arduino.h"
#include "string.h"
#include "SoftwareSerial.h"
#include "src/Button/Button.hpp"
#include "src/LED/LED.hpp"

const int LED_PIN = 2;
const int BUTTON_PIN = 0;

SoftwareSerial serial(13,15);

LED led(LED_PIN, serial);
Button button(BUTTON_PIN, serial);

void setup()
{
  Serial.begin(115200);
  serial.begin(115200);
  Serial.println("booted");
}

void loop()
{
  led.Listen();
  button.Listen();
  delay(250);
}