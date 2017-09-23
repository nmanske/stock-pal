#include <Arduino.h>

#include "Display.h"
#include "LED.h"
#include "WiFi.h"

#define BAUD_RATE 9600

void setup(void) {
    Serial.begin(BAUD_RATE);
    while (!Serial);
    initDisplay();
    initLED();
    initWiFi();
}

void loop(void) {
    String symbol = getStockSymbol();
    String response = getResponse(symbol);
    Stock_Data data = getStockData(symbol, response);
    setDisplay(data);
}
