#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <SPI.h>

static const char ssid[] = "my_ssid";
static const char password[] = "my_password";
static const char host[] = "https://jsonplaceholder.typicode.com";

static int status = WL_IDLE_STATUS;

void setup() {
    Serial.begin(115200);
    while (!Serial);

    if (WiFi.status() == WL_NO_SHIELD) {
      Serial.println("WiFi shield not present");
      while (true);
    }

    while (WiFi.status() != WL_CONNECTED) {
        Serial.println("Attempting to connect to SSID:");
        Serial.println(ssid);
        status = WiFi.begin(ssid, password);
        delay(10000);
    }

    Serial.println("You're connected to the network");
}

void loop() {
    delay(10000);
    Serial.println(WiFi.status());
}
