# Session 3: Let's make a network #

## Intro ##

Now that we know how to make a hardware solution that can communicate. In this session we are going to take this to the next level. Using a direct connection between two devices is a good beginning, but when you want to make a fully automated system you will need more than two devices. There for we are going to connect multiple devices in a network using Wi-Fi. We are going to let them communicate using a message bus. Here for we are going to use MQTT. This is one of the most used message bus systems in IOT. Now lets get started and connect our ESP-8266 / Node MCU to a Wi-Fi network.

## Connecting to Wi-Fi ##

To connect our ESP-8266 to a Wi-Fi network we are going to use the `ESP8266WiFi` library. First we are going to fill in the ssid and the password we are going to do this using the begin method of the WiFi class `WiFi.begin([SSID],[PASSWORD]);`. Next we are going to have to wait until the connection has completed. here for we are going to use status method `WiFi.status()` this returns on of the following values.

- `WL_CONNECTED` after successful connection is established
- `WL_NO_SSID_AVAIL` in case configured SSID cannot be reached
- `WL_CONNECT_FAILED` if password is incorrect
- `WL_IDLE_STATUS` when Wi-Fi is in process of changing between statuses
- `WL_DISCONNECTED` if module is not configured in station mode

We are going to wait until the connection is established or end when the connection failed. 

``` C++
bool setupDone = false;
Serial.print("Connecting");
while(!setupDone){
  wl_status_t status = Wifi.status();
  if(status == WL_CONNECTED){
    setupDone = true;
  } else if(status == WL_CONNECT_FAILED ) {
    Serial.println();
    Serial.println("Failed to connect to the wi-fi network");
  }else if(status == WL_NO_SSID_AVAIL ) {
    Serial.println();
    Serial.println("Couldn't find the SSID you provided");
  } else {
    Serial.print(".");
    delay(500);
  }
}
```

Now that we are connected to our network we can make a client and start using MQTT. But first lets print our local IP address. To do this you can print the output of `WiFi.localIP()`.

## Entering the bus *Whoot Whoot* ##

So now lets connect our device to a mqtt broker. To do this we will have to include the `PubSubClient` library. When that is included you can make a new instance of PubSubClient and pass it the WiFiClient.

``` C++
WiFiClient espClient;
PubSubClient client(espClient);
```

After creating the instance we set the broker address and port. We can do this with the `client.setServer([SERVERADDRESS],[PORT])` method.

Now lets establish a connection to the MQTT-broker. In the loop we must check that a connection is establish otherwise we have to reconnect to the broker. To check if a connection is established we use the `client.connected()` method, this returns a boolean. To connect / reconnect we use the `client.connect([CLIENTID])` method, which returns a boolean to indicate te connection was successfully established.

``` c++

void reconnect(){
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop(){
  if(client.connected()){
    reconnect();
  }

  ...
}

```

## Publishing our first messages on the bus ##

Now that we have established a connection to our broker we post our first message on a topic. To post a message on a topic you use the `client.publish([TOPIC],[PAYLOAD])` method.

### Exercise 1: Publishing our first message ###

For this exercise I want you to post your first message on the bus. I want you to post a count to a topic every 5 seconds.

To minimize the delays in your code you can use the `millis()` function this gives you a time stamp in milliseconds since the start of the program.

``` C++
long lastPosted = 0;
const long DELAY = 5000;
void loop(){
  connection logic ...

  long now = millis();
  if(now - lastPosted >= DELAY || now - lastPosted <= 0){
    lastPosted = now;

    post a message ...
  }

}
```

There are multiple tools to post and receive messages on. You can use the chrome extension *MQTT Lens* or the desktop *MQTTfx*. Those two I've used in the past. Feel free to find or write your own client *(not during the workshop)* if you prefer.

## Receiving our first message ##

Now that we can publish messages it is time to receive some posts. we do this by subscribing to atopic and when a message is pushed for one of your topics the callback function is fired.

### Registering the callback function ###

You can register the callback function with the `client.setCallback([FUNCTION])` method. The callback should have the following signature. `void callback(const char* TOPIC, const byte* PAYLOAD, unsigned int LENGTH)` To convert the payload from byte* to a string you can interpret and compare against you can use the `reinterpret_cast<const char*>(payload)` method.

Example:

``` C++
void setup (){
  ...
  client.setCallback(callback)
  ...
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  const char * data = reinterpret_cast<const char*>(payload);
  Serial.print(data);
  Serial.println();
}
```

### Exercise 2: Receiving messages ###

For this exercise I want you to subscribe to the topic of your neighbor and print the messages you receive to the SerialMonitor.
So you can continue from the previous exercise and extend it with the new things you learned above.

### Exercise 3: LED's and Buttons ###

Now that we've send and received basic messages it is time to create a *'protocol'* with your neighbor. In which you both send each other the state of a button and make each other LED turn on and off.

### Exercise 4: Libraries ###

This exercise we are going to extend what we build last exercise but split it in to multiple classes for reusability. I want you to make a Button and ToggleDevice *(something that can be turned on and off)* class which have the following common public api:

``` C++
public:
    CONSTRUCTOR(char* name, int pin);
    void Loop(void (*postMessage)(const char* , const char*)); // to place in the loop function of app.ino
    void MessageReceived(char* topic, const char* message); // to place in the mqtt callback function
    char* _name;
```

The `void (*postMessage)(const char* , const char*)` variable is like a callback function. This makes it possible to pass a method and call it in an other method.

You can use the following class to generate topics for the MQTT messages.

#### Topics.hpp ###

``` C++
#ifndef Topic_H
#define Topic_H

#include "Arduino.h"

class Topics
{
    public:
        static char* deviceTopicBase;
        static char* topicBase;
        static void getDeviceTopicByName(char * name, char * output);
};

#endif
```

#### Topics.cpp ###

``` C++
#include "Topics.hpp"

void Topics::getDeviceTopicByName(char *name, char *output)
{
  strcpy(output, deviceTopicBase);
  strcat(output, name);
}

char *Topics::deviceTopicBase = "workshopiot/device/";
char *Topics::topicBase = "workshopiot/base";
```

To use it you include the `.hpp` file and than use the following snippet to create the topic in the `dTopic` character array.

``` C++
char dTopic[100];
Topics::getDeviceTopicByName(_name, dTopic);
```

These things should get you started in enhancing your result of exercise 3 to make it scalable without having to (re)write 100 lines of code. **This is one of the most difficult exercises don't be scared to ask for help! It took me more than *8 hours* to figure everything out**

## Extra links ##

- [ESP8266WiFi documentation](https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html#quick-start)
- [PubSubClient API](https://pubsubclient.knolleary.net/api.html)
- [Arduino String()](https://www.arduino.cc/reference/en/language/variables/data-types/stringobject/)
- [ArduinoJSON](https://arduinojson.org)
- [Download MQTTFX](http://www.jensd.de/apps/mqttfx/1.7.1/)

## Thank word ##

Thank you for following my third session from the IOT-Workshop: First steps to home automation. I hope you had a great time and learned how to use the ESP8266's capability to connect to WiFi and how message bus systems like MQTT make it rather easy to make a larger system.

Next session we are going to use our own preferred languages to automate the modules that we created today. So yes you can say goodbye to c++ if you want 😉.

I hope to see you guys within two weeks!

***Rival Thompson***
