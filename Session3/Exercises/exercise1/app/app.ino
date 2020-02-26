#include "Arduino.h"
#include "ESP8266WiFi.h"
#include "PubSubClient.h"

const char *ssid = "...";
const char *password = "...";

const char *mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;

bool wifiSetupSucceeded = false;

WiFiClient espClient;
PubSubClient _client(espClient);

long lastPosted = 0;
const long DELAY = 5000;
int count = 0;

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
}

void loop()
{
  if (wifiSetupSucceeded)
  {
    if (!_client.connected())
    {
      reconnectToBroker();
    }
    long now = millis();
    if(now - lastPosted >= DELAY || now - lastPosted <= 0)
    {
      lastPosted = now;
      count = count +1;
      char countChar[4];
      String s = String(count);
      s.toCharArray(countChar, 4);
      
      _client.publish("iotworkshop/tst", countChar);

    }
    _client.loop();
  }
}