# Session 2: Lets communicate #

## Intro ##

To make a fully integrated system you should be able to communicate between different / multiple modules and solutions. Therefore you have a lot of possibilities. This session will focus on serial communication, because this is the most common and easy to set up. We are going to write messages to the console and send instructions from the serial console to the Arduino. In the next session we are going to communicate using the network and possibly the internet.

## First Serial Message ##

As seen in our previous session an Arduino can send messages over a serial bust to the serial monitor in the IDE. This is convenient for debugging and testing reasons. In our first exercise we are going to print several messages to our serial monitor.

Herefor we will need to start the predefined serial connection **'Serial'** with the ```Serial.begin([BAUDRATE]);``` method. The baud rate is a number that indicates at what speed the serial communication happens, this is expressed in bits/second. In theory you can run it at any speed you desire, as long as both sides can handle the speed you set it at. In practice there are several standard speeds you can run at, these are 1200, 2400, 4800, 9600, 19200, 38400, 57600, and 115200. Arduino IDE by default chooses 9600 where as VS Code uses 115200 by default.

To send a message over your serial connection you have several predefined methods on your Serial object to do so.

- print([DATA]) This will send the data as ASCII character(s) to the receiver without adding a new line.
- println([DATA]) This will send the data as ASCII character(s) to the receiver with adding a new line character at the end.
- write([DATA]) Will send the data as bytes to the receiver.

For most of our communication we will use `print` and `println`. These will result in human readable results in the serial monitor of your IDE.

### Exercise 1 ##

I want to see how many times the `loop` function has ran in the console. Every **10th** time the function runs, the counter should be reset and the message `10 loops completed` should be printed.

It is recommended to add a `delay` at the end of your loop function. This makes it easier to follow the message stream in the serial monitor.

``` c++
int count = 0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println(count);

  ...

  count ++;
  delay(250);
}

```

## Receiving our first message ##

In this section we are going to send a message from the serial monitor to the Arduino. To read messages from the serial connection you have multiple options. You can read it byte by byte with `Serial.read()` or into a string with `Serial.readString()`. Before we can read the data in the serial buffer we have to check if there is any. You can do this with `Serial.available()` it tells us how many bytes there are to read. The arduino platform has a serial buffer of 63bytes. So if you exceed this maximum within one read cycle you will loose data.

### Exercise 2 ###

I would like you to toggle the LED with serial commands. When you send **`On`** the LED should turn on. If you send **`Off`** the LED should turn off. The LED is connected to GPIO pin **2**. Don't forget to set the pinMode to *`OUTPUT`*.

For this exercise I recommend using the `Serial.readString()` method.

## Communication between Arduino and Arduino ##

In this section we will need an extra serial connection to communicate with an other Arduino. Therefore we will use a SoftwareSerial connection. This class can make a serial connection across almost all GPIO pins. You create a serial instance by creating an instance of SoftwareSerial `SoftwareSerial serial1(rxPin, txPin);`. For more information follow this [link](https://www.arduino.cc/en/Reference/SoftwareSerialConstructor). The SoftwareSerial class has the same interface as the Serial class, so the API should be familiar.

When connecting 2 Arduino's together make sure to connect the tx port from Arduino 1 to the rx port of Arduino 2 and vice versa. Also make sure to connect the ground of both Arduino's.

### Exercise 3 ###

For this exercise I want you to connect your Arduino to the Arduino of another group. When sending a message using the serial monitor it should appear on the serial monitor connected to the other Arduino.

PC 1 => ARDUINO 1 => Arduino 2 => PC 2
PC 1 <= ARDUINO 1 <= Arduino 2 <= PC 2

### Exercise 4 ###

For this exercise I want one team to control the LED of another team. So when team 1 presses the switch, the LED of team 2 should turn on and off. You should discuss a standard in which the both of you will communicate. The base of this exercise will be used in the following exercise.

Switch => Arduino 1 => Arduino 2 => LED
Switch => Arduino 2 => Arduino 1 => LED

## Libraries and code splitting ##

In this section we are going to learn and practice how to make modules / libraries that contain a part of your functionality. For splitting code you can resort to putting functionality in classes located in different files. These files are called libraries and they should follow a specific folder structure for the Arduino IDE to recognize them. They should reside in a **`src`** folder then a folder with the same name as the library and then the header and code files. Example: for a LED library you should have the following structure:

``` text
- app.ino
- src
  - LED
    - LED.cpp
    - LED.hpp
```

### The header file *(.hpp)* ###

The header file describes what the code file will contain from public and private api. It is not necessary to define everything in the header file, but it is recommended. When defining a library you should always check if it was not already included herefor you have the `#ifndef`, `#define`, `#endif` lines. This tells the compiler to include the files if they have not been included yet.

Example:

``` c++
#ifndef LED_H
#define LED_H

...
#endif
```

In the header file you describe which functions your class should have. For example: I want a class to represent a LED.
It should have a constructor so I can pass which pin to use, an On method to turn on the LED, an Off method to turn the LED off and a private variable to keep the pinNumber.

This would result in the following header file.

``` c++
#ifndef LED_H
#define LED_H

#include "Arduino.h"

class LED
{
    public:
        LED(int outputPin);   // constructor
        void On();            // On method to turn on the LED
        void Off();           // Off method to turn off the LED

    private:
        int _outputPin;       // private variable for pinNumber
};

#endif
```

### The code file *(.cpp)* ###

The code file contains all the implementation and logic. You should always include the header file into your code file. For class methods they should always be prefixed with the class name like `LED:: On()...`.

If we take the example from before it would result in something like this.

``` c++
#include <Arduino.h> // Inclusion of other used libraries
#include "LED.hpp" //Inclusion of the header file

LED::LED(int pin) // constructor
{
    pinMode(pin, OUTPUT);
    _outputPin = pin; // Setting the private variable defined in the header file
}

void LED::On(){  // The On method
  digitalWrite(_outputPin, HIGH);
}

void LED::Off(){ // The Off method
  digitalWrite(_outputPin, LOW);
}
```

### Using a custom library ###

When you want to use your newly written library, you should include it in another library or in your main *`.ino`* file. To include it you use `#include "..."`. For example with the LED example it would be the following `#include "src/LED/LED.hpp"`.

And you would use it like:

``` c++
#include<Arduino.h>
#include "src/LED/LED.hpp"

LED led1(2); // Constructing a LED instance

void setup(){

}

void loop(){
  led1.On(); // Calling the 'On' method on your instance
  delay(500);
  led1.Off(); // Calling the 'Off' method on your instance
  delay(500);
}
```

### Exercise 5 ###

Now that we have learned how to make libraries and split our code, I would like to return to the solution of *exercise 5* and rewrite it. The result I would like to see is a Button and an LED class.

The **Button** class should contain the following functionality.

- A constructor to define which pin to use and pass a instance of SoftwareSerial
- A private variable to store the pinNumber
- A private variable to store the SoftwareSerial instance
- A private variable to store the previous state of the button
- A public Listen method that posts a message on the serial when the button state changes.
  - Listen for changes
  - Post message on Serial line
  
The **LED** class should contain the following functionality.

- A constructor to define which pin to use and pass an instance of SoftwareSerial
- A private variable to store the pinNumber
- A private variable to store the SoftwareSerial instance
- A public variable to store the previous state of the button
- A public Listen method that listens for messages on the serial line and updates the led accordingly
  - Listen for serial message
  - Update LED state

The result should be the same as in the previous exercise.

## Extras ##

If you are ready with the exercises and feel like preparing a bit for the next session you can already read and thinker with the following libraries.

- [ESP8266WiFi](https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html)
- [Pub Sub Client](https://github.com/knolleary/pubsubclient/blob/master/examples/mqtt_esp8266/mqtt_esp8266.ino)
- [Arduino JSON](https://arduinojson.org)

## Useful links ##

[Documentation about serial communication](https://learn.sparkfun.com/tutorials/serial-communication/all)

## Thank word ##

Thank you following my second session from the IOT-Workshop: First steps to home automation. I hope you had a great time and learned how to use serial communication to integrate multiple Arduino's into one solution. in the next session we will connect our ESP8266 to the network.

I hope to see you guys within two weeks!

***Rival Thompson***
