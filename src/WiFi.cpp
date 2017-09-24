#include <ESP8266WiFi.h>

#include "WiFi.h"

#define HTTPS_PORT 443

static const char* ssid = "my_ssid";
static const char* password = "my_password";
static const char* host = "www.alphavantage.co";
static const char* fingerprint = "3C B9 DA D3 0E 01 0F 53 EB B0 42 DD 39 73 44 9B 89 BD 1D BE";

static uint8_t status = WL_IDLE_STATUS;

void initWiFi(void) {
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
    Serial.println(" dbm\n\n");
}

String getResponse(String symbol) {
    Serial.print("Connecting to ");
    Serial.println(host);

    WiFiClientSecure client;
    if (!client.connect(host, HTTPS_PORT)) {
        Serial.println("Connection failed");
        return "None";
    }

    if (client.verify(fingerprint, host)) {
        Serial.println("Certificate matches");
    } else {
        Serial.println("Certificate does not match");
    }

    String url = "/query?function=TIME_SERIES_DAILY&symbol=" + symbol + "&apikey=AMM1WB1N7FPD4U8P";
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

    String line, response;
    while(client.available()) {
        line = client.readStringUntil('}');
        if (line.indexOf("(Daily)") > 1) {
            response = line;
            break;
        }
    }

    Serial.println("Response:\n");
    Serial.println(response);
    Serial.println("\nClosing connection...\n");

    return response;
}
