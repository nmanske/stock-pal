#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <SPI.h>

void printJSON();

#define BAUD_RATE 115200
#define HTTP_PORT 80

static const char ssid[] = "my_ssid";
static const char password[] = "my_password";
static const char host[] = "jsonplaceholder.typicode.com";

static int status = WL_IDLE_STATUS;

void setup() {
    Serial.begin(BAUD_RATE);
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

    Serial.println("\nWiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Signal strength: ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dbm\n");
}

void loop() {
    delay(10000);
    printJSON();
}

void printJSON() {
    Serial.print("Connecting to ");
    Serial.println(host);

    WiFiClient client;
    if (!client.connect(host, HTTP_PORT)) {
        Serial.println("Connection failed");
        return;
    }

    String url = "/posts";
    Serial.print("Requesting URL: ");
    Serial.print(url);

    client.print(String("GET") + url +
                 " HTTP/1.1\r\n");
    delay(10);

    Serial.println("Response:");
    while(client.available()){
        String line = client.readStringUntil('\r');
        Serial.print(line);
    }

    Serial.println("\nClosing connection...\n");
}