#include <Arduino.h>

#include "Stock.h"

#define RED_PIN 16
#define GREEN_PIN 0
#define BLUE_PIN 2

void initLED(void) {
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);
}

void setLED(void) {

}
