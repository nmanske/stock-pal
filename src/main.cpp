#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <SPI.h>

String getResponse();

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
        Serial.print("Attempting to connect to SSID: ");
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
    String response = getResponse();
    Serial.println("Response:\n");
    Serial.println(response);
    Serial.println();
}

String getResponse() {
    Serial.print("Connecting to ");
    Serial.println(host);

    WiFiClient client;
    if (!client.connect(host, HTTP_PORT)) {
        Serial.println("Connection failed");
        return "No response";
    }

    String url = "/users";
    String request = String("GET ") + url + " HTTP/1.1\r\n" +
                            "Host: " + host + "\r\n" + 
                            "Connection: close\r\n\r\n";

    Serial.print("Requesting URL: ");
    Serial.println(url);
    Serial.println("Request:");
    Serial.println(request);
    Serial.println();

    client.print(request);

    while(!client.available()) {
        delay(1000);
    }

    String response = "";
    while(client.available()){
        response += client.readStringUntil('\r');
    }

    Serial.println("\nClosing connection...\n");

    return response;
}
