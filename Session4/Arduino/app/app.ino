#include "Arduino.h"
#include "ESP8266WiFi.h"
#include "./src/Topics/Topics.hpp"
#include "./src/SwitchDevice/SwitchDevice.hpp"
#include "./src/ToggleDevice/ToggleDevice.hpp"

const char* ssid = "Guest Axxes - AT Recruitment";
const char* password = "....";

const char* mqtt_server = "mqtt.robkenis.com";
const int mqtt_port = 1883;

bool wifiSetupSucceeded = false;

// SwitchDevice switch1("switch", 14);
ToggleDevice lamp1("CORLED_1", 16);
ToggleDevice lamp2("CORLED_2", 05);
ToggleDevice lamp3("CORLED_3", 04);
ToggleDevice lamp4("CORLED_4", 00);

WiFiClient espClient;
PubSubClient _client(espClient);

void setup_wifi()
{

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  bool setupDone = false;
  Serial.print("Connecting");
  while (!setupDone)
  {
    wl_status_t status = WiFi.status();
    switch (status)
    {
    case WL_CONNECTED:
      setupDone = true;
      wifiSetupSucceeded = true;
      Serial.println("");
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
      break;
    case WL_CONNECT_FAILED:
      setupDone = true;
      Serial.println();
      Serial.println("Failed to connect to the wi-fi network");
      break;
    case WL_NO_SSID_AVAIL:
      setupDone = true;
      Serial.println();
      Serial.println("Couldn't find the SSID you provided");
      break;
    default:
      Serial.print(".");
      delay(500);
      break;
    }
  }
}

void subscribeByName(char *name)
{
  char buf[100];
  Topics::getDeviceTopicByName(name, buf);
  Serial.println(buf);
  _client.subscribe(buf);
}

void subscribe()
{
  Serial.println("subscribing to topics:");
  // subscribeByName(switch1._name);
  subscribeByName(lamp1._name);
  subscribeByName(lamp2._name);
  subscribeByName(lamp3._name);
  subscribeByName(lamp4._name);
}

void postMessage(const char *message, const char *topic)
{
  _client.publish(topic, message);
}

void deviceLoop()
{
  // switch1.Loop(postMessage);
  lamp1.Loop(postMessage);
  lamp2.Loop(postMessage);
  lamp3.Loop(postMessage);
  lamp4.Loop(postMessage);
}

void callback(char *topic, byte *payload, unsigned int length)
{

  String data = String((char *)payload);

  char tst[length + 1];
 data.toCharArray(tst, length + 1);

  Serial.print("Message arrived [");
  Serial.print((topic));
  Serial.print("] ");
  Serial.println(tst);

  // switch1.MessageReceived(topic,tst);
    lamp1.MessageReceived(topic,tst);
    lamp2.MessageReceived(topic,tst);
    lamp3.MessageReceived(topic,tst);
    lamp4.MessageReceived(topic,tst);
}

void reconnectToBroker()
{
  while (!_client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    // Attempt to connect
    if (WiFi.status() == WL_CONNECTED)
    {
      if (_client.connect("module-ESP"))
      {
        Serial.println("connected");

        subscribe();
      }
      else
      {
        Serial.print("failed, rc=");
        Serial.print(_client.state());
        Serial.println(" try again in 5 seconds");
        // Wait 5 seconds before retrying
        delay(5000);
      }
    }
  }
}

void setup()
{
  Serial.begin(115200);
  setup_wifi();

  _client.setServer(mqtt_server, mqtt_port);
  _client.setCallback(callback);
}

void loop()
{
  if (wifiSetupSucceeded)
  {
    if (!_client.connected())
    {
      reconnectToBroker();
    }

    _client.loop();
    deviceLoop();
  }
}