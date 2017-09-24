#include <Arduino.h>

#include "Display.h"
#include "LED.h"
#include "Stock.h"
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
    Stock AMD ("AMD");
    Stock AMZN ("AMZN");
    Stock SNAP ("SNAP");
    Stock VTTSX ("VTTSX");
    AMD.update();
    setDisplay(AMD);
    AMZN.update();
    setDisplay(AMZN);
    SNAP.update();
    setDisplay(SNAP);
    VTTSX.update();
    setDisplay(VTTSX);
}
