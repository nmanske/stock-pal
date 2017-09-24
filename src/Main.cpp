#include <Arduino.h>
#include <EEPROM.h>

#include "Display.h"
#include "LED.h"
#include "Stock.h"
#include "WiFi.h"

#define BAUD_RATE 9600

static String stock_list[3] = {"AMD", "AMZN", "SNAP"};

void setup(void) {
    Serial.begin(BAUD_RATE);
    while (!Serial);
    initDisplay();
    initLED();
    initWiFi();
}

void loop(void) {
    for(int i = 0; i < 3; i++) {
        Stock stock = stock_list[i];
        String data = getStockData(stock.getSymbol());
        stock.update(data);
        setLED(stock.getTrend());
        setDisplay(stock);
    }
}
