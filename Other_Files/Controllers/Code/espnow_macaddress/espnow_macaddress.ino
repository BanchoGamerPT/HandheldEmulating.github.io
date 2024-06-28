#include <esp_now.h>
#include <WiFi.h>
#include <Arduino.h>

void setup()
{
  delay(1000);
  Serial.begin(115200);
}

void loop()
{
  Serial.println(WiFi.macAddress());
}
