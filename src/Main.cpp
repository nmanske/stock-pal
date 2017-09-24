#include <Arduino.h>
#include <EEPROM.h>

#include "Display.h"
#include "LED.h"
#include "Stock.h"
#include "WiFi.h"

#define BAUD_RATE 9600

static Stock AMD ("AMD");
static Stock AMZN ("AMZN");
static Stock SNAP ("SNAP");
static Stock VTTSX ("VTTSX");

void setup(void) {
    Serial.begin(BAUD_RATE);
    while (!Serial);
    initDisplay();
    initLED();
    initWiFi();
}

void loop(void) {
    AMD.update();
    setDisplay(AMD);
    AMZN.update();
    setDisplay(AMZN);
    SNAP.update();
    setDisplay(SNAP);
    VTTSX.update();
    setDisplay(VTTSX);
}
